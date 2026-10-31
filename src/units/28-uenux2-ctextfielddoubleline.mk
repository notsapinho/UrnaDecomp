# uenux2 api::CTextFieldDoubleLine ctor (target fn 3659) and GetTypeName (10926) in
# src/uenux2/src/api/gui/ctextfielddoubleline.cpp, the file the ctor's three std::source_location records name (lines
# 40, 43 and 46, col 15: the CUeGuiError 4967, 4968 and 4969 throws), with the class header
# (api/gui/ctextfielddoubleline.h) and the three enumerators of api/gui/eueguierror.h. Paths relative to src/uenux2;
# the generic uenux2 rule depends on the source and every uenux2 header. Draw (10931) and Rect (10929) are here too, Rect
# with CalcLineRect, which clang inlines twice: both copies are in its frame, with no second prologue. GetTextLines (5499,
# record 68:21) is written and `differs`: 375 over 1497 rows at the tree's -O3 (577 over 1672 at -O2), where the target's
# two calls of append(const char*, size_t) appear, where -O2 has two of __grow_by_and_replace and none of append;
# -std=c++23 adds nothing. So part of it was the level, and part is unexplained: at -O3 it still has 4 __init_copy_ctor_external to the target's 3, 5 operator new to
# its 6 and 2 __throw_out_of_range to its 1. It stays written though unexplained, because two matches need it and it holds
# no slot a trap could take: a trap would be inlined into 10929 and 10931. Neither reads its body. What carries their
# match is its line in splat/symbol_addrs.txt, `evidence:call by:10929`, and the record 68:21 is what says that line
# names the right function: without the line both go `unresolved`. Tried with no gain: one return (632),
# std::make_tuple for the braces (the same bytes). The literal "" for the second string is evidence: a default string
# stores 12 bytes of 0, the target two bytes. m_linha1.x, m_linha2.x and m_maxX are read at the top and the widths computed
# where they are used, or the two share a maxX + 1 the target does not have. The layout is the ctor's stores (60 B, the
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
# two callers of the ctor (28-uenux2-ctextfielddoubleline-roots.cpp) so binaryen does not inline it and drops the constant TColor
# argument as the target's wasm-opt did
$(ROOT)/$(APP)/28-uenux2-ctextfielddoubleline-roots.o: $(ROOT)/src/units/28-uenux2-ctextfielddoubleline-roots.cpp $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/28-uenux2-ctextfielddoubleline-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/28-uenux2-ctextfielddoubleline-roots.o
