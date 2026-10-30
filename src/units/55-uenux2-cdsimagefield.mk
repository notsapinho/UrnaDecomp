# uenux2 api::CDSImageField::~CDSImageField: the D2 (target fn 2778, vtable @1578860 slot 0), the D0 (fn 11095, slot 1)
# and their thunks at -44 in the IObserver<SharedIImage>-in-CDSImageField vtable @1578912 (fns 11096, 11094), with
# GetTypeName (fn 11091, slot 7), in src/api/gui/cdsimagefield.cpp, the file the record of the constructor's throw
# (line 29, column 15) names; the constructor itself is inlined into fn 502 and not reconstructed. The class (RTTI: a
# vmi_class of api::CImageField at +0 and api::IObserver<std::shared_ptr<api::IImage>> at +44) is declared in
# cdsimagefield.h beside it (the header's path is chosen), and the two observer templates in src/api/pattern/iobserver.h
# and iobservable.h: no record names their files, so the directory is chosen (the api pattern templates', beside
# cpolysingleton.h) and the file names are the classes'. The member names of all three are chosen too: only the layout
# (CDSImageField 56 B, IObservable's value +4, observers +12, mutex +24) reaches the bytes, with Detach, the
# erase-remove under the mutex that the D2 inlines (comum::CInfoMTLCD's D2, fn 5902, inlines the same). The destructor
# is defined out of line, so it is the class's key function and the vtable is emitted here: the D0 is D2(this);
# free(this) with the D2's result dropped (the D1 alias's call), not free(D2(this)) (in the class) nor the D2 inlined
# (implicit). GetTypeName's place (out of line, after Update) is chosen: the target's function order (Update and its
# thunk before GetTypeName) fits it and an in-class GetTypeName alike; the out-of-line form, which CTextField's and
# CImageField's GetTypeName take, is the one measured. Paths relative to src/uenux2; the generic uenux2 rule depends
# on the source and every uenux2 header.
CDSIMAGEFIELD_SRCS := src/api/gui/cdsimagefield.cpp
UENUX2_SRCS += $(CDSIMAGEFIELD_SRCS)
# Update (target fn 11093, slot 10) and its thunk (fn 11092) are not reconstructed: 55-uenux2-cdsimagefield-pending.cpp
# gives the vtable a trapping body, compiled with the unit's flags
$(ROOT)/$(APP)/55-uenux2-cdsimagefield-pending.o: $(ROOT)/src/units/55-uenux2-cdsimagefield-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/55-uenux2-cdsimagefield.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/55-uenux2-cdsimagefield-pending.cpp -o $(R)
# the constructor's caller (fn 502) is not reconstructed: 55-uenux2-cdsimagefield-roots.cpp keeps the vtable the way the
# target reaches it
$(ROOT)/$(APP)/55-uenux2-cdsimagefield-roots.o: $(ROOT)/src/units/55-uenux2-cdsimagefield-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/55-uenux2-cdsimagefield.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/55-uenux2-cdsimagefield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/55-uenux2-cdsimagefield-pending.o $(APP)/55-uenux2-cdsimagefield-roots.o
