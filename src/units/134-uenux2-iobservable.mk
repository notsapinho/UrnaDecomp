# uenux2 api::IObservable<std::shared_ptr<api::IImage>>'s destructors: target fn 11651, the D2 in slot 0 of the vtable
# @1551944, and fn 11650, the deleting one in slot 1. Both are code src/uenux2/src/api/pattern/iobservable.h (unit 55's
# header) defines: the class's only virtual member is `virtual ~IObservable() = default;` in the class, so it has no key
# function, and the D0 holds the D2's body and then frees this, the shape of an inline destructor (docs/how-to-decompile.md
# step 5). No source of its own (src/units/README.md "What a fragment holds" item 2, unit 19's shape): in the target only
# binaryen's shared destructor body of api::BatteryIconDataSource<Horizontal> and <Vertical> (fn 6049, over the thunks
# 3837 and 5510) stores the vptr, and that class's constructor and destructor are not written, so the roots file builds an
# IObservable in a function the link drops and keeps the vtable. The D2 destroys the mutex at +24, the vector at +12 and
# the shared_ptr at +4, the layout iobservable.h already had. Both match from the roots object.
# The roots file builds the class in a function the link drops and keeps its vtable; it compiles with the uenux2 tree's
# flags. Its prerequisites are every header the compile reads: the uenux2 and ecourna set the generic rule uses
# ($(UENUX2_HDRS) is not set yet when src/Makefile reads the fragments).
IOBSERVABLE_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/134-uenux2-iobservable-roots.o: $(ROOT)/src/units/134-uenux2-iobservable-roots.cpp $(ROOT)/src/units/134-uenux2-iobservable.mk $(ROOT)/src/Makefile $(IOBSERVABLE_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/134-uenux2-iobservable-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/134-uenux2-iobservable-roots.o
