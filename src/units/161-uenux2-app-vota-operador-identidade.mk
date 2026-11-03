# uenux2 vota operador identity and biometry states, in app/vota/operador/leidentidade/ and confirmaidentidade/, and the
# vota::CLogVota members they log through. Target fns matched:
# - vota::CControlaReconhecimento's static members (confirmaidentidade/ccontrolareconhecimento.cpp, the records' file):
#   AvancaTentativa 5406 (record line 167), AtingiuLimiteTentativas 5405, AtingiuLimiteVerificacoes 5404 and
#   PrimeiraTentativa 5403;
# - the StartState of vota::CEleitorJaVotou (10642), CIdentidadeInvalida (10669), CVerificaDadoEleitor (10444) and
#   CDadoEleitorNaoConfere (10448); the ProcessInput of CEleitorJaVotou (10641) and CInformaAnoNascimentoErrado (10493),
#   thunks into binaryen's 6015, which our link forms from the two of them as the target does (matched under
#   byn$mgfn-shared$_ZN4vota15CEleitorJaVotou12ProcessInputEv); vota::CPedeIdentidade::FinishState (10678) and the exit
#   destructor of its static std::mutex (10681), its GetInst (652) written and unresolved (below);
# - vota::CEleitorNaoEncontrado's slot 9 (10663) and its destructors (1907, 1689), over its new base
#   vota::IEleitorImpedidoVotar;
# - two CLogVota members out of line in app/vota/log/clogvota.cpp, unit 119's file: 2097 and 4522; three more there have
#   no target index of their own (10642, 10669 and 10444 hold them inlined);
# - libc++'s std::stoul (4661), which a stand-in brings from libc++.a, and with it 4659 and 4660, 6118 (binaryen's body
#   of those two) and 7731 (as_integer_helper, `unresolved` before; its hand line went, since a generated `pair-addr`
#   line names it now).
# The classes' destructors are bodies the link matched before, under other classes' symbols, and stay so (step 9 renamed
# no line): 244 and 387 (CControlaReconhecimento, CEleitorJaVotou, CInformaAnoNascimentoErrado, CIdentidadeInvalida,
# CVerificaDadoEleitor), 448 and 765 (CDadoEleitorNaoConfere), 1537 and 3629 (CPedeIdentidade);
# CInformaAnoNascimentoErrado's StartState is 1070, matched before.
#
# Evidence, each class's header says the rest (its RTTI, vtable, layout and the function that holds its inlined
# constructor):
# - The log members: 10642, 10669 and 10444 call vota::CLogVota::GetInst (fn 184, `call 184` at +0x3) and then open a
#   stack frame of their own (docs/reference/facts/reading.md R10) that builds the message and calls
#   comum::IEventosLog::logaAlerta (fn 1398), api::CLoga::loga (fn 433, +4 and severity 2) or IEventosLog::loga (fn
#   233), the shape of unit 142's three members; 2097 and 4522 are `f233(p0, <literal>)`, called as `f2097(f184())` by
#   the slots of five states and `f4522(f184())` by two slots of CRegistraDigitalOperador. 10663 calls GetInst inside
#   its own frame (`call 184` at +0xc, after the prologue), as unit 119's 10783 does: the call is written in the slot.
# - CControlaReconhecimento: AvancaTentativa's record names it static and its line; it throws EUeVotaError 9397 with
#   "Limite de tentativas atingido." (column 15). The other three have no record: they are out of line, called from
#   other classes' slots (ledger/callgraph.tsv: 5405 and 5406 by 10473 and 10485, 5404 by 10447 and 10448, 5403 twice by
#   10465), so external functions; that they are static members like AvancaTentativa is a choice. The statics: the
#   target's .data holds 1 at 0x18468c, 0x184690 and 0x184694, which StartState (10512) sets to 1 again, and its .bss a
#   byte at 0x1d1fbc that StartState and AvancaTentativa set to 0 and that AvancaProximoDedo1x4, inlined into 10465
#   under record 187, increments while it is not 4 (else it throws 9399); 10465 and 10425 index the word table at
#   0x1846a0 (1, 6, 2, 7, 3, 4, 5, 8, 9, 10) with it: the index of the finger being captured, an unsigned byte
#   (i32.load8_u, i32.store8), not a flag (10465 at +0xe62, +0xe90 and +0x104e, 10425 at +0x209). The limits are
#   CConfiguracaoEleicao's bytes at +136 and +140 (its CParametrosUrna at +88, numTentativasHabilitacao at +48 and
#   numTentativasVerificacao at +52), read with i32.load8_u: a uedword in the helper instead of the uebyte gives
#   `i32.load 2 136` in the object (wasm-objdump -d), so a uebyte holds the limit.
# - AvancaTentativa's form, measured with `pnpm wasm score` against the plain link: the counter read into a local before
#   CConfiguracaoEleicao::GetInst and the throw under `if (==)`, `39 over 59 rows (same 20, replaced 4 [2 operand-only],
#   inserted 17, deleted 18)`; the same local with the increment under `if (!=)` and the throw in the `else`, `15 over
#   44 rows (same 29, replaced 11 [10 operand-only], inserted 2, deleted 2)`, since the target calls GetInst before it
#   reads the counter; as written, `12 over 42 rows (same 30, replaced 12 [12 operand-only], inserted 0, deleted 0)`. So
#   the block order (the increment first, the throw last) and the order of the call and the read are evidence; that the
#   test is AtingiuLimiteTentativas inlined, which reads in that order, is a reading, and the column (15) puts the throw
#   one level in.
# - CEleitorNaoEncontrado: its destructor is out of line. With the implicit one, its deleting destructor frees what the
#   D2 returns, `4 over 7 rows (same 3, replaced 2 [1 operand-only], inserted 0, deleted 2)` against 1689; defaulted in
#   its .cpp, 1689 and 1907 score operand rows only and match (docs/reference/facts/reading.md R5).
# - The .bss byte's name: splat/symbol_addrs.txt's hand line cites StartState (10512), which clears it, 10465, which
#   reads it and increments it, and 10425, which reads it; its generated line is AvancaTentativa's own vote, so without
#   the hand line 5406 is `unresolved self-voted`.
#
# IEleitorImpedidoVotar's destructor (1257): the target's is a thunk into binaryen's fn 2902 with the class's vptr, a
# body the target forms from four thunks (1257, 1688, 1720 and 1952). It matches with unit 169's 1720 and 1952 in the
# link: binaryen then merges the three into one body, which unit 169 matches as 2902, and ours is the same thunk
# (`f3388(p0, 1391348)` on that link). Alone, ours was a whole body and `differs`. 1688 is
# vota::IConfirmaJustificativa's D2 (unit 174), the fourth thunk. 1907 and 1689 call it and match through its `vtable`
# name.
#
# vota::IEleitorImpedidoVotar's constructor and vota::CEleitorNaoEncontrado's singleton, measured in the whole link with
# pnpm wasm score before steps 7 to 9:
# - The constructor (fn 1905, matched, named by `call` from 5424), out of line in ieleitorimpedidovotar.cpp, above the
#   destructor (a choice: no band holds both). Its callers are 5424 and 10635, which calls it five times, for the other
#   five derived classes, passing 1; 5424 passes 0, so binaryen folds no constant (in our link the call that passes 1
#   is unit 243's stand-in for 10635). It takes two
#   std::function<std::string()> by value (a choice: const& was not tried; the body copies each into the builder's
#   AddTextField over a std::function, fn 5419, which the target does too) and the int at +20, which it stores before it
#   clears the form member at +12 and reads back for the switch; the form: AddLed(0), the identity typed (table slot 3907, fn
#   10586) at {1, 1}, the two functions' texts at {1, 2} and {1, 3}, then "CONFIRMA: retornar" at {40, 4} aligned right
#   for 0 or "CORRIGE: retornar" at {1, 4} for 1, AddInputControl, and GetInteractiveForm("", true) assigned to +12 in
#   the body (the target clears the member first, then moves the result in): 28 over 562 rows, all operand rows.
# - CEleitorNaoEncontrado::GetInst (fn 5424, matched, named by vptr-anchor), with the constructor, which passes
#   &TextoNaoCadastrado, &TextoVazio and 0 (the table slots 3867 and 3868 the target stores in the two
#   __func<std::string (*)(), std::string ()>), and the statics (the pointer at 1905392, the mutex at 1905368): 15 over
#   116 rows, all operand rows, with the constructor above GetInst or below it. Its callers are
#   vota::CProcuraEleitor::StartState (10631, unit 104) and 10635, which unit 243's roots stand in for. The mutex's exit
#   destructor, 10665, matches; the pointer's, 10666, is `f1959(p0, 1905392)`, a thunk into the body binaryen merged
#   from the exit destructors of the six singletons over IEleitorImpedidoVotar (10640, 10651, 10656, 10659, 10662,
#   10666), five of which 10635 creates: it waits for them, and the pointer's .bss name rests on a `callers+content` hand
#   line in splat/symbol_addrs.txt (10666 reads it; without the line 5424 reads `unresolved self-voted`).
# - TextoNaoCadastrado (fn 10664, written, `differs`): "CPF não encontrado. Digite o Título." when the identity typed
#   is a CPF (GetTipoIdentidadeDigitada, 5416, is 2) and comum::CConfiguracaoEleicao's GetTipoIdentificadorPrincipal (the
#   word at +668) is 1, else "NÃO CADASTRADO nesta urna"; both calls come before either test, as two locals. The target
#   builds each literal in a return path of its own, the first storing the pointer and the size before the bytes, and
#   ours sinks both paths' stores into one tail: 34 over 85 rows, 9 inserted, 3 deleted. No form tried keeps two
#   return paths in the object (wasm-objdump -d of try objects): the test inverted, explicit std::string returns, a
#   conditional of two std::string or of the two const char*, a const char* local, a std::string assigned in the
#   branches, an early return with the second a named local, external or internal linkage, and as written at -O2, -Os
#   and -Oz. Not explained. Its band, 1, gives its place: 10666 and 10665 (the statics' exit destructors),
#   10664, then 10663 (LogaImpedimento) in link order, so the statics are defined above it, and it is external, since
#   clang defers an internal function to the end of the TU. Its one caller is 5424 (by table slot 3867): its name is a
#   `callers+content` hand line resting on its own body, the one target function that loads its two literals; without
#   the line 5424 reads `unresolved self-voted`.
# - TextoVazio (fn 3628, matched, named by pair-fingerprint): " ", the body the target holds once for three table slots
#   (3868, 3877 and 3896: this class's line 3 and two of the siblings' 10635 builds), matched from this object; its
#   being a function of the file's anonymous namespace is a choice, as are the two functions' names, TextoNaoCadastrado's
#   being a free function of namespace vota, the statics' names and the parameters' names.
# celeitornaoencontrado.cpp includes cconfiguracaoeleicao.h, so it takes the Boost include path, as
# ccontrolareconhecimento.cpp does.
#
# Not reconstructed: the other classes' GetInst and constructors but CPedeIdentidade's (each header names the function
# that holds them inlined);
# CControlaReconhecimento::AvancaVerificacao and AvancaProximoDedo1x4 (records 176 and 187, held inlined by 10447 and
# 10465, which are pending or not written), whose lines stay blank; the slots the -pending.cpp traps, with what each
# waits for. Rows of these classes left for later: 10512 (CControlaReconhecimento's StartState), 10667, 10443, 10447,
# 10677, 10676, 10625 and 10624 (pending).
#
# Written in ccontrolareconhecimento.cpp since, and not matched (pnpm wasm score in the whole link, and step 9's rows):
# - CControlaReconhecimento::ProcessInput (10511, slot 7, the line a choice in the blank run before the records): on
#   CONFIRMA it calls LimpaBiometria (3621) and goes to CHabilitaAudioEleitor::GetInst (2743) when IsAudioAtivado (2746)
#   says so, else posts 1 to CThreadEleitor's queue and goes to CMostraEleitorVotando::GetInst (1150). 12 over 84 rows,
#   all operand-only: the calls, the record and binaryen's local numbers, the queue's address in local 1 where the
#   target reuses local 0 (`differs +0x86 target +0x85 local.tee 0 | ours +0x85 local.tee 1`). The same as a ternary
#   with the post in a comma expression (12 over 84); with the condition negated and the arms swapped, 18 over 88 (4
#   inserted, 3 deleted). Not explained; unit 282's 3883 differs the same way. Its slot keeps it written.
# - vota::MontaTelaEleitorPodeVotar (5410, a free function: it reads no state; name chosen), the form both
#   CControlaReconhecimento::GetInst (1256, not written) and vota::CInformaEleitorPodeVotar::GetInst (5399, unit 282)
#   fill +12 with: AddLed(LED_OPERACAO_0), AddBeep(1), "ELEITOR(A) PODE VOTAR" at {1, 1}, "Assinar o caderno de votação
#   antes de" at {1, 2}, "votar" at {1, 3} (the tail of "CONFIRMA: votar", built in place), "CONFIRMA: prosseguir" at
#   {1, 4} on the right, api::CMTFormBuilder::AddInputControl(4) (unit 31's file, inlined by binaryen behind its own
#   frame), GetInteractiveForm("", true). Its place before AvancaTentativa follows the uses-2 band (5410 links before
#   5406). 207 over 553 rows (195 operand-only, 5 inserted, 7 deleted): the target copies the builder's address into
#   another local before the inlined AddInputControl (`local.get 3; local.set 2`), ours does not; with the make_shared
#   in 5410 itself, 276 over 577; with a parameterless AddInputControl over make_shared<...>(), 219 over 563. Not
#   explained. The roots' TelaPodeVotar stands for 1256, its second caller. Since 5399's call is the only vote for its
#   name, 5399 reads `unresolved self-voted` until 5410 matches or 1256 is in the link.
#
# CPedeIdentidade::GetInst (fn 652, 4609 B) is written in cpedeidentidade.cpp with the constructor (inlined by binaryen:
# its 16-byte frame follows the `new` of 32 bytes) and the statics, and is `unresolved` on a name, not on its bytes.
# The end of "/{:04}" in it is, in the target, the tail of "{:02}/{:02}/{:04}" (8609), a literal whose start only fns
# 2687 and 10273 load (grep over build/out/splat/pieces/asm); with 2687 in the link (unit 265's conversaodatahora.cpp)
# pnpm wasm splat-remap prints `target 652: IDENTICAL` against our GetInst. Its row reads `unresolved self-voted +0x5
# i32.const 1905336: _ZN4vota15CPedeIdentidade6s_instE = 0x1d12b8 (evidence:vote:8 by:652)`: 652 is the one voter of
# s_inst's name (docs/reference/splat.md section 3, "No circular evidence"), and the target's other reader of 1905336,
# 10682 (below), is no function of our link. In the target's order, under a std::lock_guard of the static std::mutex
# (the bytes show its unlock, fn 150, at the end): on the first call the object
# (CAppState's constructor with EVENTO_ENTRADA | EVENTO_TICK, 6), the three ticks through CThreadOperador::GetInst
# (fn 270) and AddStoppedTick (fn 807) with 60000, 5000 and 1000, the std::make_shared<std::string>(" ") at +16, the
# form at +24 from vota::MontaTelaPedeIdentidade(m_aviso) (by value: the copy at +8 of the constructor's frame moved to
# +0; unit 51's telasoperador.cpp, where the reasons it is another object are), then vota::AgendaInspecao (fn 3620,
# unit 50) in the constructor's body; then the unique_ptr's reset (the old object through its D2, fn 1537, and
# operator delete) and the mutex's unlock. GetInst is defined before the constructor, an order measured with the
# screens' (unit 51's fragment: binaryen's choice of locals turns on it); that both come after FinishState is a choice
# (above StartState they give the same rows), and the lines are free. The statics are defined before StartState: their
# exit destructors (10682, s_inst's, and 10681, s_mutex's) sit above StartState (10680) in band 1. 10681 matches (its
# body's content; s_mutex is named by 652's votes, the one other reader of 1905312). 10682 is `f3886(1905336)`: 3886 is
# called by 10321, 10457 and 10682, the exit destructors of three static std::unique_ptr (10313 and 5396 read the other
# two), read as one body binaryen keeps for three classes' identical ~unique_ptr (the three share the D2 1537); our link
# holds two of the three statics (10313's, unit 135's CPedeDigitalMesario::s_inst, but not 5396's), and 3886, 10321 and
# 10682 stay no-candidate. Chosen: the statics' names, the lock_guard's spelling and EVENTO_ENTRADA | EVENTO_TICK for 6.
#
# CPedeIdentidade::StartState (10680, slot 2) is written in cpedeidentidade.cpp, its records on lines 62 and 63 (the
# CPolySingleton<IUrna>::instance() call of the `if` and CPolySingleton<IScreenMT>::instance()'s inside it, both at
# column 9); FinishState moved below it, a choice. In the target's order it logs "Aguardando digitação do
# identificador do eleitor" (CLogVota::GetInst, then a 16-byte frame binaryen inlined: the member
# LogaAguardandoIdentificadorEleitor, added to clogvota.cpp with CLoga::loga, fn 433, severity 1, the shape of
# LogaAguardandoHorarioZeresima), calls IInformacaoThreadOperador's slot 20 (LimpaIdentidades) on its GetInst (fn 599),
# shows the form at +24, sets the next state, calls IScreenMT's slot 19 with 0 when IUrna's Modelo() is at least 2020,
# calls comum::CInfoMTLCD::MostraIconeBateria on CInfoMTLCD::GetInst() (2284, unit 153's file), starts the tick at +11
# unless vota::EhTreinamento() or IsVotacaoBloqueadaPorHorario() (1485, 2226), and the ticks at +12 and +13 unless
# comum::CAppInfo::EhTreinamentoEleitor() (697). It scored 29 over 149 rows, all operand-only (pnpm wasm score, before
# steps 7 to 9). Chosen: the log member's name and its place in clogvota.cpp (binaryen inlined it: no index orders it),
# `>= 2020`, the slot called directly on GetInst's result rather than through a vota:: function over it, and the two
# `if`s' spelling. ProcessTick (10676) stays pending: the pending file says what it waits for.
#
# Chosen, no evidence names them: the names of the three helpers, of the statics and of every data member, and their
# types where only a width shows (int for the 32-bit counters), and uebyte as the spelling of the byte's unsigned 8-bit
# type, which the target gives: the reads that index the table load it with i32.load8_u before the shift (10465 at
# +0xe90, 10425 at +0x209), where a signed char gives i32.load8_s, and 10465's increment and its bound of 4 make it a
# counter, not a flag; the CLogVota members' names (from their messages) and their place, after GetInst;
# IEleitorImpedidoVotar's slot 9 name (LogaImpedimento, from the one override, which logs) and its +20 int;
# CPedeIdentidade's +16 member's name (m_aviso: its pointee is a std::string, which ProcessTick, fn 10676, assigns);
# GetInst and the private constructors, declared and not defined (but CPedeIdentidade's); the destructors declared
# first. The lines:
# AvancaTentativa's throw is on its record's line, the statics and the destructor above it and the helpers after line
# 187 are a choice, and so is FinishState after StartState's two record lines. Same bytes: CDadoEleitorNaoConfere's
# StartState as written and with a conditional operator choosing the form (its object's function, wasm-objdump -d). The
# paths: cpedeidentidade.cpp and ccontrolareconhecimento.cpp are the records'; every other class is in a file named
# after it (how-to step 3, rule 4), its header beside it, in the directory its vtable's neighbours give
# (docs/reference/facts/placing.md P5): CIdentidadeInvalida (@1588376), CEleitorNaoEncontrado (@1588448) and
# CEleitorJaVotou (@1588804) lie between cpedeidentidade.cpp's records (@1588276) and celeitorencontrado.cpp's
# (@1588980); IEleitorImpedidoVotar (@1589136) has celeitorencontrado.cpp's record before it and
# justificativa/iconfirmajustificativa.cpp's (@1589992) after it, with unrecorded vtables between on both sides, and
# goes beside the six classes derived from it, a choice; CInformaAnoNascimentoErrado (@1591424) lies between
# cnomeeleitor.cpp's records (@1591336) and cdigitalreconhecida.cpp's (@1591684); CDadoEleitorNaoConfere (@1592640) and
# CVerificaDadoEleitor (@1592712) after cregistradigitaloperador.cpp's records (@1592596) with no vtable between, and
# unrecorded vtables between them and aguardaeleitor/cmostraeleitorvotando.cpp's records (@1593044): the adjacent side.
# The order of the sources below follows the data, leidentidade's before confirmaidentidade's.
#
# Roots: six classes' vtables (CEleitorNaoEncontrado's goes: 5424 stores it; CPedeIdentidade's went: its constructor is
# in the link, inlined into 652), and stand-ins for the target callers of 5403 to 5406, 2097, 4522, 4661 and 652 (the
# roots file names them; 652's other caller in the link is unit 71's 10430). ccontrolareconhecimento.cpp reaches Boost
# through cconfiguracaoeleicao.h, so its object takes
# the include path below, as unit 88's do.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_OPERADOR_IDENTIDADE_SRCS := src/app/vota/operador/leidentidade/cpedeidentidade.cpp \
    src/app/vota/operador/leidentidade/cidentidadeinvalida.cpp \
    src/app/vota/operador/leidentidade/celeitorjavotou.cpp \
    src/app/vota/operador/leidentidade/celeitornaoencontrado.cpp \
    src/app/vota/operador/leidentidade/ieleitorimpedidovotar.cpp \
    src/app/vota/operador/confirmaidentidade/ccontrolareconhecimento.cpp \
    src/app/vota/operador/confirmaidentidade/cinformaanonascimentoerrado.cpp \
    src/app/vota/operador/confirmaidentidade/cdadoeleitornaoconfere.cpp \
    src/app/vota/operador/confirmaidentidade/cverificadadoeleitor.cpp
UENUX2_SRCS += $(APP_VOTA_OPERADOR_IDENTIDADE_SRCS)
# ccontrolareconhecimento.cpp includes app/comum/dados/cconfiguracaoeleicao.h, whose ecourna headers include Boost
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/confirmaidentidade/ccontrolareconhecimento.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# celeitornaoencontrado.cpp includes it too, for the identifier type the urna takes first (an include path, not a flag)
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/leidentidade/celeitornaoencontrado.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# The members not reconstructed: 161-uenux2-app-vota-operador-identidade-pending.cpp gives the vtables trapping bodies,
# compiled with the unit's flags
$(ROOT)/$(APP)/161-uenux2-app-vota-operador-identidade-pending.o: $(ROOT)/src/units/161-uenux2-app-vota-operador-identidade-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/161-uenux2-app-vota-operador-identidade.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/operador/leidentidade/*.h $(ROOT)/src/uenux2/src/app/vota/operador/confirmaidentidade/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/161-uenux2-app-vota-operador-identidade-pending.cpp -o $(R)
# nothing reconstructed references the eight classes or calls the members the roots stand for: the roots file
# (161-uenux2-app-vota-operador-identidade-roots.cpp) takes the vtables' addresses and gives those members call sites
$(ROOT)/$(APP)/161-uenux2-app-vota-operador-identidade-roots.o: $(ROOT)/src/units/161-uenux2-app-vota-operador-identidade-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/161-uenux2-app-vota-operador-identidade.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/log/*.h $(ROOT)/src/uenux2/src/app/vota/operador/confirmaidentidade/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/app/comum/log/*.h $(ROOT)/src/uenux2/src/api/uelog/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/161-uenux2-app-vota-operador-identidade-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/161-uenux2-app-vota-operador-identidade-pending.o $(APP)/161-uenux2-app-vota-operador-identidade-roots.o
