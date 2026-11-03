# uenux2 the state singletons of the comum::CAppState family: each class's GetInst, the static std::mutex and
# std::unique_ptr it uses, and their two exit-time destructors, three target rows per class. By class, GetInst, the
# mutex's destructor and the pointer's: vota::CAguardaMensagem 1337, 7482, 7485; CIniciodeCiclo 4433, 7323, 7333;
# CGravaResultado 6037, 12099, 12100; CEmitirMaisBU 3879, 12083, 12084; CImprimindoBim 5985, 12072, 12073;
# CImprimirBUOutrasObrigatorias 5984, 12066, 12067; CInicioBU 5983, 12063, 12064; CImprimindoZeresima 5973, 11992,
# 11993; CInicioZeresima 3865, 11925, 11926; CReinicioComparecimentoMesario 3864, 11918, 11919; CMaisInformacoes 1280,
# 11898, 11899; CMenuFiltrarCandidatosPorNumero 5954, 11893, 11894; CMenuVisualizarCandidatos 2288, 11882, 11883;
# CDefineRotaPosReinicio 5943, 11859, 11860; CReimprimindoResumoZeresima 5942, 11856, 11857; CReimprimindoZeresima 5941,
# 11853, 11854; CFimAquisicaoVotos 5428, 10738, 10739; CCancelaHabilitacaoEleitor 1536, 10647, 10648; CProcuraEleitor
# 5421, 10633, 10634; CFinalizaOperador 5342, 10215, 10216; CSincronismoOperador 1897, 10211, 10213;
# comum::CPedeTituloMesario 2729, 10389, 10390; comum::CGestorDadoMesario 5383, 10328, 10329. Nineteen GetInst of
# classes with no data member are thunks into binaryen's fn 764, which they form, with the mutex, the pointer, the vptr
# and the base's argument as parameters. The pointer destructors are thunks into fn 349, or fn 389 for a state with a
# std::shared_ptr. Also fn 244 and fn 387, the D2 and D0 that 49 states share (vota::CMaisInformacoes's symbols, the
# first of ours in the link), fn 3243 (StartState of CAguardaMensagem and CDefineRotaPosReinicio), fn 5974
# (CDefineRotaPosReinicio::ProcessInput) and fn 10327 (comum::CGestorDadoMesario::StartState, which builds unit 135's
# three comum::IGestorDadoMesario states through their GetInst, inlined: that unit's fragment has the evidence; its
# record, cgestordadomesario.cpp:35 column 32, is the controller's instance() bound to a reference, a chosen spelling of
# that length). 104-uenux2-app-vota-estados-pending.cpp names every other slot and what it waits for.
# vota::CQuerReimprimirZeresima landed its head, destructor and statics first, and its GetInst since (below). The
# heads say what each layout rests on. Fn 10793,
# vota::CControladorRegistraMesariosVota's slot 11, holds vota::CRegistroMesarioEncerrado's GetInst inlined; unit 119
# writes that class and matches it.
#
# Evidence, each measured with a probe of the class's shape at the tree's flags:
# - The statics are not local to GetInst: a local static's guard byte puts the pointer at mutex + 28, and the target
#   has mutex + 24 (and pairs 28 B apart: @1834776 and @1834804), with no guard read in any body.
# - They are class members, defined below GetInst, pointer first. The target has the mutex lower in .bss and the
#   pointer's destructor first in link order: table slots 896 and 897 for fns 7485 and 7482, and the index runs in
#   reverse link order. Definitions alone give both in one order, as members or file statics, either way round. Only a
#   reference ahead of both definitions separates them: LLVM creates the mutex at GetInst's first mention, and clang
#   emits the destructors in definition order. The match lines agree: 7485 is the object's __cxx_global_array_dtor,
#   7482 its .2. A file static has to be defined before its use, so it cannot give this order.
# - final: without it GetInst and the pointer's destructor delete through the vtable, and the target calls the
#   destructor or nothing. Slot 0 of a class with no member holds the base's D2 (fn 174), which rules out only an
#   out-of-line destructor.
# - The constructor is out of line in the .cpp, and binaryen inlines it into GetInst, its one caller. In the class,
#   clang inlines it and GetInst stores the base constructor's result into the pointer. Fn 764 stores what operator
#   new returned, and takes the vptr store's address from the result: the shape of `call T::T; drop`. Fn 5979 shows
#   the same with a second prologue (how-to step 3).
# - vota::CMaisInformacoes' and its siblings' destructor is out of line: fn 387 is `f244(p0); f136(p0)`, the 13-B
#   shape of docs/reference/facts/reading.md R5, and fn 244 stores no vptr, the class being final (R4).
# - CMaisInformacoes's and CMenuFiltrarCandidatosPorNumero's members are read from what fns 1280, 5954 and 11897
#   store, and CDefineRotaPosReinicio's and CSincronismoOperador's from fns 5943, 11858, 5974, 1897 and 10209.
#
# Merging is why CQuerReimprimirZeresima is here. binaryen's merge-similar-functions takes these destructors only from a
# number of members up: `wasm-opt --merge-similar-functions` over N copies of the two shapes merges fn 349's from N = 4
# and fn 389's from N = 3. Two copies of fn 389's stay whole bodies, and then 11899 and 11894 do not match, nor do 1280
# and 5954, whose s_inst names have no second voter. Its out-of-line destructor and static pointer are the third member.
# Fn 764 has 19 members here, as in the target. The two destructor bodies are named after an internal symbol that
# repeats across objects, so tools/round/splat_names.py spells the first member's object on such a pair.
#
# This unit moved the table's early slots, and slot 23 of ours held a function with no target name, so the tag 23 of
# ASN1::UTCTime::theInfo read as an open slot and a hand edit placed the object for fn 8750. The operand-kind table now
# reads the tag as the integer it is, and the line is gone (docs/reference/facts/splat.md S10 item 15).
#
# Chosen, no evidence names them: GetInst (the name the project's recorded singletons use) and its reference result,
# which unit 61 wrote; every data member's name, s_mutex and s_inst among them; the local trava; the implicit destructor
# of a class with no member; GetInst's parameter pRetorno, and its default in cmaisinformacoes.h (fn 1280's target
# callers pass both values, so nothing shows a default); the pointee of the std::shared_ptr members, the one unit 61
# chose; the +12 pointer's type in CDefineRotaPosReinicio, read from a call of slot 7; the +11 byte's bool; the base's
# argument spelled with its chosen enumerators; StartState as key function, except for the out-of-line destructors,
# declared first; the constructor's line and the definitions' place above the records of members not written (their
# lines stay blank); each header's path, beside its .cpp. The order of the statics is measured for GetInst's users.
# Records name 13 of the .cpp files. The other 11 are chosen, by how-to step 3's rule 2, then
# rule 4, from the data and the band: CAguardaMensagem in vota/eleitor/ (before cconfirmavotosemcandidato.cpp);
# CInicioBU in fimvotacao/ (after cimprimirbuoutrasobrigatorias.cpp); CInicioZeresima and CReinicioComparecimentoMesario
# in iniciovotacao/ (before cverificaeleicaopassou.cpp); CMaisInformacoes and CMenuFiltrarCandidatosPorNumero in
# auxiliares/ (before cmenuvisualizarcandidatos.cpp); CCancelaHabilitacaoEleitor and CProcuraEleitor in leidentidade/
# (beside celeitorencontrado.cpp and cpedeidentidade.cpp); CFinalizaOperador and CSincronismoOperador in vota/operador/
# (before cthreadoperador.cpp); CFimAquisicaoVotos in outrasopcoes/, the nearest recorded directory, its neighbours
# having no record.
#
# Same bytes, each compiled and compared by function with the object-local numbers masked (how-to step 3): GetInst
# returning a pointer; std::unique_lock or std::scoped_lock for std::lock_guard; `s_inst = std::unique_ptr<T>(new T())`,
# and std::make_unique with a public constructor, for reset; `== nullptr` and `new T` for the test and the new; final on
# the destructor instead of the class; `virtual ~T() override = default;` in the class of a state with no member, whose
# object is the implicit form's; the constructor above or below GetInst; `std::lock_guard trava(s_mutex)` with its
# argument deduced; a const guard initialised with braces; `s_inst.get() == nullptr`; no braces on the if;
# `*s_inst.get()`; `= nullptr` and `{}` on the statics' definitions. The out-of-line destructor as `{}`; a local
# reference in fn 1280 and `if (pRetorno)`; the data members' default member initializers for the mem-initializers; `if
# (m_pEstado)`; uebyte for the +11 bool. Statics defined before GetInst give the same functions and the other .bss
# order.
#
# Two slots written since, each measured in the whole link with pnpm wasm score against
# build/out/wasm-map/vota_web/names.tsv:
# - vota::CMaisInformacoes::ProcessInput (fn 11896) matches. Its form's pointee is the records' CInteractiveForm<IScreen,
#   IInputKbd> (Read(), record cinteractiveform.h:57 @1545360), and four of the states it goes to are written in unit 176
#   (their GetInst inlined here). Three forms are what the rows decide: the digit test as std::all_of with ::isdigit, the
#   target's `(c - 58) <u -10` on the sign-extended byte, where std::isdigit in a lambda gives `(c - 48) >=u 10`
#   (66 over 304 rows) and a char lambda `c >= '0' && c <= '9'` the same test on a masked byte (69 over 306); CORRIGE's
#   two stores as std::exchange, which stores +4 before +20 as the target does, where the two plain statements store +20
#   first (63 over 304 with ::isdigit, 58 over 301 with std::exchange); the first input field read with at(0), whose
#   out_of_range call is the one Read()'s bounds check throws through, as the target's block shows, where a test of
#   size() and front() leaves an if (52 over 299); with all three, 48 over 299, all operand-only. Same object function
#   (wasm-objdump of a --symbols try, masked): std::any_of with an int lambda `c < '0' || c > '9'`.
# - vota::CFinalizaOperador::StartState (fn 10214) is written and differs: 128 over 307 rows (97 operand-only, 8
#   inserted, 17 deleted), the rows not operands read as following from the builder's construction. Ours calls
#   api::CMTFormBuilder's constructor (out of line in api/gui/cmtformbuilder.cpp, unit 31, one body with fn 203) and
#   keeps the object's address in a local; the target clears the 12 bytes in place, as fns 5341 and 4633 do, while 88
#   other target functions call fn 203 (ledger/callgraph.tsv). That remainder is not explained. The form is built in a
#   file-static helper and its slot 2 called on the returned temporary, so the builder is destroyed before the form is
#   shown and the form released before m_pNextState is stored, the target's order; a named local of the form gave 136
#   over 310 rows (11 inserted, 20 deleted). The helper's name and its linkage are chosen; the points SPoint{20, 1}
#   and {20, 3} are the two words the target stores (65556, 196628). Unit 142's 1150 clears its builder in place too.
# - vota::CSincronismoOperador::StartState (fn 10210, in csincronismooperador.cpp, after the statics, a chosen line) is
#   written and differs, in local numbers only. It holds comum::CEleitores::MarcaVotou (records celeitores.cpp:456 and
#   460, unit 110's file) inlined by binaryen, which holds CEleitorDetalhe::MarcaVotou (unit 98's file) inlined the
#   same way (a second stack-pointer prologue each); before them, the test of comum::CAppInfo::EhTreinamentoEleitor
#   written in place (the target calls GetInst twice and keeps no call of 697, that function's own body), a choice of
#   spelling; after them, the eleitor's queue's Post(5) (its inline member builds the message), then m_pNextState.
#   Measured with pnpm wasm score: `40 over 150 rows (same 110, replaced 38 [38 operand-only], inserted 1, deleted 1)`,
#   the moved row a local number: the target keeps the frame in local 3 and the voter's record (CEleitorDetalhe*), then
#   the queue, in local 2; ours keeps the frame in 2, the record in 3 and the queue in 1. In scratch links of the same objects reordered (build/out link command, one object moved), the order
#   celeitordetalhe.cpp.o, celeitores.cpp.o, csincronismooperador.cpp.o reads `28 over 149 rows`, every row an operand
#   of a call or of the throws' destructor slot; this object moved after both others with celeitores.cpp.o first, or
#   celeitordetalhe.cpp.o moved right after this object (ahead of celeitores.cpp.o), read 40 over 150 as ours. Our link has this unit's object ahead of
#   unit 110's and unit 98's, which only renumbering landed units would change, so the row waits for that order.
# - vota::CFimAquisicaoVotos::StartState (fn 10737, in cfimaquisicaovotos.cpp after the statics, a chosen line) is
#   written and differs. When vota::RegistraMesarios() (fn 2520) says so the next state is
#   comum::CRegistrarMesarios::GetInst() (fn 3610, unit 247); else the eleitor's queue's Post(7) (CThreadEleitor::GetInst,
#   fn 316, +36; the type 7 and the queue stored in the frame, then Insert, fn 501), then CFinalizaOperador::GetInst()
#   (fn 5342). The target stores m_pNextState in each branch (two `i32.store offset=4`, the first followed by `br 1`);
#   every form compiled here stores it once after the join: as written, `16 over 41 rows (same 25, replaced 8 [5
#   operand-only], inserted 3, deleted 5)` (pnpm wasm score). clang's MergedLoadStoreMotion pass joins the two stores
#   (-mllvm -print-after-all on a scratch copy: two stores after VectorCombinePass, one after
#   MergedLoadStoreMotionPass). Forms tried, each object read with wasm-objdump -d at this directory's flags, each with
#   one store: the early return as written; if/else; the condition negated; a local next state stored once; a reference
#   to m_pNextState bound first; the queue and the message as named locals of the else branch; a ternary for the state;
#   and the if/else at -O1, -O2, -Os and -Oz, with -fno-strict-aliasing and with -fexceptions. In the target, fn 5400
#   (not written; its callers are vota::CNomeEleitor's slots 2 and 7, 10501 and 10500) has the same shape, a store in
#   each branch, the second after a Post(1), and fn 10511 (vota::CControlaReconhecimento's slot 7) holds the same calls
#   with one store after the join. Not explained. It stays
#   written: it is CFimAquisicaoVotos's slot 2 (a trap would hide it: docs/how-to-decompile.md step 5) and 3610's caller.
#
# Written since, each measured in the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv
# before steps 7 to 9 matched it:
# - vota::CQuerReimprimirZeresima::GetInst (fn 5940), unit 104's shape, its constructor copying CTelasVota's +244
#   through ctelasvota.h's GetTelaQuerReimprimirZeresima: 11 over 55 rows, operand-only. Its statics' exit
#   destructors 11851 and 11850 match with it. The member's pointee is now the getter's, CInteractiveForm<IScreen,
#   IInputKbd> (it was IForm<IScreen>, both chosen). Its one target caller, CReinicioVotacao::StartState (fn 11835,
#   pending in unit 138), calls it twice: the roots stand in.
# - vota::CInicioBU::StartState (fn 12062): in a training load whose voter training flag is set (+48 of
#   comum::CAppInfo::GetGeral() is FASE_TREINAMENTO, +72 of GetVota() is 1) it goes to vota::CQuerImprimirBU, whose
#   GetInst (unit 156's file) binaryen inlines here, else to vota::CImprimindoBU. The target calls CAppInfo::GetInst
#   (fn 185) twice, so the test is written with two calls; comum::CAppInfo::EhTreinamentoEleitor (fn 697) is the same
#   test out of line, which the target does not call here. 16 over 76 rows, operand-only.
# - vota::CEmitirMaisBU::StartState (fn 12082, records cemitirmaisbu.cpp 46:100 and 47:114): the two Assert texts
#   (ledger/strings.tsv 401102 and 399061) spell the condition on appInfo.GetVota(), and the target calls the const
#   GetVota (fn 903, not fn 261) on it, so the object is const: the local is written const comum::CAppInfo&. The codes
#   3452 and 3453 are EUeAssertError's, their names chosen to the records' columns (api/util/eueasserterror.h). It then
#   calls CLogVota::LogaMesarioIndagadoQtdViasAdicionais (fn 4563, unit 156's) and slot 2 of a copy of CTelasVota's
#   +196, which ctelasvota.h's GetTelaEmitirMaisBU returns by value, a choice (fn 11914's), and stores this in
#   m_pNextState. 20 over 106 rows, operand-only (calls, data addresses, and the exception's destructor slot in the two
#   throws). StartState is the class's key function, so cemitirmaisbu.cpp's object emits CEmitirMaisBU's vtable now, no
#   longer the pending object. Chosen: `using namespace comum;`, which lets the texts spell comum's EAVENCERRADA and
#   EAEFIMDOSTRABALHOS unqualified, the local's name being the texts'; StartState's first line, 42, below the
#   definitions written before it; ProcessInput's record line, 64, stays blank.
# - vota::CQuerReimprimirZeresima::StartState (fn 11849, record cquerreimprimirzeresima.cpp:45:15): when
#   comum::CRdvVota::GetInst().Comparecimento() (fns 555, 1269) is not 0 it logs "Erro na verificação do comparecimento"
#   (ledger/strings.tsv 125479, which only 11849 loads) through vota::CLogVota::LogaErroVerificacaoComparecimento, a
#   member binaryen inlines (its stack frame opens after CLogVota::GetInst, fn 184), added to app/vota/log/clogvota.cpp
#   after its last member, which calls comum::IEventosLog::logaErro (fn 2282) as LogaErroIdentificacaoTipoCargo does;
#   then it throws vota::EUeVotaError 9375 with the same text (app/vota/euevotaerror.h). Else it calls
#   comum::IEventosLog::LogaMesarioIndagadoImprimirZeresima (fn 5882), the form's slot 2, and stays. The target calls
#   CLogVota::GetInst once, after Comparecimento and before the branch: one GetInst() call in each arm gives that (a
#   reading: LLVM hoists the arms' common first call above the branch); a reference local taken before the test called
#   GetInst ahead of CRdvVota::GetInst (21 over 102 rows, 2 inserted, 2 deleted). 19 over 100 rows, operand-only. `!= 0` is a chosen spelling of the test
#   (TQtdVoto is unsigned).
# - vota::CReimprimindoZeresima::StartState (fn 11852) and ImprimeZeresima, the records' name
#   (creimprimindozeresima.cpp:51:22), which StartState holds after a stack prologue of its own and whose epilogue runs
#   before StartState stores CReimprimindoResumoZeresima::GetInst() (fn 5942) as the next state: out of line, binaryen's
#   inlining into its one caller. ImprimeZeresima takes CPolySingleton<api::IPaperRelatorios>'s instance (fn 905) at
#   :51:22 (the 21 characters `    auto& impresso = ` before the call are a chosen spelling of that length), builds
#   comum::CPath::GetPathTrab(FLASH_INTERNA) / "ze.dat", reads the number of copies at +96 of comum::CConfiguracaoEleicao
#   (GetParametrosUrna().GetNumZeresimas(), an int here: the target tests it `<= 0` signed and formats it with the int
#   code 3), and for each copy calls vota::CriaArquivoImprimindo (fn 1488),
#   CLogVota::LogaImprimindoRelatorio(RELATORIO_ZERESIMA, copy) (fn 1127), api::IPaper's slot 7 (PrintFile) with the
#   path's string, a comum::CSigVerifier of 1, GetPathTrab(FLASH_INTERNA), "ze.dat" and "ze.vsu" (fn 1540), "zerésima"
#   (the eight bytes the target stores, é included) and std::format("via {} de {}", copy, copies), then
#   vota::RemoveArquivoImprimindo (fn 1487); after the loop, slot 10 (EndPrintFile). Measured: a counter from 0 with `via
#   + 1` gives the target's increment before the log and its `!=` test; a counter from 1 to `<= vias` gave 8 rows
#   inserted and 4 deleted (72 over 509, measured with the title spelled without its é as well). ImprimeZeresima above
#   StartState, the callee first, gave 60 over 501 rows with locals 3 to 6 permuted (splat-match: `differs +0x2e
#   local.set 3 | ours local.set 4`); StartState above it gives 42 over 501, operand-only
#   (docs/reference/facts/codegen.md C4: the order is measured). Its object gets Boost's include path (below), which
#   cconfiguracaoeleicao.h reaches through CHorariosUrna. Chosen: ImprimeZeresima's private access, StartState's line
#   (43) above it, the locals' names.
#
# Two more slots, each measured in the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv
# before steps 7 to 9 matched it:
# - vota::CReinicioComparecimentoMesario::StartState (fn 11917, after the statics, the band's order: 11919, 11918,
#   11917) stores vota::CAguardaMensagem::GetInst() as the next state, then posts 7 to vota::CThreadOperador's queue.
#   The target's 11917 is `f6058(p0, 7)`, a thunk into binaryen's merge of it with vota::CFinalizaAquisicao's
#   StartState (fragment 223 has the evidence); our link forms the same merge, named after this one: 11917 `1 over 5
#   rows`, 6058 `3 over 29 rows`, operand-only.
# - vota::CDefineRotaPosReinicio::NeedChangeState (fn 11858, its throw on the record's line 81, column 19, as
#   `throw CUeVotaError(` at 12 spaces in a switch's case): reads the vote state; for EAVZERESIMAIMPRESSA and
#   EAVREGISTROMESARIOINICIAL (54, 55) it clears m_pEstado and goes to vota::CReinicioComparecimentoMesario when
#   vota::RegistraMesarios (fn 2520, unit 168) is true and to vota::CInicioVotacao (fn 2880) when not, for EAVVOTAR
#   (56) it clears m_pEstado and goes to CInicioVotacao, and for any other state it logs
#   LogaErroEstadoAplicativoDesconhecido (fn 3279) and throws EUeVotaError 9309 with std::format("Estado inválido = {}",
#   estado). The format's argument is a handle (type 15) on table slot 967, which comum::asn::CConversorEstadoGeralVota's
#   DoConverte (fn 11390) passes too, for the estado of ConverteEstadoVota, which it holds inlined (record
#   `ConverteEstadoVota(const EEstadoVota)`): so the local is `const comum::EEstadoVota`, the handle's type. The target
#   stores the next state once, after the switch, and calls CInicioVotacao::GetInst once for both of its paths: the
#   state is a local assigned in the cases and stored once (23 over 237 rows, operand-only); assigning m_pNextState in
#   each case gave three stores and two calls, `34 over 244 rows (... inserted 7, deleted 2)`. Chosen: the code's name
#   (euevotaerror.h), the locals' names, the cases as the enumerators, the member's place after StartState and the
#   lines above it, ProcessInput's place after it. The function's instance of the enum's handle comes first in the
#   link, so splat/symbol_addrs.txt names 536 by that symbol now, a generated line since unit 253 (unit 109's fragment
#   has the rule).
# - vota::CQuerReimprimirZeresima::ProcessInput (fn 11848, slot 7, after StartState: 11849 and 11848 in their band). It
#   takes the form's first input field (GetEntradas().at(0): the target makes that bounds check before Read's), then
#   switches on Read() (record cinteractiveform.h:57, which it holds inlined, with CPolySingleton<api::IInputKbd>'s
#   instance, fn 455): on api::INPUT_CONFIRMA (9) a text "1" or "2" cuts the paper (vota::CRelVotaUtil::CortaPapel, fn
#   2882, unit 246) and goes to vota::CReimprimindoZeresima or CReimprimindoResumoZeresima (fns 5941, 5942), and any
#   other text is cleared (the field's slot 11, Clear); on api::INPUT_CORRIGE (5) a text that is not empty is cleared,
#   else it goes to vota::CReinicioComparecimentoMesario when vota::RegistraMesarios (fn 2520) is true and to
#   vota::CInicioVotacao when not (fns 3864, 2880); on api::INPUT_BRANCO (3) to vota::CMaisInformacoes::GetInst(this)
#   (fn 1280). The text is read through GetTexto's reference each time, not copied: the target reads the field's +24
#   string at each test. 12 over 162 rows, operand-only. Chosen: the local's name and type spelling, the cases' order,
#   `== "1"` and `!empty()` as the tests' spellings, the else-if chains.
#
# CProcuraEleitor::StartState and vota::CEleitorEncontrado (leidentidade/celeitorencontrado.{h,cpp}, the file of the
# class's record), each measured in the whole link with pnpm wasm score before steps 7 to 9:
# - StartState (fn 10631, matched, named by vptr-anchor) stores into m_pNextState what EstadoAposProcura returns, an
#   external function of cprocuraeleitor.cpp that clang keeps a call (wasm-objdump -d of the object) and binaryen
#   inlines: the target pushes `this` for the one store ahead of the only stack prologue, the helper's (how-to step 3's
#   sign of a frameless caller over an inlined body), and stores after the voter's identity is destroyed. Each other
#   form measured on the final tree, the rest unchanged: the next state stored in each branch of StartState, `111 over
#   283 rows (... inserted 9, deleted 5)`; the helper in the anonymous namespace, which clang inlines, `101 over 279
#   (... inserted 5, deleted 3)`; as written, 48 over 274, all operand rows. EstadoAposProcura reads the identity typed (vota::GetIdentidadeEleitor, 1535), looks the voter up
#   (comum::CEleitores::LocalizaEleitor, 2264, over comum::md::FormataIdentidade, 2798) and returns
#   CEleitorEncontrado::GetInst() when found, else unit 243's CIniciaJustificativa::GetInst() when
#   vota::NaoAceitaJustificativa (4578, unit 168) is false and the identifier is a título (TipoIDInscricaoEleitoral, 1),
#   else vota::CEleitorNaoEncontrado::GetInst() (5424, unit 161). binaryen inlines CEleitorEncontrado's GetInst and unit
#   243's two there, as in the target.
# - CEleitorEncontrado: GetInst, the constructor (comum::CAppState's with EVENTO_NENHUM, the target's 0) and the statics
#   (the pointer at 1905616, the mutex at 1905592), whose exit destructors 10637 and 10636 match. StartState (10635) is
#   written, the key function (below). celeitorencontrado.cpp links ahead of cprocuraeleitor.cpp, the order of the two
#   classes' vtables in the target's data (@1588936, @1589008), so it is listed here, before it. In it, and in unit 243's two files, GetInst is
#   defined above the constructor: with the constructor first, 10631 scored `69 over 276 rows (... inserted 2, deleted
#   2)`, two pairs of binaryen's locals swapped in the inlined CIniciaJustificativa::GetInst and
#   CEleitorEncontrado::GetInst (docs/reference/facts/codegen.md C4); with GetInst first, 48 over 274, all operand rows.
#   Neither the object order (celeitorencontrado.cpp before or after cprocuraeleitor.cpp, unit 243's two files before
#   or after it) nor StartState above or below its helper moved that score.
# Chosen: EstadoAposProcura's name and its being a free function of namespace vota (it reads no state of the class), the
# found branch last (the target's block order), the locals' names, celeitorencontrado.h's path and the lines of
# CEleitorEncontrado's members and statics. Not measured, and they may give the same bytes: EstadoAposProcura in
# another file, or a static member in its place.
#
# vota::CEleitorEncontrado::StartState (fn 10635, slot 2, 3870 B) is written and `unresolved self-voted`: every row is
# an operand, and the name of its callee 6733, the set's range insert (below), has no voter but 10635, since 6733 does
# not match; 10635 waits for it. It is written in celeitorencontrado.cpp, its throw of the
# vota error 9394 ("Eleitor n�o posicionado", EUE_VOTA_ELEITOR_NAO_POSICIONADO added to euevotaerror.h, its name chosen
# from the message) on the record's line 102, column 15, and GetInst, the constructor and the statics after it (a choice
# that leaves that line free; GetInst stays above the constructor). It creates six states no other target function
# creates, which this unit lists ahead of it, each in a file of its own named after its class (RTTI; how-to step 3's
# rule 4) in leidentidade/, where their vtables (@1588508 to @1588876) lie, between cpedeidentidade.cpp's records and
# celeitorencontrado.cpp's (@1588980): vota::CEleitorOptouPorVotarEmTransito, CEleitorImpedidoJustificar,
# CEleitorNaoTemIdadeMinima, CEleitorNaoPossuiCargosParaVotar and CEleitorImpedidoJustificarVotoTransito, new, over
# unit 161's IEleitorImpedidoVotar, and CEleitorJaVotou, unit 161's file, moved here, its GetInst, constructor and
# statics now written. Matched with them: the six classes' statics' exit destructors (10662 and 10661, 10659 and 10658,
# 10656 and 10655, 10651 and 10650, 10640 and 10639, 10645 and 10644), 1959 (binaryen's body of the six pointers'
# destructors, named after its first member in link order), the line texts 10660, 10657, 10654, 10653, 10649, 10638 and
# 5422 (one body for two classes' "est� impedido de votar ou justificar."), and unit 161's 10666, a thunk into 1959.
# Evidence (pnpm wasm fn ../target/vota_web_wasm.wasm 10635; each class's header has its RTTI, vtable and statics):
# - The order is the target's: the voter at comum::CEleitores's cursor (GetCurrent, 656), else the throw; with an
#   impediment (CEleitorDetalhe::SemImpedimento, 2266, false), CLogVota::GetInst (184) and LogaEleitorImpedido (inlined:
#   clogvota.h), then, when vota::NaoAceitaJustificativa (4578), CEleitorOptouPorVotarEmTransito for impediment 2
#   (GetImpedimento, 3769) or CEleitorNaoEncontrado::GetInst (5424); else the turn's impediment (inline twice:
#   celeitordetalhe.h) 4 to 6 gives CEleitorImpedidoJustificar and 7 CEleitorNaoTemIdadeMinima; then impediment 2 gives
#   unit 283's CIniciaJustificativaTransito when comum::CConfiguracaoEleicao's set at +604 holds an element that is not
#   0, else CEleitorImpedidoJustificarVotoTransito, and any other unit 283's CIniciaJustificativaTemporario; with none,
#   the dynamic data's (GetDinamico, 1271) comparecimento 1 gives CEleitorNaoPossuiCargosParaVotar, 3 CEleitorJaVotou,
#   else CNomeEleitor::GetInst (5401). 1 and 3 are literals, as in celeitores.cpp.
# - Forms, read from the order of the calls in clang's object (wasm-objdump -d of compiles of the file): the set copied
#   into a named local of the branch is destroyed once, after either GetInst; the target destroys it on both paths
#   before them, tests the found iterator against end() again and puts the not-found arm after the throw. That is a
#   helper whose set dies at its return, returning find_if's iterator compared with end(); std::ranges::any_of or
#   std::any_of, in the condition, in a bool or in such a helper, keep no second test and put the found arm after the
#   throw or the not-found arm before the found one. Same bytes: std::find_if over begin() and end(),
#   std::ranges::find_if, and the caller's `if` either way round. The impediments 4 to 6: the target's `(x - 7) >= -3`
#   (unsigned) is the fold of `x != 4 && x != 5 && x != 6` returned from a helper (or negated in place, same bytes);
#   `==` three times, `>= && <=`, a switch, or the `!=` chain held in a bool fold to `(x - 4) <= 2`. The turn: read
#   through a const comum::CAppInfo&, which calls the const GetGeral (457), the target's callee; GetInst().GetGeral()
#   calls the other (291), the scan's first difference before the change.
# - The objects' order (docs/reference/facts/codegen.md C4): with the five new files and celeitorjavotou.cpp after
#   celeitorencontrado.cpp, 10635 scored `590 over 1714 rows (same 1124, replaced 525 [523 operand-only], inserted 33,
#   deleted 32)`, binaryen's locals numbered otherwise in the inlined GetInst; with celeitorjavotou.cpp alone after it,
#   `490 over 1704 rows (same 1214, replaced 445 [443 operand-only], inserted 23, deleted 22)` (a link that still held
#   unit 243's stand-in for 10635); with all six before it, `221 over 1681 rows (same 1460, replaced 221 [221
#   operand-only], inserted 0, deleted 0)` (pnpm wasm score on whole links, the rest of the tree as committed). In use
#   band 1 the target links them so too: 10662 to 10638 above 10635, in reverse link order.
# - The set's range insert (fn 6733, libc++'s std::set<ecourna::app::dados::ETipoIdentificadorEleitor>::insert over two
#   const_iterator) has a second target caller, 7787 (not written), for which unit 283's roots stand in: while 10635 was
#   its one caller, binaryen inlined it there. 6733 reads `differs`, in its locals (7 against 6): our copy is this
#   object's, built with strict aliasing; with this object alone built without it (a scratch UENUX2_NOTBAA_FILES line),
#   6733 scored `1 over 181 rows (same 180, replaced 1 [1 operand-only], inserted 0, deleted 0)`, 10635 did not
#   change, and steps 7 to 9 on that link matched 6733 and 10635, 11924 match rows against 11922, no other row moved.
#   That flag is the user's to decide; by its band, 6733 lies next to 6734, a function
#   of celeitores.cpp's records, so the target's copy may as well be another uenux2 object's built without strict
#   aliasing (a reading).
# Chosen: the helpers' names and their being functions of the file's anonymous namespace (they read no state of the
# class, and clang inlines them all), the predicate's 0 written against the set's element type (the target's compare;
# the type is cconfiguracaoeleicao.h's choice, whose enumerators start at 1), the order of the definitions, the lines
# but 102, and the six files' names.
#
# Roots: the pair for vota::CQuerReimprimirZeresima::GetInst (5940) went, its one target caller, 11835, being in the
# link (unit 138). The pairs for CReimprimindoZeresima::GetInst (5941) and CReimprimindoResumoZeresima::GetInst (5942)
# went: their target callers, 11848 with 11845 and with 11852, are in the link.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_ESTADOS_SRCS := src/app/vota/eleitor/caguardamensagem.cpp \
    src/app/vota/eleitor/ciniciodeciclo.cpp \
    src/app/vota/eleitor/fimvotacao/cgravaresultado.cpp \
    src/app/vota/eleitor/fimvotacao/cemitirmaisbu.cpp \
    src/app/vota/eleitor/fimvotacao/cimprimindobim.cpp \
    src/app/vota/eleitor/fimvotacao/cimprimirbuoutrasobrigatorias.cpp \
    src/app/vota/eleitor/fimvotacao/ciniciobu.cpp \
    src/app/vota/eleitor/iniciovotacao/cimprimindozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/ciniciozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/creiniciocomparecimentomesario.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cmenuvisualizarcandidatos.cpp \
    src/app/vota/eleitor/cdefinerotaposreinicio.cpp \
    src/app/vota/eleitor/iniciovotacao/creimprimindoresumozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/creimprimindozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/cquerreimprimirzeresima.cpp \
    src/app/vota/operador/outrasopcoes/cfimaquisicaovotos.cpp \
    src/app/vota/operador/leidentidade/celeitoroptouporvotaremtransito.cpp \
    src/app/vota/operador/leidentidade/celeitorimpedidojustificar.cpp \
    src/app/vota/operador/leidentidade/celeitornaotemidademinima.cpp \
    src/app/vota/operador/leidentidade/celeitornaopossuicargosparavotar.cpp \
    src/app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.cpp \
    src/app/vota/operador/leidentidade/celeitorjavotou.cpp \
    src/app/vota/operador/leidentidade/celeitorimpedidojustificarvototransito.cpp \
    src/app/vota/operador/leidentidade/celeitorencontrado.cpp \
    src/app/vota/operador/leidentidade/cprocuraeleitor.cpp \
    src/app/comum/comparecimentomesario/estados/cpedetitulomesario.cpp \
    src/app/comum/comparecimentomesario/estados/cgestordadomesario.cpp \
    src/app/vota/operador/cfinalizaoperador.cpp \
    src/app/vota/operador/csincronismooperador.cpp
UENUX2_SRCS += $(APP_VOTA_ESTADOS_SRCS)
# creimprimindozeresima.cpp includes app/comum/dados/cconfiguracaoeleicao.h, which reaches Boost through
# CConfiguracaoMunicipio's CHorariosUrna (an include path, not a flag of the code: unit 88 adds the same)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/iniciovotacao/creimprimindozeresima.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# celeitorencontrado.cpp includes it too, for the set StartState copies (the same include path)
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/leidentidade/celeitorencontrado.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# The members not reconstructed: 104-uenux2-app-vota-estados-pending.cpp gives the vtables trapping bodies, compiled
# with the unit's flags
$(ROOT)/$(APP)/104-uenux2-app-vota-estados-pending.o: $(ROOT)/src/units/104-uenux2-app-vota-estados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/104-uenux2-app-vota-estados.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/comparecimentomesario/estados/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/fimvotacao/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/auxiliares/*.h $(ROOT)/src/uenux2/src/app/vota/operador/*.h $(ROOT)/src/uenux2/src/app/vota/operador/leidentidade/*.h $(ROOT)/src/uenux2/src/app/vota/operador/outrasopcoes/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/104-uenux2-app-vota-estados-pending.cpp -o $(R)
# nothing reconstructed calls GetInst yet: 104-uenux2-app-vota-estados-roots.cpp stands in for the target's callers
$(ROOT)/$(APP)/104-uenux2-app-vota-estados-roots.o: $(ROOT)/src/units/104-uenux2-app-vota-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/104-uenux2-app-vota-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/104-uenux2-app-vota-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/104-uenux2-app-vota-estados-pending.o $(APP)/104-uenux2-app-vota-estados-roots.o
