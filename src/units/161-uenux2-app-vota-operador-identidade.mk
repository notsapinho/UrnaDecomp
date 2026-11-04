# uenux2 vota operador identity and biometry states, in app/vota/operador/leidentidade/ and confirmaidentidade/, and the
# vota::CLogVota members they log through. Target fns matched:
# - vota::CControlaReconhecimento's static members (confirmaidentidade/ccontrolareconhecimento.cpp, the records' file):
#   AvancaTentativa 5406 (record line 167), AtingiuLimiteTentativas 5405, AtingiuLimiteVerificacoes 5404 and
#   PrimeiraTentativa 5403;
# - the StartState of vota::CEleitorJaVotou (10642), CIdentidadeInvalida (10669), CVerificaDadoEleitor (10444) and
#   CDadoEleitorNaoConfere (10448); the ProcessInput of CEleitorJaVotou (10641) and CInformaAnoNascimentoErrado (10493),
#   thunks into binaryen's 6015, which our link forms from the two of them as the target does (matched under
#   byn$mgfn-shared$_ZN4vota15CEleitorJaVotou12ProcessInputEv); vota::CPedeIdentidade::FinishState (10678) and the exit
#   destructor of its static std::mutex (10681), its GetInst (652, below), ProcessInput (10677) and the exit destructor
#   of its static std::unique_ptr (10682, a thunk into binaryen's 3886: src/units/221-uenux2-app-comum-constructors.mk);
# - CIdentidadeInvalida::ProcessInput (10667), with 2295, the body binaryen forms from it, unit 278's 10461 and unit
#   283's 10604 (below), and vota::TextoIdentidadeInvalida (10670, below); CVerificaDadoEleitor::GetInst (2735) and its
#   statics' exit destructors (10446, 10445);
# - vota::CEleitorNaoEncontrado's slot 9 (10663) and its destructors (1907, 1689), over its new base
#   vota::IEleitorImpedidoVotar; the two destructor lines name CEleitorOptouPorVotarEmTransito's byte-identical twins
#   since that class's file (unit 104) links first (step 9 renamed them);
# - vota::IEleitorImpedidoVotar::ProcessInput (10624, slot 7 of the seven vtables): through Read() (its TU's record of
#   cinteractiveform.h:57) it goes to CPedeIdentidade::GetInst (652) on CONFIRMA when the int at +20 is 0 and on CORRIGE
#   when it is 1, the key the form's last line names; the switch's spelling is chosen;
# - two CLogVota members out of line in app/vota/log/clogvota.cpp, unit 119's file: 2097 and 4522; three more there have
#   no target index of their own (10642, 10669 and 10444 hold them inlined);
# - libc++'s std::stoul (4661), which a stand-in brings from libc++.a, and with it 4659 and 4660, 6118 (binaryen's body
#   of those two) and 7731 (as_integer_helper, `unresolved` before; its hand line went, since a generated `pair-addr`
#   line names it now).
# The classes' destructors are bodies the link matched before, under other classes' symbols, and stay so (step 9 renamed
# no line): 244 and 387 (CControlaReconhecimento, CEleitorJaVotou, CInformaAnoNascimentoErrado, CIdentidadeInvalida,
# CVerificaDadoEleitor), 448 and 765 (CDadoEleitorNaoConfere), 1537 and 3629 (CPedeIdentidade);
# CInformaAnoNascimentoErrado's StartState is 1070, matched before.
# celeitorjavotou.cpp, this unit's file, is listed in unit 104 now, ahead of celeitorencontrado.cpp: 10635 holds
# CEleitorJaVotou's GetInst and constructor, written there now, and differs in binaryen's locals with the file after it
# (unit 104's fragment has the scores). Its rows' notes stay here.
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
# - The .bss byte's name: its generated line is AvancaTentativa's own vote (`vote:1 by:5406`), and since unit 282's 10465
#   matched, which reads it and increments it, it holds without the callers+content hand line it had (a scan and
#   splat-build without that line and without 5406's and 10465's match lines keep every match), which went.
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
#   five derived classes, passing 1 for four of them and 0 for CEleitorOptouPorVotarEmTransito; 5424 passes 0, so
#   binaryen folds no constant (10635 is in the link: unit 104). It takes two
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
#   vota::CProcuraEleitor::StartState (10631) and 10635, both unit 104's, in the link. The mutex's exit
#   destructor, 10665, matches; the pointer's, 10666, is `f1959(p0, 1905392)`, a thunk into the body binaryen merged
#   from the exit destructors of the six singletons over IEleitorImpedidoVotar (10640, 10651, 10656, 10659, 10662,
#   10666), five of which 10635 creates (unit 104): 1959 and 10666 match with them. The pointer's .bss name took a
#   `callers+content` hand line while 10666 waited; with 10666 matched, two scans and splat-build without the line
#   moved no row and gave the target's sha256 (docs/reference/splat.md "Reviewing a match"), so it went: the
#   generated line (5424's votes) holds the name, with 10666's match.
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
# Not reconstructed: the other classes' GetInst and constructors but CPedeIdentidade's, CVerificaDadoEleitor's,
# CEleitorJaVotou's and CIdentidadeInvalida's (each header names the function that holds them inlined);
# CControlaReconhecimento::AvancaProximoDedo1x4 (record 187, held inlined by 10465) is written since 10465 is (below).
# Rows of these classes left for later: 10512 (CControlaReconhecimento's StartState, written, below), 10676 (written,
# below).
# Matched since: vota::IEleitorImpedidoVotar::StartState (fn 10625, slot 2 of the base and its six derived classes, in
# ieleitorimpedidovotar.cpp after the destructor, before ProcessInput: 10625 above 10624 in use band 1): the form's
# slot 2, the class's slot 9 (LogaImpedimento), vota::ApresentaFotoEleitor (fn 3616, unit 319) and `this` as the next
# state; 1 over 18 rows before steps 7 to 9, the call. Named by its vtable; its call of 3616 holds through 3616's hand
# line. The -pending.cpp that trapped it went with it.
#
# vota::CControlaReconhecimento's constructor and GetInst (target fn 1256, named by vptr-anchor) in
# ccontrolareconhecimento.cpp, in the tree's singleton form (the constructor kept out of line by clang and inlined by
# binaryen into GetInst, its one caller), with its statics' exit destructors (10515, s_inst's; 10514, s_mutex's),
# matched. The constructor calls vota::CParametrosImagemDigital::GetInst (fn 1903, unit 307) and drops its result, as
# the target's does; that the call is a statement of the constructor's body is chosen. The statics are defined after
# the file statics StartState clears and before StartState, as band 1 orders their exit destructors (10518, 10517 and
# 10516, then 10515 and 10514, then 10512: `awk -F'\t' '$1>=10511 && $1<=10518' ledger/ordinals.tsv`). Its callers in
# the link are unit 282's 10474 and 10486, which drop the result, and unit 239's 10500, which reads it; the roots stand
# in for 10425, which drops it. Before steps 7 to 9, 12 over 42 rows, operand-only. With it in the link, 5399 (unit
# 282's CInformaEleitorPodeVotar::GetInst) matched: 1256's call gave 5410's name a second vote.
# CControlaReconhecimento::StartState (10512) is written and not matched: `unresolved self-voted` on
# s_eleitoresTreinamento (@1908712), the first of the five training words, which no target function but 10512 reads or
# writes (`/usr/bin/grep -rlE 'i32\.const 1908712($|[^0-9])' build/out/splat/pieces/asm` prints 10512 alone), so its
# name has 10512's own vote only and no hand line may give it (docs/reference/splat.md, "No circular evidence"). Every
# other operand resolves, s_tentativaRegistrada through a callers+content hand line (10465 and 10425 read it; content
# cannot place a word of 1): `pnpm wasm splat-remap` on it prints `IDENTICAL` (it applies no self-vote rule), and `pnpm
# wasm score` 33 over 209 rows, operand-only. Matches rest on its votes: 10517, s_digitalRegistrada's exit destructor,
# whose name 10512 alone votes (`evidence:vote:2 by:10512`), and 10518, s_digitalCapturada's, whose name it votes with
# 10465 (unit 282). The forms, each measured on the whole link:
# - the next-state stores: SetNextState (cappstate.h) in three arms and `m_pNextState = this` in the arm without
#   biometry. The target keeps both arms' `m_form->Slot2(); this` apart; with four plain stores clang joins all four
#   into one (61 over 217, the base's), with four setter calls it sinks the two calls of SetNextState(this) into one
#   (59 over 218, with the words still one array). A call in one arm and a store in the other is the form measured that
#   keeps them apart; which arm
#   holds the store is a choice (not measured the other way round);
# - the arm without biometry first, `!TemBiometria() || !TemDedos()`: the target lays that arm's code before the one
#   that goes to CPedeDigital::GetInst (the condition written positively, 46 over 216);
# - md::CEleitor::TemBiometria out of line (unit 157's change, the form fn 10500 needs too): the target tests the
#   flag at +100 as a call's result (`i32.load8_u; if` after binaryen's inlining) where the inline accessor gives
#   `i32.const 1; i32.eq` (35 over 211, two rows);
# - the five training words five statics (ccontrolareconhecimento.h has the store order);
# - `s_tentativa = 1; s_verificacao = 1;`: clang emits these two constant stores in the reverse of the source's order
#   (wasm-objdump -d of the object, both orders), and the target stores 0x184690 first.
# Its callees match: 1823
# (vota::EhTreinamentoMesario, unit 168), 781 (the CDedo map's __tree::destroy, this object's instance, named by its
# census pair, `evidence:pair-addr`), 1393 and 2740; it reads the map's size through api::CDataMap::GetQuantidade
# (chosen name, inline).
# vota::CVerificaDadoEleitor::ProcessInput (10443), matched: on CONFIRMA the first entry's text, the log
# LogaDadoDigitadoIncompleto when it has three characters or fewer, else std::stoul (4661) against
# md::CEleitorDecorator::GetAnoNascimento (5665, unit 91) of the current voter, LogaDadoDigitadoConfere and
# CRegistraDigitalOperador::GetInst (5396), or LogaDadoDigitadoNaoConfere and CDadoEleitorNaoConfere::GetInst (its
# constructor and two forms inlined: cdadoeleitornaoconfere.h; its statics' exit destructors 10450 and 10449 match); on
# CORRIGE LogaHabilitacaoCanceladaConfirmacaoDado (2097) and CPedeIdentidade::GetInst (652). Before steps 7 to 9, 123
# over 1163 rows, operand-only. The typed year is read into a local before the compare, as the target calls std::stoul
# before GetAnoNascimento, and CLogVota::GetInst is called in each arm, which clang hoists to after the compare's
# operands, where the target has it (the form the same compare of fn 10489 measures, unit 142's fragment).
# CInformaAnoNascimentoErrado's GetInst, constructor and statics (exit destructors 10495, 10494, matched) are written
# in its file. The list below also compiles unit 142's cpedeanonascimentosembiometria.cpp, right after
# cinformaanonascimentoerrado.cpp: its 10489 holds that GetInst inlined and matches with the callee's object first,
# the two classes' order in the target's data (unit 142's fragment has the scores). Two placings give that order, and
# on whole links both give 10489 93 over 854 and the splat build the target's sha256 with every match:
# cinformaanonascimentoerrado.cpp moved into unit 142's list ahead of cpedeanonascimentosembiometria.cpp inverts 31
# object pairs the base had in the data's order (82553 inverted pairs in the whole link); this one inverts 10 (82511;
# the base's link, 82533), each object moving past the same 54 others. Pairs are read from each object's vtable and
# typeinfo addresses in splat/symbol_addrs.txt, through the link map. The 10: cpedeanonascimentosembiometria.cpp
# (@1591496 to @1591540) now after aguardaeleitor/'s cmostraeleitorvotando.cpp and cperguntacodigosuspensao.cpp (unit
# 142's), celeitordemorando.cpp, csuspensaoautomaticaeleitor.cpp, cperguntaeleitorvotando.cpp and
# cdesabilitaaudioeleitor.cpp (@1592784 to @1593308), and comum/gravadores/asn/'s cconversorversoesarquivos.cpp,
# cconversorcorrespresultado.cpp, cconversorurna.cpp and cconversorenvelopegenerico.cpp (@1596216 to @1599416).
#
# Written in ccontrolareconhecimento.cpp since, and not matched (pnpm wasm score in the whole link, and step 9's rows):
# - CControlaReconhecimento::ProcessInput (10511, slot 7, the line a choice in the blank run before the records),
#   matched since its two next-state stores call comum::CAppState::SetNextState (cappstate.h): on CONFIRMA it calls
#   LimpaBiometria (3621) and goes to CHabilitaAudioEleitor::GetInst (2743) when IsAudioAtivado (2746) says so, else
#   posts 1 to CThreadEleitor's queue and goes to CMostraEleitorVotando::GetInst (1150). With the two stores, 12 over 84
#   rows, operand-only, the queue's address in local 1 where the target reuses local 0; with the calls, 10 over 84,
#   names only (`pnpm wasm score`, whole link), and it matches (step 9). Unit 282's 3883 differs the same way and its
#   sources are not this unit's.
# - vota::MontaTelaEleitorPodeVotar (5410, a free function by choice; name chosen), the form both
#   CControlaReconhecimento::GetInst (1256) and vota::CInformaEleitorPodeVotar::GetInst (5399, unit 282)
#   fill +12 with: AddLed(LED_OPERACAO_0), AddBeep(1), "ELEITOR(A) PODE VOTAR" at {1, 1}, "Assinar o caderno de votação
#   antes de" at {1, 2}, "votar" at {1, 3} (the tail of "CONFIRMA: votar", built in place), "CONFIRMA: prosseguir" at
#   {1, 4} on the right, api::CMTFormBuilder::AddInputControl(4) (unit 31's file, inlined by binaryen behind its own
#   frame), GetInteractiveForm("", true). Its place before AvancaTentativa follows the uses-2 band (5410 links before
#   5406). 207 over 553 rows (195 operand-only, 5 inserted, 7 deleted): the target copies the builder's address into
#   another local before the inlined AddInputControl (`local.get 3; local.set 2`), ours does not; with the make_shared
#   in 5410 itself, 276 over 577; with a parameterless AddInputControl over make_shared<...>(), 219 over 563. Not
#   explained. Its second caller, 1256, is in the link, and the roots' stand-in for it went.
#
# CPedeIdentidade::GetInst (fn 652, 4609 B) is written in cpedeidentidade.cpp with the constructor (inlined by binaryen:
# its 16-byte frame follows the `new` of 32 bytes) and the statics. It matches. The end of "/{:04}" in it is, in the
# target, the tail of "{:02}/{:02}/{:04}" (8609), a literal whose start only fns 2687 and 10273 load (grep over
# build/out/splat/pieces/asm), and 2687 is in the link (unit 265's conversaodatahora.cpp). 652 is the one voter of
# s_inst's name (`_ZN4vota15CPedeIdentidade6s_instE = 0x1d12b8; // ... evidence:vote:8 by:652`), so its row read
# `unresolved self-voted +0x5 i32.const 1905336` while the target's other reader of 1905336, 10682 (below), was no
# function of our link (docs/reference/splat.md section 3, "No circular evidence"); 10682 matches now and re-points
# through that name (its row's `readings: address symbol`), and 652 matches with it. In the target's order, under a
# std::lock_guard of the static std::mutex
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
# two), read as one body binaryen keeps for three classes' identical ~unique_ptr (the three share the D2 1537). With
# 5396's static in our link (vota::CRegistraDigitalOperador's, unit 221) binaryen forms 3886 from the three, and 3886,
# 10321, 10457 and 10682 match (unit 221's fragment). Chosen: the statics' names, the lock_guard's spelling and
# EVENTO_ENTRADA | EVENTO_TICK for 6.
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
# `if`s' spelling.
#
# CPedeIdentidade::ProcessTick (10676, slot 8) is written in cpedeidentidade.cpp, after ProcessInput, a chosen line, and
# does not match. In the target's order: on the tick at +11, when IsVotacaoBloqueadaPorHorario (fn 2226) holds,
# CThreadOperador's StopTick (fn 422) of it and CLogVota::GetInst, then a 16-byte frame binaryen inlined: the member
# LogaVotacaoBloqueadaPorHorario, added to clogvota.cpp, logaAlerta (fn 1398) of "Votacao foi bloqueada por horario"
# (a literal only 10676 loads); on the tick at +12, when api::CDateTime::Now() (fn 479) is not before
# IInformacaoThreadOperador's slot 18 (GetDataHoraInspecao, called on fn 599's result; operator<=>, fn 759),
# vota::AgendaInspecao (fn 3620), Post(12) on CThreadEleitor's queue (fns 316 and 501) and vota::CAguardaInspecao's
# state, whose GetInst and constructor it holds inlined (unit 281's caguardainspecao.cpp; the one store of that vptr,
# 1590732); on the tick at +13, *m_aviso becomes "CORRIGE: outras opções" (string::__assign_external, fn 276) when the
# text of the field with the form's focus is empty, else " " (a one-character store in place); the field is read with
# std::vector::at at CInteractiveForm's +84, the index of the focus, through GetEntradaAtual, added to
# api/gui/cinteractiveform.h (its out_of_range call is fn 234). Measured with pnpm wasm score in the whole link, before
# steps 7 to 9: `96 over 510 rows (same 414, replaced 81 [80 operand-only], inserted 3, deleted 12)`, and every row
# that is no operand is in the inlined CAguardaInspecao constructor's form: the target clears the builder's 12 bytes in
# place (`i32.store[l2+44] = 0; i64.store[l2+36] = 0`) and uses the frame's address, ours calls
# api::CMTFormBuilder's constructor (fn 203's body) and keeps its result in a local, which shifts the locals after it.
# That is the remainder units 02, 104, 142 and 165 record for 4633, 10214, 1150 and 5343, GetForm's callers (fn 1694):
# not explained. The slot keeps it written (docs/how-to-decompile.md step 5); its trap went. Its row reads `unresolved`
# on CAguardaInspecao::s_inst's .bss address, which no target name holds while 10676 does not match (step 8 names the
# function by its vtable slot, which casts no vote). Chosen: the log member's name and its place in clogvota.cpp,
# GetEntradaAtual's name and result (a field pointer; an index getter with at() in ProcessTick is not measured), `>=` on
# the two times, the slot called on GetInst's result directly, the literal 12, and the `if` and `else if` spelling.
#
# CPedeIdentidade::ProcessInput (10677, slot 7) is written in cpedeidentidade.cpp, after the constructor, a chosen
# line. Read() of the form at +24; on CORRIGE (5) the next state is CEscolheOpcao::GetInst's (fn 2753); on CONFIRMA (9),
# in the training mode (comum::CAppInfo::EhTreinamentoEleitor, fn 697), the state a 16-byte frame returns, else the one
# a 32-byte frame returns, stored only when not null. Each frame is a function binaryen inlined at its one call site,
# and clang keeps both out of line (wasm-objdump -x of cpedeidentidade.cpp.o lists them): ProximoEstadoTreinamento
# (CEleitores::GetInst, fn 326, twice: the cursor's Reset, inline in api/io/cdatamap.h, and GetCurrent, fn 656; the
# voter's identity of its own type, fn 708; SetIdentidadeDigitada and SetTipoIdentidadeDigitada, fns 5414 and 3619;
# CNomeEleitor::GetInst, fn 5401) and ProximoEstadoIdentidadeDigitada (the form's first input's text copied, no state
# when it is empty; CLogVota::GetInst, then the member LogaIdentificadorDigitadoMesario held inlined, which calls
# api::CLoga::loga, fn 433, with +4, severity 1 and "Identificador do eleitor digitado pelo mesário", added to
# clogvota.cpp, unit 119's file; CHorarioVotacaoTerminou::GetInst, fn 5430, when IsVotacaoBloqueadaPorHorario, fn
# 2226; else SetIdentidadeDigitada of the text filled to 12 characters with '0', fns 753 and 5414, and
# CValidaIdentidade::GetInst, unit 278's, with its constructor inlined: the one store of that vptr, 1589072, is
# 10677's). It matches. Chosen: the two helpers' names and their result type, ProximoEstadoIdentidadeDigitada's being
# a member (it reads the form at +24) and ProximoEstadoTreinamento's a free function of vota with external linkage (it
# reads nothing of the class), the log member's name and its place in clogvota.cpp, and the switch's spelling.
#
# CIdentidadeInvalida::GetInst and its constructor have no target index: vota::CValidaIdentidade::StartState (10627,
# unit 278's, written and not matched) holds them inlined, the one store of the vptr (1588384). They are written in
# cidentidadeinvalida.cpp with the statics (s_inst @1905364, s_mutex @1905340) and the form's text function,
# vota::TextoIdentidadeInvalida (10670, `f3623(p0)`: the identifier typed, passed by its table slot 3860): the form is
# AddBeep(2), "Identidade:" at {1, 1}, 10670's text at {13, 1}, "Número errado" at {1, 2}, "CORRIGE: retornar" at
# {1, 4}, AddInputControl and GetInteractiveForm("", true), built in the member list by a helper (fn 301 writes into the
# member). In band 1, 10672 and 10671 (the statics' exit destructors, the pointer's first) lie above 10670 and 10670
# above StartState (10669): the statics are defined, the pointer first, before 10670, and 10670 before StartState,
# external, since clang defers an internal function to the end of the TU. 10670 matches (its census pair, `shape`); the
# exit destructors wait for 10627's match (unit 278's fragment). Chosen: the names, 10670's being a free function of
# vota, the helper's name and its anonymous namespace, and the constructor's and GetInst's lines above the statics.
#
# CIdentidadeInvalida::ProcessInput (10667, slot 7) is written in cidentidadeinvalida.cpp: `f2295(p0, 5, <its Read()
# record>)`, a thunk into the body binaryen merges from five states' slot 7 that go to CPedeIdentidade::GetInst's state
# on one key (2295's callers 10461, 10604, 10667, 10709 and 10757: ledger/callgraph.tsv). Our link forms 2295 from the
# same five: 10667, unit 278's 10461, unit 283's 10604 (vota::CEleitorImpedidoJustificarVotoCPF::ProcessInput, slot 7
# of the vtable @1589588 in ledger/vtables.json) and unit 277's 10709 and 10757, each written as `if (m_form->Read() ==
# <key>) m_pNextState = &CPedeIdentidade::GetInst();` (wasm-objdump -d of the link: our 2295's five callers are those
# five), and the six match. Each thunk passes its own TU's record of Read() (`readings: address same-content`), and
# step 8 names each slot by its class's vtable, so each line names its own class's member. The census's pairs among the
# five thunks are a tie and move with the link (at one landing it paired 10604 with our 10709's body): before unit
# 283's file held 10604, the census paired it with our 10667, the same thunk over the same key, and its line carried
# 10667's symbol. 10709 and 10757 matched once 10461's key, 9 against the others' 5, made binaryen pass the key as a
# parameter, as the target's 2295 does.
#
# CVerificaDadoEleitor::GetInst (2735) is written in cverificadadoeleitor.cpp with the constructor and the statics:
# s_inst @1909204 and s_mutex @1909180 (exit destructors 10446, `f389(p0, 1909204)`, and 10445), a new of 20 bytes,
# CAppState's constructor with EVENTO_ENTRADA (2), the vptr 1592720 (2735 is the one function that stores it: grep over
# build/out/splat/pieces/asm, so the vtable sink of this class went), and the form at +12 built in the constructor's one
# 96-byte frame: the voter's name (CEleitorDadoNomeParaUrna::Text) at {1, 1} with "{:2}", GetTextoIdentidadeDigitada at
# {1, 2}, "Seq:" at {32, 2}, CEleitorDadoSequencial::Text at {40, 2} with "{:04}" on the right, "Digite o ANO de
# nascimento:" at {1, 3}, AdicionaCampoNumerico(builder, 4, true, {29, 3}) (fn 1151), "CORRIGE: cancelar" at {1, 4} and
# "CONFIRMA: habilitar" at {40, 4} on the right, GetInteractiveForm("", true); no LED. It matches, with 10446 and 10445.
# The builder is a function of the file's anonymous namespace, which clang inlines into the constructor
# (cverificadadoeleitor.cpp.o has no function of its own for it), the shape of unit 239's CNomeEleitor form; the same
# code written in the constructor's body is not measured. Chosen: the builder's name and namespace, the statics' names,
# the lock_guard's spelling, and GetInst's and the statics' lines after the destructor. Its four target callers (10447,
# this unit's, and 10473, 10477 and 10485, unit 282's) are in the link, and unit 278's stand-in for them went.
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
# Matched since: vota::CDadoEleitorNaoConfere::ProcessInput (10447, srcloc-anchor on the record it holds,
# ccontrolareconhecimento.cpp:176). On CONFIRMA, when CControlaReconhecimento::AtingiuLimiteVerificacoes (5404) says
# the verifications reached their limit, CLogVota::LogaHabilitacaoCanceladaConfirmacaoDado (2097) and
# CPedeIdentidade::GetInst (652) as the next state; else CControlaReconhecimento::AvancaVerificacao, which binaryen
# inlines (a frame of its own), and CVerificaDadoEleitor::GetInst (2735). AvancaVerificacao is written at its record,
# line 176, column 15: the second counter (@1590928) compared with the parameters' numTentativasVerificacao byte (+140
# of CConfiguracaoEleicao, the compare in place: clang inlines AtingiuLimiteVerificacoes there), incremented, or else
# EUeVotaError 9398 thrown with "Limite de verificações de dado do eleitor atingido." (the enumerator's name chosen).
# Before steps 7 to 9, 19 over 109 rows, all operand-only (pnpm wasm score). CControlaReconhecimento::GetTentativa, an
# inline accessor of the first counter that vota::CPedeDigital::StartState (unit 282) reads, is chosen.
#
# Roots: three classes' vtables (CEleitorNaoEncontrado's goes: 5424 stores it; CPedeIdentidade's and
# CVerificaDadoEleitor's went: their constructors are in the link, inlined into 652 and 2735; CEleitorJaVotou's went:
# its constructor is in the link, inlined into its GetInst, which 10635 holds; CIdentidadeInvalida's went: its
# constructor is in the link, inlined into its GetInst, which unit 278's 10627 holds), and stand-ins for the target
# callers of 5403, 2097, 4522, 4661 and 652 (the roots file names them, and the callers in the link); those of 5404 to
# 5406 went, their callers 10447, 10448, 10473 and 10485 being in the link. ccontrolareconhecimento.cpp reaches Boost
# through cconfiguracaoeleicao.h, so its object takes
# the include path below, as unit 88's do.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_OPERADOR_IDENTIDADE_SRCS := src/app/vota/operador/leidentidade/cpedeidentidade.cpp \
    src/app/vota/operador/leidentidade/cidentidadeinvalida.cpp \
    src/app/vota/operador/leidentidade/celeitornaoencontrado.cpp \
    src/app/vota/operador/leidentidade/ieleitorimpedidovotar.cpp \
    src/app/vota/operador/confirmaidentidade/ccontrolareconhecimento.cpp \
    src/app/vota/operador/confirmaidentidade/cinformaanonascimentoerrado.cpp \
    src/app/vota/operador/confirmaidentidade/cpedeanonascimentosembiometria.cpp \
    src/app/vota/operador/confirmaidentidade/cdadoeleitornaoconfere.cpp \
    src/app/vota/operador/confirmaidentidade/cverificadadoeleitor.cpp
UENUX2_SRCS += $(APP_VOTA_OPERADOR_IDENTIDADE_SRCS)
# ccontrolareconhecimento.cpp includes app/comum/dados/cconfiguracaoeleicao.h, whose ecourna headers include Boost
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/confirmaidentidade/ccontrolareconhecimento.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# celeitornaoencontrado.cpp includes it too, for the identifier type the urna takes first (an include path, not a flag)
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/leidentidade/celeitornaoencontrado.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# nothing reconstructed calls the members the roots stand for: the roots file
# (161-uenux2-app-vota-operador-identidade-roots.cpp) gives those members call sites
$(ROOT)/$(APP)/161-uenux2-app-vota-operador-identidade-roots.o: $(ROOT)/src/units/161-uenux2-app-vota-operador-identidade-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/161-uenux2-app-vota-operador-identidade.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/log/*.h $(ROOT)/src/uenux2/src/app/vota/operador/confirmaidentidade/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/app/comum/log/*.h $(ROOT)/src/uenux2/src/api/uelog/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/161-uenux2-app-vota-operador-identidade-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/161-uenux2-app-vota-operador-identidade-roots.o
