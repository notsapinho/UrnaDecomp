# uenux2 comum::IInterfaceInit::~IInterfaceInit (target fn 5898, slot 0 of the IInterfaceInit vtable @1552152 and of
# simulador::CWasmInit's @1528764: one table entry, 535, so CWasmInit's destructor is this one) in
# src/app/comum/iinterfaceinit.cpp, the file the records of the class's other members name (no record falls in the
# destructor: it is placed at the top, and the link order puts it before line 148, iinterfaceinit.h says why). Its
# body frees the two members, a std::string at +12 and a std::shared_ptr<bool> at +4, after storing the vptr. With it:
# the class header (src/app/comum/iinterfaceinit.h) and the out-of-line constructor, which no target function holds
# (binaryen inlined it into its one caller, fn 8302). Paths relative to src/uenux2; the generic uenux2 rule depends on
# the source and every uenux2 header.
IINTERFACEINIT_SRCS := src/app/comum/iinterfaceinit.cpp
UENUX2_SRCS += $(IINTERFACEINIT_SRCS)
# CurrentBootDevice (target fn 11646) is not reconstructed: 35-uenux2-iinterfaceinit-pending.cpp gives the vtable a
# trapping body, compiled with the unit's flags
$(ROOT)/$(APP)/35-uenux2-iinterfaceinit-pending.o: $(ROOT)/src/units/35-uenux2-iinterfaceinit-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/35-uenux2-iinterfaceinit.mk $(ROOT)/src/uenux2/src/app/comum/iinterfaceinit.h $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/35-uenux2-iinterfaceinit-pending.cpp -o $(R)
# the destructor's callers are not reconstructed yet: 35-uenux2-iinterfaceinit-roots.cpp takes its address, as the
# two vtables do
$(ROOT)/$(APP)/35-uenux2-iinterfaceinit-roots.o: $(ROOT)/src/units/35-uenux2-iinterfaceinit-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/35-uenux2-iinterfaceinit-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/35-uenux2-iinterfaceinit-pending.o $(APP)/35-uenux2-iinterfaceinit-roots.o
