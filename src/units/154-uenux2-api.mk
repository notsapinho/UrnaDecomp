# uenux2 api::CSynchronizer in src/uenux2/src/api/util/csynchronizer.cpp and api::KeyName(char) in
# src/uenux2/src/api/hwil/iinput.h, the files their std::source_location records name:
#   600   CSynchronizer::GetInst, holding CreateInst inlined   record at csynchronizer.cpp line 37, col 15 (7030)
#   5729  CSynchronizer's constructor, out of line; 10867, the destructor of its static instance
#   744   KeyName, an inline function of the header             record at iinput.h line 61, col 19 (5169)
#   620   CSynchronizer::Sync, no record; GetOpenFlag, no target index (inlined into CSystem::CopyFile, unit 32)
# with the header api/util/csynchronizer.h, the 7030 enumerator of api/util/eueutilerror.h and the 5169 enumerator of
# api/hwil/euehwilerror.h. Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2
# header. CSynchronizer: 600 creates the instance on first use, `new` of one byte and a call of 5729, which stores its
# bool argument and returns this, and throws "Instancia ja criada" when one exists: CreateInst's record, so CreateInst
# is inlined into it. The constructor is out of line in this file: at -fPIC a call of a C1 stays a call in its own TU
# (docs/reference/facts/codegen.md C6), as 600's does. The instance is a static std::unique_ptr: 10867 destroys the word
# at 1839324 through fn 349, which unit 03's fragment reads as a static std::unique_ptr's destructor (its 9268), and our
# object's destructor of the static matches it. The data name of that word, CSynchronizer::s_instancia, is a generated
# `vote:5 by:600` line; the other reader of the address in the target is 10867, the static's destructor, which matches
# from this object too. Names other than CreateInst's are chosen; csynchronizer.h says from what. Fn 620 (14 callers,
# 8 B) loads the byte and drops it: `if (m_habilitado) sync();` gives it, as emscripten's sync() only calls
# __syscall_sync, a weak stub that returns 0 (emscripten's system/lib/libc/emscripten_syscall_stubs.c), so binaryen
# keeps the load alone, a reading; its name, Sync, is chosen after ecourna's CSynchronizer::Sync(int), and its place
# after the constructor is chosen too (its use band, 25, holds nothing else of this file). GetOpenFlag returns O_SYNC
# when the byte is set: CopyFile (378) needs it out of line for the target's rows (unit 32's fragment has the
# measurement), and it has no target index, binaryen inlining it into its one caller; its being a member, its name and
# its line are chosen. KeyName: the target
# range-tests '0' to '9' and then jumps on 'B', 'C' and 'D' with a table. Written as an `if` over '0' to '9' before the
# switch, it scored `72 over 282 rows` (24 inserted, 24 deleted); with the digits as case labels of the switch, `21 over
# 258`, all operand-only (pnpm wasm score on the whole link, and on a whole-link try of the roots object against the
# header in an -iquote overlay). The keys are spelled as character literals, a choice: the target holds only their
# values. The target's copy reads as cinstrucaovotacaoacessibilidade.cpp's object's (its record 1533820 follows that
# file's records), which is not reconstructed; until it is, the roots object emits the copy.
API154_SRCS := src/api/util/csynchronizer.cpp
UENUX2_SRCS += $(API154_SRCS)
# KeyName is a header's inline code and none of its five callers (fns 653, 1455, 2243, 7787 and 12903) is reconstructed:
# 154-uenux2-api-roots.cpp emits it, and calls GetInst and the constructor, whose callers are not reconstructed either.
# The roots object compiles at the uenux2 tree's flags, not APP_CXXFLAGS, so no match rests on a flag the tree lacks
# (src/units/README.md "Companion files").
$(ROOT)/$(APP)/154-uenux2-api-roots.o: $(ROOT)/src/units/154-uenux2-api-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/154-uenux2-api.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/154-uenux2-api-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/154-uenux2-api-roots.o
