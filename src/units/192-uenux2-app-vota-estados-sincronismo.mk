# uenux2 vota states no landed file holds: vota::CSincronismoEleitor (app/vota/eleitor/csincronismoeleitor.{h,cpp}) and
# vota::CPedeDigital (app/vota/operador/confirmaidentidade/cpededigital.{h,cpp}). Paths relative to src/uenux2.
#
# Target functions matched:
#   vota::CSincronismoEleitor::StartState (slot 2)             7178
#   vota::CPedeDigital's destructor and deleting destructor     2739, 10469
#   vota::CPedeDigital::ProcessInput (slot 7)                   10466
# Pending, trapped in 192-uenux2-app-vota-estados-sincronismo-pending.cpp (its header says what each waits for):
# CSincronismoEleitor::ProcessKey (7181), CPedeDigital's StartState (10468), FinishState (10467) and ProcessTick (10465).
# Not written: each class's GetInst and constructor, inlined into fns 4454 and 2740, which call functions with no name
# or that no form has matched; the roots keep the two vtables by their addresses (the roots' header).
#
# Evidence:
# - CSincronismoEleitor::StartState posts 13 to the operator's queue (the queue's inline Post: Insert, fn 501, with
#   priority 1 and the queue's address in the message), sets m_pNextState, resets vota::CTelasVota's progress bar at
#   +180 to its +28 (api::CProgressBar::SetValor, fn 3667, with GetLimiteInferior) and shows the form at +172 (slot 2),
#   through ctelasvota.h's GetBarraSincronismo and GetTelaSincronismo. Insert of a temporary message gives the same
#   function (measured: both `4 over 43 rows`, every row a call's or an address's operand); Post is written, as for
#   the operador states' messages (fragment 152 has the case where only Post gives the target's frame).
# - CPedeDigital: 84 bytes (fn 2740 allocates them and passes EVENTO_ENTRADA | EVENTO_TICK, 6, to the base's
#   constructor); its destructor is out of line, 10469 being `f2739(p0); drop; f136(p0)` (docs/reference/facts/reading.md
#   R5), and final, 2739 storing no vptr first (R4): it calls api::CApplicationContext's destructor (fn 1468) for +32 and
#   releases +24 and +16. ProcessInput is CInteractiveForm<IScreenMT, IInputMT>::Read() on the form at +16 (its record,
#   cinteractiveform.h:57 @1592168), and on INPUT_CORRIGE (5) vota::CLogVota's
#   LogaHabilitacaoCanceladaReconhecimentoBiometrico (fn 2495) and vota::CCancelaHabilitacaoEleitor::GetInst (fn 1536).
#   cpededigital.h has the layout and the bytes it rests on.
#
# Paths and lines. cpededigital.cpp is the file the class's records name (StartState's lines 115, 120 and 125,
# FinishState's 131 and 132, ProcessTick's 162 to 164, three private members' 234, 262 and 279); every record line
# stays blank. The destructor (line 105) and ProcessInput (line 137) have no record: their lines are a choice, in their
# use band's order (10469, the deleting destructor, links before StartState's 10468 and FinishState's 10467, and
# ProcessInput's 10466 after them and before ProcessTick's 10465). No record names CSincronismoEleitor: its file is
# chosen, the class's name in lower case under app/vota/eleitor/, where its vtable (@1534076) and typeinfo lie in the
# data between cfimvotoeleitor.cpp's record (1534048) and csincronismovotoeleitor.cpp's (1534132), in that directory's
# name order; the end of either neighbour's object fits the data too.
#
# Chosen, no evidence names them: the data members' names (the bytes' type is AddStoppedTick's result's), the form's
# second member's pointee, every local's name, and the declaration order of the virtual members: CPedeDigital's
# destructor is declared first, so that cpededigital.cpp emits its vtable, and CSincronismoEleitor, whose destructor is
# implicit, has StartState first, so that csincronismoeleitor.cpp emits its (how-to step 3).
APP_VOTA_ESTADOS_SINCRONISMO_SRCS := src/app/vota/eleitor/csincronismoeleitor.cpp \
    src/app/vota/operador/confirmaidentidade/cpededigital.cpp
UENUX2_SRCS += $(APP_VOTA_ESTADOS_SINCRONISMO_SRCS)

# The pending traps, at the unit's flags; the rule depends on every header of both trees (src/units/README.md "What a
# fragment holds" item 3).
ESTADOS_SINCRONISMO_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/192-uenux2-app-vota-estados-sincronismo-pending.o: $(ROOT)/src/units/192-uenux2-app-vota-estados-sincronismo-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/192-uenux2-app-vota-estados-sincronismo.mk $(ESTADOS_SINCRONISMO_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/192-uenux2-app-vota-estados-sincronismo-pending.cpp -o $(R)

# The roots: the two vtables' addresses (asm labels only, no header).
$(ROOT)/$(APP)/192-uenux2-app-vota-estados-sincronismo-roots.o: $(ROOT)/src/units/192-uenux2-app-vota-estados-sincronismo-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/192-uenux2-app-vota-estados-sincronismo.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/192-uenux2-app-vota-estados-sincronismo-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/192-uenux2-app-vota-estados-sincronismo-pending.o $(APP)/192-uenux2-app-vota-estados-sincronismo-roots.o
