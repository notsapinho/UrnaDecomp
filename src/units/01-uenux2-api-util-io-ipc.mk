# The uenux2 units the uenux2 flags were measured on (docs/reference/facts/app-flags.md §F6); paths relative to src/uenux2
# CPosixSemaphore::Wait (fn 10247, record at cposixsemaphore.cpp line 48) is written and differs: `score 97 over 264
# rows (same 167, replaced 87 [86 operand-only], inserted 2, deleted 8)`. The target leaves its entry block for the
# untimed wait with a br_if where ours enters an if, and numbers the frame pointer's local otherwise. Taking the untimed
# wait first (96 over 265, the entry block unchanged) or returning early after it (164 over 272) does not close it, nor does a
# whole-link try at `--flags -fstrict-aliasing` (97 over 264): the cause is not known.
UENUX2_SRCS += src/api/util/cwait.cpp src/api/io/cinikey.cpp src/api/ipc/posix/cposixmutex.cpp src/api/ipc/posix/cposixsemaphore.cpp
UENUX2_SRCS += wasm/vota_web/posix_sem_shim.cpp
