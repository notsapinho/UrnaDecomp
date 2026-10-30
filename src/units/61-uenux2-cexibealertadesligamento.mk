# uenux2 vota::CExibeAlertaDesligamento::~CExibeAlertaDesligamento (target fn 2883, the base-object destructor in
# slot 0 of the CExibeAlertaDesligamento vtable @1543004, and fn 12019, the deleting one in slot 1) in
# src/app/vota/eleitor/iniciovotacao/cexibealertadesligamento.cpp, the file the records of its StartState and
# ProcessTick name (lines 45, 53, 54; both pending). The class is final (its destructor stores no vptr) and holds an
# api::CDateTime (+12), a std::shared_ptr to its form (+24), a tick id (+32) and a state pointer (+36); the destructor
# releases the shared_ptr. It is out of line, as the deleting one calling it shows, and declared first, so it is the
# key function and cexibealertadesligamento.o emits the vtable. The constructor (inlined into GetInst, fn 5979) and
# GetInst are not reconstructed.
#
# Its base comum::CAppState, the base of every application state: the constructor (fn 224) and the inline
# NeedChangeState (fn 7480, slot 3), in src/app/comum/cappstate.cpp and cappstate.h, with api::CState
# (src/api/pattern/cstate.h). No record names either class's file. cappstate.cpp: the CAppState vtable and typeinfo lie
# between comum::CAbstractTelaProgresso's and the records of app/comum/carquivosresultado.cpp, comum::CAppStateContext's
# vtable right after them, which is the name order of the root of app/comum/ (cappstate.h says more). The destructor is
# its key function: chosen, as no evidence says which member is out of line, only that one is. cstate.h's directory is
# chosen. Chosen names, marked in the headers: CAppState's slots 4 (GetNextState) and 6 (ProcessKey), its constructor's
# argument type and the enumeration of its bits, CExibeAlertaDesligamento::GetInst, the type of the +24 pointee
# (api::IForm<api::IScreen>) and every member name. The +12 member's type is unit 50's api::CDateTime
# (api/util/cdatetime.h and cdate.h, unchanged).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CEXIBEALERTADESLIGAMENTO_SRCS := src/app/comum/cappstate.cpp src/app/vota/eleitor/iniciovotacao/cexibealertadesligamento.cpp
UENUX2_SRCS += $(CEXIBEALERTADESLIGAMENTO_SRCS)
# StartState and ProcessTick (target fns 12018, 12017) are not reconstructed: 61-uenux2-cexibealertadesligamento-pending.cpp
# gives the vtable trapping bodies, compiled with the unit's flags
$(ROOT)/$(APP)/61-uenux2-cexibealertadesligamento-pending.o: $(ROOT)/src/units/61-uenux2-cexibealertadesligamento-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/61-uenux2-cexibealertadesligamento.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/uenux2/src/api/util/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/61-uenux2-cexibealertadesligamento-pending.cpp -o $(R)
# nothing reconstructed references the CExibeAlertaDesligamento vtable or calls the CAppState constructor yet:
# 61-uenux2-cexibealertadesligamento-roots.cpp takes the vtable's address and stands in for the constructor's callers
$(ROOT)/$(APP)/61-uenux2-cexibealertadesligamento-roots.o: $(ROOT)/src/units/61-uenux2-cexibealertadesligamento-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/61-uenux2-cexibealertadesligamento.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/61-uenux2-cexibealertadesligamento-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/61-uenux2-cexibealertadesligamento-pending.o $(APP)/61-uenux2-cexibealertadesligamento-roots.o
