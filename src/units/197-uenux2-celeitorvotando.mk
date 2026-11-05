# uenux2 vota::CEleitorVotando in src/app/vota/eleitor/celeitorvotando.cpp, the file the class's records name, with its
# head (celeitorvotando.h, which says what the layout rests on); the objects of the vota application that the voting
# states share, in src/app/vota/eleitor/comum/cinformacaoeleitor.{h,cpp}, with the votes' class comum::md::CCedula in
# src/app/comum/dados/md/rdv/ccedula.{h,cpp}; the five vota::CLogVota members the votes are logged with, in
# app/vota/log/clogvota.cpp (in unit 104's list; unit 119's fragment gives its object Boost's include path); and unit
# 116's cthreadoperador.cpp, listed here (below).
#
# Matched, by object (target fns):
# - celeitorvotando.cpp: GetInst 3229 with the constructor inlined, its statics' exit destructors 7416 (s_inst) and
#   7405 (s_mutex), the D2 2483 and D0 7385, StartState 7377 (slot 2) with IniciaCiclo inlined, NeedChangeState 7352
#   (slot 3), FinishState 7370 (slot 5), RegistraVoto 4471, the free MostraCargoNoOperador 4464,
#   ChamaEstadoProximoCargo 4459 (EUeVotaError 9310), ProcessTick 7349 (slot 8), ProcessInput 7345 (slot 7), ProcessKey
#   7337 (slot 6), DescartaVotos 4449, suspenderEleitor 4442 (EUeVotaError 9312 and 9313) and FinalizaEleitor 4454,
#   below;
# - cinformacaoeleitor.cpp: the exit destructors of g_numeroDigitado (13593) and g_votosEleitor (13588), and
#   AdicionaVoto 4192 with comum::md::CCedula::Adiciona inlined by binaryen;
# - ccedula.cpp: CCedula's constructor, one body with api::CFormBuilder's (fn 203): this object links ahead of
#   cformbuilder.cpp's, so 203's match line takes its name;
# - clogvota.cpp: LogaVotoCargoSemCandidatoPorSuspensao 3272, LogaVotoBrancoPorSuspensao 4546,
#   LogaVotoCargoSemCandidato 4542, LogaVotoNuloPorSuspensao 4541 and LogaVotoConfirmado 4537, each a thunk of
#   binaryen's one body for the five, fn 2302, which matches too.
# The other objects' functions slot 2 and FinalizaEleitor reach, and what matches with them, are in their units'
# fragments: unit 88 (ccargos.cpp: FiltraPorAbrangencia, the sorts, the comparators), unit 110 (celeitores.cpp:
# GetCurrentAbrangenciaEleitor), unit 91 (celeitordecorator.cpp: GetAbrangencia, 3721), unit 13 (md/rdv/ and
# crdvvota.cpp: the ballot's way into the RDV), unit 93 (cestadogeralvota.cpp: MarcaUltimoVoto) and unit 192
# (csincronismoeleitor.cpp: GetInst).
# Every slot is written.
# celeitorvotando.cpp is compiled through unit 13's list, ahead of crdvvota.cpp and md/rdv/ (that fragment has the order
# and its measurements); the rest of this unit's sources are in its own list (below).
#
# Where the objects are defined is a reading of the data. The .bss holds, in this order, the statics
# CVotacaoStateAudio::FormataMensagem reads (fn 6999: 1833216 and 1833256), vota::CEstadoAudio's (1833260 to 1833287,
# unit 116's, whose file is a choice), the string (1833288), the votes (1833300, a 12-byte object __wasm_call_ctors
# builds with a call of fn 203's body), the CDateTime (built there by fns 1382 and 2230 on 1833312 and 1833320, right
# after the votes), then the std::mutex of vota::impl::IPoliticaExecucaoEleitor::GetInst (1833324, GetInst's record
# is comum/cpoliticaexecucaoeleitor.cpp:45, held by fn 5925) and, at 1833372, CTelasVota's statics
# (comum/ctelasvota.cpp). The exit destructors of the string, the votes and that mutex take the table slots 1078, 1079
# and 1080 (fns 13593, 13588, 13574). The byte lies in the data at 1536340, between the record of
# comum/cinformacaoeleitor.cpp (1536276, vota::CInformacaoEleitor::CarregarDadosEstaticos, line 181, which fn 7787
# holds inlined) and the record of comum/cpoliticaexecucaoeleitor.cpp (1536344); in the data the records run
# cvotacaostateaudio.cpp (to 1535176), comum/cinformacaoeleitor.cpp, comum/cpoliticaexecucaoeleitor.cpp. So
# comum/cinformacaoeleitor.cpp, the one file whose records lie between cvotacaostateaudio.cpp's and
# cpoliticaexecucaoeleitor.cpp's, is chosen for all four; cvotacaostateaudio.cpp, whose FormataMensagem reads the
# string, the votes and the byte, is the other reading. Their readers say what each is (cinformacaoeleitor.h has
# them). The file's record line 181 stays blank, past the file's end.
#
# The votes' type is read as comum::md::CCedula, the class the records of CVotosCargos::InsereCedula and ConfereCedula
# and of CVotosEleicoesVota::RecebeCedula take by const reference. FinalizaEleitor (fn 4454) holds the three inlined: it
# copies the votes' 20-byte elements one by one into the vectors of CCedula values it builds with a call of fn 203's
# body, the call __wasm_call_ctors makes on the votes, and its ConfereCedula tests the size of that vector (ccedula.h
# has the readout). The reading rests on those bytes: the votes have the class's 12 bytes, its constructor call and its
# elements. Both calls stay calls, so the constructor is out of line (a reading), and fn 4192 holds Adiciona behind a
# frame of its own: both are in ccedula.cpp, in md/rdv/ beside the classes that take it (unit 13's list compiles
# those; the path is chosen). The element is an aggregate, SVotoCargo, and Limpa and Adiciona(const SVotoCargo&) are out
# of line beside them: ccedula.h says what each rests on, and the members below have the measurements. With the
# element a std::pair before, 4192 and 13588 matched; as an aggregate they still do (this commit's scan).
# This unit lists ccedula.cpp, after cinformacaoeleitor.cpp, and the place is a choice: a private link with its object
# after unit 13's cvoto.cpp instead, ahead of AdicionaVoto's object, scanned with that link's symbol file and match
# list (docs/reference/facts/workflow.md W13), gave the same 10898 matches, 4192, 13588 and 203 among them, and moved no
# row into or out of match (measured before Limpa and the second Adiciona were written).
#
# The members, measured with pnpm wasm score against the whole link:
# - GetInst and the constructor: GetInst holds s_mutex through a std::lock_guard (the form unit 116's singletons use;
#   the target's body ends with fn 150 on it) and, with no instance, builds one (72 bytes) and resets s_inst with it;
#   the constructor, private and inlined there, stores the layout celeitorvotando.h gives. The destructor is
#   out of line (the D0 calls the D2 and frees `this`: docs/reference/facts/reading.md R5), and the D2 destroys the
#   context at +20 and stores no vptr, so the class is final (R4); `= default` is the form written (`{}` not measured).
#   The data names rest on more than one reader: s_mutex (`vote:1 by:3229` in splat/symbol_addrs.txt) is also the
#   operand of its exit destructor, 7405; s_inst's line names 3229 and 7416.
# - FinishState: sets the operator's +108 string to " " (CThreadOperador::SetTextoEleitor(const char*), inline) and
#   takes the post's context back out of api::CApplication::s_contextos through CApplicationContextStack::Pop (fn 5553,
#   unit 193's, matched and named by its census pair), whose result it drops.
# - MostraCargoNoOperador: builds "VOTANDO PARA: " and the post's name (with the choice's ordinal for a post of several
#   choices), cut to 40 characters, gives it to the operator thread and posts 9 to its queue. It holds
#   CThreadOperador::SetTextoEleitor(const std::string&) inlined by binaryen, a second 16-byte frame right after the
#   call of CThreadOperador::GetInst (fn 270). With cthreadoperador.cpp in unit 116's list, its object linked ahead of
#   this unit's, the body scored 47 over 596 rows (all operand rows, 16 of them locals 2 and 3 swapped from that call
#   on); listed here after cinformacaoeleitor.cpp, it matches (docs/reference/facts/codegen.md C4: the caller's
#   object first). The target's data have that order too: celeitorvotando.cpp's vtable and records at 1533144 to
#   1533300, cthreadoperador.cpp's vtable and record at 1601200 to 1601232. A scan of the moved link with the symbol
#   file and match list of the link before the move (docs/reference/facts/workflow.md W13) moved no other row.
#   cthreadoperador.cpp's notes stay in unit 116's fragment.
# - RegistraVoto: celeitorvotando.h says what it does and why it is a member. Its callers are in the link, and
#   suspenderEleitor (4442) holds it inlined, with its calls of AdicionaVoto and of the five loggers.
# - ProcessKey (7337), suspenderEleitor (4442) and DescartaVotos (4449): celeitorvotando.h says what each does, what
#   rests on what and what is chosen. Before step 8 each scored operand rows only (7337 6 over 45, 4442 74 over 506,
#   4449 20 over 139: pnpm wasm score against our symbols), and each matches at step 9, 4442 and 4449 named by their
#   records' anchors, 7337 by its vtable slot. suspenderEleitor reads the two suspension forms through unit 111's
#   comum::CInformacaoEleicao (cinformacaoeleicao.h says why one getter is in the class and the other, 657, out of
#   line), throws the two EUeVotaError codes its records give (euevotaerror.h), and holds RegistraVotosSuspensao, a
#   member binaryen inlines (its 32-byte frame), with RegistraVoto inlined by clang into that. It and DescartaVotos hold
#   four CLogVota members inlined (clogvota.h); DescartaVotos shows CTelasVota's +164 form (ctelasvota.h). The throws'
#   column 23 puts the cases of their switches one level in.
# - AdicionaVoto: with the append written as a free function beside it in cinformacaoeleitor.cpp, clang inlined it,
#   one 48-byte frame where the target has AdicionaVoto's 16-byte frame and then binaryen's 32-byte one: 102 over 328
#   rows (14 inserted, 23 deleted); with the append in ccedula.cpp it matches. With the constructor there too,
#   our __wasm_call_ctors calls it on g_votosEleitor as the target's calls fn 203's body on 1833300. g_votosEleitor is
#   named by a `vote` line (splat/symbol_addrs.txt; its count grows with the matches that use the address); 4192,
#   7377, 6999, 4454 and 11683 are among the target's other users of it.
# - The five loggers: clogvota.h says what they are. Their places in clogvota.cpp are a choice. Use band 2 puts
#   4546, 4542, 4541 and 4537 after fns 4556 and 4551 and before 4535, 4529, 4522 and 4511, which that file's lines do
#   not allow together (4556 and 4551 already come after 4535, 4529 and 4522): right after
#   LogaMesarioIndagadoQualidadeBU (4551) they keep the band's order with 4556, 4551 and 4511, and stand inverted
#   against 4535, 4529 and 4522 (12 pairs), as 4556 and 4551 already do; at the file's end, the first place measured,
#   the four matched as well. Use band 3 puts 3272 after fn 3279 (LogaErroEstadoAplicativoDesconhecido), so it is at
#   the end. That file's include of cconfiguracaoeleicao.h takes the place of the blank line after its own header's
#   include: two lines added above line 37 moved GetInst's record (fn 184 left match, its row `source_location not in
#   the target`).
# - ChamaEstadoProximoCargo (record :229:19, EUeVotaError 9310, "Tipo de cargo nao identificado", after
#   vota::CLogVota::LogaErroIdentificacaoTipoCargo, app/vota/log/clogvota.h): the next state is
#   vota::CConfirmaVotoSemCandidato's (GetInst inlined, unit 150's) for a post with no candidate that is no referendum,
#   CPedeMajoritario's (fn 5921) for a majority post or a referendum, CPedeProporcional's (fn 3849) for a proportional
#   one; it finishes the old state, stores the new one, empties the number typed and starts the new state. The target
#   calls comum::CCandidaturas::GetInst before CCargos::GetCurrent and compares the candidates' end with their begin:
#   the two GetInst into locals first and `candidatos.size() == 0` give operand rows only; the post from
#   `CCargos::GetInst().GetCurrent()` first with `candidatos.empty()` gave 44 over 258 rows (3 inserted, 4 deleted).
#   The throw's column 19 puts it three blocks deep: the nested if inside the else is that, a choice of shape.
# - ProcessTick: on its own tick it stops it, posts 3 to the operator thread's queue on the first choice of the first
#   post and 4 otherwise (api::CPriorityMessageQueue::Post, Insert fn 501 out of line), and sets +17; else it passes
#   the tick to the post's state. Two Post calls in an if/else give operand rows only; one Post of a ternary over two
#   bool locals, 38 over 87 rows (10 inserted, 20 deleted). It reads the byte through vota::g_escolhaAtual, which only
#   a hand line in splat/symbol_addrs.txt names: pairs vote for .bss objects alone and one byte is too little content
#   to place it (docs/reference/splat.md section 2); the line's evidence is the target's other readers of the address,
#   and its comment lists them.
# - ProcessInput: stops and starts the tick again, and when +17 is set posts 5, logs "Eleitor voltou a digitar
#   enquanto estava sendo suspenso" (vota::CLogVota::LogaEleitorVoltouADigitar) and clears it; then passes the input to
#   the post's state.
# - StartState (slot 2): pushes a copy of the context at +20 (api::CApplication::PushContext, fn 3684), posts 6 to the
#   operator thread's queue and calls IniciaCiclo, which binaryen inlines: its body sits behind a 16-byte prologue of
#   its own after StartState's code (docs/reference/facts/reading.md R10), so it is out of line. IniciaCiclo clears
#   the screen through api::IScreen's slots 4 (Clear, colour 1), 27 (Refresh) and 14, under record :125 (column 21,
#   CPolySingleton<IScreen>::instance), calls slot 7 of the keyboard (record :131, column 18), starts the tick, clears
#   +17 and +18, sets the next state to this, empties the number typed and the votes cast and sets g_escolhaAtual to 1;
#   then it filters the posts by the voter's reach (CEleitores::GetCurrentAbrangenciaEleitor, then
#   CCargos::FiltraPorAbrangencia, in that order of calls: the reach is computed into a local first), sorts them
#   (CCargos::OrdenaPorAquisicao), goes back to the first (CCargos::Reset, fn 2269) and clears the keyboard (slot 4).
#   With no post left it finishes the post's state; with audio on (vota::CEstadoAudio::Ativo) it shows the
#   accessibility instruction (its text in the operator's string, message 9, vota::CInstrucaoVotacaoAcessibilidade as
#   the state, +18 set); otherwise MostraCargoNoOperador and ChamaEstadoProximoCargo. Measured together, in one link:
#   with CCedula::Limpa inline in the class, FiltraPorAbrangencia's ESTADUAL case first and its element appended by
#   emplace_back, 234 over 1089 rows (30 inserted, 30 deleted): the votes' new end stored after g_escolhaAtual's (the
#   target stores it before), the unswitched filter's two loops in the other order, and the element stored in two
#   parts (the target builds one 8-byte value); as written, operand rows only, and 7377 matches. The local names at
#   :125 and :131 (monitor, keys) are chosen to give the records' columns.
# - NeedChangeState (slot 3): with no post state it stops the tick and returns true; else, when that state wants to
#   change, it moves to the state's next one, or, with none, counts the choice (g_escolhaAtual against the post's
#   choices, CCargos::Next on the last) unless the voter comes from the instruction (+18, cleared), beeps once
#   (api::IBeep::BeepConfirm(1), record :294, column 19) and either ends the voter (FinalizaEleitor, true) or shows the
#   next post (false). The target calls CCargos::IsFim between the IBeep singleton's instance() and BeepConfirm: with
#   the test after the beep, 23 over 134 rows (2 inserted, 3 deleted); the result taken first (`const bool fim`),
#   operand rows only. Its call of FinalizaEleitor resolves on 4454's srcloc-anchor name: 4454's own records, with
#   the same opcodes on both sides now (docs/reference/splat.md section 2). The callers+content hand line that named
#   4454 from its own body before went: with it removed, splat-match added no match and moved no verdict.
# - FinalizaEleitor (fn 4454, celeitorvotando.h says what it does). In the target its band (use
#   band 2 of ledger/ordinals.tsv) puts it after ChamaEstadoProximoCargo (4459) and before DescartaVotos (4449), but the
#   lines between them do not hold it: 4459 ends at :240, below its record :229, and DescartaVotos' records :253 and
#   :254 follow five calls of its own, so it begins at :246 at the latest, which leaves five lines. It is defined above
#   4459 instead, against the band's order, a choice; 4454 scores 178 over 2686 rows in either place (below, and on
#   this link). The state's finishing is the inline helper TerminaEstado (celeitorvotando.h). It reaches, each out of
#   line in its own file and inlined by binaryen into this one body (none of them is in names.tsv):
#   comum::CRdvVota::RecebeCedula (crdvvota.cpp), md::CVotosEleicoesVota::RecebeCedula, CVotosCargos::InsereCedula and
#   ConfereCedula, CVotos::Insere and its
#   ErroPosicao (md/rdv/), CEstadoGeralVota::MarcaUltimoVoto and CSincronismoEleitor::GetInst with its constructor; unit
#   13's fragment has the md members. Measured (pnpm wasm score against 4454, on the whole link, each step on the one
#   before): 1438 over 3181 rows (495 inserted) while 5681 and 3251, the map copy's __emplace_hint_unique_key_args and
#   __find_equal, had one caller here and binaryen inlined them (the roots now stand in for their other target callers);
#   1011 over 2780 (94 inserted, 101 deleted) with them out of line and CCedula::Adiciona(const SVotoCargo&) inline in
#   ccedula.h; 958 over 2759 (73 inserted, 79 deleted) with it out of line in ccedula.cpp, where the push of a vote into
#   a ballot takes the target's shape (the new end stored in the fast path, the slow path's after it); 562 over 2719 (33
#   inserted, 34 deleted) with this file and md/rdv/ in the target's data order in unit 13's list, where binaryen keeps
#   the inlined members' ballot (the map node + 20) in a local and loads at small offsets from it, as the target does
#   (it folded them onto the node before); 180 over 2687 (1 inserted, 1 deleted) with InsereCedula's swap and
#   ConfereCedula's search in the forms unit 13's fragment gives; 178 over 2686, operand rows only, with
#   vota::CSincronismoEleitor's constructor out of line in csincronismoeleitor.cpp (unit 192's; csincronismoeleitor.h
#   says what shows it). Before these, a probe link with md/rdv/'s objects built with -fno-strict-aliasing
#   (UENUX2_TBAA_DIRS without md/rdv/, docs/reference/facts/app-flags.md F6) gave 968 over 2789 rows (103 inserted, 107
#   deleted); with the form above and cvotoscargos.cpp alone built so, 222 over 2696 (10 inserted, 1 deleted): the
#   inlined ConfereCedula's map insert reloads the child pointer after the begin node's store, and the swap reloads a
#   word, reloads the target's 4454 does not have. So the md/rdv/ code it holds reads as compiled with strict aliasing,
#   as md/ builds. The row read `unresolved self-voted` on its call of 5681, the map copy's
#   __emplace_hint_unique_key_args, while 4454's call was the only vote for 5681's name and 5681 did not match. It
#   matches since 5681's other target caller, 11349 (comum::asn::CConversorEleicoesVota::DoDesconverte, unit 140's), is
#   written and its object, app/comum/dados/asn/rdv/cconversoreleicoesvota.cpp, outside UENUX2_TBAA_DIRS, links in unit
#   13's list ahead of md/rdv/: 11349's call is a second vote for 5681's name (`evidence:call by:4454,11349` in
#   splat/symbol_addrs.txt), and 5681 matches as that object's copy, which has the reload cvotoscargos.cpp gives without
#   strict aliasing (unit 13's fragment has the measurement), where 4454's inlined md/rdv/ code matches built with it.
#   In our link the two now match as the code of two objects, one built with strict aliasing and one without, which is
#   what this note read from the reload before (a reload alone is no proof, docs/reference/facts/app-flags.md F9 item
#   8). 4454 scored 178 over 2686 rows, operand rows only, before and after the move. 3709, the destroy of
#   ConfereCedula's count map (written by it, std::map<TCargoID, size_t>), matches: 4454's srcloc-anchor name casts its
#   call votes. So do the exit destructors of vota::CSincronismoEleitor's statics, 7195 (s_inst) and 7187 (s_mutex),
#   unit 192's: 4454's anchor votes the two objects' names (1833160 and 1833136), and 4454, 7195 and 7187 are the three
#   target functions that hold those addresses (/usr/bin/grep -rlE 'i32\.const (1833160|1833136)($|[^0-9])'
#   build/out/splat/pieces/asm).
#
# The lines of members with no record are a choice: the constructor, GetInst, the statics and the destructor first,
# RegistraVoto before StartState and IniciaCiclo's records (:125, :131), FinishState and MostraCargoNoOperador after
# them, in the order use bands 1 and 2 link them (7416, 7405, 7385, 7377, 7370; 4471, then 4464 and 4459, first
# mentioned in IniciaCiclo); FinalizaEleitor before 4459 (above), DescartaVotos after it at its records (:253, :254),
# NeedChangeState ends after its record (:294), and ProcessTick, ProcessInput and ProcessKey follow, in the order use
# band 1 links them (7352, 7349, 7345, 7337); suspenderEleitor last, at its records (:410, :427), as band 2 links it
# after 4449, with RegistraVotosSuspensao, which has no index, above it. The
# callee comum::CCargos::IsPrimeiro (ccargos.h) is inline. The number typed is assigned through SetNumeroDigitado("")
# (cinformacaoeleitor.h says what it rests on).
#
# Companions. The destructor, declared first, is the key function, so celeitorvotando.cpp's object emits the vtable,
# whose slots are all written: the pending file went with ProcessKey.
# 197-uenux2-celeitorvotando-roots.cpp stands in for callers not in the link: Obtem, which stood for GetInst's fn 7481,
# went when unit 104 wrote 7481 (7428 and 11754 were in the link; Registra, which stood for 11754's RegistraVoto calls,
# went before), Abrange for GetAbrangencia's (fn 5761; 2824 is in the link), Imprime for OrdenaPorImpressao's (fns 12098
# and 12110; 5604 is in the link). Procura, which stood for 3251's caller 2386, went when unit 150 wrote 2386. Precisa
# and Inicia, which stood for 7352 and 7377, went with them, Suspende, which stood for suspenderEleitor's (fn 4442)
# calls of AdicionaVoto, the five loggers and FinalizaEleitor, with 4442, and Converte, which stood for 5681's caller
# 11349, with 11349 (unit 140's). GetInst's constructor stores the vptr, the target's one reference to the vtable, so no
# root takes it.
#
# Chosen, no evidence names them: GetInst (the name the project's recorded singletons use), g_numeroDigitado,
# g_dataHoraDesligamento, g_escolhaAtual, g_votosEleitor, CCedula's members' names, SVotoCargo and its members' names,
# that the vector is private and the accessors members, AdicionaVoto, RegistraVoto, MostraCargoNoOperador,
# FinalizaEleitor, TerminaEstado and that it is a function, SetTextoEleitor, the five LogaVoto* names (from their
# messages) and SetNumeroDigitado; that the objects are of namespace vota rather than static members of a class, that
# AdicionaVoto and MostraCargoNoOperador are free functions and RegistraVoto a member that is not static, that
# IniciaCiclo and FinalizaEleitor are private; cinformacaoeleitor.h's path, CCedula's namespace (comum::md: the records
# print it unqualified), the paths of ccedula.h and ccedula.cpp; CEleitorVotando's data members' names,
# CCargos::IsPrimeiro, the locals, the message codes written as literals (as 7221's Post(12) is), and the declaration
# order of the class's virtual members (the destructor first). Readings, not choices: that g_votosEleitor is a CCedula
# and that its element is an aggregate (above, ccedula.h).
#
# vota::ArtigoCandidato, in cinformacaoeleitor.cpp: the letter of the "{o/a}" tag of
# vota::CVotacaoStateAudio::FormataMensagem (fn 6999, unit 97, whose fragment has the measurement), 'a' when the current
# candidacy's holder is a woman, else 'o'. 6999 holds it inlined by binaryen, and in 6999's own file clang forms a select
# the target does not have, so it is a function of another TU. Its name, its being a free function and this file, beside
# the voter's statics, are chosen; its one caller is 6999, so it has no index of its own.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
# celeitorvotando.cpp itself is in unit 13's list (13-uenux2-crdvvota.mk).
CELEITORVOTANDO_SRCS := src/app/vota/eleitor/comum/cinformacaoeleitor.cpp src/app/comum/dados/md/rdv/ccedula.cpp src/app/vota/operador/cthreadoperador.cpp
UENUX2_SRCS += $(CELEITORVOTANDO_SRCS)
# celeitorvotando.cpp reads comum::CConfiguracaoEleicao, whose header reaches Boost through CConfiguracaoMunicipio's
# CHorariosUrna: an include path, not a flag of the code (src/units/README.md "What a fragment holds")
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/celeitorvotando.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# GetInst and the callees the Companions paragraph names have target callers not in the link:
# 197-uenux2-celeitorvotando-roots.cpp stands in for them
$(ROOT)/$(APP)/197-uenux2-celeitorvotando-roots.o: $(ROOT)/src/units/197-uenux2-celeitorvotando-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/197-uenux2-celeitorvotando.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/197-uenux2-celeitorvotando-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/197-uenux2-celeitorvotando-roots.o
