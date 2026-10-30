# uenux2 api::CFormBuilder::GetLabeledKeyPos (target fn 5544), the class's static member, in
# src/uenux2/src/api/gui/cformbuilder.cpp, the file its std::source_location record names (line 372 col 11, the
# CUeGuiError 4914 throw), with the class header (api/gui/cformbuilder.h) and the 4914 enumerator of
# api/gui/eueguierror.h. The rest of the class (AddStatusHeader, fn 502) is not reconstructed. Paths relative to
# src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
#
# What the bytes fix and what is chosen: the throw's column (11, one level in) puts it after the switch, so each arm
# returns; the arms' order (left, centre, right) is the target's block order (br_table 3 1 0 2); the arms assign a
# temporary SPoint to the named result, because with SPoint an aggregate (primitives.h) only that evaluates both
# coordinates before the first store, as the target does (a constructor SPoint(TPosition, TPosition) would give the
# same code from return SPoint(...)). The names of the three distances, of the parameters and of the enumerator are
# chosen; the alignment is formatted as an int (the argument type 3 the throw stores).
CFORMBUILDER_SRCS := src/api/gui/cformbuilder.cpp
UENUX2_SRCS += $(CFORMBUILDER_SRCS)
# its one caller in the target (fn 3678, two call sites) is not reconstructed yet: 31-uenux2-cformbuilder-roots.cpp
# gives it the same two calls
$(ROOT)/$(APP)/31-uenux2-cformbuilder-roots.o: $(ROOT)/src/units/31-uenux2-cformbuilder-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/31-uenux2-cformbuilder-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/31-uenux2-cformbuilder-roots.o
