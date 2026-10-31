# uenux2 api::CLedFieldMT::Draw (target fn 11050) in src/uenux2/src/api/gui/cledfieldmt.cpp, the file its
# std::source_location record names (line 46 col 19, the CUeGuiError 4940 throw under the switch's default), with the
# class header (api/gui/cledfieldmt.h) and its ELedOperacao enum, the api::IScreenMT interface Draw calls
# (api/gui/iscreenmt.h, slots 0-11 declared) and the 4940 enumerator of api/gui/eueguierror.h. Chosen, as no evidence
# gives them: both headers' paths (beside iscreen.h, as the records put the class's .cpp in api/gui/), every IScreenMT
# member name (Slot2-Slot7, Led0-Led3), the enum, its enumerators and the member's name, and the enumerator's name. The
# switch's four calls compile to one call through IScreenMT's vtable[32 + 4 * operation]. Draw is the class's only virtual
# member defined out of line, its key function, so its object emits the vtable with the implicit destructors (slot 0
# is IFormFieldBase<IScreenMT>'s, 11052; the deleting destructor, slot 1, is target fn 2777, a thunk into merged 1565)
# and the inline members of api/gui/iformfield.h. The constructor has no target function of its own: binaryen inlined it
# into its one caller, api::CMTFormBuilder::AddLed (fn 435, a thunk into the merged body 3890), so it is defined out of line
# in cledfieldmt.cpp (31-uenux2-cformbuilder.mk has the measurement). Paths relative to src/uenux2; the generic uenux2 rule
# depends on the source and every uenux2 header.
CLEDFIELDMT_SRCS := src/api/gui/cledfieldmt.cpp
UENUX2_SRCS += $(CLEDFIELDMT_SRCS)
# api::CMTFormBuilder::AddLed (target fn 435, src/api/gui/cmtformbuilder.cpp) stores the field's vptr, which keeps the
# vtable, the only way the target reaches Draw and the destructors.
