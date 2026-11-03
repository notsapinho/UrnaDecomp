# uenux2 vota operador: the justification's states in app/vota/operador/justificativa/ that no landed unit compiles.
# vota::CPedeAnoNascimento (cpedeanonascimento.{h,cpp}), the screen vota::IConfirmaJustificativa::ProcessInput (fn
# 10588, unit 174) goes to when the identifier typed is no CPF, and its two answers, vota::CEleitorMenor16Anos and
# vota::CAnoInformadoInvalido (celeitormenor16anos.{h,cpp}, canoinformadoinvalido.{h,cpp});
# vota::CEleitorImpedidoJustificarVotoCPF (celeitorimpedidojustificarvotocpf.{h,cpp}), which unit 174 lists (its
# fragment has why); and the Temporario and
# Transito pairs of unit 243's two classes that vota::CEleitorEncontrado::StartState (fn 10635, unit 104) goes to:
# CConfirmaJustificativaTemporario, CIniciaJustificativaTemporario, CConfirmaJustificativaTransito and
# CIniciaJustificativaTransito, a file each. Paths relative to src/uenux2. Target fns matched:
# - CPedeAnoNascimento::GetInst (5418), with the constructor inlined behind a stack frame of its own (its form:
#   GetTextoIdentidadeDigitada at {1, 1}, "Digite o ANO de nascimento: ", a four-digit numeric field through
#   outrasopcoes/cescolheopcao.h's AdicionaCampoNumerico at {29, 2}, "CORRIGE: cancelar" and "CONFIRMA: justificar"),
#   and its statics' exit destructors (10592, 10591); its callers are 10588 and 6014;
# - CEleitorMenor16Anos::ProcessInput (10598) and CAnoInformadoInvalido::ProcessInput (10601), thunks into 6014, the
#   body binaryen merges from the two, which our link forms the same way (matched under
#   byn$mgfn-shared$_ZN4vota21CAnoInformadoInvalido12ProcessInputEv): on CONFIRMA, back to CPedeAnoNascimento;
# - CEleitorImpedidoJustificarVotoCPF's statics' exit destructors (10606, 10605: unit 174's object) and its ProcessInput
#   (10604, slot 7, in celeitorimpedidojustificarvotocpf.cpp after StartState): `f2295(p0, 5, <its Read() record>)`, a
#   thunk into the body binaryen merges from five states' slot 7, written as its siblings are,
#   `if (m_form->Read() == api::INPUT_CORRIGE) m_pNextState = &CPedeIdentidade::GetInst();`
#   (src/units/161-uenux2-app-vota-operador-identidade.mk has 2295's family); the census pairs 10604 with it, and the
#   scan matches it under its own name;
# - the four pair classes' statics' exit destructors (10615 and 10614, 10613 and 10612, 10611 and 10610, 10609 and
#   10608) and 3885, binaryen's body of the three Confirma pointers' destructors (10615, 10611 and unit 243's 10622, a
#   thunk into it, which matches with them).
# Pending (283-uenux2-app-vota-operador-justificativa-pending.cpp says what each waits for):
# CPedeAnoNascimento::ProcessInput (10590).
# CEleitorMenor16Anos's and CAnoInformadoInvalido's GetInst and constructors are written and unreferenced: in the target
# only 10590 holds them, inlined, so they are compared with nothing, and their statics' exit destructors (10600 and
# 10599, 10603 and 10602) wait for 10590's match to name the objects.
#
# Evidence, each class's header says the rest (RTTI, vtable, statics, the function that holds GetInst inlined):
# - The pairs' constructors pass IConfirmaJustificativa's (3625) the literals 10635 loads, "está impedido de votar nesta
#   seção" and "optou por votar EM TRÂNSITO" (strings 122762 and 326637), and the Inicia classes hand
#   IIniciaJustificativa's (3624) their Confirma's GetInst(), as unit 243's CIniciaJustificativa does; 10635 holds each
#   pair's GetInst and constructors inlined (binaryen: one caller each), Inicia's around Confirma's. The Confirma
#   classes' destructor is out of line (slot 0 is 3626, the D2 the three share; slot 1 2748), the Inicia classes' left
#   implicit (174 and 144), as unit 243's two; GetInst above the constructor, as there. Their vtables alternate with
#   unit 243's in the data (@1589252 to @1589532), and in use band 1 their exit destructors (10615 down to 10608) link
#   after unit 243's (10622 to 10616), this unit's order.
# - The year-of-birth states: CPedeAnoNascimento's slots 0 and 1 are 244 and 387 (a std::shared_ptr at +12),
#   StartState (1718) shows the form and stays; CEleitorMenor16Anos's and CAnoInformadoInvalido's ProcessInput differ
#   only in their TU's record of api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (cinteractiveform.h:57),
#   the merge's parameter. The two answers' texts are read from 10590's body, CPedeAnoNascimento's from 5418's.
# Chosen: the eight new files' names (after the classes, how-to step 3's rule 4) and their directory (the vtables' data
#   neighbours are unit 243's and unit 142's justificativa/ classes'), the forms' helper names, the lines, and every
#   member and local name.
#
# Roots (283-uenux2-app-vota-operador-justificativa-roots.cpp): CEleitorMenor16Anos's and CAnoInformadoInvalido's
# vtables, whose one vptr store is in 10590 (pending), and a stand-in for fn 7787 (not written), the second target
# caller of std::set<ecourna::app::dados::ETipoIdentificadorEleitor>'s range insert (6733), which 10635 calls: with
# 10635 as its one caller, binaryen inlined it there and 10635 differed by that body. Unit 104's fragment has the rest
# of 6733, which matches from celeitorencontrado.cpp.o, built without strict aliasing (src/Makefile's
# UENUX2_NOTBAA_FILES).
APP_VOTA_OPERADOR_JUSTIFICATIVA_SRCS := src/app/vota/operador/justificativa/canoinformadoinvalido.cpp \
    src/app/vota/operador/justificativa/cconfirmajustificativatemporario.cpp \
    src/app/vota/operador/justificativa/cconfirmajustificativatransito.cpp \
    src/app/vota/operador/justificativa/celeitormenor16anos.cpp \
    src/app/vota/operador/justificativa/ciniciajustificativatemporario.cpp \
    src/app/vota/operador/justificativa/ciniciajustificativatransito.cpp \
    src/app/vota/operador/justificativa/cpedeanonascimento.cpp
UENUX2_SRCS += $(APP_VOTA_OPERADOR_JUSTIFICATIVA_SRCS)
APP_VOTA_OPERADOR_JUSTIFICATIVA_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/283-uenux2-app-vota-operador-justificativa-pending.o: $(ROOT)/src/units/283-uenux2-app-vota-operador-justificativa-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/283-uenux2-app-vota-operador-justificativa.mk $(APP_VOTA_OPERADOR_JUSTIFICATIVA_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(call uenux2_cxxflags,src/app/vota/operador/justificativa/cpedeanonascimento.cpp) -c src/units/283-uenux2-app-vota-operador-justificativa-pending.cpp -o $(R)
$(ROOT)/$(APP)/283-uenux2-app-vota-operador-justificativa-roots.o: $(ROOT)/src/units/283-uenux2-app-vota-operador-justificativa-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/283-uenux2-app-vota-operador-justificativa.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/283-uenux2-app-vota-operador-justificativa-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/283-uenux2-app-vota-operador-justificativa-pending.o $(APP)/283-uenux2-app-vota-operador-justificativa-roots.o
