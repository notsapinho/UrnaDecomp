# uenux2 api::CLineField::Rect and GetTypeName (target fns 11067 and 11066, slots 8 and 7 of the CLineField vtable
# @1579356) in src/uenux2/src/api/gui/clinefield.cpp, with the class header api/gui/clinefield.h. No record names the
# class's file: the stubs sat in src/uenux2/unplaced.cpp, link-order cluster 395, whose neighbours' file
# (ledger/tu-clusters.tsv) is the class convention uenux2/src/api/gui/clinefield.cpp, between cmoviefield.cpp and
# cimagefieldupdate.cpp, which the GUI fields' records put in api/gui/ (docs/how-to-decompile.md step 3, rules 2 and
# 3). GetTypeName is the first virtual member the header declares out of line, so clinefield.o emits the vtable and the
# implicit destructors. The members are trivially destructible, so clang emits no complete destructor of the class's
# own: slot 0 is IFormFieldBase<IScreen>'s (12658, matched with unit 14). The deleting one (3681) is a thunk into
# fn 1565, binaryen's one body for eight deleting destructors that store a vptr and free the string at +12
# (ledger/callgraph.tsv: 2777 3681 5516 10362 10369 10374 12317 12564): two are enough for binaryen to form that body,
# this one and unit 56's (2777). Draw (11068, slot 2) is one call of IScreen's slot 8, DrawLine in api/gui/iscreen.h,
# with the width 1, above Rect in the band's order. Move (5527) is binaryen's one body for this class's and
# CTextFieldDoubleLine's, which comes first in link order: the match line and the forms are in
# 28-uenux2-ctextfielddoubleline.mk; its place between Rect and GetTypeName is a choice. The constructor has no target
# function of its own (the std::make_shared of fn 2244 inlines it), so the header defines it. Paths relative to
# src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CLINEFIELD_SRCS := src/api/gui/clinefield.cpp
UENUX2_SRCS += $(CLINEFIELD_SRCS)
# nothing reconstructed references the vtable yet: 54-uenux2-clinefield-roots.cpp builds the field with
# std::make_shared, as fn 2244 does, which keeps every member in the table as the target has them and brings the
# control block's D2 and D0 (target fns 11122, 11121). The rule lists the headers by directory: every header
# clinefield.h includes, transitively, is in api/gui/ ($(UENUX2_HDRS) is still empty when the fragments are read)
$(ROOT)/$(APP)/54-uenux2-clinefield-roots.o: $(ROOT)/src/units/54-uenux2-clinefield-roots.cpp $(ROOT)/src/units/54-uenux2-clinefield.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/54-uenux2-clinefield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/54-uenux2-clinefield-roots.o
