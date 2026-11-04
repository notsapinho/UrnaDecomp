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
#   (10483 and 10484; 10475 and 10476, a thunk into 2903, unit 152's fragment has it);
# - the ProcessInput of the three not-recognized states (10473, 10477, 10485), whose next-state stores call
#   comum::CAppState::SetNextState (cappstate.h): with the stores, 13 over 78, 10 over 72 and 13 over 78 rows, the input
#   field's pointer in local 1 where the target keeps local 0; with the calls, 11 over 78, 8 over 72 and 11 over 78,
#   names only (pnpm wasm score on the whole link), and step 9 matches them;
# - CDigitalReconhecida::ProcessInput (10481) and CPedeDigital::ProcessTick (10465), below, with what they hold:
#   CDigitalNaoReconhecidaPorTempo's GetInst and constructor (no target function: 10465 holds them inlined) and its
#   statics' exit destructors (10487, s_mutex's; 10488, s_inst's), which match through the names 10465's votes give;
#   2223, std::map<uebyte, int>'s __tree::destroy, cpededigital.cpp.o's instance; 6269, musl's log2f (below).
#   10465 and its callees 2742 (unit 307's) and 2223 hold each other: the two callees' names are `call by:10465` only,
#   and splat-build without 2742's or 2223's match line refuses 10465 as self-voted, so the three land or leave
#   together.
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
# Matched since: CInformaAnoDesabilitadoDemo::GetInst, its constructor and form, which have no target function of their
# own: fn 10500 (unit 239's CNomeEleitor::ProcessInput) holds them inlined, and the statics' exit destructors (10505,
# s_mutex's; 10506, s_inst's) match through the names 10500's votes give the statics. 10500 needs this file's object
# ahead of cnomeeleitor.cpp's, so this list compiles unit 239's two files after it (below).
#
# Written and not matched, and what each waits for:
# - 3883 itself: 10 over 83 rows against our shared body, all operand-only: the calls, the record and binaryen's local
#   numbers (the queue's address in local 2 where the target reuses local 0, the same difference as 10511's, unit 161).
# CInformaEleitorPodeVotar::GetInst (5399) matches since unit 161's CControlaReconhecimento::GetInst (1256) is in the
# link: before, 5410's name had 5399's own call as its one vote and 5399 read `unresolved self-voted`.
#
# The StartState of the three not-recognized states, matched (pnpm wasm score before steps 7 to 9, then step 9):
# - CDigitalNaoReconhecidaPorTempo's (10486): `this` as the next state; "Tentativa {} de {}" formatted into +12's string
#   from CControlaReconhecimento::GetInst().GetTentativa() and GetInst().GetLimiteTentativas() (the target calls GetInst
#   before each read and drops its result; ccontrolareconhecimento.h says why both are static members and the second
#   is out of line), both unsigned (argument code 6 twice); CLogVota's LogaTimeoutReconhecimentoDedo (unit 119's file);
#   the form at +20 shown. 26 over 397 rows, operand-only.
# - CDigitalNaoReconhecidaDecBiometria's (10478): `this`, the form shown, then LogaErroDecifracaoBiometria (a chosen
#   name, in the class's file, external, kept out of line by clang and inlined by binaryen behind its 432-byte frame),
#   which holds TemErroDecifracaoBiometria (a chosen name, inlined by clang) and logs "Erro ao decifrar a biometria do
#   eleitor - Código ({})" through comum::IEventosLog::logaErro (2282) in one expression, the code formatted through
#   its enum's handle (cbiometriaeleitor.h). With a named CBiometriaEleitor and the message in a local, 38 over 285 rows
#   (the format argument's copy in another frame slot and CLogVota::GetInst called after the format, where the target
#   calls it before the second GetCurrentBiometriaEleitor); in one expression, 21 over 284, operand-only.
# - CDigitalNaoReconhecida's (10474, record :82 column 22, the line of its instance call): `this`; when
#   TemErroDecifracaoBiometria (behind a 48-byte frame: binaryen's inlining of this TU's one call) says so,
#   CDigitalNaoReconhecidaDecBiometria::GetInst, with its constructor and form behind an 80-byte frame (its statics' exit
#   destructors 10480 and 10479 match); else the attempt's text into +12, "Score: {}" into +20 when +11 says so (as
#   10482 does), LogaTentativaReconhecimentoDedo and the form at +28 shown. 92 over 1148 rows, operand-only. The
#   function's lines from 73 put the record's call at line 82, and ProcessInput after it (the band: 10474 before 10473).
# CDigitalNaoReconhecidaDecBiometria's GetInst and constructor are written in its file (its notes in its header), and
# so are CDigitalNaoReconhecidaPorTempo's, which 10465 holds inlined: GetInst in the singleton form, the constructor
# (behind a 96-byte frame there) passing EVENTO_ENTRADA, std::make_shared<std::string>("Tentativa x de x") at +12 and
# the form at +20 from an anonymous-namespace helper clang inlines: AddLed(LED_OPERACAO_0), AddBeep(1),
# CEleitorDadoNomeParaUrna::Text with "{:2}" at {1, 1}, "Eleitor(a) não reconhecido(a)" centred at {20, 2}, a
# CTextSource over +12 with "%s" centred at {20, 3}, "CORRIGE: cancelar" at {1, 4}, "CONFIRMA: retornar" at {40, 4} on
# the right, AddInputControl, GetInteractiveForm("", true). Its statics are defined before StartState (band 1: 10488 and
# 10487 above 10486).
#
# CDigitalReconhecida::ProcessInput (10481, slot 7), matched: on CONFIRMA (Read() inlined, its record
# cinteractiveform.h:57 @1591712), CHabilitaAudioEleitor::GetInst as the next state when IsAudioAtivado says so, else
# the post of 1 to CThreadEleitor's queue and CMostraEleitorVotando::GetInst (SetNextState in both arms, 10511's form);
# then impl::IInformacaoThreadOperador's slot 13 (SetBiometriaEleitor; iinformacaothreadoperador.h reads slots 9 to 15)
# and CLogVota::LogaTipoHabilitacaoEleitor(1) (clogvota.cpp), which the target holds behind a 400-byte frame: a
# std::map<uebyte, std::string> {{1, "biométrica"}, {2, "por código"}} built from an initializer list (the hinted
# insert 3266, called twice), its at(1) formatted into "Tipo de habilitação do eleitor [{}]", and the map destroyed
# (2499); the `#include <map>` that member needs takes the place of clogvota.cpp's blank line before `namespace vota {`,
# so its records keep their lines. 34 over 421 rows before steps 7 to 9, operand-only. Its callees needed two things:
# 3266's target copy is one a
# uenux2 object builds without strict aliasing (it loads a pointer again after a store), which
# clogvota.cpp's copy, under app/vota/, does not give (15 over 101 rows, 5 deleted) and an instance at UENUX2_CXXFLAGS
# does (2 over 101, the calls), so src/app/roots_set.cpp holds that instance (its comment says for whom); and 2499, a
# recursive map destroy whose one other caller is not written and whose caller here casts no vote, takes a
# callers+content hand line in splat/symbol_addrs.txt. The key type (one byte: the pairs' keys are i32.store8 stores),
# the member's name and parameter, and the direct call of slot 13 where a free wrapper (iinformacaothreadoperador.h)
# gives the same code, are chosen.
#
# CPedeDigital::ProcessTick (10465, slot 8), matched: on a tick that is none of its three it returns; on the first in
# the first attempt or the second in a later one (CControlaReconhecimento::PrimeiraTentativa, 5403, called twice), it
# stops the ticks (PararTicks) and goes to CDigitalNaoReconhecidaPorTempo::GetInst; on the third, after the detection,
# scanner and urna singletons (records 162 to 164), it takes up to three captures from the scanner's slot 4 (each
# checked against slot 0's size), keeps one at once on the urna models 2009, 2010, 2020 and 2022 (IUrna::Modelo, called
# before each compare) and otherwise keeps the one of highest entropy (CalculaEntropia) above 4, returning on one below;
# then, when the detection's slot 2 accepts it, it shows the second form, logs LogaDigitalCapturada (clogvota.cpp) and
# runs VerificaDigitalTreinamento in the mesarios' training or else, after InvertColors (models up to 2019) and
# VerticalFlip, unit 307's CConversorWsq, a std::make_shared copy of its result, RegistraDigitalCapturada and
# VerificaDigital; each path ends in ObtemEstadoPosReconhecimentoBiometrico (5397) and SetQualidadeCapturada. Before
# steps 7 to 9, 162 over 1992 rows, operand-only (pnpm wasm score on the whole link); step 9 then read it `unresolved
# self-voted` on s_qualidadeCapturada, which matches with that word's callers+content hand line (10425 reads it). The
# forms the bytes asked for, each measured on the whole link:
# - CalculaEntropia a function of its own with external linkage in cpededigital.cpp: the target holds it behind a
#   16-byte frame, binaryen's inlining into its one caller (an internal one clang would inline: a reading); it takes the
#   shared_ptr by reference, since the target reloads the vector through it after the counting loop, and returns
#   `-soma` (the target adds each p * log2(p) and negates once). Its name, its being free and its line are chosen;
# - musl's log2f (6269) has two target callers, 10316 and 10465, and with 10465 its one caller binaryen inlined it, so
#   unit 282's roots called it for 10316 (with that and the next form together, 995 over 2258 rows became 352 over 2059)
#   until 10316 was written (unit 135): with both callers in the link the stand-in went, and 6269 still matches;
# - the best image kept by `imagem = api::TSharedImageVector(captura)`: the copy-assignment `imagem = captura` there
#   stays a call of libc++'s operator= (wasm-objdump -d of the object: one call, and none with the temporary), which
#   keeps the image in the frame where the target holds it in locals and calls the out-of-line ~shared_ptr (424) of a
#   temporary instead. The temporary is a form chosen for those bytes; the first branch's plain assignment is inlined
#   either way;
# - api::IFingerMatcher::Slot3 returning an int the call drops (the target's `(i32 i32 i32)->(i32)` and `drop`), and
#   DigitalReconhecidaTreinamento building the four sums in order (the target loads each sixth after the test before
#   it; with the sums first, all four loads came first): together, 352 over 2059 became 335 over 2044;
# - DigitalReconhecidaTreinamento reading the voter's number itself (the target reads it after the matcher's instance),
#   and GetMinuciasDedoCorrente's copy made in one expression, so that both temporaries are destroyed after it (the
#   target copies before it destroys them): together, 174 over 1998 (6 inserted, 4 deleted);
# - that copy a std::vector<api::SXYT>, the CDedo's vector through its copy constructor, which zeroes the result before
#   it reads the source as the target does, where a std::vector<uebyte> built from the two pointers reads them first:
#   162 over 1992, operand-only. This needs md::CDedo::GetMinucias (cdedo.h);
# - unit 307's stand-ins for the callers of 2224, 2742 and 1379 that are not written (unit 307's roots say which).
# VerificaDigital and VerificaDigitalTreinamento's lines put their instance calls on records 262 and 279 (column 25
# inside the loop, 21 in the function), and the three ProcessTick's on 162 to 164 (the variables' names' lengths give
# the columns 27, 26 and 23); the other lines of the three are chosen. ObtemDuasVezes, the roots' stand-in for 10465's
# two calls of 5397, went with it, and so did the sink of CDigitalNaoReconhecidaPorTempo's vtable.
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
# This list also compiles unit 239's cnomeeleitor.cpp and cnomeeleitorauxiliares.cpp, after
# cinformaanodesabilitadodemo.cpp and before cinformaeleitorpodevotar.cpp, the order of the classes' vtables in the
# target's data (@1591104, @1591176, CNomeEleitor's @1591248, @1591352): unit 239's fn 10500 holds
# CInformaAnoDesabilitadoDemo::GetInst inlined and reads 172 over 1736 rows, all operand rows, with this file's object
# ahead of cnomeeleitor.cpp's, 335 over 1748 the other way (src/units/239-uenux2-cnomeeleitor.mk has the measurement
# and the four pairs of objects the move inverts). 3883's merge name stays CInformaBioDesabilitadaDemo's, the first of
# the three in link order.
CONFIRMAIDENTIDADE_ESTADOS_SRCS := src/app/vota/operador/confirmaidentidade/cinformabiodesabilitadademo.cpp \
    src/app/vota/operador/confirmaidentidade/cinformaanodesabilitadodemo.cpp \
    src/app/vota/operador/confirmaidentidade/cnomeeleitor.cpp \
    src/app/vota/operador/confirmaidentidade/cnomeeleitorauxiliares.cpp \
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
# Every slot of these classes is written: the -pending.cpp that trapped CDigitalReconhecida::ProcessInput and
# CPedeDigital::ProcessTick went with them. Two callees have a caller not reconstructed (5399's 10451, 6269's 10316):
# 282-uenux2-confirmaidentidade-estados-roots.cpp stands in for those callers; it keeps no vtable.
$(ROOT)/$(APP)/282-uenux2-confirmaidentidade-estados-roots.o: $(ROOT)/src/units/282-uenux2-confirmaidentidade-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/282-uenux2-confirmaidentidade-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/282-uenux2-confirmaidentidade-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/282-uenux2-confirmaidentidade-estados-roots.o
