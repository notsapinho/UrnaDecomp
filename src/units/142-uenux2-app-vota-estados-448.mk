# uenux2 five vota states over the D2 that 19 states share (fn 448), each a final comum::CAppState with two
# std::shared_ptr at +12 and +20: vota::CUrnaInspecionada's StartState (target fn 1718, slot 2, one body with the slot 2
# of six other states) and ProcessKey (11794, slot 6); vota::CJustificativaEfetuada's StartState (10594);
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
#   headers list what each stores). They stay unwritten here: fns 11797, 2747, 10500 and 10415 call functions with no
#   name (ledger/callgraph.tsv against splat/symbol_addrs.txt; each header names them), and fn 1150, whose callees all
#   have names, passes table slots of functions with no body here.
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
# Same bytes, each compiled and compared by function with the object-local numbers masked (how-to step 3): in
# ProcessKey an early return and `13 == tecla`; in CMostraEleitorVotando::ProcessInput an early return, and the local
# typed api::IInput&; in CJustificativaEfetuada::StartState assign() for either assignment and a local reference to the
# string; in LogaPedidoTituloSuspensao the message in a const local; the destructor as `{}`, and final on the
# destructor instead of the class (D2 and D0). Forms that do not: in CUrnaInspecionada's two slots and in
# CJustificativaEfetuada::StartState the next state stored before the form's call; in
# CPerguntaCodigoSuspensao::StartState the form's call, or the bool's store, before the log; CJustificativaEfetuada's
# test negated with the arms swapped; the instance read twice in ProcessInput; LogaJustificativaRecebida with the
# message as a temporary argument. So those orders and forms are evidence.
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
