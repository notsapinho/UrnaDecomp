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
# (inlined into fn 12098) is written, unrooted (below). Inicia, Finaliza and Incrementa (12103, 12102, 12101, slots 2 to
# 4, names chosen in the base's header) hold the mutex over CProgressBar's SetValor and Incrementa; a std::unique_lock
# or std::scoped_lock for the std::lock_guard gives the same object code in Inicia, the one measured. Paths relative to
# src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
# The constructor and the screen it takes the form and the bar from, written, unrooted, with no target index: fn 12098
# holds std::make_shared of the class (56 bytes: the control block's vptr 1541140, then at +12 the base's vptr 1551212,
# m_form zeroed, this class's vptr 1540596, the other members zeroed) and the constructor behind a 16-byte stack frame
# of its own (binaryen's inlining: lines 2582 to 2794 of pnpm wasm fn's folded readout of 12098), which holds the pair
# vota::TelaProgressoEncerramento (ctelasvota.cpp, declared in ctelasvota.h with what it builds; its name and the pair
# as its result chosen) returns, behind an 80-byte frame of its own; the constructor copies the form into +4 and the bar
# into +12 (each count incremented and the old pointer released: assignments from the pair's members, a reading) and
# destroys the pair. Read against that readout on the objects (wasm-objdump -d): the screen's frame and every frame
# offset are the readout's (the builder +68, the three text fields' results +60, +40, +32, the strings +48, the bar +24,
# its corners +12 and +20, the form +12), and so is the order of the bar's and the pair's stores. The base's vptr store
# is evidence that comum::CAbstractTelaProgresso's constructor is another TU's, and that TU is
# src/app/comum/cabstracttelaprogresso.cpp (its file chosen, beside its header, which says what was measured): with the
# implicit inline constructor cprogressoencerramento.cpp.o stores the members' zeros and then the vptr, with no base
# store; with the base's constructor declared and defined in another TU it calls it and then stores +4, the vptr and +12
# to +36, the target's order. The new file's place in this list, after cprogressoencerramento.cpp, is chosen: its object
# is dropped while nothing constructs the class, so no count over the data's order ranks it yet; the target's data put
# the base's vtable (@1551204) right before comum::CAppState's (cappstate.cpp). The screen's font,
# vota::FONTE_BARRA_PROGRESSO, is external, a chosen linkage (the user's decision; ctelasvota.h), and unit 31's roots'
# BarraProgresso (7787's and 12098's stand-in) passes it, so that fn 5545 (api::CFormBuilder::AddProgressBar) folds the
# font parameter beside the screen as in the target: with the roots' own copy of its bytes, a scratch link with one
# object calling the screen gave our AddProgressBar seven parameters, and with this font six, the target's (unit 31's
# fragment).
CPROGRESSOENCERRAMENTO_SRCS := src/app/vota/eleitor/fimvotacao/cprogressoencerramento.cpp src/app/comum/cabstracttelaprogresso.cpp
UENUX2_SRCS += $(CPROGRESSOENCERRAMENTO_SRCS)
# nothing reconstructed references the vtable yet: 48-uenux2-cprogressoencerramento-roots.cpp takes its address, which
# keeps both destructors in the table as the target has them
$(ROOT)/$(APP)/48-uenux2-cprogressoencerramento-roots.o: $(ROOT)/src/units/48-uenux2-cprogressoencerramento-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/48-uenux2-cprogressoencerramento.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/48-uenux2-cprogressoencerramento-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/48-uenux2-cprogressoencerramento-roots.o
