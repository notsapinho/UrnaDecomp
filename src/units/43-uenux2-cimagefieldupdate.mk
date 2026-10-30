# uenux2 api::CImageFieldUpdate's destructors (target fns 5531 and 11086, vtable slots 0 and 1) and GetTypeName (11085,
# slot 7), all three defined inline in the class header src/uenux2/src/api/gui/cimagefieldupdate.h (new). The class
# derives from api::IFormField<api::IScreen> (RTTI), not from api::CImageField: its base-object destructor stores no
# CImageField vptr. The destructor is declared and defaulted in the class: the deleting destructor 11086 is
# free(D2(this)), the shape of a D2 called directly and not inlined, which neither an out-of-line destructor (called
# through the D1 alias: D2(this); free(this)) nor an implicit one (inline-specified, so inlined into the D0) gives
# with these flags. GetTypeName follows the deleting destructor in the target's function order (ledger/ordinals.tsv),
# with the members the vtable emission creates, so it is inline too. The header's comment gives the layout (from 5531
# and the constructor that binaryen inlined into fn 3059) and the evidence for each member; the member names are
# chosen. The file the records name, src/uenux2/src/api/gui/cimagefieldupdate.cpp (the constructor's throw at line 32,
# Rect's at line 80), holds none of the unit's code: the constructor is not reconstructed (no target function of its
# own; it needs api::ITimerScheduler and the lambda it hands to it) and every member defined out of the class is
# pending, so the unit has no source of its own, as unit 19 has none. Paths relative to src/uenux2.
# Draw, Show, Hide, Rect and Move are not reconstructed: 43-uenux2-cimagefieldupdate-pending.cpp defines them with
# trapping bodies and names each with its target function. Draw, the first of them the class declares, is the key
# function, so that object emits the vtable and with it the destructors and GetTypeName. Every header of ours it
# reads is in src/uenux2/src/api/gui.
$(ROOT)/$(APP)/43-uenux2-cimagefieldupdate-pending.o: $(ROOT)/src/units/43-uenux2-cimagefieldupdate-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/43-uenux2-cimagefieldupdate.mk $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/43-uenux2-cimagefieldupdate-pending.cpp -o $(R)
# nothing reconstructed references the vtable yet: 43-uenux2-cimagefieldupdate-roots.cpp takes its address, which keeps
# both destructors in the table and the base-object one called from the deleting one, as the target has them
$(ROOT)/$(APP)/43-uenux2-cimagefieldupdate-roots.o: $(ROOT)/src/units/43-uenux2-cimagefieldupdate-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/43-uenux2-cimagefieldupdate.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/43-uenux2-cimagefieldupdate-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/43-uenux2-cimagefieldupdate-pending.o $(APP)/43-uenux2-cimagefieldupdate-roots.o
