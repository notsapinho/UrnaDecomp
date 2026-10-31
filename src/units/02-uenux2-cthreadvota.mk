# uenux2 vota::CThreadVota (uenux2 src/app/vota/cthreadvota.cpp) and api::CTickManager (src/api/util/ctickmanager.cpp).
# Target fn 700 is CThreadVota::StartTick with CTickManager::StartTick inlined by binaryen (its only caller); 422 is
# CThreadVota::StopTick and 5451 CTickManager::StopTick, each with a second caller from the roots (their comments say which).
# CThreadVota::AddTick(size_t) has one caller, unit 119's slot 2 (10800), which holds it inlined.
# 4640 is CThreadVota::AddTick(const std::chrono::milliseconds &), 807 CThreadVota::AddStoppedTick and 5452
# CTickManager::AddStoppedTick: thunks over m_ticks (+20) and over AddTick and StopTick. No record names them: their
# names, and the type of 4640's parameter, are chosen (the headers say from what). 4640 and 807 are in cthreadvota.cpp
# by choice, as the class's members (their link-order clusters, 699 and 1297, have no label). 5452 is in ctickmanager.cpp,
# its class's file, beside StopTick: 5451 and 5452 are neighbours in use band 2 (stretch 762, labelled by 5451's record),
# where the higher index is linked first, so 5452 is defined before StopTick (record at line 60), and our link has them
# in that order (ld_index, build/out/wasm-map/vota_web/names.tsv). Where before StopTick is a choice: after AddTick, line 41.
# So is the order of 4640 and 807 in cthreadvota.cpp, which no band ties to the other members.
# CTickManager::AddTick (3644, record 31:15) is written and `differs`. The census pairs it and its three callers (4640,
# 5452, 10800) with nothing, so no call vote names it: a callers+content hand line of splat/symbol_addrs.txt does, from
# the two records 3644 alone loads, and 4640, 5452, 807 and 10800 match through it (with the line out of copies of the
# symbol file and the match list, a scan run twice leaves the four `no-candidate` and `unresolved`, 9667 match rows
# against the control's 9671, and splat-build gives the target's sha256 with 9667 matches).
# AddTick's STick is built by STick's constructor, out of line: the target holds it after a second stack prologue around
# gettimeofday. SearchNextId (record 128:11) is `inline`, a choice: the target holds its loop in AddTick's own frame;
# at -O2 the plain definition stayed a call in the object, which binaryen inlined with a second prologue (the earlier
# source), and at -O3 clang inlines the plain definition as well (measured), so the frame does not tell the two
# spellings apart. With both, the -O2 link read `score 109 over 441 rows (same 332, replaced 68 [64 operand-only],
# inserted 20, deleted 21)` against `229 over 493` before. The search loop's shape is -O3's: compiled at -O3 the object
# has the target's (the test of the tree's root hoisted out of the loop over ids, the id's mask once per id,
# `node < id`), at -O2 not. The level does not close the body alone: at the tree's -O3 the link reads `score 83 over
# 432 rows (same 349, replaced 63 [63 operand-only], inserted 11, deleted 9)`; what those 20 rows are is not read.
# Five spellings of SearchNextId's loop give the same object for AddTick (wasm-objdump -d, compared row by row): an
# unsigned, int or size_t counter, `<= 0xff` or `< 256`, and static_cast<uebyte> on the key and the result or none.
UENUX2_SRCS += src/api/util/ctickmanager.cpp src/app/vota/cthreadvota.cpp
# The roots' headers are named here: $(UENUX2_HDRS) is still empty when the fragments are read.
CTHREADVOTA_HDRS := $(addprefix $(ROOT)/src/uenux2/src/,api/util/ctickmanager.h api/util/cwait.h api/util/eueutilerror.h api/ipc/cthread.h app/vota/cthreadvota.h)
$(ROOT)/$(APP)/02-uenux2-cthreadvota-roots.o: $(ROOT)/src/units/02-uenux2-cthreadvota-roots.cpp $(ROOT)/src/Makefile $(CTHREADVOTA_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/02-uenux2-cthreadvota-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/02-uenux2-cthreadvota-roots.o
