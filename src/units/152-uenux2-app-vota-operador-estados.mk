# uenux2 vota operador states over comum::CAppState, and the members of other classes they need. Target fns matched:
# - vota::CSuspensaoAutomaticaEleitor (aguardaeleitor/csuspensaoautomaticaeleitor.cpp): the destructor and deleting
#   destructor (fns 2732, 10411, slots 0 and 1) and FinishState (10408, slot 5), which stops its tick through
#   vota::CThreadOperador::GetInst() (fn 270) and CThreadVota::StopTick (fn 422) and clears the byte at +24; StartState
#   (10409, slot 2), ProcessInput (10407, slot 7) and ProcessTick (10405, slot 8), and the members they call: the text's
#   update, AtualizaMensagem (3612), DisparaSinalizacaoSonora (5392, the record's name, csuspensaoautomaticaeleitor.cpp:89
#   being its lambda's line) with std::thread's __thread_proxy over that lambda (10410), and the destroy of the local
#   std::map StartState builds (3613);
# - vota::CPerguntaEleitorVotando::ProcessKey (5394, slot 6, one body with vota::CEleitorDemorando's slot 6, a class our
#   link does not hold) and vota::CHabilitaAudioEleitor::ProcessInput (10523, slot 7);
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
# Evidence, each read in the target (`pnpm wasm fn` of each function):
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
#   state's store and the log is the target's. The logs (offsets from `pnpm wasm fn` of each target function): fns
#   10416, 10436, 10524 and 10758 call vota::CLogVota::GetInst (fn 184) at +0x03 and set up their only stack frame at
#   +0x06, after it; fn 11798 calls it at +0x1c, after the form's call and the next state's store, and sets up its only
#   frame at +0x1f. A frame opened after the call of GetInst is the prologue of a member binaryen inlined
#   (docs/reference/facts/reading.md R10), the shape of unit 142's: so each of the five logs through a CLogVota member
#   that builds the message and calls comum::IEventosLog::logaAlerta (fn 1398), loga (fn 233) or api::CLoga::loga (fn
#   433, on CLogVota's +4). Measured on 10436 at the tree's flags (llvm-objdump -d of the object): the message built in
#   place, CLogVota::GetInst().loga("..."), puts the frame at entry, before the call of GetInst; the member gives `call
#   GetInst; call LogaPedidoDesconexaoFone` and no frame in StartState. Fn 10715 sets up its frame at +0x03, before
#   everything, and calls fn 184 at +0x25, so its message is built in StartState's own frame. Measured: the same message
#   in a CLogVota member gives a prologue after the form's call, `21 over 82 rows (... inserted 5, deleted 5)`, and the
#   call in place `11 over 77 rows (... [11 operand-only] ...)` and a match after step 9.
# - CLogVota::LogaAudioDesativadoFimVotacao and LogaSuspensaoAbortada: out of line with two callers each (fns 10435 and
#   10646; 10407 and 10420), each building its message and calling loga (fn 233) on `this`.
# - IIniciaJustificativa: its record (iiniciajustificativa.cpp:27, column 15) names the constructor and spells its
#   parameter `IConfirmaJustificativa *`; fn 3624 passes 0 to CAppState's constructor, stores the argument at +12 before
#   the vptr (a derived class's member), and throws CBaseError<vota::EUeVotaError, {9300, 9500}> (fn 253) with 9396 and
#   "Confirma√ß√£o de justificativa nula" when it is null. Its vtable's slots 0 and 1 are fns 174 and 144, the shared
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
#   in eleitor/). The directory both sides share. Its form is the voter screen's: its slot 7 (fn 11797) loads the record
#   of api::CInteractiveForm<api::IScreen, api::IInputKbd>::Read() (cinteractiveform.h:57 @1547504), where the operator
#   states' slots 7 load the <api::IScreenMT, api::IInputMT> one; cinspecionaurna.h types +12 so.
#
# Not reconstructed, and what each waits for (callees with no name: ledger/callgraph.tsv against
# splat/symbol_addrs.txt):
# - every GetInst of these states and its constructor, which build the forms through fn 395 (the MT builder's input
#   control) or 1151: 5393 (CDesabilitaAudioEleitor's), the one inlined into 10440 (CSuspensaoAutomaticaEleitor's), and
#   the others' callers. 395 and 1151 call fns 3673 and 3674, whose callers in the target are 395, 1151 and 5410; 5410
#   builds a state's form in another TU and still calls 3674. Fn 3674 is vector<shared_ptr<...>>::emplace_back(&&), out
#   of line. With 395 written as an out-of-line CMTFormBuilder member in api/gui/cmtformbuilder.cpp that pushes through
#   a by-value AddField there, clang inlines emplace_back into it: at the tree's flags `-Rpass=inline` prints `inlined
#   into 'AddInputControl' with (cost=300, threshold=325)`, at -std=c++20 and at -std=c++23 alike. Written instead as an
#   in-class AddInputControl over a private AddField(SharedField&&) in api/gui/cmtformbuilder.cpp, the object keeps the
#   call (`not inlined into 'AddField' ... (cost=340, threshold=325)`), but the link's binaryen inlines emplace_back
#   into AddField, its one caller, where the target keeps fn 3674 with three: `pnpm wasm score` gives 395 `179 over 271
#   rows` and 3674 against AddField `68 over 157 rows`. So 395, 1151, 3673 and 3674 are not written.
# - the pending slots: the -pending.cpp header lists them.
#
# Evidence and forms of the members written since (each measured in the whole link with pnpm wasm score):
# - StartState (10409) runs the tick part in a function of its own that binaryen inlined: `this` copied to a local at
#   entry, the 16-byte frame of the local std::map opened and closed around it, and the map built through two locals
#   that hold its address and the thread's tick map's (the signs of a callee's parameters). So InicializaTick, a private
#   member (name chosen), holds the map's copy (api::CTickManager::GetEstadoTicks, out of line in unit 02's
#   ctickmanager.cpp, inlined by binaryen in turn), its find and either a new stopped tick of 1000 ms or a stop of the
#   active one; the caller compares the map's byte with 1, which reads as no bool (api::CTickManager::EEstadoTick, chosen).
#   Written in StartState, the body read `181 over 302 rows`; with GetEstadoTicks out of line (and the find's test
#   negated, its arms swapped), `105 over 281 rows`; with InicializaTick out of line too, as written, `10 over 262 rows`,
#   operand rows only, and it matches. The destroy (3613) is
#   recursive and has one caller besides itself, so no vote names it: a callers+content hand line does, on that caller
#   and the aligned call; 10409 and 3613 match through it. The map's mapped type in its symbol is chosen.
# - In ProcessTick the stores of +24 and +16 come out in the reverse of the source's order, and StartState's pair is
#   written the same way, each in the order that gives the target's: ProcessTick with the stores swapped read `14 over 82 rows (same 68,
#   replaced 6 [6 operand-only], inserted 4, deleted 4)`, and with them as written `7 over 78`, operand rows only.
# - The messages go through the queue's inline Post (api/ipc/cmessagequeue.h), whose own local is the message: written
#   as Insert of a temporary, ProcessInput (10407) read `16 over 88 rows`, operand rows only but frame slots swapped: the
#   target keeps Read()'s std::source_location at +4 and the message at +8, ours at +12 and +4; with Post, 11 over 88,
#   names only.
#   StartState's Post (3) and CHabilitaAudioEleitor's Posts are written so too.
# - DisparaSinalizacaoSonora: `std::thread([] { ... }).detach();` on line 89, which puts the lambda's
#   CPolySingleton<api::IScreenMT>::instance() call at column 22, its record's; the lambda buzzes the MT screen (slot 6,
#   Buzz, 50 and 3). Ours keeps the member out of line, with std::thread's constructor inlined in it, and it matches 5392,
#   whose wasm type has no parameter; whether the target's 5392 is that member or the constructor is not in its bytes (a
#   reading, not measured the other way). AtualizaMensagem (3612, name chosen) builds "Suspens„o autom·tica em " +
#   std::to_string(+16) + " segundo..."/" segundos..." into +36's string, the literal built first.
# - CHabilitaAudioEleitor::ProcessInput reads the form, asks vota::impl::IInformacaoThreadOperador's slot 5
#   (IsAudioAtivadoCadastro) and on CONFIRMA clears the operator's audio flag (5415), posts 8 or 9 and then 1 to the
#   eleitor's queue, goes to CMostraEleitorVotando::GetInst (1150, unit 142's) and, when the record's audio is on, logs
#   "¡udio ativado conforme cadastro" through a CLogVota member binaryen inlines (unit 119's file).
# - The roots' stand-in for 4535's caller 10407 went with 10407 (the roots' header).
# Chosen: InicializaTick's and AtualizaMensagem's names and lines, the enumeration's names, the local names, the queue
# held in a local for the 8/9 choice in CHabilitaAudioEleitor (one GetInst, as the target calls it once there).
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
