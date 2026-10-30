# uenux2 api::CLineField::Rect and GetTypeName (target fns 11067 and 11066, slots 8 and 7 of the CLineField vtable
# @1579356) in src/uenux2/src/api/gui/clinefield.cpp, with the class header api/gui/clinefield.h. No record names the
# class's file: the stubs sat in src/uenux2/unplaced.cpp, link-order cluster 395, whose neighbours' file
# (ledger/tu-clusters.tsv) is the class convention uenux2/src/api/gui/clinefield.cpp, between cmoviefield.cpp and
# cimagefieldupdate.cpp, which the GUI fields' records put in api/gui/ (docs/how-to-decompile.md step 3, rules 2 and
# 3). GetTypeName is the first virtual member the header declares out of line, so clinefield.o emits the vtable and the
# implicit destructors. The members are trivially destructible, so clang emits no complete destructor of the class's
# own: slot 0 is IFormFieldBase<IScreen>'s (12658, matched with unit 14). The deleting one is a body of its own here;
# the target's (3681) is a thunk into fn 1565, binaryen's one body for eight deleting destructors that store a vptr and
# free the string at +12 (ledger/callgraph.tsv: 2777 3681 5516 10362 10369 10374 12317 12564), so it stays unmatched
# until our link has the others. Draw (11068) and Move (5527) are pending. The constructor has no target function of
# its own (the std::make_shared of fn 2244 inlines it), so the header defines it. Paths relative to src/uenux2; the
# generic uenux2 rule depends on the source and every uenux2 header.
CLINEFIELD_SRCS := src/api/gui/clinefield.cpp
UENUX2_SRCS += $(CLINEFIELD_SRCS)
# Draw and Move are not reconstructed: 54-uenux2-clinefield-pending.cpp defines them with trapping bodies (see its
# header); nothing reconstructed references the vtable yet: 54-uenux2-clinefield-roots.cpp takes its address, which
# keeps every member in the table as the target has them. Both rules list the headers by directory: every header
# clinefield.h includes, transitively, is in api/gui/ ($(UENUX2_HDRS) is still empty when the fragments are read)
$(ROOT)/$(APP)/54-uenux2-clinefield-pending.o: $(ROOT)/src/units/54-uenux2-clinefield-pending.cpp $(ROOT)/src/units/54-uenux2-clinefield.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/54-uenux2-clinefield-pending.cpp -o $(R)
$(ROOT)/$(APP)/54-uenux2-clinefield-roots.o: $(ROOT)/src/units/54-uenux2-clinefield-roots.cpp $(ROOT)/src/units/54-uenux2-clinefield.mk $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/54-uenux2-clinefield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/54-uenux2-clinefield-pending.o $(APP)/54-uenux2-clinefield-roots.o
