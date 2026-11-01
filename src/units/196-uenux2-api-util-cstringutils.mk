# uenux2's api::CStringUtils, in src/uenux2/src/api/util/cstringutils.cpp, the file its records name; its header,
# api/util/cstringutils.h, is a chosen path (no record names one). Target functions:
#   matched    1539 GetVersionNumber (record line 59): the start of a version string that matches
#              "^[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+", through ecourna's CStringUtils::FindRegex (2199, unit 00, written and
#              `unresolved`, whose name 654's and this function's calls give); when the match does not start at 0, or
#              there is none, it throws CUeUtilError 7025 with the message at 231188 (ledger/strings.tsv), formatted with
#              the string. The expression is a named local: the target frees its string after the substr.
#   not written SetBit, the records at lines 71 and 83: only functions that hold it inlined load them (2772, the second),
#              so their lines stay blank, and the header declares the two overloads as the records print them.
# Chosen: the parameter's and the locals' names; 7025's local constant in the .cpp, as
# app/comum/dados/asn/processoeleitoral/cconversortipoidentificadoreleitor.cpp names a code the shared header lacks
# (api/util/eueutilerror.h has no enumerator for it; the constant goes when it gains one); GetVersionNumber's line within
# what its record leaves free. Its six target callers, 5579, 5596, 5604, 11908, 12105 and 12110, are not in our link:
# 196-uenux2-api-util-cstringutils-roots.cpp stands for them.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CSTRINGUTILS_UENUX2_SRCS := src/api/util/cstringutils.cpp
UENUX2_SRCS += $(CSTRINGUTILS_UENUX2_SRCS)
# nothing in the skeleton calls GetVersionNumber: 196-uenux2-api-util-cstringutils-roots.cpp stands for its callers,
# through an asm label, so its rule needs no header
$(ROOT)/$(APP)/196-uenux2-api-util-cstringutils-roots.o: $(ROOT)/src/units/196-uenux2-api-util-cstringutils-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/196-uenux2-api-util-cstringutils.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/196-uenux2-api-util-cstringutils-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/196-uenux2-api-util-cstringutils-roots.o
