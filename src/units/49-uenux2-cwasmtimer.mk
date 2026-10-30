# uenux2 simulador::CWasmTimer, the wasm build's api::ITimer, in src/uenux2/mock/app/simulador/wasm/cwasmtimer.cpp
# (+ cwasmtimer.h), with the api::ITimer interface (src/uenux2/src/api/util/itimer.h):
# - ~CWasmTimer (target fn 3347, vtable @1532080 slot 0) and the deleting destructor (fn 7926, slot 1). The D0 calls
#   the D2, so the destructor is user-declared and defined out of line: the key function, so this TU emits the vtable.
#   Its body is Stop, inlined, then m_state's release. No vptr store: the class is final (cwasmtimer.h).
# - Stop (fn 7934, slot 3), IsRunning (fn 7902, slot 4) and SetInterval (fn 7896, slot 5).
# - the constructor and State's, read from fn 7871 (simulador::CWasmTimerScheduler slot 0, not reconstructed), which
#   inlines them; they are no target function. The constructor's make_shared<State> brings the control block
#   std::__shared_ptr_emplace<CWasmTimer::State> (D2 7890, D0 7885, __on_zero_shared 7878), which matches from this
#   TU; the roots' make_shared<CWasmTimer> brings std::__shared_ptr_emplace<CWasmTimer> (D2 7862, D0 7851,
#   __on_zero_shared 7839, the destructor's second caller), which matches from the roots object (libc++ code both
#   instantiate, not a stand-in's).
# Start (fn 7918, slot 2) is pending, with the callback it schedules (fn 7909): 49-uenux2-cwasmtimer-pending.cpp says
# why and holds their source. No record names any of it. The file is the one ledger/tu-clusters.tsv gives clusters 37,
# 38 and 945 (the `neighbours' file` of their unplaced.cpp stubs), in the directory where simulador's other wasm
# classes have records (cwasmthread.cpp, cwasmclp.cpp). The names of ITimer's four members and of State's members are
# chosen (itimer.h and cwasmtimer.h say from what); the class, State and the base are RTTI's. Paths relative to
# src/uenux2; the generic uenux2 rule compiles mock/ too and depends on the source and every uenux2 header.
CWASMTIMER_SRCS := mock/app/simulador/wasm/cwasmtimer.cpp
UENUX2_SRCS += $(CWASMTIMER_SRCS)
# Start (target fn 7918) is not reconstructed: 49-uenux2-cwasmtimer-pending.cpp gives the vtable a trapping body,
# compiled with the unit's flags
$(ROOT)/$(APP)/49-uenux2-cwasmtimer-pending.o: $(ROOT)/src/units/49-uenux2-cwasmtimer-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/49-uenux2-cwasmtimer.mk $(ROOT)/src/uenux2/mock/app/simulador/wasm/cwasmtimer.h $(ROOT)/src/uenux2/src/api/util/itimer.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/49-uenux2-cwasmtimer-pending.cpp -o $(R)
# nothing reconstructed creates a timer yet: 49-uenux2-cwasmtimer-roots.cpp does the target's make_shared<CWasmTimer>
# (see the file header)
$(ROOT)/$(APP)/49-uenux2-cwasmtimer-roots.o: $(ROOT)/src/units/49-uenux2-cwasmtimer-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/49-uenux2-cwasmtimer.mk $(ROOT)/src/uenux2/mock/app/simulador/wasm/cwasmtimer.h $(ROOT)/src/uenux2/src/api/util/itimer.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/49-uenux2-cwasmtimer-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/49-uenux2-cwasmtimer-pending.o $(APP)/49-uenux2-cwasmtimer-roots.o
