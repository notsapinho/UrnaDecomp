# uenux2 five vota states over the D2 that 19 states share (fn 448), each a final comum::CAppState with two
# std::shared_ptr at +12 and +20: vota::CUrnaInspecionada's StartState (target fn 1718, slot 2, one body with the slot 2
# of six other states) and ProcessKey (11794, slot 6); vota::CJustificativaEfetuada's StartState (10594) and
# ProcessInput (10593, slot 7: on Read()'s 9, api::INPUT_CONFIRMA, it goes to vota::CCancelaHabilitacaoEleitor::GetInst,
# fn 1536; Read() is unit 135's, in api/gui/cinteractiveform.h);
# vota::CPedeAnoNascimentoSemBiometria's StartState (10490); vota::CMostraEleitorVotando's ProcessInput (10426, slot 7);
# vota::CPerguntaCodigoSuspensao's StartState (10421); and the destructor and deleting destructor every one of them holds
# (fns 448 and 765, slots 0 and 1, matched under CUrnaInspecionada's symbols, the first of the five classes in link
# order; the target holds these two bodies once for 19 classes). vota::CLogVota gains the three members
# 10594 and 10421 hold inlined (app/vota/log/clogvota.cpp, unit 119's file). The class headers say what each layout
# rests on; 142-uenux2-app-vota-estados-448-pending.cpp names every slot left and what it waits for.
#
# Evidence, each read in the target:
# - final, and the destructor out of line in each class's .cpp: fn 765 is `f448(p0); drop; f136(p0)`, the 13-B shape of
#   docs/reference/facts/reading.md R5, and fn 448 destroys the members and stores no vptr (R4). Measured on
#   CUrnaInspecionada: without final the D2 gains the vptr store (55 rows against 50).
# - The members' offsets and types: the constructors that fns 11797, 2747, 10500, 1150 and 10415 hold inlined (the class
#   headers list what each stores). None stays unwritten here: 10500's is written (below), and so are
#   CUrnaInspecionada's GetInst and constructor, which 11797 holds, in curnainspecionada.cpp with its statics (exit
#   destructors 11796 and 11795, matched with 11797, whose cinspecionaurna.cpp this list compiles), and its vtable
#   sink in the roots went. Fns 1150 and 2747 are written
#   (below), and so is CPerguntaCodigoSuspensao's GetInst, which 10415 (unit 152's
#   CPerguntaEleitorVotando::ProcessInput) holds inlined.
# - The log members: fns 10594 and 10421 call vota::CLogVota::GetInst (fn 184) and then open a stack frame of their own
#   (docs/reference/facts/reading.md R10) that builds the message and calls api::CLoga::loga (fn 433) on CLogVota's +4,
#   or comum::IEventosLog::loga (fn 233), as unit 119's four Loga members do.
# - CMostraEleitorVotando::ProcessInput reads the api::IInputMT singleton through api::CPolySingleton's instance (record
#   cmostraeleitorvotando.cpp:64, column 22, the default argument's) and holds api::IInput::GetKey inlined (record
#   iinput.h:86); the record's column fixes the length of what precedes the call on its line, and the local's name and
#   `auto&` that fill it are a choice (docs/reference/facts/reading.md R19).
#
# Chosen, no evidence names them: every data member's name and, where only a width shows, its type (bool or int, the
# plainest of that width); api::IForm<api::IScreen> as CUrnaInspecionada's forms' pointee, after api::CFormBuilder's
# GetForm, the builder that fns 2380 and 6557 use; the key 13 written as a literal (no evidence names the key); the three
# CLogVota members' names (from their messages) and their place after LogaTituloInvalidoRegistroMesario; GetInst and the
# private constructor, declared and not defined (but CMostraEleitorVotando's, now that fn 1150 is written), their names
# following the project's other singletons; the destructor
# declared first, so that the class's own .cpp emits the vtable (how-to step 3). The paths:
# app/vota/operador/aguardaeleitor/cmostraeleitorvotando.cpp is the record's; the four others are chosen by how-to step 3
# from the data (docs/reference/facts/placing.md P4, P5), each header beside its .cpp and the file named after the class:
# - CUrnaInspecionada in app/vota/eleitor/: its vtable (@1547520) has vota::IConfereVotoEmCargo's (@1547576) and
#   cconferevotoemcargo.cpp's records (@1547652) after it with nothing between, and before it vota::CInspecionaUrna's
#   vtable (@1547448, no record) and then app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.cpp's records. The
#   adjacent side, a choice (P5).
# - CJustificativaEfetuada in app/vota/operador/justificativa/: its vtable (@1589804) has vota::CPedeAnoNascimento's
#   (@1589876, no record) and then justificativa/iconfirmajustificativa.cpp's records (@1589992) after it, and ten
#   unrecorded vtables back to leidentidade/celeitorencontrado.cpp's record (@1588980). The adjacent side, a choice.
# - CPedeAnoNascimentoSemBiometria in app/vota/operador/confirmaidentidade/: its vtable (@1591496) lies between
#   confirmaidentidade/cnomeeleitor.cpp's records (@1591308) and cdigitalreconhecida.cpp's (@1591684), with unrecorded
#   vtables only between: both sides name the directory.
# - CPerguntaCodigoSuspensao in app/vota/operador/aguardaeleitor/: its vtable (@1593120) follows
#   cmostraeleitorvotando.cpp's object (typeinfo @1593092, then a record of iinput.h) and precedes
#   vota::CPerguntaEleitorVotando's (no record) and csuspensaoautomaticaeleitor.cpp's records (@1593320): both sides name
#   the directory.
#
# Same bytes, each compiled at -O2, the tree's level when they were measured, and compared by function with the
# object-local numbers masked (how-to step 3): in
# ProcessKey an early return and `13 == tecla`; in CMostraEleitorVotando::ProcessInput an early return, and the local
# typed api::IInput&; in CJustificativaEfetuada::StartState assign() for either assignment and a local reference to the
# string; in LogaPedidoTituloSuspensao the message in a const local; the destructor as `{}`, and final on the
# destructor instead of the class (D2 and D0). Forms that do not: in CUrnaInspecionada's two slots and in
# CJustificativaEfetuada::StartState the next state stored before the form's call; in
# CPerguntaCodigoSuspensao::StartState the form's call, or the bool's store, before the log; CJustificativaEfetuada's
# test negated with the arms swapped; the instance read twice in ProcessInput; LogaJustificativaRecebida with the
# message as a temporary argument. So those orders and forms are evidence.
#
# CMostraEleitorVotando's singleton, in cmostraeleitorvotando.cpp, at chosen lines between the destructor and
# ProcessInput's record and, for CriaForm, after it:
# - GetInst (fn 1150), with the constructor inlined, which clang gives, and the form's builder CriaForm inlined by
#   binaryen (a second stack frame, entered with a copy of +12's std::shared_ptr<std::string> made before it, so it takes
#   the pointer by value). The form: AddLed(1); then, when comum::CAppInfo::EhTreinamentoEleitor() (697), the text
#   "TREINAMENTO DE ELEITORES" at {1, 1}, else the name (11529, "{:35}") at {1, 1}, the identity typed (10586) at
#   {1, 2}, "Seq:" at {32, 2}, the sequence number (11528, "{:04}", right-aligned) at {40, 2}, "Seção:" at {30, 3} and the
#   section (11527, "{:04}", right-aligned) at {40, 3}; then 10539's text at {1, 3} and the name's api::CTextSource at
#   {1, 4}; GetForm(""). The points are the words the target stores (65537 and on), the texts its literals. It is written
#   and differs: `score 184 over 803 rows (same 619, replaced 109 [108 operand-only], inserted 26, deleted 49)`, the
#   rows not operands read as following from the builder's construction, which the target clears in place (12 bytes at +104 of the frame) where
#   ours calls api::CMTFormBuilder's constructor (fn 203's body) and keeps its result in a local, as unit 104's 10214
#   does: of the seven target callers of GetForm (1694; `grep -rlE 'call 1694( |$)' build/out/splat/pieces/asm`), only
#   10204 calls fn 203; 1150 clears the builder in place, as unit 104's fragment reads 10214, 4633 and 5341 doing and
#   unit 165's reads 5343 doing (and unit 161's 10676, written, does), where 88 other target functions call 203. That remainder is not explained. No vote names 1150 (its callers are vtable slots or not written,
#   and its body anchors nothing), so a hand line names it by `rtti-vptr`: it alone holds the class's address point
#   1593008. 5394, 10407 and 10523 (unit 152's) match through it.
# - Its statics' exit destructors, 10429 (the std::unique_ptr at 1909316) and 10428 (the std::mutex at 1909292), match:
#   their .bss names come from two `callers+content` hand lines, each resting on 1150's use of the address. The statics
#   are defined after GetInst, s_inst first: 10429 lies above 10428 in their use band, so it links first.
# - 10539, the text "ÁUDIO ATIVADO" or " ": " " unless CThreadEleitor's instance exists (read under its mutex, through
#   the inline CThreadEleitor::Existe added to cthreadeleitor.h) and CEstadoAudio's mode is not 2, or
#   IsAudioAtivadoMesario (1687, unit 50's) holds. Only 1150 passes its slot. It is a function of this file's anonymous
#   namespace, TextoAudioAtivado: name, linkage and file are chosen, the file against its band, which puts 10539 right
#   after the __func slots of api::CTextFieldUpdateMT's timer lambda (10540 to 10544, unit 51's; the class's own
#   members are 10545 to 10549), not among this file's functions (10424 to 10429).
# Chosen too: CriaForm's name and its being a static member, the statics' names.
#
# CJustificativaEfetuada's singleton, in cjustificativaefetuada.cpp, at chosen lines after the destructor (the file has
# no record): GetInst (fn 2747, matched, named by vptr-anchor), with the constructor inlined, which builds +12 with
# std::make_shared<std::string>("justificou/ja justificou"), initializes the form at +20 from MontaTela, a helper of the
# file's anonymous namespace that takes the title by value (2747 adds a reference to the block before the form and drops
# it after, vota::CEleitorVotouNaoVotou's shape) and that the constructor holds inlined, and sets +28 to true; the form:
# AddLed(0), the identity typed (slot 3907, fn 10586) at {1, 1}, the title's api::CTextSource with "%s" at {1, 2},
# "CONFIRMA: continuar" at {1, 4} aligned right (the point 262145 and the alignment 1 the target passes, both evidence),
# AddInputControl, GetInteractiveForm("", true). Its statics' exit destructors, 10597 (the std::unique_ptr at 1905952)
# and 10595 (the std::mutex at 1905928), match: the statics are defined before StartState, s_inst first, since 10597 and
# 10595 lie above StartState (10594) in use band 1. Its callers are vota::IIniciaJustificativa::StartState (10587, unit
# 152), which calls it twice and clears +28 through the first result with SetRecebida(false), a setter added to
# cjustificativaefetuada.h, and fn 10590 (not written). Chosen: the helper's name and linkage, SetRecebida's name and its
# being a setter (a public member is the other form, not tried), the statics' names.
#
# Two more slots match, written in their classes' files (scores from pnpm wasm score before steps 7 to 9):
# - CMostraEleitorVotando::StartState (10427, 3 over 74 rows, all operand-only), at a chosen line before ProcessInput's
#   record: it copies vota::CThreadOperador's string at +108 into the string +12 points to (std::string's operator=,
#   through CThreadOperador::GetTextoEleitor, an accessor added to cthreadoperador.h, its name chosen), shows +20's
#   form, calls comum::CInfoMTLCD::MostraIconeBateria on CInfoMTLCD::GetInst()'s result (2284, unit 153's file) and sets
#   the next state, in the target's order.
# - CPerguntaCodigoSuspensao::ProcessInput (10420, 56 over 873 rows, all operand-only): Read() (record
#   cinteractiveform.h:57 @1593176), then nothing more while +28 is set; on INPUT_CORRIGE,
#   CLogVota::LogaSuspensaoAbortada (4535), CThreadEleitor's queue's Post(4) and CMostraEleitorVotando::GetInst() as the
#   next state; on INPUT_CONFIRMA, the text of the form's GetEntradas().at(0), and when it is not empty three functions
#   binaryen inlines, each in a stack frame of its own after its call: the CLogVota member LogaTituloSuspensaoDigitado
#   (loga, fn 233), vota::ValidaTituloSuspensao and LogaTituloSuspensaoInvalido or LogaTituloSuspensaoValido
#   (std::format of the title, logaAlerta, fn 1398); an invalid title shows +20's form, waits 3000 ms through
#   api::CSystem::Dorme (the target's test of the byte at 1584624 around emscripten_sleep) and shows +12's form again, a
#   valid one posts 2 and sets +28. The empty vector branches to the same std::out_of_range throw as Read()'s bounds
#   check, and the vector's end is loaded before its begin: at(0). Measured, with the helper below still in the
#   caller's TU: an `if (!GetEntradas().empty())` around `[0]` gave 90 over 881 rows (8 inserted, 8 deleted), the begin
#   loaded first and Read()'s check an `if` where the shared throw gives a `block` and `br_if`; `size() > 0`, with the
#   switch inside `if (!m_bLido)`, loaded the end first and kept the `if` (119 over 877, 4 inserted, 4 deleted);
#   at(0) with the early return, 115 over 877 (4 inserted, 3 deleted), the helper's difference alone.
# - ValidaTituloSuspensao (no target index: 10420 holds it, in a 48-byte frame) formats the title typed and the voter's
#   identity typed (GetIdentidadeDigitada, fn 3623) with comum::md::FormataIdentidade and type 1, compares them (memcmp
#   with the voter's first) before CValidadorIdentidade::EhValida, and returns the AND of the two and the formatted
#   title, a copy. It is in a file of its own, validatitulosuspensao.cpp, listed after cperguntacodigosuspensao.cpp:
#   defined in the caller's TU it gave 115 over 877 rows (4 inserted, 3 deleted), the result's address (+8 of the
#   caller's frame) computed before the helper's frame instead of at the store and the locals renumbered after it; in a
#   TU of its own, the score above. A function that reads no state of the class goes in another TU than its caller as a
#   free function (docs/reference/facts/reading.md R10).
# Chosen: the three CLogVota members' names (from their messages; their place after LogaPedidoTituloSuspensao),
# ValidaTituloSuspensao's name, its std::pair<bool, std::string> result, its file and its declaration in
# cperguntacodigosuspensao.h, the locals' names, `valido && diferente`, the switch's default, and the early return (the
# `if` around the switch was measured only with `size() > 0`).
#
# comum::CEleitorDadosHabilitacao's constructor (target fn 2733, no record) matches, defined out of line in
# cmostraeleitorvotando.cpp after the file's last record line (159), at chosen lines (src/README.md "Gaps").
# - Its layout is unit 130's celeitordadoshabilitacao.h: it copies the identity (its std::string inline or through
#   __init_copy_ctor_external, fn 138), stores the kind and the audio word, and copies the biometric part with its
#   std::optional and the photo's 8 bytes, in the members' order; the parameters' order is the wasm signature's.
# - Out of line: its one caller, ProcessKey (10425, slot 6, pending; its records are those of SalvaHabilitacaoEleitor,
#   which it holds inlined), calls it four times, with the kinds 1, 2, 2 and 0, and keeps the returned `this` each time.
#   A probe caller with those four constructions, compiled at the tree's flags, inlines the constructor at all four when
#   the header defines it in its class, and keeps the four calls when it is defined out of line, in another TU or in the
#   caller's (docs/reference/facts/codegen.md C6).
# - Placement, by how-to step 3's rule 2: in its use band (uses 4, ledger/ordinals.tsv) 2733 links after 2735,
#   CVerificaDadoEleitor::GetInst (its vtable @1592712), and 2734 (CEleitorDemorando::GetInst, unit 152's), and before
#   aguardaeleitor/csuspensaoautomaticaeleitor.cpp's 2732 (stretch 1080 of ledger/tu-clusters.tsv, labelled that file).
#   In the data the one recorded file between those ends is this one (record @1593044), and the lower end is
#   aguardaeleitor's too: so the directory is app/vota/operador/aguardaeleitor/, against the class's namespace. The file
#   is a choice there: it holds the one caller, and a small class one file constructs can be defined there
#   (docs/reference/facts/placing.md P2); a file named after the class there (rule 4) is the other reading, which no
#   data place.
# - The roots file stands in for ProcessKey with two calls whose results it reads: with a stand-in that dropped them,
#   our body lost its i32 result, 4 over 98 rows (one deleted), against 2 over 98, all operand-only, with the results
#   read (pnpm wasm score, before steps 7 to 9, the constructor then in a file of its own).
# Chosen too: the parameters' names; the photo taken by reference (the caller passes the address of a temporary, which a
# by-value photo takes too); the member-initializer list; the header's path, unit 130's (a choice against rule 1, which
# would move it beside this file: celeitores.cpp and celeitordetalhe.cpp include it there). This file builds with strict
# aliasing (UENUX2_TBAA_DIRS), comum/dados/ without: compiled with -fno-strict-aliasing too, the file gives the
# constructor the same code.
#
# Matched since: CPedeAnoNascimentoSemBiometria::StartState (fn 10490). The target stores +4 (the next state) first,
# then +32 and +28. Each of the six orders of the three statements written as assignments compiles at the tree's flags
# with the +4 store last (the wasm code generator moves it). comum::CAppState::SetNextState (out of line in
# cappstate.cpp, which binaryen inlines) called first keeps it first: the call clang cannot move a store across, the
# replay reading of unit 61's fragment. With it, `m_tentativas = 0` then `m_bPrimeira = true` give +32 then +28 (the
# other order gave them reversed: 6 over 21 rows, 3 inserted, 3 deleted), byte-exact before steps 7 to 9.
# Matched since: CPedeAnoNascimentoSemBiometria::GetInst with its constructor and the two helpers that build its forms,
# which have no target function of their own: fn 10500 (unit 239's CNomeEleitor::ProcessInput) holds them inlined, and
# the statics' exit destructors (10491, s_mutex's; 10492, s_inst's) match through the names 10500's votes give the
# statics, which they read. The constructor: CAppState's with EVENTO_ENTRADA (2), the vptr, the two forms from one
# builder slot (+84 of a 96-byte frame), then +32 = 1 and +28 = 0. The first form: CEleitorDadoNomeParaUrna::Text at
# {1, 1} with "{:2}", GetTextoIdentidadeDigitada at {1, 2}, "Seq:" at {32, 2}, CEleitorDadoSequencial::Text at {40, 2}
# with "{:04}" on the right, "Digite o ANO de nascimento:" at {1, 3}, vota::AdicionaCampoNumerico(builder, 4, true,
# {29, 3}), "CORRIGE: cancelar" at {1, 4}, "CONFIRMA: habilitar" at {40, 4} on the right, GetInteractiveForm("", true);
# the second: the same four fields, "ANO DE NASCIMENTO INCORRETO" at {1, 3}, "CONFIRMA: tentar novamente" at {40, 4} on
# the right, AddInputControl, GetInteractiveForm("", true). The statics are defined before StartState, their
# destructors' place in use band 0 (10492, 10491 above 10490). The vtable's sink in the roots went with 10500's landing.
#
# Matched since: vota::CPerguntaCodigoSuspensao::ProcessKey (10419, slot 6, in cperguntacodigosuspensao.cpp after
# ProcessInput, the band's order: 10420 links before 10419). Key 5 goes to CMostraEleitorVotando::GetInst (1150); keys 2
# and 13 clear the byte at +28 and go to vota::CEleitorVotouNaoVotou::GetInst (1901) with its +11 set to false, or to
# vota::CSincronismoOperador::GetInst (1897) with its +11 set to true, through two setters added to unit 71's and unit
# 104's headers (SetVotou, SetSincronizado; names chosen). The cases are written 5, 2, 13: the br_table sends key 5 to
# the first block and 13 to the last. With 2, 5, 13, 11 over 38 rows (3 inserted, 3 deleted); as written, 5 over 35,
# operand rows only, and a match (pnpm wasm score before steps 7 to 9).
#
# Matched since: vota::CPerguntaCodigoSuspensao::GetInst, inlined into 10415 (unit 152's fragment has its rows), with
# its statics' exit destructors (10422, s_mutex's; 10423, s_inst's), named by 10415's votes. The constructor, behind a
# 64-byte frame of its own: CAppState's with EVENTO_TECLA | EVENTO_ENTRADA (3), the forms at +12 and +20, each from a
# helper clang inlines whose builders share one frame slot (+52): AddClock({33, 1}), "Informe seu título para" at {1,
# 1}, "suspender a votação" at {1, 2}, "CORRIGE: retornar" at {1, 4}, "CONFIRMA: suspender" at {40, 4} on the right,
# AdicionaCampoNumerico(builder, 12, true, {1, 3}) (fn 1151), GetInteractiveForm("", true); then AddClock({33, 1}),
# "Título inválido para" at {1, 1}, "suspender a votação" at {1, 2}, GetInteractiveForm("", true); +28 cleared after
# both (the member list's order). The vtable's sink in the roots went: this constructor stores the vptr. Chosen: the
# helpers' names, their anonymous namespace, the statics' lines before StartState (10423 and 10422 above 10421 in use
# band 1).
#
# CPedeAnoNascimentoSemBiometria::ProcessInput (10489), matched: the reading of its first form in the private member
# LeAnoDigitado (a chosen name), which binaryen inlines behind its 16-byte frame, and of the second in ProcessInput's
# own frame; LeAnoDigitado holds CInformaAnoNascimentoErrado's GetInst, constructor and form inlined (written in
# cinformaanonascimentoerrado.cpp, its statics' exit destructors 10495 and 10494 matched) and two CLogVota members
# (unit 119's file), over md::CEleitorDecorator::GetAnoNascimento (5665, unit 91) and std::stoul (4661). Measured with
# pnpm wasm score in the whole link: the counter at +28 an int, 102 over 858 rows (its `<= 1` compiled as a signed
# `<= 0`, where the target compares the incremented value with 1 unsigned); unsigned, 98 over 857; with
# CLogVota::GetInst called in each arm instead of once into a local before the compare, 95 over 855 (the target calls it
# after the year's read, where clang hoists the arms' calls), with a local tee in the inlined GetInst left; with this
# file linked right after cinformaanonascimentoerrado.cpp (unit 161's, which linked after it), 93 over 854,
# operand-only. The target's data put CInformaAnoNascimentoErrado's vtable (@1591424) before
# CPedeAnoNascimentoSemBiometria's (@1591496): the callee's object first is that order (docs/reference/facts/codegen.md
# C4). So unit 161's list compiles this file, right after cinformaanonascimentoerrado.cpp; unit 161's fragment has the
# two placings measured and the 10 object pairs this one inverts. With the move no row left `match` (step 9's join
# against the base).
# Its form brings "Por favor oriente o eleitor a procurar o" (142758, 40 bytes), whose last character is where the
# target keeps the string "o": 7-Zip's FindPropIdExact (4929) loads 142797, and boost's lookup_default_collate_name's
# names table (@1618944, fn 9353's) holds it in its word 112. With the literal in the link both matched, and with
# 9353's name lookup_collatename (3498, `unresolved self-voted` before). Those matches are their libraries' bodies'.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
# cpedeanonascimentosembiometria.cpp, this unit's, is compiled in unit 161's list (10489's paragraph above).
# cinspecionaurna.cpp, unit 152's, links here ahead of curnainspecionada.cpp, the target data's order (CInspecionaUrna's
# vtable @1547448 before CUrnaInspecionada's @1547520): fn 11797 (CInspecionaUrna::ProcessInput), which holds
# CUrnaInspecionada::GetInst inlined, differs in local numbers with the other order (65 over 243 rows, pnpm wasm score in
# the whole link) and has operand rows only with this one (38 over 243). The move puts cinspecionaurna.cpp.o ahead of
# five objects whose data the target holds before its vtable (cconversorsecaoeleitoral.cpp, cconfirmavotosemcandidato.cpp,
# cinstrucaovotacaoacessibilidade.cpp, cvisualizarcandidatos.cpp and ctelascargo.cpp, by their records and vtables) and
# takes it behind sixteen whose data the target holds after it, which the link had before it.
APP_VOTA_ESTADOS_448_SRCS := src/app/vota/eleitor/cinspecionaurna.cpp \
    src/app/vota/eleitor/curnainspecionada.cpp \
    src/app/vota/operador/justificativa/cjustificativaefetuada.cpp \
    src/app/vota/operador/aguardaeleitor/cmostraeleitorvotando.cpp \
    src/app/vota/operador/aguardaeleitor/cperguntacodigosuspensao.cpp \
    src/app/vota/operador/aguardaeleitor/validatitulosuspensao.cpp
UENUX2_SRCS += $(APP_VOTA_ESTADOS_448_SRCS)
# The members not reconstructed: 142-uenux2-app-vota-estados-448-pending.cpp gives the vtables trapping bodies, compiled
# with the unit's flags
$(ROOT)/$(APP)/142-uenux2-app-vota-estados-448-pending.o: $(ROOT)/src/units/142-uenux2-app-vota-estados-448-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/142-uenux2-app-vota-estados-448.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/operador/justificativa/*.h $(ROOT)/src/uenux2/src/app/vota/operador/confirmaidentidade/*.h $(ROOT)/src/uenux2/src/app/vota/operador/aguardaeleitor/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/142-uenux2-app-vota-estados-448-pending.cpp -o $(R)
# 142-uenux2-app-vota-estados-448-roots.cpp keeps no vtable (every class's constructor is in the link) and stands in
# for ProcessKey's (10425) calls of comum::CEleitorDadosHabilitacao's constructor
$(ROOT)/$(APP)/142-uenux2-app-vota-estados-448-roots.o: $(ROOT)/src/units/142-uenux2-app-vota-estados-448-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/142-uenux2-app-vota-estados-448.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/142-uenux2-app-vota-estados-448-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/142-uenux2-app-vota-estados-448-pending.o $(APP)/142-uenux2-app-vota-estados-448-roots.o
