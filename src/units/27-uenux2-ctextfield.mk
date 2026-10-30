# uenux2 api::CTextField ctor (target fn 1918), GetTypeName (10947) and its implicit destructors (10950, 10948, emitted
# with the vtable) in src/uenux2/src/api/gui/ctextfield.cpp, with the class header ctextfield.h and the 4964 enumerator
# of eueguierror.h; paths relative to src/uenux2.
UENUX2_SRCS += src/api/gui/ctextfield.cpp
# the class's members not reconstructed yet (trapping bodies the vtable needs; see the file header), and two callers of
# the ctor (27-uenux2-ctextfield-roots.cpp) so binaryen does not inline it and keeps both TColor parameters, as the
# target's six callers do
$(ROOT)/$(APP)/27-uenux2-ctextfield-pending.o: $(ROOT)/src/units/27-uenux2-ctextfield-pending.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/27-uenux2-ctextfield-pending.cpp -o $(R)
$(ROOT)/$(APP)/27-uenux2-ctextfield-roots.o: $(ROOT)/src/units/27-uenux2-ctextfield-roots.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/27-uenux2-ctextfield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/27-uenux2-ctextfield-pending.o $(APP)/27-uenux2-ctextfield-roots.o
