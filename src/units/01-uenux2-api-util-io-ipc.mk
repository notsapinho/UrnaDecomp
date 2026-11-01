# The uenux2 units the uenux2 flags were measured on (docs/reference/facts/app-flags.md §F6); paths relative to src/uenux2
# CPosixSemaphore::Wait (fn 10247, record at cposixsemaphore.cpp line 48) is written and differs: `score 97 over 264
# rows (same 167, replaced 87 [86 operand-only], inserted 2, deleted 8)`. The target leaves its entry block for the
# untimed wait with a br_if where ours enters an if, and numbers the frame pointer's local otherwise. Taking the untimed
# wait first (96 over 265, the entry block unchanged) or returning early after it (164 over 272) does not close it, nor does a
# whole-link try at `--flags -fstrict-aliasing` (97 over 264): the cause is not known. Re-measured at 694de52: 95 over
# 264 rows (same 169, replaced 85 [84 operand-only], inserted 2, deleted 8); posix_sem_shim.cpp linked ahead of
# cposixsemaphore.cpp gives a byte-identical link.
# CWait::Wait (fn 5446, no record: the name is chosen) loops while CSystem::s_dorme is set, until gettimeofday reaches
# the end the constructor stored, and sleeps 200 us at a time with libc's usleep (fn 3966), over libc's nanosleep (fn
# 6265). The flag's first test compares with 1 and the back edge tests it bare, a bool's two reads
# (docs/reference/facts/reading.md R14). The time test: the target compares the seconds with i64.gt_s and then
# i64.ge_s before the microseconds' i32.ge_s, which `sec > || (sec >= && usec >=)` gives. `!timercmp(&agora, &m_inicio,
# <)` scored `17 over 55 rows` (8 inserted, 4 deleted, one of them a drop that a stand-in reading usleep's result gave)
# in the whole link, and in object probes timercmp(>=) and a `sec ==` second test compare otherwise; the form written
# scores `3 over 47`, operand-only. No caller of Wait or of usleep is reconstructed: 01-uenux2-api-util-io-ipc-roots.cpp gives each a
# second call site. nanosleep's other target caller, SQLite's unixSleep (12902), is in our link and matches with it.
UENUX2_SRCS += src/api/util/cwait.cpp src/api/io/cinikey.cpp src/api/ipc/posix/cposixmutex.cpp src/api/ipc/posix/cposixsemaphore.cpp
UENUX2_SRCS += wasm/vota_web/posix_sem_shim.cpp
$(ROOT)/$(APP)/01-uenux2-api-util-io-ipc-roots.o: $(ROOT)/src/units/01-uenux2-api-util-io-ipc-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/01-uenux2-api-util-io-ipc-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/01-uenux2-api-util-io-ipc-roots.o
