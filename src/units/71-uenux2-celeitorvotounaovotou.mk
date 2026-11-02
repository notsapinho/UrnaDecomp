# uenux2 vota::CEleitorVotouNaoVotou::StartState (target fn 10431, slot 2 of its vtable @1592928) and ProcessInput (fn
# 10430, slot 7) with its destructor
# and deleting destructor (fns 1284, 2884, slots 0 and 1), its GetInst (fn 1901) with the constructor and the static
# destructor of s_mutex (fn 10433), and comum::IPedeTituloMesario's StartState, constructor and
# implicit destructor (fns 10314, 3608, 1378). The class headers say what the layout rests on; IPedeTituloMesario's
# ProcessInput (fn 10313) is pending. api::CInteractiveForm<MEDIA, INPUT> (api/gui/cinteractiveform.h, named by
# records) and its base api::IForm<MEDIA> (api/gui/iform.h) are unit 120's.
#
# CEleitorVotouNaoVotou::ProcessInput (fn 10430): the form's Read() (record cinteractiveform.h:57 @1592984, the class's
# inline member) and, on INPUT_CONFIRMA (9), the next state: vota::CDesabilitaAudioEleitor::GetInst (fn 5393) when
# CEstadoAudio::GetInst()'s mode at +4 (fn 509) is not 2 (CEstadoAudio::Ativo), else vota::CPedeIdentidade::GetInst
# (fn 652). Its line is after StartState's, as band 1 has them (10431 above 10430). It matches with 652 named by its
# vptr anchor (652 is the one function that stores CPedeIdentidade's vptr, 1588240: grep over build/out/splat/pieces/asm),
# while 652 itself waits for a literal (unit 161's fragment). The if/else around the two GetInst is written as a
# choice; no other form was measured.
#
# The file of vota::CEleitorVotouNaoVotou: no record names it, and the path is chosen, on this evidence. Its cluster's
# comment, app/vota/eleitor/fimvotacao/celeitorvotounaovotou.cpp, is the tool's class-convention guess, and the data
# speak against it: fimvotacao/'s records lie at @1540116-1542976 and this vtable at @1592928, and the class's form is
# the operator's api::CInteractiveForm<api::IScreenMT, api::IInputMT>. The target's Read() records of the IScreen
# instance all sit between app/vota/eleitor/ records, and none of the IScreenMT instance's does. Band and data order:
# the next object is app/vota/operador/aguardaeleitor/cmostraeleitorvotando.cpp, recorded @1593044 with nothing
# between. In band 1 this class's fns 10431 and 10430 are followed by fns 10429 and 10428, the exit-time destructors of
# that class's singleton statics (only fn 1150, which stores its vptr, uses them), and then by its fns 10427 to 10425.
# Fns 10434 and 10433 are this class's own (fn 1901's statics), just before fn 10431 with one function of another place
# between them, 10432, a libc++ function. The table's order has no such gap: elem 4215 to 4222 hold fns 10434 and 10433,
# this vtable's 1284, 2884, 10431 and 10430, then fns 10429 and 10428. The previous recorded object is
# app/vota/operador/confirmaidentidade/cregistradigitaloperador.cpp (@1592596), four unrecorded states away
# (CDadoEleitorNaoConfere, CVerificaDadoEleitor, CEleitorDemorando, CDesabilitaAudioEleitor). So the two recorded
# sides name different directories and the data do not place the boundary between them: aguardaeleitor/ is a choice,
# for the adjacent neighbour. Name order agrees and proves nothing: aguardaeleitor's cmostraeleitorvotando,
# cperguntacodigosuspensao, cperguntaeleitorvotando and csuspensaoautomaticaeleitor run in name order and this name
# sorts before them, but confirmaidentidade's files do not run in name order. The file name is the class-name
# convention. The header's path, the member names and GetInst are chosen too, and so are two things of the +11 flag:
# bool (with a uebyte the object differs, and with that one object swapped on the link line the plain link is
# cmp-identical to this one) and private with no setter, although fns 10425, 10419 and 10209, of three other classes,
# write it. No byte depends on the second, and those classes need a setter or public access when they are written.
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
# form, then +12's. The destructor is implicit: unit 97's derived classes show it inline. Chosen: the header's path,
# beside that file; StartState as the key function (the vtable's place shows that a member is out of line there, not
# which); Slot9, its name and its int result (no record, symbol or caller
# names it, and the derived classes return 1 and 2); the member and parameter names.
#
# IPedeTituloMesario::GetTelaEleitor, after StartState, is unit 247's: the second copy of comum::TelaRegistroMesarios
# (cregistrarmesarios.cpp), which binaryen joins with it into target fn 1255. Unit 247's fragment has the evidence for a
# second function and what is chosen (this class, a protected non-static member, its name), and its roots stand in for
# the copy's callers, the three derived constructors in fn 10388.
#
# GetInst (1901), the project's singleton, holds the constructor inlined behind a 96-byte frame of its own: CAppState's
# with EVENTO_ENTRADA, +11 cleared, two std::make_shared<std::string> (the first from "pode/nao pode entregar comp", the
# second from "": its size byte and first byte stored, where make_shared<std::string>() zeroed the twelve bytes, 45 over
# 520 rows, 3 not operands), one more reference taken on each before the form is built and dropped after it, the two
# arguments of a helper that takes them by value, which initializes the form at +28 in the member list (fn 301 writes
# it in place). The helper: AddLed(LED_OPERACAO_0), GetTextoIdentidadeDigitada at {1, 1}, a CTextSource over each string
# with "%s" at {1, 2} and {1, 3} (fn 1152), "CONFIRMA: prosseguir" at {40, 4} on the right, AddInputControl,
# GetInteractiveForm("", true). Before steps 7 to 9: 42 over 520 rows, all operand-only, the statics' addresses. The
# helper's being in an anonymous namespace, its name and its parameters are chosen. The statics are defined before
# StartState: their destructors (10434, 10433) sit above 10431 in band 1. s_inst (@1909288) has a hand line in
# splat/symbol_addrs.txt: step 8 names it by GetInst's votes alone, which the self-vote rule refuses, and its static
# destructor 10434, the other function that reads it (a thunk into 2903, the body four classes' statics share; elem
# 4215 to 4222 tie it to this class), does not match: the census pairs our destructor of it with fn 10414 (the same
# body as ours, over another class's pointer and D2: a shape pair), and 10434 stays no-candidate. The roots stand
# for 1901's target callers (10209, 10419, 10425), and the vtable sink went: 1901's constructor stores the vptr.
#
# Slot 2 of api::IForm is called through its chosen name, as api/gui/iform.h declares it. That header is unit 120's now
# (unit 65 wrote its first form): this unit adds nothing to it.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CELEITORVOTOUNAOVOTOU_SRCS := src/app/vota/operador/aguardaeleitor/celeitorvotounaovotou.cpp src/app/comum/comparecimentomesario/estados/ipedetitulomesario.cpp
UENUX2_SRCS += $(CELEITORVOTOUNAOVOTOU_SRCS)
# IPedeTituloMesario::ProcessInput (target fn 10313) is not reconstructed: 71-uenux2-celeitorvotounaovotou-pending.cpp
# gives the vtable a trapping body, compiled with the unit's flags
$(ROOT)/$(APP)/71-uenux2-celeitorvotounaovotou-pending.o: $(ROOT)/src/units/71-uenux2-celeitorvotounaovotou-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/71-uenux2-celeitorvotounaovotou.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/operador/aguardaeleitor/*.h $(ROOT)/src/uenux2/src/app/comum/comparecimentomesario/estados/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/71-uenux2-celeitorvotounaovotou-pending.cpp -o $(R)
# nothing reconstructed references either class yet: 71-uenux2-celeitorvotounaovotou-roots.cpp takes the first vtable's
# address and stands in for the IPedeTituloMesario constructor's callers
$(ROOT)/$(APP)/71-uenux2-celeitorvotounaovotou-roots.o: $(ROOT)/src/units/71-uenux2-celeitorvotounaovotou-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/71-uenux2-celeitorvotounaovotou.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/71-uenux2-celeitorvotounaovotou-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/71-uenux2-celeitorvotounaovotou-pending.o $(APP)/71-uenux2-celeitorvotounaovotou-roots.o
