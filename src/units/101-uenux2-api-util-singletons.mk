# uenux2 singletons of api/util over unit 100's api::CPolySingleton, and the timer the scheduler makes:
# - api::ITimerScheduler::GetInst (target fn 1259, record itimerscheduler.cpp:23:12) and CreateInst<api::CTimerScheduler>
#   (5444, record itimerscheduler.h:40:19), with api::CTimerScheduler (api/util/ctimerscheduler.h, a chosen path). GetInst's
#   callers are not written: unit 100's roots call it. CreateInst returns what GetInst returns, as its record spells it; no
#   caller reads it, so binaryen dropped the result. The 7085 enumerator of EUeUtilError is new, its name chosen.
# - api::CAjusteDataHora (api/util/cajustedatahora.{h,cpp}, chosen paths): Registra (10876, a chosen name: only table slot 118
#   reaches it, so the roots take its address), Ajusta(const CDateTime&) (10875, slot 0, the clock set to
#   CDateTime::ConvertToLocalTime's time_t, fn 1381, unit 125) and Ajusta(const time_t&) (10874). The three are defined in
#   that order, the band's (ledger/ordinals.tsv, uses 1: 10876, 10875, 10874 in reverse link order); the class's vtable is
#   emitted with Ajusta(const CDateTime&), its key function. 10876 holds set<IAjusteDataHora> and
#   push<IAjusteDataHora>, which binaryen inlined (two more prologues), so unit 100's fragment reads it for push. The file
#   is placed by data order: the vtable (@1584156) and the interface's typeinfo lie between api/io/cinisection.cpp's records and
#   api/util/cdate.cpp's. api::IAjusteDataHora's header has its members now, with their slots.
# - api::CTimer (api/util/ctimer.h, its path chosen, has the layout) and CTimerScheduler::CreateTimer (10846), here in
#   itimerscheduler.cpp: CTimer's vtable and typeinfo lie with CTimerScheduler's and __shared_ptr_emplace<CTimer>'s right
#   before this file's first record (1585468), the place api::CSystemDateTime has before isystemdatetime.cpp's, and fn
#   10846 builds the CTimer. A choice the data support. The members: the destructor (D2 5445, D0 10852, out of line, the
#   key function), IsRunning (10851), Start (10850), SetInterval (10848) and Stop (10847), defined in the order of the u=1
#   band (10852 down to 10846, CreateTimer last; the proxy 10849 takes its place at Start, its first mention), which
#   names.tsv's ld_index follows. Start's lambda is the thread's loop; the target holds it in the thread proxy only (fn
#   10849, not matched: among other rows, the target calls libc++'s __thread_local_data where our link inlines it).
#   Measured in the plain link with `pnpm wasm score`: Stop takes its lock first, since the target computes the second
#   mutex's address before it clears the flag (with the lock after the notify, 9 over 24 rows); CreateTimer passes the
#   callback as an lvalue, so the constructor's by-value parameter is a copy (the target calls the function's __clone())
#   that then moves into the member.
#   Written and not matched: the destructor (5445, 25 over 76 rows: it inlines Stop, and the target computes the second
#   mutex's address after the join, where ours computes it for the lock at the start and keeps it; not explained).
#   CreateTimer (10846) matches at the tree's -O3 in the whole link. At -O2 it scored 59 over 190 rows: the target keeps
#   make_shared out of line, binaryen's second frame, with the control block's constructor inside it, where clang at -O2
#   inlines make_shared, cost 35 at threshold 337, and leaves the constructor out, cost 225 at threshold 225, per
#   -Rpass=inline on the file; std::atomic<bool> for the flag, the flag in the constructor's list, the constructor
#   defined after the class and the file without -fno-strict-aliasing keep 225; with std::move(callback) the score was
#   31 over 201 rows, and the rows that differ build the parameter (measured while the callback was a by-value
#   parameter). It is a const reference since api/util/itimerscheduler.h says why; 10846's body is the same with it
#   (masked object compare: one difference, the name of the allocate_shared it calls, whose template arguments name the
#   parameter's type), and it scores 4 over 187 rows, all operand-only, in the whole link.
#   libc++'s thread::join (4653) and std::__thread_struct's constructor (2541) come in with Stop and Start; the roots file
#   gives 2541 the second call site the target has. Chosen: the data members' names and the flag's type, the
#   constructor's parameters, the lambda (the proxy's tuple holds one pointer, this), and defining Stop's lock with
#   std::lock_guard.
# ISystemDateTime::GetInst and CreateInst (1155, records isystemdatetime.cpp:23 and .h:46) are in unit 81's source, the same
# shape; 1155 holds instance<T> because it is its only caller, and CreateInst for the same reason.
# Chosen, no byte decides: every name but GetInst's, CreateInst's and the messages'; has<T> and not a member of CPolySingleton
# in the two tests; std::unique_ptr<T>(new T) for make_unique, the same object.
API_UTIL_SINGLETONS_SRCS := src/api/util/cajustedatahora.cpp src/api/util/itimerscheduler.cpp
UENUX2_SRCS += $(API_UTIL_SINGLETONS_SRCS)
# a second call site of libc++'s std::__thread_struct constructor, which api::CTimer::Start calls (the roots file says why)
$(ROOT)/$(APP)/101-uenux2-api-util-singletons-roots.o: $(ROOT)/src/units/101-uenux2-api-util-singletons-roots.cpp $(ROOT)/src/units/101-uenux2-api-util-singletons.mk $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/101-uenux2-api-util-singletons-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/101-uenux2-api-util-singletons-roots.o
