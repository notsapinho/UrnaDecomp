# uenux2 api::CIniSection (api/io/cinisection.cpp, the file the record of its operator= names): SetKey, target fn 5482.
#
# Evidence: 5482 looks a CIniKey's name up in a std::map<std::string, CIniKey> at +12 of its object; when the name is
# there it assigns the key through CIniKey::operator= (5483, unit 01), otherwise it builds a pair of the name and a copy
# of the key and inserts it with the map's end node as the hint (the hinted __find_equal, 1346, after the pair is
# built). Its two target call sites are in 5480, the INI loader that holds CIniStrings::ParseKeyLine's records
# (cinistrings.cpp 183, 187) and CIniSection::operator='s (cinisection.cpp 36): one passes a section held in a map
# node (+28), the other runs over another section's keys, which reads as operator= copying them. In the uses-2 band
# 5482 links right after 5483 (cinikey.cpp), which reads as cinisection.cpp's object, next in name order.
#
# Written and not matched: at the tree's flags SetKey scores 19 over 242 rows (pnpm wasm score, the whole link; 4
# inserted, 1 deleted): ours reloads the inserted node's pointer (*__child) after __insert_node_at's begin-node store
# and the target does not (3 rows), the split unit 113 measured for 5377 to 5379 and 5725, and one argument comes from
# the other local. With -fstrict-aliasing added to this object alone (a scratch link) it scores 8 over 238, every row a
# call or data operand. The row waits for uenux2's
# src/api objects with strict aliasing, a flag decision (docs/reference/facts/app-flags.md F6); this unit adds no flag.
#
# Evidence for the forms (the whole link, pnpm wasm score at the tree's flags):
# - CIniKey's copy and move constructors, declared in api/io/cinikey.h: the target moves the pair's three strings into
#   the node (each source zeroed after its copy). Without them CIniKey's user-declared copy assignment leaves it no move
#   constructor: the CIniKey is copied into the node, the hinted emplace comes with a frame of its own (a second
#   prologue in SetKey), and SetKey scores 128 over 301.
# - The hint is end(), which the target passes from the compare's own end(): the find's result as the hint (it equals
#   end() there) scores 21 over 242, the extra row the hint argument.
#
# Chosen: the name SetKey and the class head in api/io/cinisection.h (the 12 bytes before the map as the section's
# name, the member names, the header's path); the constructors' `= default`; SetKey's line (40), below operator='s
# record line 36, which stays blank. std::make_pair, a pair of the map's value_type and emplace_hint(end(), name, key)
# give the same object (wasm-objdump -d of the object, local and relocation numbers masked). cinikey.cpp's object
# defines the same functions with the same code before and after the constructors (the same comparison).
#
# SetKey's calls of the map's find and hinted __find_equal score as the target's 163 and 1346, the bodies matched as the
# std::map<std::string, unsigned short> instances, and step 9 renamed no match line.
#
# Roots: 175-uenux2-cinisection-roots.cpp stands in for 5480, which is not written.
CINISECTION_SRCS := src/api/io/cinisection.cpp
UENUX2_SRCS += $(CINISECTION_SRCS)

$(ROOT)/$(APP)/175-uenux2-cinisection-roots.o: $(ROOT)/src/units/175-uenux2-cinisection-roots.cpp $(ROOT)/src/Makefile \
    $(ROOT)/src/units/175-uenux2-cinisection.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/175-uenux2-cinisection-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/175-uenux2-cinisection-roots.o
