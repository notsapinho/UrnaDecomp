# uenux2 vota::CProgressoEncerramento::~CProgressoEncerramento (target fn 3907, the base-object destructor in slot 0 of
# the CProgressoEncerramento vtable @1540588, and fn 12104, the deleting one in slot 1) in
# src/uenux2/src/app/vota/eleitor/fimvotacao/cprogressoencerramento.cpp. No record names the class, so the file is
# chosen (docs/how-to-decompile.md step 3): its name is the one the stubs' link-order clusters 622 and 1033 give, its
# directory the one where vota's end-of-voting states have their records, among them CGravaResultado, whose StartState
# (fn 12098, records cgravaresultado.cpp:63 and 79) is the only place that builds the class. New headers: the class
# (cprogressoencerramento.h) and its base comum::CAbstractTelaProgresso (src/app/comum/cabstracttelaprogresso.h; no
# evidence names its directory or its three virtual members, see the header). The class is final (its destructor
# stores no vptr); it holds a std::shared_ptr to the form (+4), one to the api::CProgressBar (+12) and a std::mutex
# (+20), which the destructor destroys in reverse order. The destructor is out of line, as the deleting one calling it
# shows, and declared first, so it is the key function and cprogressoencerramento.o emits the vtable. The constructor
# (inlined into fn 12098) is not reconstructed. Paths relative to src/uenux2; the generic uenux2 rule depends on the
# source and every uenux2 header.
CPROGRESSOENCERRAMENTO_SRCS := src/app/vota/eleitor/fimvotacao/cprogressoencerramento.cpp
UENUX2_SRCS += $(CPROGRESSOENCERRAMENTO_SRCS)
# slots 2 to 4 (target fns 12103, 12102, 12101) are not reconstructed: 48-uenux2-cprogressoencerramento-pending.cpp
# gives the vtable trapping bodies, compiled with the unit's flags
$(ROOT)/$(APP)/48-uenux2-cprogressoencerramento-pending.o: $(ROOT)/src/units/48-uenux2-cprogressoencerramento-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/48-uenux2-cprogressoencerramento.mk $(ROOT)/src/uenux2/src/app/vota/eleitor/fimvotacao/cprogressoencerramento.h $(ROOT)/src/uenux2/src/app/comum/cabstracttelaprogresso.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/48-uenux2-cprogressoencerramento-pending.cpp -o $(R)
# nothing reconstructed references the vtable yet: 48-uenux2-cprogressoencerramento-roots.cpp takes its address, which
# keeps both destructors in the table as the target has them
$(ROOT)/$(APP)/48-uenux2-cprogressoencerramento-roots.o: $(ROOT)/src/units/48-uenux2-cprogressoencerramento-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/48-uenux2-cprogressoencerramento.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/48-uenux2-cprogressoencerramento-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/48-uenux2-cprogressoencerramento-pending.o $(APP)/48-uenux2-cprogressoencerramento-roots.o
