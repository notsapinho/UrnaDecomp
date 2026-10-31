# uenux2 vota operador states over comum::CAppState, and the members of other classes they need. Target fns matched:
# - vota::CSuspensaoAutomaticaEleitor (aguardaeleitor/csuspensaoautomaticaeleitor.cpp): the destructor and deleting
#   destructor (fns 2732, 10411, slots 0 and 1) and FinishState (10408, slot 5), which stops its tick through
#   vota::CThreadOperador::GetInst() (fn 270) and CThreadVota::StopTick (fn 422) and clears the byte at +24;
# - the StartState (slot 2) of six states over the destructors 49 final states share (fns 244 and 387):
#   vota::CPerguntaEleitorVotando (10416) and vota::CDesabilitaAudioEleitor (10436) in aguardaeleitor/,
#   vota::CHabilitaAudioEleitor (10524) in confirmaidentidade/, vota::CHorarioVotacaoTerminou (10758) and
#   vota::CPerguntaFilaEleitorVazia (10715) in outrasopcoes/, vota::CInspecionaUrna (11798) in app/vota/eleitor/;
# - vota::IIniciaJustificativa's constructor (3624, justificativa/iiniciajustificativa.cpp, its record's file);
# - vota::CLogVota::LogaAudioDesativadoFimVotacao and LogaSuspensaoAbortada (4529, 4535), in app/vota/log/clogvota.cpp
#   (unit 119's file), with the five members five of the StartStates hold inlined.
# The class headers say what each layout rests on; 152-uenux2-app-vota-operador-estados-pending.cpp names every slot
# left and what it waits for.
#
# Evidence, each read in the target (build/out bundles of `pnpm wasm fn`):
# - CSuspensaoAutomaticaEleitor: fn 10411 is `f2732(p0); drop; f136(p0)`, an out-of-line destructor
#   (docs/reference/facts/reading.md R5), and fn 2732 releases +44's, +36's and +28's std::shared_ptr and stores no
#   vptr, so the class is final (R4). The members: StartState (fn 10409) writes a C string into +28's pointee through
#   basic_string::__assign_external (fn 276) and tests +11 to choose it, sets +16 with an i64 10 and +12 from
#   CThreadVota::AddStoppedTick (fn 807); ProcessTick (fn 10405) counts +16 down with i64.ge_s; ProcessInput (fn 10407)
#   reads +44 through CInteractiveForm<IScreenMT, IInputMT>::Read() (record cinteractiveform.h:57); fn 10440 holds the
#   constructor inlined and fills +28 and +36 with blocks whose vptr is __shared_ptr_emplace<std::string>'s, so both are
#   std::make_shared<std::string>. The csuspensaoautomaticaeleitor.cpp:89 record (DisparaSinalizacaoSonora's lambda, fn
#   10410) keeps its line blank; the destructor is defined above it and FinishState below it, the band's order (fns
#   10411 above 10410 above 10409 above 10408), their lines a choice.
# - The six states: slots 0 and 1 are fns 244 and 387, which release +12's std::shared_ptr and nothing else (49 vtables
#   hold the pair: `python3 -I -c "import json; print(sum(e['functions'][:2] == [244, 387] for e in
#   json.load(open('ledger/vtables.json'))))"`); +12 is the form, which StartState shows (api::IForm's slot 2) and each
#   slot 7 reads through Read() (record cinteractiveform.h:57). Each StartState's order of the form's call, the next
#   state's store and the log is the target's. The logs: fn 11798 calls vota::CLogVota::GetInst (fn 184) after the
#   form's call and the store, and then opens a second stack frame that builds the message and calls
#   comum::IEventosLog::loga (fn 233), so its log is a CLogVota member binaryen inlined (docs/reference/facts/reading.md
#   R10), the shape of unit 142's. Fns 10416, 10436, 10524 and 10758 log first, so their only frame is at entry
#   whichever way the message is built: they are written as CLogVota members like 11798's (logaAlerta, fn 1398; loga, fn
#   233; api::CLoga::loga, fn 433, on CLogVota's +4) and match; the call in place was not compiled for them, so the
#   member is a choice there. Fn 10715 logs last and opens its frame at entry, before the next state's store, so its
#   message is built in StartState's own frame. Measured: the same message in a CLogVota member gives the second
#   prologue after the form's call, `21 over 82 rows (... inserted 5, deleted 5)`, and the call in place `11 over 77
#   rows (... [11 operand-only] ...)` and a match after step 9.
# - CLogVota::LogaAudioDesativadoFimVotacao and LogaSuspensaoAbortada: out of line with two callers each (fns 10435 and
#   10646; 10407 and 10420), each building its message and calling loga (fn 233) on `this`.
# - IIniciaJustificativa: its record (iiniciajustificativa.cpp:27, column 15) names the constructor and spells its
#   parameter `IConfirmaJustificativa *`; fn 3624 passes 0 to CAppState's constructor, stores the argument at +12 before
#   the vptr (a derived class's member), and throws CBaseError<vota::EUeVotaError, {9300, 9500}> (fn 253) with 9396 and
#   "Confirmação de justificativa nula" when it is null. Its vtable's slots 0 and 1 are fns 174 and 144, the shared
#   bodies an implicit destructor over CAppState's gives; slot 2 (fn 10587) is StartState, here the key function.
#
# Chosen, no evidence names them: every data member's name and, where only a width shows, its type (bool for the bytes,
# ueint64 for +16); GetInst and the private constructors, declared and not defined; the CLogVota members' names (from
# their messages) and their place after LogaTituloInvalidoRegistroMesario; the enumerator's name
# (app/vota/euevotaerror.h); the headers' paths, beside their .cpp, and every new .cpp's file name (the class name in
# lower case). The directories (how-to step 3, docs/reference/facts/placing.md P4, P5):
# - CPerguntaEleitorVotando, aguardaeleitor/: its vtable (@1593192) lies between unit 142's CPerguntaCodigoSuspensao's
#   (@1593120, after aguardaeleitor/cmostraeleitorvotando.cpp's records) and the record of
#   aguardaeleitor/csuspensaoautomaticaeleitor.cpp (@1593320): both sides name the directory.
# - CPerguntaFilaEleitorVazia, outrasopcoes/: its vtable (@1587692) lies between the records of
#   outrasopcoes/caguardaeleitoresvotarem.cpp (@1587664) and cencerramentohorarioinvalido.cpp (@1587808): both sides.
# - CDesabilitaAudioEleitor, aguardaeleitor/: its vtable (@1592856) lies between CEleitorDemorando's and unit 71's
#   CEleitorVotouNaoVotou's, unrecorded states back to confirmaidentidade/cregistradigitaloperador.cpp's records
#   (@1592596) and forward to aguardaeleitor/cmostraeleitorvotando.cpp's (@1593044). The adjacent side, as unit 71's.
# - CHabilitaAudioEleitor, confirmaidentidade/: its vtable (@1590852) follows CAguardaInspecao's and
#   CConfirmaInspecionada's (unrecorded), a record of api/gui/ctextsource.h and unit 51's CTextFieldUpdateMT's vtable
#   (operador/comum/), and precedes confirmaidentidade/ccontrolareconhecimento.cpp's records (@1591028) with nothing
#   between. The adjacent recorded side.
# - CHorarioVotacaoTerminou, outrasopcoes/: its vtable (@1586824) follows unit 119's CRegistroMesarioEncerrado's (a path
#   unit 119 guessed) and library objects, and precedes unrecorded vtables, unit 146's CInputFieldMT's among them, up to
#   outrasopcoes/caguardaeleitoresvotarem.cpp's records (@1587664). The nearest recorded side.
# - CInspecionaUrna, app/vota/eleitor/: its vtable (@1547448) lies between the records of
#   eleitor/iniciovotacao/testeteclado/ctesteteclado.cpp (@1547432) and unit 142's CUrnaInspecionada's vtable (@1547520,
#   in eleitor/). The directory both sides share.
#
# Not reconstructed, and what each waits for (callees with no name: ledger/callgraph.tsv against
# splat/symbol_addrs.txt):
# - every GetInst of these states and its constructor, which build the forms through fn 395 (the MT builder's input
#   control) or 1151: 5393 (CDesabilitaAudioEleitor's), the one inlined into 10440 (CSuspensaoAutomaticaEleitor's), and
#   the others' callers. 395 calls vector::emplace_back(&&), fn 3674, which clang inlines where the target keeps a call
#   (board fact on 3674; round 10's on 395 and 1151); fns 3673 and 3674 wait with them.
# - the pending slots: the -pending.cpp header lists them.
# - fn 10410, DisparaSinalizacaoSonora's lambda: it calls fn 3321, which has no name.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_OPERADOR_ESTADOS_SRCS := src/app/vota/operador/aguardaeleitor/csuspensaoautomaticaeleitor.cpp \
    src/app/vota/operador/aguardaeleitor/cperguntaeleitorvotando.cpp \
    src/app/vota/operador/aguardaeleitor/cdesabilitaaudioeleitor.cpp \
    src/app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.cpp \
    src/app/vota/operador/justificativa/iiniciajustificativa.cpp \
    src/app/vota/operador/outrasopcoes/chorariovotacaoterminou.cpp \
    src/app/vota/operador/outrasopcoes/cperguntafilaeleitorvazia.cpp \
    src/app/vota/eleitor/cinspecionaurna.cpp
UENUX2_SRCS += $(APP_VOTA_OPERADOR_ESTADOS_SRCS)
# The members not reconstructed: 152-uenux2-app-vota-operador-estados-pending.cpp gives the vtables trapping bodies,
# compiled with the unit's flags
$(ROOT)/$(APP)/152-uenux2-app-vota-operador-estados-pending.o: $(ROOT)/src/units/152-uenux2-app-vota-operador-estados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/152-uenux2-app-vota-operador-estados.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/operador/aguardaeleitor/*.h $(ROOT)/src/uenux2/src/app/vota/operador/confirmaidentidade/*.h $(ROOT)/src/uenux2/src/app/vota/operador/justificativa/*.h $(ROOT)/src/uenux2/src/app/vota/operador/outrasopcoes/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/152-uenux2-app-vota-operador-estados-pending.cpp -o $(R)
# nothing reconstructed references the seven states' vtables, IIniciaJustificativa's constructor or the two CLogVota
# members with two callers: 152-uenux2-app-vota-operador-estados-roots.cpp takes the vtables' addresses and stands in
# for the callers
$(ROOT)/$(APP)/152-uenux2-app-vota-operador-estados-roots.o: $(ROOT)/src/units/152-uenux2-app-vota-operador-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/152-uenux2-app-vota-operador-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/152-uenux2-app-vota-operador-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/152-uenux2-app-vota-operador-estados-pending.o $(APP)/152-uenux2-app-vota-operador-estados-roots.o
