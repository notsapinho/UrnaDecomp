# uenux2 vota::CEleitorVotouNaoVotou::StartState (target fn 10431, slot 2 of its vtable @1592928) with its destructor
# and deleting destructor (fns 1284, 2884, slots 0 and 1), and comum::IPedeTituloMesario's StartState, constructor and
# destructor (fns 10314, 3608, 1378). The class headers say what the layout rests on; ProcessInput of each (fns 10430,
# 10313) is pending. api::CInteractiveForm<MEDIA, INPUT> (api/gui/cinteractiveform.h, named by records) is declared
# as far as these states need it, its base api::IForm<MEDIA> (api/gui/iform.h).
#
# The file of vota::CEleitorVotouNaoVotou: no record names it, and the path is chosen, on this evidence. Its cluster's
# comment, app/vota/eleitor/fimvotacao/celeitorvotounaovotou.cpp, is the tool's class-convention guess, and the data
# speak against it: fimvotacao/'s records lie at @1540116-1542960 and this vtable at @1592928, and the class's form is
# the operator's api::CInteractiveForm<api::IScreenMT, api::IInputMT>. The target's Read() records of the IScreen
# instance all sit between app/vota/eleitor/ records, and none of the IScreenMT instance's does. Band and data order:
# the next object is app/vota/operador/aguardaeleitor/cmostraeleitorvotando.cpp, recorded @1593044 with nothing
# between. In band 1 this class's fns 10431 and 10430 are followed by fns 10429 and 10428, the exit-time destructors of
# that class's singleton statics (only fn 1150, which stores its vptr, uses them), and then by its fns 10427 to 10425;
# this class's own fns 10434 and 10433 come right before fn 10431. The previous recorded object is
# app/vota/operador/confirmaidentidade/cregistradigitaloperador.cpp (@1592596), four unrecorded states away
# (CDadoEleitorNaoConfere, CVerificaDadoEleitor, CEleitorDemorando, CDesabilitaAudioEleitor). So the two recorded
# sides name different directories and the data do not place the boundary between them: aguardaeleitor/ is a choice,
# for the adjacent neighbour. Name order agrees and proves nothing: aguardaeleitor's cmostraeleitorvotando,
# cperguntacodigosuspensao, cperguntaeleitorvotando and csuspensaoautomaticaeleitor run in name order and this name
# sorts before them, but confirmaidentidade's files do not run in name order. The file name is the class-name
# convention. The header's path, the member names and GetInst are chosen too.
#
# Other forms of StartState that give the same bytes (each compiled and compared with this one; none is singled out
# by the target): assign() for either assignment, the literal held in a local const char* first, an if/else with one
# assignment in each arm, ' ' for " ", and !m_bVotou with the arms swapped, which differs only in the literals' order
# in the object, which the link's string merge does not keep. Forms that do not: the next state stored first or the
# form called first (the target's order is its source's), and a temporary std::string. The destructor as `{}`, final
# on the destructor instead of the class, the +28 member typed api::IForm<api::IScreenMT>, and StartState declared
# first (so the key function) leave StartState, the D2 and the D0 as they are; without final the D2 gains a vptr
# store.
#
# comum::IPedeTituloMesario: src/app/comum/comparecimentomesario/estados/ipedetitulomesario.cpp is the file its record
# names. Line 30 of it, the anonymous GetControlador, stays blank, and the functions written come after it: their
# lines are a choice (no record gives one). The order inside StartState is the target's: the next state, then +20's
# form, then +12's.
#
# Slot 2 of api::IForm is called through its chosen name, as api/gui/iform.h declares it. That header is unit 65's, byte
# for byte: this unit adds nothing to it.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CELEITORVOTOUNAOVOTOU_SRCS := src/app/vota/operador/aguardaeleitor/celeitorvotounaovotou.cpp src/app/comum/comparecimentomesario/estados/ipedetitulomesario.cpp
UENUX2_SRCS += $(CELEITORVOTOUNAOVOTOU_SRCS)
# ProcessInput of each class (target fns 10430, 10313) is not reconstructed: 71-uenux2-celeitorvotounaovotou-pending.cpp
# gives the vtables trapping bodies, compiled with the unit's flags
$(ROOT)/$(APP)/71-uenux2-celeitorvotounaovotou-pending.o: $(ROOT)/src/units/71-uenux2-celeitorvotounaovotou-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/71-uenux2-celeitorvotounaovotou.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/operador/aguardaeleitor/*.h $(ROOT)/src/uenux2/src/app/comum/comparecimentomesario/estados/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/71-uenux2-celeitorvotounaovotou-pending.cpp -o $(R)
# nothing reconstructed references either class yet: 71-uenux2-celeitorvotounaovotou-roots.cpp takes the first vtable's
# address and stands in for the IPedeTituloMesario constructor's callers
$(ROOT)/$(APP)/71-uenux2-celeitorvotounaovotou-roots.o: $(ROOT)/src/units/71-uenux2-celeitorvotounaovotou-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/71-uenux2-celeitorvotounaovotou.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/71-uenux2-celeitorvotounaovotou-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/71-uenux2-celeitorvotounaovotou-pending.o $(APP)/71-uenux2-celeitorvotounaovotou-roots.o
