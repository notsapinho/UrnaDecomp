# uenux2 api::CThread in src/uenux2/src/api/ipc/cthread.cpp, three members:
# - ~CThread (target fn 2721, CThread vtable @1599952 slot 0), placed where the stub's link-order placement put it (no
#   std::source_location record falls in the destructor, so its line is not evidence). Its body is the two
#   std::unique_ptr<IThreadImpl> members (+12 m_impl, +16 m_implEspera) reset in reverse order; IThreadImpl
#   (api/ipc/ithreadimpl.h) has a virtual destructor, slot 1 of its vtable.
# - Start (target fn 1684), named by its record (line 68 col 19, the CUeIpcError 6231 throw, whose enumerator
#   api/ipc/eueipcerror.h now holds): sets the state (+4) to running and m_iniciada (+8) to false, and hands the thread
#   routine and `this` to IThreadImpl::Create (slot 2).
# - Rotina (target fn 10255), the thread routine Start passes as a plain argument (table slot 4527: `wasm-objdump -x -j
#   Elem target/vota_web_wasm.wasm` prints `elem[4527] = ref.func:10255`): calls Run (CThread slot 2) and sets the
#   state to finished (3). No record or symbol names it, and its bytes do not depend on its name: that it is a private
#   static member of CThread (it reads private state) and the name Rotina are our choice; a captureless lambda's
#   invoker would compile the same. The state values 0, 1 and 3 are the constructor's, Start's and the routine's stores.
# The constructor (3598) is not reconstructed yet. Paths relative to src/uenux2.
CTHREAD_SRCS := src/api/ipc/cthread.cpp
UENUX2_SRCS += $(CTHREAD_SRCS)
# the roots that keep the destructor and Start linked (see the file header)
$(ROOT)/$(APP)/18-uenux2-cthread-roots.o: $(ROOT)/src/units/18-uenux2-cthread-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/18-uenux2-cthread-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/18-uenux2-cthread-roots.o
