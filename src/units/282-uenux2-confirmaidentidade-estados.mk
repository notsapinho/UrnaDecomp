# uenux2 vota operador: identification states in app/vota/operador/confirmaidentidade/, a file each:
# vota::CInformaBioDesabilitadaDemo, vota::CInformaAnoDesabilitadoDemo, vota::CInformaEleitorPodeVotar and
# vota::CDigitalReconhecida. Paths relative to src/uenux2. Each class header says what its layout rests on.
#
# Target fns matched:
# - CInformaBioDesabilitadaDemo::GetInst (5402), with its statics' exit destructors (10509, s_mutex's; 10510, s_inst's);
# - CInformaEleitorPodeVotar's statics' exit destructors (10497, 10499);
# - the three classes' ProcessInput (slot 7: 10508, 10504, 10496), thunks into binaryen's shared body of the three, fn
#   3883, which our link forms too, as byn$mgfn-shared$_ZN4vota27CInformaBioDesabilitadaDemo12ProcessInputEv (the
#   first member in link order); a callers+content hand line in splat/symbol_addrs.txt names it, and the three match
#   through it (without it, step 9 read each `unresolved ... byn$mgfn-shared$... has no target function`);
# - CDigitalReconhecida::StartState (10482, record cdigitalreconhecida.cpp:47).
#
# Evidence, each read in the target (`pnpm wasm fn` of each function):
# - The classes: RTTI and their vtables, @1591104 [244, 387, 1718, 7480, 1661, 218, 425, 10508, 425], @1591176 [... 1718
#   ... 10504 ...], @1591352 [... 1070 ... 10496 ...] and @1591640 [448, 765, 10482, 7480, 1661, 218, 425, 10481, 425].
#   The vptrs are stored by 5402, 10500 (CNomeEleitor::ProcessInput, CInformaAnoDesabilitadoDemo's GetInst and
#   constructor inlined), 5399 and 5397 alone (`/usr/bin/grep -rlE 'i32\.const <vptr>($|[^0-9])'
#   build/out/splat/pieces/asm`). Slots 0 and 1 are the shared out-of-line destructors (244 and 387 release a
#   std::shared_ptr at +12; 448 and 765 two, at +20 and +12), so each destructor is out of line, `= default`.
# - StartState: 1718 (one body with vota::CUrnaInspecionada's: the form's slot 2, then `this` as the next state) for
#   the two Demo states, 1070 (comum::CDigitalMesarioNaoReconhecida's: the other order) for CInformaEleitorPodeVotar,
#   each written so; our bodies merge with those matched ones.
# - ProcessInput: 3883 reads the form through Read() under the record its second parameter carries, and on CONFIRMA
#   goes to CHabilitaAudioEleitor::GetInst (2743, unit 152) when IsAudioAtivado (2746) says so, else posts 1 to
#   CThreadEleitor's queue and goes to CMostraEleitorVotando::GetInst (1150). Each thunk passes its TU's copy of the
#   record cinteractiveform.h:57 (1591160, 1591232, 1591408), so the three classes are three TUs.
# - The GetInst: the project's singleton (lock_guard on s_mutex, s_inst reset with a new 20-byte object), the
#   constructor inlined behind a frame of its own, CAppState's with EVENTO_ENTRADA (2). GetInteractiveForm (301) writes
#   the form at +12 with no zeroing first, so the form comes from the member list, from a helper clang inlines (5402),
#   or from vota::MontaTelaEleitorPodeVotar (5410, ccontrolareconhecimento.cpp, unit 161) for CInformaEleitorPodeVotar.
#   5402's form: AddLed(LED_OPERACAO_0), "Biometria desabilitada em demonstração" at {1, 1}, "CONFIRMA: prosseguir" at
#   {1, 4}, AddInputControl, GetInteractiveForm("telaInformaBioDesabilitadaDemo", false); CInformaAnoDesabilitadoDemo's,
#   read in 10500: AddLed(LED_OPERACAO_0), "A validação do ano de nascimento" at {1, 1}, "é desabilitada em
#   demonstração" at {1, 2}, "CONFIRMA: prosseguir" at {1, 4}, AddInputControl,
#   GetInteractiveForm("telaInformaAnoDesabilitadoDemo", false). Before steps 7 to 9 (pnpm wasm score), 5402 read 36
#   over 314 rows and 5399 11 over 40, all operand-only.
# - CDigitalReconhecida::StartState: `this` as the next state, then CPolySingleton<api::IFingerMatcher>::instance()
#   (its default argument is the record, column 22 on line 47) and, when the byte at +11 is set, std::format("Score: {}",
#   slot 4's int) moved into +12's string, then the form at +20 shown. Before steps 7 to 9, 12 over 215 rows, all
#   operand-only.
#
# Written and not matched, and what each waits for:
# - CInformaEleitorPodeVotar::GetInst (5399): `unresolved self-voted` on 5410's name, whose one vote is 5399's own call
#   (`evidence:call by:5399`); 5410 is written and differs (unit 161's fragment has the rows), and 1256, its other target
#   caller, is not written. It matches once 5410 matches or 1256 is in the link.
# - 3883 itself: 10 over 83 rows against our shared body, all operand-only: the calls, the record and binaryen's local
#   numbers (the queue's address in local 2 where the target reuses local 0, the same difference as 10511's, unit 161).
# - CInformaAnoDesabilitadoDemo::GetInst, its constructor and form have no target function of their own: 10500 holds
#   them inlined and is not written, so they link nowhere (wasm-ld drops the GetInst), and its statics' exit
#   destructors (10505, 10506) read `differs`: nothing names s_mutex and s_inst, which only 10500 reads.
# Pending (282-uenux2-confirmaidentidade-estados-pending.cpp says what each waits for): CDigitalReconhecida::ProcessInput
# (10481). CDigitalReconhecida's GetInst and constructor are declared only: 5397, which holds them inlined, is not
# written.
#
# Chosen, no evidence names them: the four files' names (the class name in lower case) and their directory, which the
# data give (the vtables and records lie among confirmaidentidade/'s: ccontrolareconhecimento.cpp's records @1591028,
# cnomeeleitor.cpp's @1591292, cdigitalnaoreconhecida.cpp's @1591844; cdigitalreconhecida.cpp is the record's own);
# every member name; bool for CDigitalReconhecida's byte; the form helpers' name (MontaTela) and their being in an
# anonymous namespace; the statics' lines before StartState and ProcessInput (in use band 1 their exit destructors,
# s_inst's first, link before slot 7: 10510 and 10509 above 10508, 10499 and 10497 above 10496, `awk -F'\t' '$1>=10496
# && $1<=10510' ledger/ordinals.tsv`, so they are defined first, as unit 239's are); the local name in
# CDigitalReconhecida::StartState (`digitais`, whose length puts the record's column at 22).
CONFIRMAIDENTIDADE_ESTADOS_SRCS := src/app/vota/operador/confirmaidentidade/cinformabiodesabilitadademo.cpp \
    src/app/vota/operador/confirmaidentidade/cinformaanodesabilitadodemo.cpp \
    src/app/vota/operador/confirmaidentidade/cinformaeleitorpodevotar.cpp \
    src/app/vota/operador/confirmaidentidade/cdigitalreconhecida.cpp
UENUX2_SRCS += $(CONFIRMAIDENTIDADE_ESTADOS_SRCS)
# The members not reconstructed: 282-uenux2-confirmaidentidade-estados-pending.cpp gives the vtables trapping bodies,
# compiled with the unit's flags.
$(ROOT)/$(APP)/282-uenux2-confirmaidentidade-estados-pending.o: $(ROOT)/src/units/282-uenux2-confirmaidentidade-estados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/282-uenux2-confirmaidentidade-estados.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/operador/confirmaidentidade/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/282-uenux2-confirmaidentidade-estados-pending.cpp -o $(R)
# Two of the GetInst have no caller reconstructed, and two classes' constructors are not in the link:
# 282-uenux2-confirmaidentidade-estados-roots.cpp stands in for those callers and keeps those vtables.
$(ROOT)/$(APP)/282-uenux2-confirmaidentidade-estados-roots.o: $(ROOT)/src/units/282-uenux2-confirmaidentidade-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/282-uenux2-confirmaidentidade-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/282-uenux2-confirmaidentidade-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/282-uenux2-confirmaidentidade-estados-pending.o $(APP)/282-uenux2-confirmaidentidade-estados-roots.o
