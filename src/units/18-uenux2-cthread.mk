# uenux2 api::CThread in src/uenux2/src/api/ipc/cthread.cpp, five members:
# - ~CThread (target fn 2721, CThread vtable @1599952 slot 0), placed where the stub's link-order placement put it (no
#   std::source_location record falls in the destructor, so its line is not evidence). Its body is the two
#   two std::unique_ptr members (+12 m_pImpl, +16 m_sync) reset in reverse order; both pointees have a virtual destructor,
#   slot 1 of their vtables.
# - Start (target fn 1684), named by its record (line 68 col 19, the CUeIpcError 6231 throw, whose enumerator
#   api/ipc/eueipcerror.h now holds): sets the state (+4) to running and m_parar (+8) to false, and hands the thread
#   routine and `this` to IThreadImpl::Create (slot 2).
# - Rotina (target fn 10255), the thread routine Start passes as a plain argument (table slot 4527: `wasm-objdump -x -j
#   Elem target/vota_web_wasm.wasm` prints `elem[4527] = ref.func:10255`): calls Run (CThread slot 2) and sets the
#   state to finished (3). No record or symbol names it, and its bytes do not depend on its name: that it is a private
#   static member of CThread (it reads private state) and the name Rotina are our choice; a captureless lambda's
#   invoker would compile the same. The state values 0, 1 and 3 are the constructor's, Start's and the routine's stores.
# - CThread::CThread (target fn 3598): the records at lines 31 and 32 are the two default arguments of
#   CPolySingleton<T>::instance, for IGenericFactory<IThreadImpl> (fn 5423's name) and IGenericFactory<ISyncCtl> (3164), so
#   +16 is a std::unique_ptr<ISyncCtl> and not the IThreadImpl it was declared as. Both are Create() of slot 2. Their
#   columns, 15 and 14, are where the calls begin: as mem-initializers with this indent the two names have 7 and 6 letters,
#   which is all the evidence for m_pImpl and m_sync. No store precedes either, so they are mem-initializers and not
#   assignments. binaryen inlined the first instance (its one caller). 270, 316 and 1898 call the constructor (unit 116).
#   Paths relative to src/uenux2.
# - The head: slots 3 and 4 are pure, and unit 116 declares them with what vota::CThreadVota's overriders take. +8 and +9
#   swapped their chosen names there: +8 is the flag the Run loops test, so it is m_parar.
# - Wait (target fn 1900, a chosen name, after IThreadImpl's slot 3 that it calls): when the state (+4) is running (1),
#   waits through m_pImpl's slot 3 and sets the state to created (0). Its two callers are vota::CExecucaoVota's slots 2
#   and 4 (fns 10236, 10234, fragment 165), in another TU, and the target keeps it as a function, so it is out of line
#   here (that clang would inline the 40-B body from the class is a reading, not measured). Its line, after Rotina, is
#   a choice: no record falls in it.
# Start's three target callers, fns 10233, 10235 and 10236, are fragment 165's, so this unit has no roots file: the two
# stand-ins that gave Start more than one call site went when they landed.
CTHREAD_SRCS := src/api/ipc/cthread.cpp
UENUX2_SRCS += $(CTHREAD_SRCS)
