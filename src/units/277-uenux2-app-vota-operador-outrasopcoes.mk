# uenux2 vota operador outras opcoes: the states of the closing of the voting and of the audio option over
# comum::CAppState, each in its own app/vota/operador/outrasopcoes/<class in lower case>.{h,cpp}. Target fns matched:
# - vota::CPedeTituloEncerramento::GetInst (3631) and vota::CConfirmaEncerramento::GetInst (3632), each holding its
#   constructor and the form's helper inlined, named by vptr-anchor, with their statics' exit destructors (10724, 10725;
#   10735, 10736), whose objects the GetInsts' votes name;
# - over the destructors 49 final states share (fns 244 and 387): CAguardaEleitoresVotarem::StartState (10718, record
#   caguardaeleitoresvotarem.cpp:47:5), CTituloEncerramentoInvalido::ProcessInput (10727),
#   CHabilitacaoAudioNaoPermitida::StartState (10754) and CContadoresBiometria::ProcessInput (10698); over the ones 19
#   states share (fns 448 and 765), CHabilitaAudioManualmente::StartState (10751);
# - TituloEncerramentoDigitado (10728, a free function, its name chosen), the text of CTituloEncerramentoInvalido's form,
#   by the content pass; 10721, which passes its slot (3781) to AddTextField (fn 619), passes ours at the aligned site;
# - the slots that hold another class's GetInst inlined by binaryen, matches with the list in the target's data order
#   (below), which links that class's object ahead of the slot's own: CConfirmaAudio::ProcessInput (10740,
#   CHabilitaAudioManualmente's GetInst), CPedeTituloEncerramento::StartState (10722, CEncerramentoAntecipado's) and
#   ProcessInput (10721, CTituloEncerramentoInvalido's), unit 152's CPerguntaFilaEleitorVazia::ProcessInput (10713,
#   CAguardaEleitoresVotarem's), and CIniciaFinalizacao::StartState (10706, CEncerramentoHorarioInvalido's), which also
#   needs CLogVota::LogaEncerramentoAntesDoHorario's log call made through a member (below);
# - CEncerramentoAntecipado::ProcessInput (10731) and CEncerramentoHorarioInvalido::StartState (10710), with their
#   next-state stores through comum::CAppState::SetNextState (unit 61's fragment has the measurements);
# - CConfirmaEncerramento::ProcessInput (10734), named by srcloc-anchor, which holds unit 93's
#   CEstadoGeralVota::MarcaFimAquisicao behind a 48-byte prologue: it matches with that member's first test through
#   CEstadoGeralVota::IsFimAquisicaoMarcado, a call clang inlines (unit 93's fragment has the forms measured);
# - the exit destructors of the statics of those five GetInst's classes, CEncerramentoHorarioInvalido (10711, 10712),
#   CAguardaEleitoresVotarem (10719, 10720), CTituloEncerramentoInvalido (10729, 10730), CEncerramentoAntecipado (10732,
#   10733) and CHabilitaAudioManualmente (10752, 10753): each object has two target readers, the slot that holds its
#   class's GetInst inlined and its exit destructor (`/usr/bin/grep -rlE 'i32\.const <address>($|[^0-9])'
#   build/out/splat/pieces/asm`), and the matched slot's votes name it (splat/symbol_addrs.txt, `vote:N by:10706`,
#   `by:10713`, `by:10721`, `by:10722`, `by:10740`). The ten callers+content hand lines that named them while the slots
#   did not match went: weighed on copies of the symbol file without them and of the match list without the slots'
#   and destructors' lines, scanned twice beside a control over the same match copy, the copy and the control hold the
#   same match rows (eight lines: 12362 and 12362; the last two, once 10706 matched: 12363 and 12363) and splat-build
#   gives the target's sha256 on both pairs.
# This unit's members in other units' files, each noted in that unit's fragment: CPerguntaFilaEleitorVazia's GetInst
# (5426) with its statics' destructors (10716, 10717), its ProcessInput (10713) and CHorarioVotacaoTerminou's (10757)
# (unit 152; cperguntafilaeleitorvazia.cpp itself is in this unit's list, for its link order);
# CSincronizaVota::SincronizaEstadoGeral (3333, unit 205) over CAppInfo::SalvaGeralInterno and SalvaGeralExterno (unit
# 109); CEstadoGeralVota::MarcaFimAquisicao (unit 93, held by 10734); eight CLogVota members and LogaAlertaVota, the
# private helper of one of them (unit 119's file); comum::CAppState::SetNextState (unit 61's file); accessors in
# vota::CThreadOperador's and comum::CConfiguracaoEleicao's headers (each says what it rests on). The class headers say
# what each layout rests on.
#
# Evidence, each read in the target (`pnpm wasm fn`):
# - The vtables (ledger/vtables.json): every class's lies in the run from CHorarioVotacaoTerminou's (@1586824, unit
#   152's, outrasopcoes/) to CEscolheOpcao's (@1587996, unit 121's outrasopcoes/cescolheopcao.cpp, its records
#   @1588040 to @1588072 after it), with unit 104's CFimAquisicaoVotos (@1587212, outrasopcoes/) and the records of
#   outrasopcoes/caguardaeleitoresvotarem.cpp (@1587664) and cencerramentohorarioinvalido.cpp (@1587808, @1587824)
#   inside, and no record of another directory (`awk -F'\t' '$1>=1586700 && $1<=1588100' ledger/source-locations.tsv`
#   lists those and cinteractiveform.h's and ctextsource.h's): outrasopcoes/ on both sides (placing.md P4, P5).
# - The destructors: slots 0 and 1 are 244 and 387 (49 vtables), 448 and 765 (19) or, for CIniciaFinalizacao, 174 and
#   144 (`python3 -I -c "import json; v=json.load(open('ledger/vtables.json')); print(sum(e['functions'][:2] == [244,
#   387] for e in v))"`, and so for the others).
# - The forms, as unit 152's rule reads them: built in the member list from a helper where the builder's result is
#   written into the member (fn 301's result address is the member's, nothing zeroed before): CPedeTituloEncerramento,
#   CTituloEncerramentoInvalido, CEncerramentoAntecipado, CConfirmaEncerramento, CEncerramentoHorarioInvalido and unit
#   152's CPerguntaFilaEleitorVazia (3631, 3632 and 5426 match so); built in the constructor's body and assigned, the
#   member's two words zeroed first: CAguardaEleitoresVotarem and CHabilitaAudioManualmente.
# - Members the bodies hold behind a frame of their own (reading.md R10): CPedeTituloEncerramento::ConfirmaTitulo (16
#   bytes) and TituloValido (400) in 10721, and the CLogVota members after their caller's call of CLogVota::GetInst.
# - TituloValido: the target builds the whole number ("{:0>{}}" with 12) before it calls CValidadorIdentidade::GetInst
#   (1926) and EhValida (2803), and keeps the text's begin and size across the digit loop. Measured on the object
#   (wasm-objdump -d of the TU): the number in a local gives both; formatted in the call, GetInst came between the format
#   and the string, and the text's words were loaded again after the loop. std::all_of, a range-for and
#   std::ranges::all_of give the same object.
#
# Measured (pnpm wasm score <target> <index> <link> <ours from names.tsv>):
# - The seven matched above, before: with the assignments and the lists as they were (cperguntafilaeleitorvazia.cpp in
#   unit 152's list, ahead of this one; ciniciafinalizacao.cpp first here), 10706 read 237 over 671 rows (inserted 14,
#   deleted 13), 10710 51 over 126 (13, 9), 10721 313 over 1046 (11, 10), 10722 171 over 423 (4, 3), 10713 52 over 611
#   (deleted 2), 10731 8 over 70 (every row an operand: `local.tee 0` against our `local.tee 1`) and 10740 102 over 422
#   (8, 7): binaryen's local numbers and places, and 10706's log call. With the list in the data's order, 10740, 10722,
#   10721 and 10713 read operand rows only (38 over 414, 43 over 419, 74 over 1035, 46 over 611) and matched at step 9;
#   10706 read 81 over 664 (inserted 7, deleted 7), all in the log call below. A replay of the link's wasm-opt with unit
#   104's cfimaquisicaovotos.cpp and unit 152's chorariovotacaoterminou.cpp moved into the data's order too gave the same
#   scores (unit 61's fragment says how the replay is run), so those two stay in their units.
# - CLogVota::LogaEncerramentoAntesDoHorario (clogvota.cpp, unit 119's file), which 10706 holds inlined: the target calls
#   api::CLoga::loga while the format's argument temporaries live ("hh:mm:ss" at +8 of the member's frame, the time's
#   text at +20), destroys the message (+352) before them, and reads +4 after the message is built. On 10706: the message
#   in a named local reads +4 after the format but destroys the temporaries before the call (81 over 664); the call in
#   one statement reads +4 before the format (measured when the member was written); the three strings as named locals
#   in that order give the destructions' order and the call's place but put "hh:mm:ss" and the time's text at +16 and
#   +4 (73 over 657, operand rows); the call made through a member given the message in one statement, LogaAlertaVota,
#   defined above it, gives the target's rows, names only, and so does a lambda that captures `this` in its place (the
#   same module, sha256). The member, its name and its being a member and not a lambda or another helper are chosen.
# - CConfirmaEncerramento::ProcessInput (10734), before MarcaFimAquisicao's test went through IsFimAquisicaoMarcado: 49
#   over 273 (inserted 2, deleted 2), all in MarcaFimAquisicao (unit 93's fragment has the forms measured), on the
#   whole link with its store of the state through
#   CEstadoGeralVota::SetEstadoVota out of line in cestadogeralvota.cpp (cestadogeralvota.h says what keeps it there);
#   with the setter written in the class it scores the same 49 over 273, both on the link that also holds unit 156's
#   CEstadoGeralVota::SetEstadoEncerramento (left out of line) and on an earlier one without it. With the list in the
#   data's order it reads the same 49 over 273, and its two stores through SetNextState gave a byte-identical module (on
#   the link before that order).
# - CEncerramentoHorarioInvalido::ProcessInput (10709) and unit 152's CHorarioVotacaoTerminou::ProcessInput (10757)
#   match since the link holds 2295's other three members (units 161, 278 and 283): with only these two, our link
#   merged them into one shared body of two parameters, each 14-byte thunk passing its record, where the target's 2295
#   takes the input code as a third, since its five thunks pass 5 (10604, 10667, 10709, 10757) or 9 (10461,
#   CTentativaCapturaDigitalEsgotada's slot 7): pnpm wasm score of 2295 against that body, 23 over 61, the one row not
#   an operand `local.get 1` against `i32.const 5`, beside the signature. With 10461 in the link, binaryen passes the
#   key too, and 2295 matches under that merge's name
#   (`byn$mgfn-shared$_ZN4vota23CHorarioVotacaoTerminou12ProcessInputEv`, the first member in link order).
#
# For vota::CEscolheOpcao::ProcessInput (10689, unit 121's, written and not matched: that fragment has the
# measurement), which holds them inlined: the GetInst, constructor, form and statics of CIniciaFinalizacao,
# CConfirmaAudio, CHabilitacaoAudioNaoPermitida and CContadoresBiometria, written in their files as the matched
# CConfirmaEncerramento's are (no target function of their own; in 10689 the last three constructors open frames of
# 64, 48 and 64 bytes that hold their form's builder too: MontaTela in the anonymous namespace, one frame for both, as
# unit 247's fragment measures for that linkage). With them, matched
# by the content pass, the texts their forms pass by table slot, free functions of namespace vota defined after the
# statics: CContadoresBiometria's TextoHabilitacaoBiometrica, TextoHabilitacaoBiografica and
# TextoHabilitacaoSemBiometria (10701, 10700, 10699, slots 3818 to 3820: "n.a." when comum::CLocal::UrnaBiometrica is
# false, else "{:04}" of comum::CEleitores' count of that kind of enabling, formatted into "Habilitação biométrica: {}"
# and the two others), and CConfirmaAudio's TextoConfirmaAudio (10742, slot 3757: "Deseja realmente desativar o
# áudio?" or "... ativar o áudio?" by IsAudioAtivadoMesario, two returns, the target's two fixed copies). In band 1 each
# file's statics' destructors come first, then the texts, then the slots (10705, 10704, 10701 to 10699, 10698;
# 10744, 10743, 10742, 10740), the order they are defined in, which names.tsv's ld_index gives our link too. The four
# vtable sinks went with this unit's roots file:
# 10689's constructors store the four vptrs. Their names, the texts' being free functions, the texts' form (a local
# set to "n.a." and overwritten when UrnaBiometrica holds; no other form was measured) and the GetInst's form are
# chosen.
# The four states' statics' exit destructors (10707, 10708; 10743, 10744; 10755, 10756; 10704, 10705) wait for 10689's
# match.
#
# CIniciodeCiclo::StartState (7306) is written since, in ciniciodeciclo.cpp (unit 104's fragment).
#
# Chosen, no evidence names them: every file's name and path (beside its class), the helpers' (MontaTela, in each
# file's anonymous namespace) and locals' names, every data member's name, GetInst's and the constructors' access,
# ConfirmaTitulo's and TituloValido's names and their being members (TituloValido
# reads no member: a static member, where a free function of external linkage was not tried), TituloEncerramentoDigitado's
# being a free function, each function's line (no record but 10718's and 10710's, whose lines the files keep), the
# local next state in CIniciaFinalizacao::StartState (the bytes ask for one store, which a local gives), and that the
# setter called for 10731's and 10710's next-state stores is a setter (unit 61's fragment: an empty call binaryen
# inlines gives them the same rows), and that the other members assign (for those measured the two forms gave one
# module).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header. The list is in the
# order of the classes' vtables in the target's data (placing.md P4; ledger/vtables.json): CHabilitacaoAudioNaoPermitida
# @1586896, CHabilitaAudioManualmente @1586952, CConfirmaAudio @1587140, CConfirmaEncerramento @1587268,
# CEncerramentoAntecipado @1587340, CTituloEncerramentoInvalido @1587412, CPedeTituloEncerramento @1587548,
# CAguardaEleitoresVotarem @1587620, unit 152's CPerguntaFilaEleitorVazia @1587692 (its file moved here, as how-to step
# 3 and src/units/README.md "Names" say for a file whose order against another unit's decides a body: 10713),
# CEncerramentoHorarioInvalido @1587764, CIniciaFinalizacao @1587868, CContadoresBiometria @1587924 and, last, unit 121's
# cescolheopcao.cpp (CEscolheOpcao @1587996: its ProcessInput, 10689, holds the GetInst of four of this list's classes;
# unit 121's fragment has its measurement and keeps the file's notes). Measured, as the first item above says; the two
# classes of this run in other units' lists, unit 152's CHorarioVotacaoTerminou (@1586824) and unit 104's
# CFimAquisicaoVotos (@1587212), stay there.
APP_VOTA_OPERADOR_OUTRASOPCOES_SRCS := src/app/vota/operador/outrasopcoes/chabilitacaoaudionaopermitida.cpp \
    src/app/vota/operador/outrasopcoes/chabilitaaudiomanualmente.cpp \
    src/app/vota/operador/outrasopcoes/cconfirmaaudio.cpp \
    src/app/vota/operador/outrasopcoes/cconfirmaencerramento.cpp \
    src/app/vota/operador/outrasopcoes/cencerramentoantecipado.cpp \
    src/app/vota/operador/outrasopcoes/ctituloencerramentoinvalido.cpp \
    src/app/vota/operador/outrasopcoes/cpedetituloencerramento.cpp \
    src/app/vota/operador/outrasopcoes/caguardaeleitoresvotarem.cpp \
    src/app/vota/operador/outrasopcoes/cperguntafilaeleitorvazia.cpp \
    src/app/vota/operador/outrasopcoes/cencerramentohorarioinvalido.cpp \
    src/app/vota/operador/outrasopcoes/ciniciafinalizacao.cpp \
    src/app/vota/operador/outrasopcoes/ccontadoresbiometria.cpp \
    src/app/vota/operador/outrasopcoes/cescolheopcao.cpp
UENUX2_SRCS += $(APP_VOTA_OPERADOR_OUTRASOPCOES_SRCS)
# comum::CConfiguracaoEleicao's header reaches ecourna's chorariosurna.hpp, which includes Boost.Date_Time
$(addprefix $(ROOT)/$(APP)/uenux2/,$(addsuffix .o,src/app/vota/operador/outrasopcoes/ciniciafinalizacao.cpp src/app/vota/operador/outrasopcoes/cpedetituloencerramento.cpp src/app/vota/operador/outrasopcoes/cencerramentohorarioinvalido.cpp src/app/vota/operador/outrasopcoes/cescolheopcao.cpp)): UENUX2_CXXFLAGS += -I$(BOOST_HDR)
