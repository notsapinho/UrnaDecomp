# uenux2 api::CThread in src/uenux2/src/api/ipc/cthread.cpp, three members:
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
CTHREAD_SRCS := src/api/ipc/cthread.cpp
UENUX2_SRCS += $(CTHREAD_SRCS)
# the roots that keep Start linked (see the file header)
$(ROOT)/$(APP)/18-uenux2-cthread-roots.o: $(ROOT)/src/units/18-uenux2-cthread-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/18-uenux2-cthread-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/18-uenux2-cthread-roots.o
