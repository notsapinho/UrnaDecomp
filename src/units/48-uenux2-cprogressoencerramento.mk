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
# (inlined into fn 12098) is not reconstructed (below). Inicia, Finaliza and Incrementa (12103, 12102, 12101, slots 2 to 4, names
# chosen in the base's header) hold the mutex over CProgressBar's SetValor and Incrementa; a std::unique_lock or
# std::scoped_lock for the std::lock_guard gives the same object code in Inicia, the one measured. Paths relative to src/uenux2; the generic uenux2 rule depends on the
# source and every uenux2 header.
# The constructor waits for the screen it takes the form and the bar from. fn 12098 holds std::make_shared of the class
# (56 bytes: the control block's vptr 1541140, then at +12 the base's vptr 1551212, the members zeroed and this class's
# vptr 1540596) and the constructor behind a 16-byte stack frame of its own (binaryen's inlining: lines 2582 to 2794 of
# pnpm wasm fn's folded readout of 12098). That frame holds two std::shared_ptrs a function returns through it, behind
# an 80-byte frame of its own: an api::CFormBuilder (fns 502, 202 and 5545 are its members) with AddStatusHeader(5),
# three text fields ("Preparando dados para encerramento", the texts at 65600 and 377563) over the fonts at 474888 and
# 474992, AddProgressBar and vota::GetFormulario (fn 886) over "telaProgressoEncerramento". The constructor then copies
# the form into +4 and the bar into +12 (each count incremented and the old pointer released: assignments from an
# lvalue, a reading) and frees the pair. That screen function is not written: no name, declaration or file of ours holds
# it, so the constructor has nothing to call yet. Its file is a reading, ctelasvota.cpp, where
# vota::TelaPreparandoDadosEncerramento (fn 6583), a screen of the same builder over "telaPreparandoDadosEncerramento",
# is written.
CPROGRESSOENCERRAMENTO_SRCS := src/app/vota/eleitor/fimvotacao/cprogressoencerramento.cpp
UENUX2_SRCS += $(CPROGRESSOENCERRAMENTO_SRCS)
# nothing reconstructed references the vtable yet: 48-uenux2-cprogressoencerramento-roots.cpp takes its address, which
# keeps both destructors in the table as the target has them
$(ROOT)/$(APP)/48-uenux2-cprogressoencerramento-roots.o: $(ROOT)/src/units/48-uenux2-cprogressoencerramento-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/48-uenux2-cprogressoencerramento.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/48-uenux2-cprogressoencerramento-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/48-uenux2-cprogressoencerramento-roots.o
