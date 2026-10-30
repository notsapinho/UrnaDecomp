# uenux2 api::CTextFieldDoubleLine ctor (target fn 3659) and GetTypeName (10926) in
# src/uenux2/src/api/gui/ctextfielddoubleline.cpp, the file the ctor's three std::source_location records name (lines
# 40, 43 and 46, col 15: the CUeGuiError 4967, 4968 and 4969 throws), with the class header
# (api/gui/ctextfielddoubleline.h) and the three enumerators of api/gui/eueguierror.h. Paths relative to src/uenux2;
# the generic uenux2 rule depends on the source and every uenux2 header. The layout is the ctor's stores (60 B, the
# 72 B make_shared blocks of its callers); the member and parameter names are chosen, after the messages ("maxX",
# "linha 1", "linha 2"). The implicit destructors emitted with the vtable are 10928/10927, 12 B thunks into bodies
# binaryen merges with CTextRectField's (6022, 6021), which form since unit 90 brought that class.
# Move (target fn 5527, slot 9) is binaryen's one body for this class's and CLineField's, written in each class's file;
# binaryen keeps the first in link order, this one, so the match line names it. Its place below line 133 is a choice.
# The two deltas are read before the first store: `m_linha2.x += posicao.x - m_linha1.x` written in place reads y again
# after that store, which the target does not. Forms that give the object code of the delta locals after the test, by
# the function's disassembly in a compile with the unit's flags: the deltas before the test, tested with `dx == 0 && dy ==
# 0` or around the body with `dx != 0 || dy != 0`; a SPoint of the two deltas; the four coordinates in locals; the x compare
# spelled `m_linha1.x == posicao.x`; a free SPoint operator== for the test. So all of those are choices. A lone link
# (tools/round/try-tu.sh --single) of any of them scores 12 over 68: the y pair's two loads come out swapped there and four
# rows are the library callee, and the whole link matches.
CTEXTFIELDDOUBLELINE_SRCS := src/api/gui/ctextfielddoubleline.cpp
UENUX2_SRCS += $(CTEXTFIELDDOUBLELINE_SRCS)
# the class's members not reconstructed yet (trapping bodies the vtable needs; see the file header), and two callers of
# the ctor (28-uenux2-ctextfielddoubleline-roots.cpp) so binaryen does not inline it and drops the constant TColor
# argument as the target's wasm-opt did
$(ROOT)/$(APP)/28-uenux2-ctextfielddoubleline-pending.o: $(ROOT)/src/units/28-uenux2-ctextfielddoubleline-pending.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/28-uenux2-ctextfielddoubleline-pending.cpp -o $(R)
$(ROOT)/$(APP)/28-uenux2-ctextfielddoubleline-roots.o: $(ROOT)/src/units/28-uenux2-ctextfielddoubleline-roots.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/28-uenux2-ctextfielddoubleline-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/28-uenux2-ctextfielddoubleline-pending.o $(APP)/28-uenux2-ctextfielddoubleline-roots.o
