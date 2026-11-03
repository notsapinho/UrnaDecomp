# uenux2 vota operador: identification states in app/vota/operador/confirmaidentidade/, a file each:
# vota::CInformaBioDesabilitadaDemo, vota::CInformaAnoDesabilitadoDemo, vota::CInformaEleitorPodeVotar,
# vota::CDigitalNaoReconhecidaPorTempo, vota::CDigitalReconhecida, vota::CDigitalNaoReconhecidaDecBiometria,
# vota::CDigitalNaoReconhecida and vota::CPedeDigital (cpededigital.cpp, unit 192's until the order below moved it
# here). Paths relative to src/uenux2. Each class header says what its layout rests on.
#
# Target fns matched:
# - CInformaBioDesabilitadaDemo::GetInst (5402), with its statics' exit destructors (10509, s_mutex's; 10510, s_inst's);
# - CInformaEleitorPodeVotar's statics' exit destructors (10497, 10499);
# - the three classes' ProcessInput (slot 7: 10508, 10504, 10496), thunks into binaryen's shared body of the three, fn
#   3883, which our link forms too, as byn$mgfn-shared$_ZN4vota27CInformaBioDesabilitadaDemo12ProcessInputEv (the first
#   member in link order); a callers+content hand line in splat/symbol_addrs.txt names it, and the three match through
#   it (without it, step 9 read each `unresolved ... byn$mgfn-shared$... has no target function`);
# - CDigitalReconhecida::StartState (10482, record cdigitalreconhecida.cpp:47);
# - CPedeDigital's destructor and deleting destructor (2739, its match line now the D1 alias, and 10469), FinishState
#   (10467, records 131 and 132) and ProcessInput (10466), as unit 192 matched them;
# - CPedeDigital::GetInst (2740, vptr-anchor) with its statics' exit destructors (10471, s_mutex's; 10472, s_inst's),
#   StartState (10468, records 115, 120 and 125) and ObtemEstadoPosReconhecimentoBiometrico (5397, record 234), which
#   holds CDigitalReconhecida's and CDigitalNaoReconhecida's GetInst inlined, with their statics' exit destructors
#   (10483 and 10484; 10475 and 10476, a thunk into 2903, unit 152's fragment has it).
#
# Evidence, each read in the target (`pnpm wasm fn` of each function):
# - The classes: RTTI and their vtables, @1591104 [244, 387, 1718, 7480, 1661, 218, 425, 10508, 425], @1591176 [... 1718
#   ... 10504 ...], @1591352 [... 1070 ... 10496 ...] and @1591640 [448, 765, 10482, 7480, 1661, 218, 425, 10481, 425].
#   The vptrs are stored by 5402, 10500 (CNomeEleitor::ProcessInput, CInformaAnoDesabilitadoDemo's GetInst and
#   constructor inlined), 5399 and 5397 alone (`/usr/bin/grep -rlE 'i32\.const <vptr>($|[^0-9])'
#   build/out/splat/pieces/asm`). Slots 0 and 1 are the shared out-of-line destructors (244 and 387 release a
#   std::shared_ptr at +12; 448 and 765 two, at +20 and +12), so each destructor is out of line, `= default`.
# - StartState: 1718 (one body with vota::CUrnaInspecionada's: the form's slot 2, then `this` as the next state) for the
#   two Demo states, 1070 (comum::CDigitalMesarioNaoReconhecida's: the other order) for CInformaEleitorPodeVotar, each
#   written so; our bodies merge with those matched ones.
# - ProcessInput: 3883 reads the form through Read() under the record its second parameter carries, and on CONFIRMA goes
#   to CHabilitaAudioEleitor::GetInst (2743, unit 152) when IsAudioAtivado (2746) says so, else posts 1 to
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
# - CDigitalReconhecida::StartState: `this` as the next state, then CPolySingleton<api::IFingerMatcher>::instance() (its
#   default argument is the record, column 22 on line 47) and, when the byte at +11 is set, std::format("Score: {}",
#   slot 4's int) moved into +12's string, then the form at +20 shown. Before steps 7 to 9, 12 over 215 rows, all
#   operand-only.
#
# - CPedeDigital (moved here from unit 192 with its notes): 84 bytes (fn 2740 allocates them and passes EVENTO_ENTRADA |
#   EVENTO_TICK, 6, to the base's constructor); its destructor is out of line, 10469 being `f2739(p0); drop; f136(p0)`
#   (docs/reference/facts/reading.md R5), and final, 2739 storing no vptr first (R4): it calls
#   api::CApplicationContext's destructor (fn 1468) for +32 and releases +24 and +16. ProcessInput is
#   CInteractiveForm<IScreenMT, IInputMT>::Read() on the form at +16 (its record, cinteractiveform.h:57 @1592168), and
#   on INPUT_CORRIGE (5) vota::CLogVota's LogaHabilitacaoCanceladaReconhecimentoBiometrico (fn 2495) and
#   vota::CCancelaHabilitacaoEleitor::GetInst (fn 1536). FinishState (10467) at its records (cpededigital.cpp:131 and
#   :132, column 5, each the start of a CPolySingleton<api::IFingerScanner>::instance() call that takes the default
#   argument): the scanner's slot 7 with 0, its slot 6, then api::CApplication::s_contextos.Pop of the context at +32
#   (5553), as unit 197's CEleitorVotando pops its own. cpededigital.h has the layout and the bytes it rests on. Its
#   lines: StartState's records 115, 120 and 125, FinishState's 131 and 132, ProcessTick's 162 to 164 (blank: pending)
#   and three private members' 234, 262 and 279 (262 and 279, VerificaDigital and VerificaDigitalTreinamento, held
#   inlined by ProcessTick, blank); the destructor (line 105) and ProcessInput (line 137) have no record: their lines
#   are a choice, in their use band's order (10469 links before StartState's 10468 and FinishState's 10467, and
#   ProcessInput's 10466 after them and before ProcessTick's 10465). CPedeDigital's destructor is declared first, so
#   that cpededigital.cpp emits its vtable (how-to step 3).
# - CPedeDigital::GetInst (2740): the project's singleton (lock_guard on s_mutex, s_inst reset with a new 84-byte
#   object, the old one deleted through the D2 2739), the constructor inlined behind a 96-byte frame of its own:
#   CAppState's with EVENTO_ENTRADA | EVENTO_TICK (6), the three tick ids CThreadOperador's AddStoppedTick returns for
#   30000, 15000 and 50 ms (+11 to +13), the forms at +16 and +24, and api::CriaContextoAplicacao(2, "Captura da digital
#   do eleitor", "Falha na captura da digital", "Ocorreu um erro durante captura da digital do eleitor.") at +32. The
#   two forms come from two helpers clang inlines, whose builders share one frame slot (+84): AddLed(LED_OPERACAO_0),
#   AddBuzz(52, 5), "Solicite que o(a) eleitor(a)" at {20, 1} and CEleitorDadoNomeParaUrna::Text with "{:2}" at {20, 2},
#   both centred, "posicione POLEGAR ou INDICADOR no sensor" at {1, 3}, "CORRIGE: cancelar" at {1, 4}, AddInputControl,
#   GetInteractiveForm("", true); then AddLed(LED_OPERACAO_0), "Por favor, aguarde." centred at {1, 2},
#   GetInteractiveForm("", true).
# - CPedeDigital::StartState (10468): CApplication::PushContext of a copy of +32; CLogVota::LogaSolicitaDigital (held
#   inlined, unit 119's file) of CControlaReconhecimento's attempt and the parameters' numTentativasHabilitacao, each a
#   byte (`i32.load8_u`); the throw of EUeVotaError 9400 at line 115 unless CConfiguracaoEleicao's biometry flag (+665)
#   is set; the form's slot 2; the finger scanner's slot 7 with 2 (record 120); StartTick of the three ticks; its slot 3
#   (record 125); `this` as the next state.
# - CPedeDigital::ObtemEstadoPosReconhecimentoBiometrico (5397, record cpededigital.cpp:234, column 22, the default
#   argument of CPolySingleton<api::IFingerScanner>::instance() after `auto& digitais = `): the scanner's slot 7 with 1
#   and CDigitalReconhecida::GetInst() as the next state when its bool is set, slot 7 with 3 and
#   CDigitalNaoReconhecida::GetInst() otherwise, then api::CSystem::Dorme(1000). Each GetInst holds its class's
#   constructor behind a frame of its own (16 and 112 bytes), the sign of a function binaryen inlined
#   (docs/reference/facts/reading.md R10): GetInst and the constructor are out of line in the class's file, a reading.
#   CDigitalReconhecida's form comes from a third frame (80 bytes) with the CTextSource's null test of ctextsource.h:37
#   left in, so its helper is out of line too: measured on the objects (wasm-objdump -d of cdigitalreconhecida.cpp.o at
#   the tree's flags), the helper with external linkage stays a function of its own, which the constructor calls, and in
#   an anonymous namespace clang inlines it. CDigitalReconhecida: +11 GetExibirScoreBiometria, +12
#   std::make_shared<std::string>(" "), +20 the form: AddLed(LED_OPERACAO_0), AddBuzz(52, 5), "ELEITOR(A)
#   RECONHECIDO(A)" at {1, 1}, a CTextSource over +12 with "%s" at {40, 1} on the right, "Não assinar o caderno de
#   votação" at {1, 2}, "CONFIRMA: prosseguir" at {40, 4} on the right, AddInputControl, GetInteractiveForm("", true).
#   CDigitalNaoReconhecida: +11 the same byte, +12 and +20 std::make_shared<std::string> of "Tentativa x de x" and " ",
#   +28 the form: AddLed(LED_OPERACAO_0), AddBeep(1), CEleitorDadoNomeParaUrna::Text with "{:2}" at {1, 1}, "Eleitor(a)
#   não reconhecido(a)" centred at {1, 2}, CTextSources over +12 (centred) and +20 (on the right) with "%s" at {1, 3},
#   "CORRIGE: cancelar" at {1, 4}, "CONFIRMA: prosseguir" at {40, 4} on the right, AddInputControl,
#   GetInteractiveForm("", true).
# - The ProcessInput of the three not-recognized states (10473, 10477, 10485): the form's Read(), and in the target's
#   block order CONFIRMA first: CVerificaDadoEleitor::GetInst (2735) as the next state (10477), or, for 10473 and 10485,
#   that state when CControlaReconhecimento's attempts reached their limit and else AvancaTentativa and
#   CPedeDigital::GetInst; CORRIGE: CLogVota's LogaHabilitacaoCanceladaReconhecimentoBiometrico (2495) and
#   CCancelaHabilitacaoEleitor::GetInst (1536). The forms are at +28, +12 and +20.
# - Before steps 7 to 9 (pnpm wasm score on this link): 2740 82 over 755 rows, 10468 40 over 369, 5397 115 over 1283,
#   all operand-only.
# - The order measured (docs/reference/facts/codegen.md C4): binaryen inlines CDigitalReconhecida's and
#   CDigitalNaoReconhecida's GetInst into 5397, and the target links both classes' objects before cpededigital.cpp's
#   (their vtables, 1591640 and 1591800, before CPedeDigital's, 1591888). With cpededigital.cpp in unit 192's list,
#   ahead of both, 5397 scored 456 over 1317 rows (inserted 34, deleted 32, local numbers); with
#   cdigitalnaoreconhecida.cpp alone ahead of it, 324 over 1296 (inserted 13, deleted 12); with both ahead, in this
#   list, 115 over 1283, operand-only. So this list holds the five files in the order of their vtables in the data, and
#   unit 192's lists csincronismoeleitor.cpp alone. The move left 2739, 10466, 10467 and 10469 matched.
#
# Written and not matched, and what each waits for:
# - CInformaEleitorPodeVotar::GetInst (5399): `unresolved self-voted` on 5410's name, whose one vote is 5399's own call
#   (`evidence:call by:5399`); 5410 is written and differs (unit 161's fragment has the rows), and 1256, its other
#   target caller, is not written. It matches once 5410 matches or 1256 is in the link.
# - 3883 itself: 10 over 83 rows against our shared body, all operand-only: the calls, the record and binaryen's local
#   numbers (the queue's address in local 2 where the target reuses local 0, the same difference as 10511's, unit 161).
# - CInformaAnoDesabilitadoDemo::GetInst, its constructor and form have no target function of their own: 10500 holds
#   them inlined and is not written, so they link nowhere (wasm-ld drops the GetInst), and its statics' exit destructors
#   (10505, 10506) read `differs`: nothing names s_mutex and s_inst, which only 10500 reads.
# - The ProcessInput of CDigitalNaoReconhecida, CDigitalNaoReconhecidaDecBiometria and CDigitalNaoReconhecidaPorTempo
#   (10473, 10477, 10485): `differs`, 13 over 78, 10 over 72 and 13 over 78 rows, every row an operand, the calls, the
#   records and two local numbers: the target keeps the input field's pointer in local 0 once `this` is pushed for the
#   store after the switch, ours in local 1. The same remainder as unit 277's 10731; in our link 10415 (unit 152), a
#   body binaryen inlines callees into, takes local 0 as the target does, and
#   app/comum/dados/md/estadoaplicacao/cestadogeralvota.h measures such a move of local numbers for SetEstadoVota. Not
#   explained: neither form measured here gives local 0 (the switch as written, and the three files linked ahead of the
#   objects of the functions they call, a scratch link).
# Pending (282-uenux2-confirmaidentidade-estados-pending.cpp says what each waits for):
# CDigitalReconhecida::ProcessInput (10481), the StartState of the three not-recognized states (10474, 10478, 10486) and
# CPedeDigital::ProcessTick (10465). CDigitalNaoReconhecidaDecBiometria's and CDigitalNaoReconhecidaPorTempo's GetInst
# and constructors are declared only: 10474 and 10465 hold them inlined.
#
# cdigitalreconhecida.cpp's, cdigitalnaoreconhecida.cpp's and cpededigital.cpp's names and directory are their records'.
# The other files' directory is a reading of the data: their vtables lie among confirmaidentidade/'s records
# (ccontrolareconhecimento.cpp's @1591028, cnomeeleitor.cpp's @1591292, cdigitalreconhecida.cpp's @1591684,
# cdigitalnaoreconhecida.cpp's @1591844). Chosen, no evidence names them: those five files' names (the class name in
# lower case); every member name; bool for the bytes; the form helpers' names (MontaTela, MontaTelaLeitura,
# MontaTelaAguarde, MontaTelaDigitalReconhecida), their being in an anonymous namespace where clang inlines them and
# MontaTelaDigitalReconhecida's external linkage (a static member of the class gives an out-of-line function too, not
# measured); the statics' lines before StartState and ProcessInput (in use band 1 their exit destructors, s_inst's
# first, link before slot 7: 10510 and 10509 above 10508, 10499 and 10497 above 10496, 10484 and 10483 above 10482,
# 10476 and 10475 above 10474, 10472 and 10471 above 10469, `awk -F'\t' '$1>=10466 && $1<=10510' ledger/ordinals.tsv`,
# so they are defined first, as unit 239's are); the local names in CDigitalReconhecida::StartState and
# ObtemEstadoPosReconhecimentoBiometrico (`digitais`, whose length puts each record's column at 22); the lines of the
# functions with no record (each file's head comment says which); cpededigital.cpp's StartState statements between its
# records' lines.
CONFIRMAIDENTIDADE_ESTADOS_SRCS := src/app/vota/operador/confirmaidentidade/cinformabiodesabilitadademo.cpp \
    src/app/vota/operador/confirmaidentidade/cinformaanodesabilitadodemo.cpp \
    src/app/vota/operador/confirmaidentidade/cinformaeleitorpodevotar.cpp \
    src/app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidaportempo.cpp \
    src/app/vota/operador/confirmaidentidade/cdigitalreconhecida.cpp \
    src/app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidadecbiometria.cpp \
    src/app/vota/operador/confirmaidentidade/cdigitalnaoreconhecida.cpp \
    src/app/vota/operador/confirmaidentidade/cpededigital.cpp
UENUX2_SRCS += $(CONFIRMAIDENTIDADE_ESTADOS_SRCS)
# cdigitalreconhecida.cpp, cdigitalnaoreconhecida.cpp and cpededigital.cpp include
# app/comum/dados/cconfiguracaoeleicao.h, whose ecourna headers include Boost (an include path, not a flag)
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/confirmaidentidade/cdigitalreconhecida.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/confirmaidentidade/cdigitalnaoreconhecida.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/confirmaidentidade/cpededigital.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# The members not reconstructed: 282-uenux2-confirmaidentidade-estados-pending.cpp gives the vtables trapping bodies,
# compiled with the unit's flags.
$(ROOT)/$(APP)/282-uenux2-confirmaidentidade-estados-pending.o: $(ROOT)/src/units/282-uenux2-confirmaidentidade-estados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/282-uenux2-confirmaidentidade-estados.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/operador/confirmaidentidade/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/282-uenux2-confirmaidentidade-estados-pending.cpp -o $(R)
# Two of the GetInst and ObtemEstadoPosReconhecimentoBiometrico have no caller reconstructed, and three classes'
# constructors are not in the link: 282-uenux2-confirmaidentidade-estados-roots.cpp stands in for those callers and
# keeps those vtables.
$(ROOT)/$(APP)/282-uenux2-confirmaidentidade-estados-roots.o: $(ROOT)/src/units/282-uenux2-confirmaidentidade-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/282-uenux2-confirmaidentidade-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/282-uenux2-confirmaidentidade-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/282-uenux2-confirmaidentidade-estados-pending.o $(APP)/282-uenux2-confirmaidentidade-estados-roots.o
