# The uenux2 units the uenux2 flags were measured on (docs/reference/facts/app-flags.md §F6); paths relative to src/uenux2
# CPosixMutex's constructor (fn 10254, record cposixmutex.cpp line 30) matches, and with it the executable TU's
# CDefaultGenericFactory<ISyncCtl, CPosixMutex>::Create (fn 10869, unit 170's), which passes the constructor's table
# slot to binaryen's merge body 6023. The body is as written before: at 21a541d4 it scored 19 over 209 rows (18
# operand-only, and the target's `drop` after its call of libc's pthread_mutexattr_init, fn 3977, deleted). The
# target's 3977 (`*p = 0; return 0`) keeps an i32 result, which its third caller reads: libc++'s recursive_mutex
# constructor, inlined into the static initializers (fn 14478). Our link had no such caller, and there the function
# had no result and was a void twin (12936's scan detail at 21a541d4: `ours +0x49 call 2269`, CCargos::Reset's 9 B):
# dead-argument elimination drops a result no caller reads (how-to step 2). The initializer is read as unit 12's file
# mutex's, a std::recursive_mutex (unit 12's fragment has the reading); with it ours keeps the result, and 3977 and
# SQLite's pthreadMutexAlloc (12936) match as well. pthread_mutex_init and
# pthread_mutexattr_destroy return 0 in emscripten's single-threaded libc (library_pthread_stub.o,
# pthread_mutexattr_destroy.o) and leave no code, so the target shows neither call: the constructor's POSIX sequence
# after the test is a choice.
# CPosixSemaphore::Wait (fn 10247, records cposixsemaphore.cpp lines 48 and 76) is written and differs: on the link
# that matches 10254, `score 95 over 264 rows (same 169, replaced 85 [84 operand-only], inserted 2, deleted 8)`. The
# target leaves a block for the untimed wait with an `if` that holds a `br 1`, where ours enters an if; it keeps the
# frame pointer in local 2 and reuses local 0 inside the clock's throw, where ours keeps it in local 0 (`this`, which
# no code reads); and it sets local 1 to 0 after the join, a set nothing reads. Taking the untimed wait first (96 over
# 265, the entry block unchanged) or returning early after it (164 over 272) does not close it, nor does a whole-link
# try at `--flags -fstrict-aliasing` (97 over 264). On the link that matches 10254, a posix_sem_shim.cpp whose
# sem_timedwait calls the libc stub (`return sem_wait(sem)`, or sem_trywait with ETIMEDOUT when it fails: the two give
# one link, byte-identical) gives ours that dead set after the join, at 94 over 265 rows (same 171, replaced 85 [85
# operand-only], inserted 3, deleted 6), with the frame pointer still in local 0, the entry still an if and a `return`
# before the end; with that shim, `resultado` left unset until the arms gives the same link, the untimed wait first
# the same score, and one sem_timedwait call after the branch, on a pointer left null for the untimed wait, 122 over
# 270. emscripten's single-threaded libc defines sem_wait as `return 0` (library_pthread_stub.o) and no sem_timedwait.
# The cause is not known, and the shim keeps `return 0`. posix_sem_shim.cpp linked ahead of cposixsemaphore.cpp gives a
# byte-identical link with either shim.
# CWait::Wait (fn 5446, no record: the name is chosen) loops while CSystem::s_dorme is set, until gettimeofday reaches
# the end the constructor stored, and sleeps 200 us at a time with libc's usleep (fn 3966), over libc's nanosleep (fn
# 6265). The flag's first test compares with 1 and the back edge tests it bare, a bool's two reads
# (docs/reference/facts/reading.md R14). The time test: the target compares the seconds with i64.gt_s and then
# i64.ge_s before the microseconds' i32.ge_s, which `sec > || (sec >= && usec >=)` gives. `!timercmp(&agora, &m_inicio,
# <)` scored `17 over 55 rows` (8 inserted, 4 deleted, one of them a drop that a stand-in reading usleep's result gave)
# in the whole link, and in object probes timercmp(>=) and a `sec ==` second test compare otherwise; the form written
# scores `3 over 47`, operand-only. No roots: Wait's two target callers, 11891 and 11982 (the slot 7 of
# vota::CMenuFiltrarCandidatosPorNumero and of vota::CInformacaoZeresimaTardia, units 104 and 169), are in the link,
# and the roots' EsperaDuas, which stood for both with two call sites, went with 11891, and with it the roots file;
# usleep's target callers (Wait, 10204 and 10435, units 116 and 152) are in the link too. nanosleep's other target
# caller, SQLite's unixSleep (12902), is in our link and matches with it.
UENUX2_SRCS += src/api/util/cwait.cpp src/api/io/cinikey.cpp src/api/ipc/posix/cposixmutex.cpp src/api/ipc/posix/cposixsemaphore.cpp
UENUX2_SRCS += wasm/vota_web/posix_sem_shim.cpp
