# uenux2 api::CEncryptedFile (api/io/cencryptedfile.cpp, the file its records name): Save, target fn 2767, the member at
# record line 88, which holds ecourna's CFile::Flush inlined by binaryen (record cfile.cpp:145). With it, the copy of
# std::vector<uebyte>'s range insert that this object instantiates, 1927, matches, and CFile::Close (336, fragment 03)
# matches because Save is the second voter for the name of CFile::Sync, which both call.
#
# Evidence for the forms (whole link, pnpm wasm score against the target before steps 7 to 9):
# - Save calls CFile's constructor (517) and does not inline it: the constructor is out of line in cfile.cpp (fragment
#   03). Inline in cfile.hpp, clang inlined it into Save (27 rows inserted).
# - The padding loop's counter is an int: a uebyte counter is masked (`i32.const 255; i32.and; i32.gt_u` where the target
#   compares with `i32.ne`).
# - The target throws vector's length error (158) for a negative total before the insert, which is reserve's check, so
#   the content is reserved, inserted, then padded with push_back.
# - 1927 is in the target's table (slot 6666), which keeps its result; the roots file takes its address. Called only, it
#   lost its result to binaryen, and Save then lacked the target's `drop` after the call.
# - The target holds one body for 1927 and for std::vector<char>'s instance of the same insert, which the target's
#   uenux2 converters 11397 and 11399 call and ecourna's converters 9063, 9201 and 9227 invoke. Unit 124's
#   cconversorestadogeral.cpp (11397) instantiates that one at the tree's flags, ahead of ecourna's objects, whose own
#   copy differs, so binaryen merges it with this object's; 1927's match line names the vector<char> symbol, the first in
#   link order, and 1927 matches from that object. With no uenux2 copy ahead of ecourna's, the three converters left
#   match (their slot operand had no target function).
#
# Chosen: the class head in api/io/cencryptedfile.h (its path, the member names, the shared_ptr), the enumerator name
# EUE_IO_NOME_ARQUIVO_VAZIO (from its message, in api/io/eueioerror.h), Save's place in the file above its record line.
# Not written: Load (3653), and 2766 and 3652, which hold MemWrite (records 142, 145) and MemRead (161 to 167) inlined;
# their stubs stay in cencryptedfile.cpp. No constructor or destructor of the class is identified.
CENCRYPTEDFILE_SRCS := src/api/io/cencryptedfile.cpp
UENUX2_SRCS += $(CENCRYPTEDFILE_SRCS)

$(ROOT)/$(APP)/128-uenux2-cencryptedfile-roots.o: $(ROOT)/src/units/128-uenux2-cencryptedfile-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/128-uenux2-cencryptedfile.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/128-uenux2-cencryptedfile-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/128-uenux2-cencryptedfile-roots.o
