# ASN.1 runtime fork (src/asn1): compiled with its own flags — -Os -fexceptions -fignore-exceptions -std=c++17
# (docs/reference/facts/asn1.md §A1, §A2): no landing pads, since no asn1 function calls an invoke_* import, and
# libc++'s exceptions-on ABI tag, since the runtime calls the `ne` inline copies the program shares (194, 158, 938),
# which a -fno-exceptions object cannot name. Plain -Os gives the same objects: this spelling is a choice.
# Nothing in the skeleton calls the runtime yet, so a
# generated roots TU (tools/round/gen_try_roots.py, address-taken functions) keeps the objects linked.
# src/Makefile reads this file after the unit fragments: the runtime's objects follow theirs in EXTRA_OBJS.
# EXTRA_OBJS from a `make EXTRA_OBJS=…` command line (try-tu.sh) overrides these additions.

# The generated ASN.1 modules (src/asn1/modules/*.cxx): their theInfo/nameList/fieldInfos records are the DATA every
# converter that builds an entity references (Turno::theInfo, ...). Compiled with the runtime's flags plus the modules'
# include dir; the converters' fragment (src/units/04-ecourna-app-dados-asn.mk) puts them in the link, where the
# records nothing references are garbage-collected.
ASN1MOD_DIR  := $(APP)/asn1/modules
ASN1MOD_SRCS := $(sort $(notdir $(wildcard $(ROOT)/src/asn1/modules/*.cxx)))
ASN1MOD_OBJS := $(addprefix $(ROOT)/$(ASN1MOD_DIR)/,$(ASN1MOD_SRCS:.cxx=.o))
# This rule comes before the runtime's: make 3.81 takes the first pattern that applies, and the runtime's
# $(ASN1_DIR)/%.o matches modules/<name>.o too.
$(ROOT)/$(ASN1MOD_DIR)/%.o: $(ROOT)/src/asn1/modules/%.cxx $(wildcard $(ROOT)/src/asn1/modules/*.h $(ROOT)/src/asn1/*.h) $(ROOT)/src/mk/asn1.mk
	$(H) mkdir -p $(ASN1MOD_DIR) && build/docker-build.sh em++ $(ASN1_CXXFLAGS) -Isrc/asn1/modules -c src/asn1/modules/$*.cxx -o $(R)

ASN1_DIR      := $(APP)/asn1
ASN1_CXXFLAGS := -Os -fexceptions -fignore-exceptions -std=c++17 -DNDEBUG -Isrc/asn1
ASN1_SRCS     := $(sort $(notdir $(wildcard $(ROOT)/src/asn1/*.cxx)))
ASN1_OBJS     := $(addprefix $(ROOT)/$(ASN1_DIR)/,$(ASN1_SRCS:.cxx=.o))

$(ROOT)/$(ASN1_DIR)/%.o: $(ROOT)/src/asn1/%.cxx $(wildcard $(ROOT)/src/asn1/*.h) $(ROOT)/src/mk/asn1.mk
	$(H) mkdir -p $(ASN1_DIR) && build/docker-build.sh em++ $(ASN1_CXXFLAGS) -c src/asn1/$*.cxx -o $(ASN1_DIR)/$*.o

$(ROOT)/$(ASN1_DIR)/roots_asn1.cpp: $(ASN1_OBJS) $(ROOT)/tools/round/gen_try_roots.py
	$(H) python3 -I tools/round/gen_try_roots.py --exclude=_ZN4ASN16CHOICEC $(ASN1_DIR)/roots_asn1.cpp $(patsubst $(ROOT)/%,%,$(ASN1_OBJS))
$(ROOT)/$(ASN1_DIR)/roots_asn1.o: $(ROOT)/$(ASN1_DIR)/roots_asn1.cpp $(ROOT)/src/Makefile
	$(H) build/docker-build.sh em++ $(APP_CXXFLAGS) -c $(ASN1_DIR)/roots_asn1.cpp -o $(ASN1_DIR)/roots_asn1.o

# The runtime's calls of both vector<unsigned>::push_back overloads reach RHVoice's -O3 body in the target (938), and
# its bands put RHVoice before the runtime (docs/reference/facts/link-order.md §L3). Only the two objects that define
# them move, to here: the set and the place are measured, not recovered (docs/reference/facts/asn1.md §A2).
RHVOICE_BEFORE_ASN1 := $(filter %/document.cpp.o %/language.cpp.o,$(RHVOICE_OBJS))
override EXTRA_OBJS += $(RHVOICE_BEFORE_ASN1) $(ASN1_OBJS) $(ROOT)/$(ASN1_DIR)/roots_asn1.o
