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
# - the exit destructors of the statics of CEncerramentoHorarioInvalido (10711, 10712), CAguardaEleitoresVotarem (10719,
#   10720), CTituloEncerramentoInvalido (10729, 10730), CEncerramentoAntecipado (10732, 10733) and
#   CHabilitaAudioManualmente (10752, 10753), through ten callers+content hand lines (splat/symbol_addrs.txt, "Unit
#   277"): each object has two target readers, the slot that holds its class's GetInst inlined (named by vtable, which
#   casts no vote) and its exit destructor (`/usr/bin/grep -rlE 'i32\.const <address>($|[^0-9])'
#   build/out/splat/pieces/asm`). Weighed together: scanned twice on copies without the ten lines and the ten match
#   lines, the ten rows fall (to differs and no-candidate), the five slots go from differs to unresolved, and so do six
#   other exit destructors the census pairs with these statics' destructors, unmatched either way (7239, 10223, 10341,
#   10364, 10371 and 10418).
# This unit's members in other units' files, each noted in that unit's fragment: CPerguntaFilaEleitorVazia's GetInst
# (5426) with its statics' destructors (10716, 10717), its ProcessInput (10713) and CHorarioVotacaoTerminou's (10757)
# (unit 152); CSincronizaVota::SincronizaEstadoGeral (3333, unit 205) over CAppInfo::SalvaGeralInterno and
# SalvaGeralExterno (unit 109); CEstadoGeralVota::MarcaFimAquisicao (unit 93, held by 10734); eight CLogVota members
# (unit 119's file); accessors in vota::CThreadOperador's and comum::CConfiguracaoEleicao's headers (each says what it
# rests on). The class headers say what each layout rests on.
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
# Written, not matched, at this link (pnpm wasm score <target> <index> <link> <ours from names.tsv>):
# - CIniciaFinalizacao::StartState (10706): 237 over 671 rows (inserted 14, deleted 13). The next state is a local
#   stored once at the end, which our object then holds as one store after the arms, as matched 11838's object does;
#   this stage's first link, with a store in each arm and the log's message built in the call, read 289 over 679
#   (inserted 22, deleted 15). Left: binaryen's choice of locals in the
#   inlined CEncerramentoHorarioInvalido::GetInst, and LogaEncerramentoAntesDoHorario's call of api::CLoga::loga, which
#   the target makes while the format's temporaries live and after reading +4: of the two forms measured, the message
#   in a local reads +4 after the format but destroys the temporaries before the call, and the call in one statement
#   reads +4 before the format.
# - CEncerramentoHorarioInvalido::StartState (10710): 51 over 126 (inserted 13, deleted 9): the target's condition is
#   the `i32.or` of GetDemoMode's result and the training flag, ours of the flag and the result, and the target stores
#   the record of CPolySingleton<comum::IInterfaceInit>::instance() before the info call, ours after it. Our object
#   tests the flag first and calls first with the condition written either way and with the demo call in the
#   condition (three forms measured on the object, one object).
# - CPedeTituloEncerramento::ProcessInput (10721, 313 over 1046, inserted 11, deleted 10), StartState (10722, 171 over
#   423, inserted 4, deleted 3), CPerguntaFilaEleitorVazia::ProcessInput (10713, unit 152), CEncerramentoAntecipado::
#   ProcessInput (10731, 8 over 70, every row an operand: `local.tee 0` against our `local.tee 1`) and CConfirmaAudio::
#   ProcessInput (10740, 102 over 422, inserted 8, deleted 7): every row that differs is a local's number, binaryen's
#   (in 10731 the target gives the field pointer p0 where ours gives it l1, after `this` is pushed for the merged
#   store; matched 11838 takes l1 as ours does). For 10731 the switch, an if chain, the cases swapped and the cases
#   ending in return each give one store after the switch in the object (measured). Not explained.
# - CConfirmaEncerramento::ProcessInput (10734): 49 over 273 (inserted 2, deleted 2), all in MarcaFimAquisicao (unit
#   93's fragment has the forms measured). Its store of the state goes through CEstadoGeralVota::SetEstadoVota, out of
#   line in cestadogeralvota.cpp (unit 156's measurement); written in the class instead, 10734 scored the same.
# - CEncerramentoHorarioInvalido::ProcessInput (10709) and unit 152's CHorarioVotacaoTerminou::ProcessInput (10757)
#   match since the link holds 2295's other three members (units 161, 278 and 283): with only these two, our link
#   merged them into one shared body of two parameters, each 14-byte thunk passing its record, where the target's 2295
#   takes the input code as a third, since its five thunks pass 5 (10604, 10667, 10709, 10757) or 9 (10461,
#   CTentativaCapturaDigitalEsgotada's slot 7): pnpm wasm score of 2295 against that body, 23 over 61, the one row not
#   an operand `local.get 1` against `i32.const 5`, beside the signature. With 10461 in the link, binaryen passes the
#   key too, and 2295 matches under that merge's name
#   (`byn$mgfn-shared$_ZN4vota23CHorarioVotacaoTerminou12ProcessInputEv`, the first member in link order).
#
# Not written, and what each waits for:
# - vota::CEscolheOpcao::ProcessInput (10689), which holds the GetInst of CIniciaFinalizacao, CConfirmaAudio,
#   CHabilitacaoAudioNaoPermitida and CContadoresBiometria inlined: unit 121's -pending.cpp says what it waits for.
#   Those four GetInst, their constructors and statics are declared and not defined; their statics' exit destructors
#   (10707, 10708; 10743, 10744; 10755, 10756; 10704, 10705) and the text functions their forms pass by slot (10742;
#   10699, 10700, 10701) wait with it. The roots sink the four vtables until then.
# - CIniciodeCiclo::StartState (7306): unit 104's -pending.cpp.
#
# Chosen, no evidence names them: every file's name and path (beside its class), the helpers' (MontaTela, in each
# file's anonymous namespace) and locals' names, every data member's name, GetInst's and the constructors' access,
# ConfirmaTitulo's and TituloValido's names and their being members (TituloValido
# reads no member: a static member, where a free function of external linkage was not tried), TituloEncerramentoDigitado's
# being a free function, each function's line (no record but 10718's and 10710's, whose lines the files keep), and the
# local next state in CIniciaFinalizacao::StartState (the bytes ask for one store, which a local gives).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_OPERADOR_OUTRASOPCOES_SRCS := src/app/vota/operador/outrasopcoes/ciniciafinalizacao.cpp \
    src/app/vota/operador/outrasopcoes/cpedetituloencerramento.cpp \
    src/app/vota/operador/outrasopcoes/ctituloencerramentoinvalido.cpp \
    src/app/vota/operador/outrasopcoes/cencerramentoantecipado.cpp \
    src/app/vota/operador/outrasopcoes/cconfirmaencerramento.cpp \
    src/app/vota/operador/outrasopcoes/caguardaeleitoresvotarem.cpp \
    src/app/vota/operador/outrasopcoes/cencerramentohorarioinvalido.cpp \
    src/app/vota/operador/outrasopcoes/cconfirmaaudio.cpp \
    src/app/vota/operador/outrasopcoes/chabilitaaudiomanualmente.cpp \
    src/app/vota/operador/outrasopcoes/chabilitacaoaudionaopermitida.cpp \
    src/app/vota/operador/outrasopcoes/ccontadoresbiometria.cpp
UENUX2_SRCS += $(APP_VOTA_OPERADOR_OUTRASOPCOES_SRCS)
# comum::CConfiguracaoEleicao's header reaches ecourna's chorariosurna.hpp, which includes Boost.Date_Time
$(addprefix $(ROOT)/$(APP)/uenux2/,$(addsuffix .o,src/app/vota/operador/outrasopcoes/ciniciafinalizacao.cpp src/app/vota/operador/outrasopcoes/cpedetituloencerramento.cpp src/app/vota/operador/outrasopcoes/cencerramentohorarioinvalido.cpp)): UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# nothing reconstructed references four of the states' vtables: 277-uenux2-app-vota-operador-outrasopcoes-roots.cpp
# takes their addresses
$(ROOT)/$(APP)/277-uenux2-app-vota-operador-outrasopcoes-roots.o: $(ROOT)/src/units/277-uenux2-app-vota-operador-outrasopcoes-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/277-uenux2-app-vota-operador-outrasopcoes.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/277-uenux2-app-vota-operador-outrasopcoes-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/277-uenux2-app-vota-operador-outrasopcoes-roots.o
