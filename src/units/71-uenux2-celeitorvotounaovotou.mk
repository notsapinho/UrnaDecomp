# uenux2 vota::CEleitorVotouNaoVotou::StartState (target fn 10431, slot 2 of its vtable @1592928) and ProcessInput (fn
# 10430, slot 7) with its destructor
# and deleting destructor (fns 1284, 2884, slots 0 and 1), its GetInst (fn 1901) with the constructor and the static
# destructor of s_mutex (fn 10433), and comum::IPedeTituloMesario's StartState, constructor and
# implicit destructor (fns 10314, 3608, 1378), and its ProcessInput (fn 10313). The class headers say what the layout
# rests on. api::CInteractiveForm<MEDIA, INPUT> (api/gui/cinteractiveform.h, named by records) and its base
# api::IForm<MEDIA> (api/gui/iform.h) are unit 120's.
#
# CEleitorVotouNaoVotou::ProcessInput (fn 10430): the form's Read() (record cinteractiveform.h:57 @1592984, the class's
# inline member) and, on INPUT_CONFIRMA (9), the next state: vota::CDesabilitaAudioEleitor::GetInst (fn 5393) when
# CEstadoAudio::GetInst()'s mode at +4 (fn 509) is not 2 (CEstadoAudio::Ativo), else vota::CPedeIdentidade::GetInst
# (fn 652). Its line is after StartState's, as band 1 has them (10431 above 10430). It matches with 652 named by its
# vptr anchor (652 is the one function that stores CPedeIdentidade's vptr, 1588240: grep over build/out/splat/pieces/asm),
# while 652 itself was unresolved, self-voted on CPedeIdentidade::s_inst, until 10682 matched (unit 161's fragment). The
# if/else around the
# two GetInst is written as a choice; no other form was measured.
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
# cmp-identical to this one) and private, written by fns 10425, 10419 and 10209, of three other classes, through
# SetVotou (celeitorvotounaovotou.h), a setter whose name is chosen; 10419 (unit 142) does so now.
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
# names. Line 30 of it is the anonymous GetControlador's return (the record's column 12), and the functions written
# come after it: their lines are a choice (no record gives one). The order inside StartState is the target's: the next state, then +20's
# form, then +12's. The destructor is implicit: unit 97's derived classes show it inline. Chosen: the header's path,
# beside that file; StartState as the key function (the vtable's place shows that a member is out of line there, not
# which); Slot9, its name and its int result (no record, symbol or caller
# names it, and the derived classes return 1 and 2); the member and parameter names.
#
# IPedeTituloMesario::ProcessInput (fn 10313, slot 7) is defined after StartState, the band's order (10314 above 10313),
# and calls the anonymous GetControlador, whose record returns a non-const reference: the target calls the controller's
# slot 18 (SetTituloMesario, the one slot not const) through it. What the target holds: Read() (record
# cinteractiveform.h:57); on 9 or 5, the text of the form's GetEntradas().at(0) (one bounds check, then `== 9`); on 9 an
# empty text goes to CTituloMesarioVazio, else std::format("{:0>{}}", text, 12) (the format @1034 and the argument types
# 109, a string and an int: docs/reference/facts/reading.md R13), a std::string of twelve '0' built before
# SetTituloMesario and freed after the next state is stored, then CTituloMesarioInvalido when
# md::CValidadorIdentidade::EhValida(1, titulo) (fn 2803) fails or the titulo is the twelve zeros,
# CTituloMesarioJaRegistrado when MesarioJaRegistrado finds it, CGestorDadoMesario::GetInst (fn 5383) when
# CLocal::EhExterior (unit 89) holds or CConfiguracaoEleicao's byte at +665 (HabilitaBiometria) is clear, and
# CPedeDigitalMesario's GetInst otherwise; on 5 an empty text goes to CConfirmaFimRegistroMesarios::GetInst (fn 5389).
# CConfiguracaoEleicao::GetInst (fn 187) is called whatever EhExterior returns, so both are read before the test. The
# four other states' GetInst, with their constructors and form builders, are unit 135's, inlined here by binaryen.
# MesarioJaRegistrado has a 48-byte frame of its own that opens before CRegistradorMesario::GetInst (fn 815) and calls
# Slot9 inside, so it is a function of its own that takes `this`, and clang leaves it a call in the object; its
# CEleitorIdentidade and string copy are freed before CDataMap::Find (fn 2222's search, the cursor stored at +12), so the
# CComparecimentoMesarioPK is a named local.
# Forms measured in the whole link (`pnpm wasm score` against 10313; the form written gives 202 over 2650 rows, all
# operand-only, and matches after step 9), each one change from it:
# - the field held and its text read at each use: a `const std::string&` to the text keeps the text's address in a
#   local where the target loads at +24 of the field, 216 over 2653 (3 inserted, 2 deleted);
# - one test for 9 or 5 before at(0): a switch whose two cases each read the field, 239 over 2671 (21 inserted, 8
#   deleted), where the target sends both to one block (br_table [0 1 1 1 0]);
# - the next state in a local stored once (the target's block result before one store): a store in each branch, 362
#   over 2666 (16 inserted, 10 deleted);
# - CGestorDadoMesario's branch first: the other order, 211 over 2653 (3 inserted, 4 deleted).
# Same bytes: MesarioJaRegistrado defined above ProcessInput (the whole wasm's sha256 is the same). Chosen:
# MesarioJaRegistrado's name, its being a const member, the locals' names, and 12 and '0' written as literals.
# IPedeTituloMesario's slot 7 rests on a hand line of splat/symbol_addrs.txt, weighed by removal (10313 alone leaves
# match without it, `unresolved self-voted`): CNomeMesariosUrnaDS::Text (10319), the source of that state's form, which
# only 10313 holds by table slot. A second one, comum::CPedeDigitalMesario::s_inst, went once that name's other
# reader, the exit destructor 10321, a thunk into 3886, matched (src/units/221-uenux2-app-comum-constructors.mk has
# the measurement).
#
# comum::TelaEleitorRegistroMesarios, after StartState, is unit 247's: the second copy of comum::TelaRegistroMesarios
# (cregistrarmesarios.cpp), which binaryen joins with it into target fn 1255. Unit 247's fragment has the evidence for a
# second function, and ipedetitulomesario.h what the bytes decide of its form and what is chosen; its callers are the
# three derived constructors fn 10388 holds (unit 97's files).
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
# 4215 to 4222 tie it to this class), matches only since our link forms 2903 too, from three of the target's four
# members (10434, and 10442 and 10476, the statics of units 152's and 282's vota::CEleitorDemorando and
# CDigitalNaoReconhecida); before that the census paired our destructor of it with fn 10414 (the same body as ours,
# over another class's pointer and D2: a shape pair), and 10434 read no-candidate. The roots stand
# for 1901's target callers not in the link (10209, 10425; 10419, unit 142's, is), and the vtable sink went: 1901's
# constructor stores the vptr.
#
# Slot 2 of api::IForm is called through its chosen name, as api/gui/iform.h declares it. That header is unit 120's now
# (unit 65 wrote its first form): this unit adds nothing to it.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CELEITORVOTOUNAOVOTOU_SRCS := src/app/vota/operador/aguardaeleitor/celeitorvotounaovotou.cpp src/app/comum/comparecimentomesario/estados/ipedetitulomesario.cpp
UENUX2_SRCS += $(CELEITORVOTOUNAOVOTOU_SRCS)
# IPedeTituloMesario::ProcessInput reads comum::CConfiguracaoEleicao, whose header reaches ecourna's CHorariosUrna and
# so Boost's headers: an include path, not a flag of the code
$(ROOT)/$(APP)/uenux2/src/app/comum/comparecimentomesario/estados/ipedetitulomesario.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# vota::CEleitorVotouNaoVotou::GetInst's callers are not all written: 71-uenux2-celeitorvotounaovotou-roots.cpp stands
# in for them
$(ROOT)/$(APP)/71-uenux2-celeitorvotounaovotou-roots.o: $(ROOT)/src/units/71-uenux2-celeitorvotounaovotou-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/71-uenux2-celeitorvotounaovotou.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/71-uenux2-celeitorvotounaovotou-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/71-uenux2-celeitorvotounaovotou-roots.o
