# uenux2 vota::CThreadVota (uenux2 src/app/vota/cthreadvota.cpp) and api::CTickManager (src/api/util/ctickmanager.cpp).
# Target fn 700 is CThreadVota::StartTick with CTickManager::StartTick inlined by binaryen (its only caller); 422 is
# CThreadVota::StopTick and 5451 CTickManager::StopTick, each with a second caller from the roots (their comments say which).
# CThreadVota::AddTick has one caller, unit 119's slot 2, which holds it inlined.
# CTickManager::AddTick (3644, record 31:15) is written and `no-candidate`. Its STick is built by STick's constructor, out of
# line: the target holds it after a second stack prologue around gettimeofday. SearchNextId (record 128:11) is `inline`,
# a choice at this tree's level: the target holds its loop in AddTick's own frame, and at -O2 the plain definition
# stayed a call in the object, which binaryen inlined with a second prologue (the earlier source), while at -O3 clang
# inlines the plain definition as well (measured), so the frame does not tell the two spellings apart. With both, the
# link reads `score 109 over 441 rows (same 332, replaced 68 [64 operand-only], inserted 20, deleted 21)` against
# `229 over 493` before. What is left is the search loop's shape: compiled at -O3 the object has the target's (the test
# of the tree's root hoisted out of the loop over ids, the id's mask once per id, `node < id`), at -O2 not; so it waits
# for the level. Five spellings of SearchNextId's loop give the same object for AddTick (wasm-objdump -d, compared row by
# row): an unsigned, int or size_t counter, `<= 0xff` or `< 256`, and static_cast<uebyte> on the key and the result or
# none.
UENUX2_SRCS += src/api/util/ctickmanager.cpp src/app/vota/cthreadvota.cpp
# The roots' headers are named here: $(UENUX2_HDRS) is still empty when the fragments are read.
CTHREADVOTA_HDRS := $(addprefix $(ROOT)/src/uenux2/src/,api/util/ctickmanager.h api/util/cwait.h api/util/eueutilerror.h api/ipc/cthread.h app/vota/cthreadvota.h)
$(ROOT)/$(APP)/02-uenux2-cthreadvota-roots.o: $(ROOT)/src/units/02-uenux2-cthreadvota-roots.cpp $(ROOT)/src/Makefile $(CTHREADVOTA_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/02-uenux2-cthreadvota-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/02-uenux2-cthreadvota-roots.o
