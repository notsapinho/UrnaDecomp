# uenux2 api::CLedFieldMT::Draw (target fn 11050) in src/uenux2/src/api/gui/cledfieldmt.cpp, the file its
# std::source_location record names (line 46 col 19, the CUeGuiError 4940 throw under the switch's default), with the
# class header (api/gui/cledfieldmt.h) and its ELedOperacao enum, the api::IScreenMT interface Draw calls
# (api/gui/iscreenmt.h, slots 0-11 declared) and the 4940 enumerator of api/gui/eueguierror.h. Chosen, as no evidence
# gives them: both headers' paths (beside iscreen.h, as the records put the class's .cpp in api/gui/), every IScreenMT
# member name (Slot2-Slot7, Led0-Led3), the enum, its enumerators and the member's name, and the enumerator's name. The
# switch's four calls compile to one call through IScreenMT's vtable[32 + 4 * operation]. Draw is the class's only virtual
# member defined out of line, its key function, so its object emits the vtable with the implicit destructors (slot 0
# is IFormFieldBase<IScreenMT>'s, 11052; the deleting destructor, slot 1, is target fn 2777, a thunk into merged 1565)
# and the inline members of api/gui/iformfield.h. The constructor is declared only: the target inlines it into the
# merged factory 3890. Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2
# header.
CLEDFIELDMT_SRCS := src/api/gui/cledfieldmt.cpp
UENUX2_SRCS += $(CLEDFIELDMT_SRCS)
# the class's users are not reconstructed yet: 56-uenux2-cledfieldmt-roots.cpp takes the vtable's address, the only
# way the target reaches Draw and the destructors
$(ROOT)/$(APP)/56-uenux2-cledfieldmt-roots.o: $(ROOT)/src/units/56-uenux2-cledfieldmt-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/56-uenux2-cledfieldmt.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/56-uenux2-cledfieldmt-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/56-uenux2-cledfieldmt-roots.o
