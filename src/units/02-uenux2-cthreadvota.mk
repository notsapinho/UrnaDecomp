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
# cthreadvota.cpp also holds an AddStoppedTick(const std::chrono::milliseconds&) overload with no target function of
# its own: binaryen inlines it into its one caller, vota::CVerificaHorarioZeresima's constructor in fn 5947 (unit
# 138's fragment has it); its place after AddStoppedTick(size_t) is a choice.
# CTickManager::AddTick (3644, record 31:15) matches since src/api/ builds with strict aliasing (below). The census
# paired it and its three callers (4640, 5452, 10800) with nothing, and two lines of splat/symbol_addrs.txt name it: a generated `evidence:call` line, since
# 1285's vptr anchor names 4640 (`call by:1285`) and 4640 and 5452 vote for 3644, and a callers+content hand line from
# the two records 3644 alone loads, which stays for that evidence. Measured at -O2 with unit 97's states written,
# scans run twice on copies of the symbol file and the match list: with the hand line alone out every match holds;
# with 3644's name out on both sides of the marker 10800, 1285, 4640 and 5452 fall.
# AddTick's STick is built by STick's constructor, out of line: the target holds it after a second stack prologue around
# gettimeofday. SearchNextId (record 128:11) is `inline`, a choice: the target holds its loop in AddTick's own frame;
# at -O2 the plain definition stayed a call in the object, which binaryen inlined with a second prologue (the earlier
# source), and at -O3 clang inlines the plain definition as well (measured), so the frame does not tell the two
# spellings apart. With both, the -O2 link read `score 109 over 441 rows (same 332, replaced 68 [64 operand-only],
# inserted 20, deleted 21)` against `229 over 493` before. The search loop's shape is -O3's: compiled at -O3 the object
# has the target's (the test of the tree's root hoisted out of the loop over ids, the id's mask once per id,
# `node < id`), at -O2 not. The level does not close the body alone: at the tree's -O3 the link reads `score 83 over
# 432 rows (same 349, replaced 63 [63 operand-only], inserted 11, deleted 9)`. Two places hold those 20 rows: the map's
# __insert_node_at, where our object reads the new node back after the store to the begin node and the target keeps it
# in a local, and the loads of the key in __find_equal's loop, in another order. In a whole-link try with
# ctickmanager.cpp and cthreadvota.cpp at `--flags -fstrict-aliasing` the link reads `score 28 over 421 rows`, every row
# an operand: those rows are -fno-strict-aliasing's, and src/api/ builds with strict aliasing (src/Makefile UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6),
# so 3644 matches.
# Five spellings of SearchNextId's loop give the same object for AddTick (wasm-objdump -d, compared row by row): an
# unsigned, int or size_t counter, `<= 0xff` or `< 256`, and static_cast<uebyte> on the key and the result or none.
# CTickManager::GetExpiredTicks (5450, no record: the name is chosen) returns the ids of the running ticks whose time
# has come and moves each one on to its next time after now, by whole intervals. Its callers, 4349 (whose record is
# CThreadEleitor::ProcessarEntrada's) and 10204 (CThreadOperador's slot 2), are not reconstructed: the roots stand for
# them. It is defined last in ctickmanager.cpp, a choice: in use band 2 it links after 5452 and 5451 (StopTick) and
# before 5449 (api::IsValidTime, ctime.cpp), so after StopTick, and the 26 free lines above SearchNextId (95 to 120)
# are too few for it. Its `#include <cmath>` (for round) takes the blank line that followed `namespace {`, which keeps
# AddTick's record on line 31. Measured in the whole link (pnpm wasm score against our symbol, names.tsv after
# tools/round/link-map.sh): with the time test written as the due condition (CWait's, `agora > || (agora >= && usec
# >=)`), `90 over 327 rows (same 237, replaced 64 [60 operand-only], inserted 12, deleted 14)`; written as the
# condition to skip (`agora < || (agora <= && usec <)`, then continue), which tests `<` first as the target does, `84
# over 324 rows (same 240, replaced 64 [61 operand-only], inserted 9, deleted 11)`. The rest was the loop that brings
# the microseconds under a second: clang turns it into a closed form, and with the loop in the function's body that
# form is `x - umin(x, 1999999)` with the extra second added before the zero-extension, where the target has the
# select of `x - 1999999` and the second added in i64. With the loop in a function of its own that the body calls,
# NormalizaMicrossegundos (file-static, its name chosen), the object has the target's form (a reading of why: clang
# simplifies the helper on its own before it inlines it) and the link reads `12 over 315 rows (same 303, replaced 12 [12 operand-only], inserted 0, deleted
# 0)`, the callees and the literals 1000000 and 999999, and the scan matches it. Object probes at the tree's flags
# (wasm-objdump -d of ctickmanager.cpp compiled alone): the helper written as a lambda gives the same object, and so
# does the skip test joined with the m_parado test in one if; `timercmp(&agora, &tick.m_proximo, <)` and the negated
# due condition give others. With the loop in the body, `> 999999`, `x = x - 1000000` and time_t and int locals for
# the two parts give the same object as the loop as first written; an int counter of the seconds and a do-while under
# an if give others.
UENUX2_SRCS += src/api/util/ctickmanager.cpp src/app/vota/cthreadvota.cpp
# The roots' headers are named here: $(UENUX2_HDRS) is still empty when the fragments are read.
CTHREADVOTA_HDRS := $(addprefix $(ROOT)/src/uenux2/src/,api/util/ctickmanager.h api/util/cwait.h api/util/eueutilerror.h api/ipc/cthread.h app/vota/cthreadvota.h)
$(ROOT)/$(APP)/02-uenux2-cthreadvota-roots.o: $(ROOT)/src/units/02-uenux2-cthreadvota-roots.cpp $(ROOT)/src/Makefile $(CTHREADVOTA_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/02-uenux2-cthreadvota-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/02-uenux2-cthreadvota-roots.o
