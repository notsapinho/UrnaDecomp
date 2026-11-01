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
#   headers list what each stores). Four stay unwritten here: fns 11797, 2747, 10500 and 10415 call functions with no
#   name (ledger/callgraph.tsv against splat/symbol_addrs.txt; each header names them). Fn 1150 is written (below).
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
# private constructor, declared and not defined, their names following the project's other singletons; the destructor
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
#   10204 calls fn 203; 1150 clears the builder in place, as unit 104's fragment reads 10214, 4633 and 5341 doing (5343
#   and 10676 not read), where 88 other target functions call 203. That remainder is not explained. No vote names 1150 (its callers are vtable slots or not written,
#   and its body anchors nothing), so a hand line names it by `rtti-vptr`: it alone holds the class's address point
#   1593008. 5394, 10407 and 10523 (unit 152's) match through it.
# - Its statics' exit destructors, 10429 (the std::unique_ptr at 1909316) and 10428 (the std::mutex at 1909292), match:
#   their .bss names come from two `callers+content` hand lines, each resting on 1150's use of the address. The statics
#   are defined after GetInst, s_inst first: 10429 lies above 10428 in their use band, so it links first.
# - 10539, the text "ÁUDIO ATIVADO" or " ": " " unless CThreadEleitor's instance exists (read under its mutex, through
#   the inline CThreadEleitor::Existe added to cthreadeleitor.h) and CEstadoAudio's mode is not 2, or
#   IsAudioAtivadoMesario (1687, unit 50's) holds. Only 1150 passes its slot. It is a function of this file's anonymous
#   namespace, TextoAudioAtivado: name, linkage and file are chosen, the file against its band, which puts 10539 right
#   after api::CTextFieldUpdateMT's constructor's lambda's slots (10540 to 10544), not among this file's functions
#   (10424 to 10429).
# Chosen too: CriaForm's name and its being a static member, the statics' names.
#
# A written body that does not match: CPedeAnoNascimentoSemBiometria::StartState (fn 10490) is `differs`. The target
# stores +4 (the next state) first, then +32 and +28. Each of the six orders of the three statements compiles at the
# tree's flags with the +4 store last, and the order written here does so at -O1, -O2, -O3, -Os and -Oz, and with and
# without -fno-strict-aliasing; its IR keeps the source's order, so the wasm code generator moves the store. No form
# found gives the target's order; the body kept is the plainest one, in the target's order.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_ESTADOS_448_SRCS := src/app/vota/eleitor/curnainspecionada.cpp \
    src/app/vota/operador/justificativa/cjustificativaefetuada.cpp \
    src/app/vota/operador/confirmaidentidade/cpedeanonascimentosembiometria.cpp \
    src/app/vota/operador/aguardaeleitor/cmostraeleitorvotando.cpp \
    src/app/vota/operador/aguardaeleitor/cperguntacodigosuspensao.cpp
UENUX2_SRCS += $(APP_VOTA_ESTADOS_448_SRCS)
# The members not reconstructed: 142-uenux2-app-vota-estados-448-pending.cpp gives the vtables trapping bodies, compiled
# with the unit's flags
$(ROOT)/$(APP)/142-uenux2-app-vota-estados-448-pending.o: $(ROOT)/src/units/142-uenux2-app-vota-estados-448-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/142-uenux2-app-vota-estados-448.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/operador/justificativa/*.h $(ROOT)/src/uenux2/src/app/vota/operador/confirmaidentidade/*.h $(ROOT)/src/uenux2/src/app/vota/operador/aguardaeleitor/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/142-uenux2-app-vota-estados-448-pending.cpp -o $(R)
# nothing reconstructed references the five classes yet: 142-uenux2-app-vota-estados-448-roots.cpp takes their vtables'
# addresses
$(ROOT)/$(APP)/142-uenux2-app-vota-estados-448-roots.o: $(ROOT)/src/units/142-uenux2-app-vota-estados-448-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/142-uenux2-app-vota-estados-448.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/142-uenux2-app-vota-estados-448-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/142-uenux2-app-vota-estados-448-pending.o $(APP)/142-uenux2-app-vota-estados-448-roots.o
