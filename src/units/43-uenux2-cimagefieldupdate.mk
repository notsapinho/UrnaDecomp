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
# Rect's at line 80), holds Show and Hide (fns 11089, 11088, slots 3 and 4: Start and Stop of the timer, whose class it
# includes, api/util/itimer.h) at lines that are a choice, above line 80 in the band's order, and Move (one of the five
# functions of target fn 2241, see 27-uenux2-ctextfield.mk, which lists the forms) below it, a choice. The constructor is
# not reconstructed (no target function of its own; it needs api::ITimerScheduler and the lambda it hands to it), so
# lines 32 and 80 stay free. Paths relative to src/uenux2.
# Draw (target fn 11090, slot 2), the class's key function, is in cimagefieldupdate.cpp above Show, in the band's order,
# at lines that are a choice, so that object emits the vtable and with it the destructors and GetTypeName. Testing
# m_tamanho for null first is evidence: testing it != nullptr first swaps the two calls. Same object code, by the
# function's disassembly with the object-local numbers masked: `!m_tamanho`, and a `return` after the first call in
# place of the `else`; so those spellings are choices. Rect (11087) is CImageField's without the null test: the
# constructor throws on a null image.
CIMAGEFIELDUPDATE_SRCS := src/api/gui/cimagefieldupdate.cpp
UENUX2_SRCS += $(CIMAGEFIELDUPDATE_SRCS)
# nothing reconstructed references the vtable yet: 43-uenux2-cimagefieldupdate-roots.cpp takes its address, which keeps
# both destructors in the table and the base-object one called from the deleting one, as the target has them
$(ROOT)/$(APP)/43-uenux2-cimagefieldupdate-roots.o: $(ROOT)/src/units/43-uenux2-cimagefieldupdate-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/43-uenux2-cimagefieldupdate.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/43-uenux2-cimagefieldupdate-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/43-uenux2-cimagefieldupdate-roots.o
