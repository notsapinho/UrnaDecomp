# uenux2 api::CFillField, api::CRectField and api::CTextRectField in src/uenux2/src/api/gui/; paths relative to
# src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header. Target functions:
#   CFillField      Draw 11142, GetTypeName 11141, Rect 5551 (one body with CRectField's), slots 2, 7 and 8
#   CRectField      the constructor 5501, Draw 10960, GetTypeName 10959
#   CTextRectField  Draw 10906, GetTypeName 10902, the implicit destructors 10904 and 10903, thunks into binaryen's 6022
#                   and 6021, which form with CTextFieldDoubleLine's (10928, 10927: unit 28's, matched since this unit)
#   the control blocks the roots build: 11124, 11123, 11126, 11125, 11118, 11117, 11120, 11119
# Pending, in the -pending.cpp, whose header says what each waits for: Move (2783), CTextRectField::Rect (10905).
#
# Evidence. The classes and their base are RTTI's; ctextrectfield.cpp and its constructor's and Rect's lines are the
# records' (51:15, 71:21), and the constructor's code 4976 and message are bytes of fn 5546, which binaryen inlined it
# into (its second stack-pointer prologue). No byte compares that constructor: it has no target function of its own, and
# its three store orders all equal fns 11805, 5546 and 2245. The layouts are the constructors' and the Draws' stores and loads. Slot 2 of
# each is Draw by RTTI and slot (api::IFormField<api::IScreen>), and it calls IScreen's slots 6, 9 and 20.
# CTextRectField's first test is the width compared with 1, as api::CTextFieldUpdate::Draw's:
# 42-uenux2-ctextfieldupdate.mk has the measurement. In its Draw the if/else with two calls is evidence too: a ternary on
# the two calls and one call with a ternary colour compile to one call, and the if/else negated swaps the blocks.
#
# The directory of cfillfield.* and crectfield.* is evidence, from the data: CFillField's vtable @1577780 lies between
# the records of cfixedimage.cpp and cformbuilder.cpp, CRectField's @1582172 between the record of
# cqrcodeimagepaper.cpp @1582156 and CTextBox's vtable, all of api/gui/.
#
# Chosen, no evidence gives them. The files' names: no record names either class, so they are the classes' in lower
# case (docs/how-to-decompile.md step 3, rule 4); ctextrectfield.h, beside its .cpp. Every member
# and parameter name, and the enumerator's name. CRectField's colour parameter: 5501 stores the constant 2, which a
# parameter every caller passes gives as a fixed colour does, and it is written as CFillField's is. CFillField's
# constructor out of line: fn 2245 holds it inlined and shows no sign of which inliner did it; a fn 5501 of its own says
# only that CRectField's is. Declaring Draw first, so it is the key function of all three: CTextRectField's band
# (uses 1: Draw, Rect, the destructors, GetTypeName) fits it and places GetTypeName in the class; for the other two
# the band shows Draw above GetTypeName and the D0 is shared, so GetTypeName in the class follows CTextRectField's and
# is a choice (written in the .cpp, CRectField's has the same code). The lines of Draw and of the constructors, but for
# the records'. m_preencher's bool: an unsigned char compared with 1 gives the same code (facts/reading.md R14).
#
# Same object code, by the function's disassembly with the object-local numbers masked: in CTextRectField::Draw a local
# SRect assigned in both branches and stored after them, the colour of FillRect in a local TColor, and the unsigned char
# above. A CRectField constructor with no colour parameter that stores 2 has the rows of fn 5501 in its object. Assigning
# the members in the constructor's body gives another body in a whole link (65 B against 58), as does a local SRect in
# CTextField::Draw (27-uenux2-ctextfield.mk).
API_GUI_SRCS := src/api/gui/cfillfield.cpp src/api/gui/crectfield.cpp src/api/gui/ctextrectfield.cpp
UENUX2_SRCS += $(API_GUI_SRCS)
$(ROOT)/$(APP)/90-uenux2-api-gui-pending.o: $(ROOT)/src/units/90-uenux2-api-gui-pending.cpp $(ROOT)/src/units/90-uenux2-api-gui.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/90-uenux2-api-gui-pending.cpp -o $(R)
$(ROOT)/$(APP)/90-uenux2-api-gui-roots.o: $(ROOT)/src/units/90-uenux2-api-gui-roots.cpp $(ROOT)/src/units/90-uenux2-api-gui.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/90-uenux2-api-gui-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/90-uenux2-api-gui-pending.o $(APP)/90-uenux2-api-gui-roots.o
