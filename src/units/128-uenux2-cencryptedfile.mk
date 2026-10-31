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
# The destructor (fn 1691), and Write and Read (2766, 3652), which hold MemWrite (records 142, 145) and MemRead (161 to
# 167): the same object keeps MemWrite and MemRead out of line (wasm-objdump -d of cencryptedfile.cpp.o), and binaryen
# inlines each into its one caller, so 2766 sets up its frame after the early return, where MemWrite's own begins. The
# roots file stands in for their target callers (5736, 5737, 6734, 7174).
#
# Evidence for the forms (whole link, pnpm wasm score against the target before steps 7 to 9):
# - Write and Read return uedword, MemWrite's or MemRead's count or 0, which every caller drops and binaryen removes:
#   Read's target body keeps the if (result i32) of MemRead's count or 0 and drops it, and 2766 returns early. Write as
#   void, `if (!dados.empty()) MemWrite(...)`, scored 24 over 185 rows (inserted 1, deleted 2: the body nested in an if
#   where the target returns).
# - MemRead tests `m_dados.size() == 0`, which loads the end before the begin, as the target does; `m_dados.empty()`
#   loads the begin first (3 rows inserted, 3 deleted).
# - Read pads with 255 (the target's memory.fill); `0xFF` is the spelling chosen.
#
# Chosen: the class head in api/io/cencryptedfile.h (its path, the member names, the shared_ptr), the names Write and
# Read and their parameter types past what the bodies read, the enumerator names EUE_IO_NOME_ARQUIVO_VAZIO and 5996 to
# 6000's (from their messages, in api/io/eueioerror.h), the destructor `= default` in the .cpp and its line, Save's place
# above its record line, and Write's and Read's lines between Save and MemWrite. Save comes before Write in the object and
# Load before Read: in their use bands (4 and 3) the higher target index links first.
#
# Not written:
# - The constructor (fn 1692), which copies the cipher's shared_ptr into +0 and +4 and zeroes +8 to +20. In the target
#   +16 (i32), +8 (i64) and +20 (i32) are three stores in that order; every spelling measured merges +16 and +20 into
#   one i64 store (a scratch class of this layout at UENUX2_CXXFLAGS, its object's stores: the position as an in-class
#   initializer, in the member-init list, assigned in the body, value-initialized, after m_dados.clear(), from
#   m_dados.size(); the content moved from a temporary; the cipher assigned in the body; the same at -Oz). A
#   position taken from a parameter is stored first. A call after the content's stores (a member defined in another TU)
#   leaves +16 and +8 as the target has them, and binaryen inlining a function with one caller would put the +20 store
#   after them: a reading, and nothing names such a member.
# - Load (3653): it calls fn 412, `f6019(nome, 32768)`. 6019 masks the word at +4 of a buffer fn 1690 fills with 61440
#   and compares it with that argument, read as stat's file type against a regular file's; nothing names 412, 6019 or
#   1690. Its stub stays in cencryptedfile.cpp.
CENCRYPTEDFILE_SRCS := src/api/io/cencryptedfile.cpp
UENUX2_SRCS += $(CENCRYPTEDFILE_SRCS)

$(ROOT)/$(APP)/128-uenux2-cencryptedfile-roots.o: $(ROOT)/src/units/128-uenux2-cencryptedfile-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/128-uenux2-cencryptedfile.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/128-uenux2-cencryptedfile-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/128-uenux2-cencryptedfile-roots.o
