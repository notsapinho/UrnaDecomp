# uenux2 simulador::CWasmTimer, the wasm build's api::ITimer, in src/uenux2/mock/app/simulador/wasm/cwasmtimer.cpp (+
# cwasmtimer.h), with the api::ITimer interface (src/uenux2/src/api/util/itimer.h), and simulador::CWasmTimerScheduler,
# which builds the timers, in cwasmtimerscheduler.cpp (+ cwasmtimerscheduler.h):
# - ~CWasmTimer (target fn 3347, vtable @1532080 slot 0) and the deleting destructor (fn 7926, slot 1). The D0 calls the
#   D2, so the destructor is user-declared and defined out of line: the key function, so this TU emits the vtable. Its
#   body is Stop, inlined, then m_state's release. No vptr store: the class is final (cwasmtimer.h).
# - Stop (fn 7934, slot 3), IsRunning (fn 7902, slot 4) and SetInterval (fn 7896, slot 5).
# - the constructor and State's, read from fn 7871, which inlines them; they are no target function. The constructor's
#   make_shared<State> brings the control block std::__shared_ptr_emplace<CWasmTimer::State> (D2 7890, D0 7885,
#   __on_zero_shared 7878), which matches from this TU.
# - CWasmTimerScheduler's slot 0, CreateTimer (fn 7871): a make_shared<CWasmTimer> with a copy of its callback (a const
#   reference since api/util/itimerscheduler.h says why; with it 7871 scores 5 over 237 rows, all operand-only, in the
#   whole link, and still matches), which brings std::__shared_ptr_emplace<CWasmTimer> (D2 7862, D0 7851, __on_zero_shared 7839, the destructor's second
#   caller), matched from cwasmtimerscheduler.cpp.o. binaryen inlines CWasmTimer's constructor into it (its frame sits
#   inside 7871), as it has one caller here too: the roots' make_shared<CWasmTimer> stand-in that stood for 7871 is
#   gone. The scheduler's own object, after this one, is the band's: 7871 runs after cwasmtimer.cpp's deferred members
#   (the State block's 7890 to 7878) and before its own block's; the vtable and typeinfo (1532172, 1532192) lie between
#   the State block's and the CWasmTimer block's. Its place on the link line is measured: with cwasmtimerscheduler.cpp.o
#   ahead of cwasmtimer.cpp.o (a fragment of its own numbered 127 sorts before 49) 7871 scores 86 over 245 rows, 8
#   inserted and 9 deleted, rows of locals and operand order; after it, 5 over 237, all operand-only
#   (docs/reference/facts/codegen.md C4). So the scheduler is in this unit, after the timer.
# - Start (fn 7918, slot 2) and the callback it hands to emscripten_async_call (fn 7909, table slot 838, chosen as the
#   private static Fire; both call the chosen Schedule, which clang or binaryen inlines into them and which has no
#   target function). `pair-depth0` under splat/symbol_addrs.txt's hand-edit marker names 7909: nothing else can, as its
#   only referrers are its own body and 7918, which is named by `vtable` and so casts no `table` vote. The two are the
#   target's as written, and neither source shape is settled: the same functions come from Fire with a raw pointer and
#   `delete`, without the `state` reference, with early returns, with load() and store() spelled on the atomics, and
#   with the new generation in a local.
# No record names any of it. The file is the one ledger/tu-clusters.tsv gives clusters 37, 38 and 945 (the `neighbours'
# file` of their unplaced.cpp stubs), in the directory where simulador's other wasm classes have records
# (cwasmthread.cpp, cwasmclp.cpp); cwasmtimerscheduler.cpp is cluster 36's guess, chosen too. CreateTimer's name is
# api::ITimerScheduler's (chosen there). The names of ITimer's four members and of State's members are chosen (itimer.h
# and cwasmtimer.h say from what); the class, State and the base are RTTI's. Paths relative to src/uenux2; the generic
# uenux2 rule compiles mock/ too and depends on the source and every uenux2 header.
CWASMTIMER_SRCS := mock/app/simulador/wasm/cwasmtimer.cpp mock/app/simulador/wasm/cwasmtimerscheduler.cpp
UENUX2_SRCS += $(CWASMTIMER_SRCS)
# nothing reconstructed creates the scheduler yet: 49-uenux2-cwasmtimer-roots.cpp keeps its vtable, the reference the
# target's vptr store (fn 8302) gives
$(ROOT)/$(APP)/49-uenux2-cwasmtimer-roots.o: $(ROOT)/src/units/49-uenux2-cwasmtimer-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/49-uenux2-cwasmtimer.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/49-uenux2-cwasmtimer-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/49-uenux2-cwasmtimer-roots.o
