# uenux2 api::CFormBuilder, and its two siblings for the other media, api::CMTFormBuilder and api::CPaperFormBuilder, in
# src/uenux2/src/api/gui/. cformbuilder.cpp is the file the records name: GetLabeledKeyPos (target fn 5544, line 372 col
# 11, the CUeGuiError 4914 throw) and AddStatusHeader (fn 502, lines 292 and 305, not reconstructed). No record names the
# other two .cpp files, whose paths are chosen, each the class's in lower case beside cformbuilder.cpp; cpaperformbuilder.h
# is a record's. Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
#
# Target functions, all matched but one:
#   CFormBuilder       203 (constructor, one body with CMTFormBuilder's), 202 and 1191 (AddTextField), 3068 (AddDoubleLineField),
#                      5547 (AddImage), 2244 (AddLine), 2245 (AddFill), 3680 (AddRect), and 426 (AddField), written and differs
#   CMTFormBuilder     180, 619, 651, 1152, 5409, 5419 (AddTextField), 435 (AddLed), 1072 (AddBeep), 941 (AddBuzz), 728 (AddClock)
#   CPaperFormBuilder  193, 604 (AddTextField), 198 (AddNewLine), 1264 (AddCut)
#   binaryen's         3890, the one body of 435, 1072 and 198; 1400, vector<shared_ptr<IFormField<...>>>::emplace_back(const
#                      value_type&), one body of the media's instantiations, under the first in the link
#
# 426, AddField, waits for -O3, which is the tree's flag and not this unit's: it stays written (docs/how-to-decompile.md
# step 5). At -O2 it scores 292 over 449 rows: clang inlines std::string::append into operator+, and one loop compares the
# name. The target calls append (fn 160) and holds two copies of that loop, one for a long name and one for a short one,
# which only -O3's loop unswitching gives. The object alone at -O3 in the plain link, by docs/reference/facts/workflow.md
# W13: 18 over 334 rows, 14 of them operand-only; the other four are one add's operand order, n + (it != end), which the
# object has and our link swaps. -O2 with -std=c++23 changes nothing (292 over 449), and -O3 with -std=c++23 gives the same
# 18. The rows that pinned the form, each at -O3: the name is a temporary, destroyed before the push (`SetName(GeraNome(...))`:
# with a named local the push comes first), and `sufixo += repetido` gives the target's add where `if (repetido) ++sufixo`
# gives an add under the test. Its name reaches 202 and the rest by the hand edit of splat/symbol_addrs.txt, whose comment
# says what it rests on: 426 has 36 target callers and the only ones written here need it to be named.
#
# What the bytes fix:
# - In each of the MT and paper adders the text local outlives the field's allocation: the field's `new` follows the text's
#   control block, and a temporary in the field's own `new` expression would allocate first. 5419 destroys its std::function
#   copy before that `new`, so `text` is a named local and not an argument of a call.
# - push_back goes through its const reference: each adder takes a reference on the field and drops one, where a moved
#   temporary takes none. Two forms of it are the same call: where the result is the object the caller gave, clang keeps
#   emplace_back out of line (`cost=340, threshold=325`, by -Rpass-missed=inline on cmtformbuilder.cpp), which is fn 1400; where the
#   field is a local, the reference is to an alloca and it inlines (`cost=320, threshold=325`), the bodies of 941, 728, 3890.
# - AddField takes its shared_ptr by value: 426 releases it at its end, and 202 copies the two words into a temporary.
# - 202's `text` is a std::shared_ptr<CFixedText>: 202 builds a temporary SharedIText for the constructor and releases it
#   right after; a local SharedIText makes no temporary (167 rows against 142 in the object).
# - The constructors of CLedFieldMT, CBeepFieldMT, CClockFieldMT, CNewLineFieldPaper, CLineField and CFillField are out of line,
#   in their classes' files: each has one caller, binaryen inlines it there, and that caller is then optimized again, which is
#   what gives the target's locals and, in 2244 and 2245, the object's address kept in a local. In the class, where clang
#   inlines them, 728 scores 61 over 189 (8 over 177 out of line), 3890 59 over 188 (6 over 176), 2244 34 over 81 (4 over
#   72) and 2245 93 over 138 (4 over 110). The rows that differ for 728 and 3890 are locals only. CBuzzFieldMT's
#   gives 941 the same 8 over 179 both ways: out of line is a choice there, as its siblings have it.
# - `new CCutFieldPaper()`, with the parentheses: 1264 zeroes the object first; without them the rows differ in the object.
# - AddRect from two points calls an AddRect of a SRect that clang inlines: 3680's frame has the temporary of the AddField
#   call above the rectangle, which puts the temporary in a callee (an inlined callee's allocas come first), and 2245's has
#   them the other way. Written in one function, 3680 scores 12 over 94 with the frame the other way, and four spellings
#   of that one function give the same frame. 7787 holds the same make_shared<CRectField> and a call of AddField, so the inner one has a
#   caller of its own in the target; `inline` in the .cpp and private are chosen, for a header that would need CRectField.
#
# Chosen, the bytes do not decide:
# - Every adder's name, GeraNome, every parameter name, the name and the file of CMTFormBuilder, and that the classes share
#   no base. Which overloads share a name. That the adders are plain members of the .cpp files and not templates of a header:
#   each has one body in the target either way, and this is the form no stand-in has to instantiate. The order of the
#   definitions in the .cpp files, but for what the use bands of ledger/ordinals.tsv give (203 above 202, 2245 above 2244,
#   5419 above 5409), and all of cformbuilder.cpp's lines above 348.
# - The colours 2 and 1 of 1191, the 2 of 3068 and 3680, the alignment 0 of 3068, 5409 and 5419, the EStyle 1 of 604 and the
#   anchor 1 of 5547 are constants in the body or defaults of a parameter: binaryen folds a parameter every caller passes
#   (docs/how-to-decompile.md step 2), and each is written as the first, but for the alignment of 5409 and 5419, a default
#   argument. ANCHOR_TOP_RIGHT is api/gui/iimage.h's name for 1.
# - In each pair below the two forms give the function's rows, by the function's disassembly with the object-local numbers
#   masked: the private CMTFormBuilder::AddTextField, or its statements written in place, or the member without `inline`; `text`
#   and `campo` const or not; `m_campos.push_back(campo)` or `emplace_back(campo)` in the four adders with a const local (not
#   in the text adders, whose non-const `campo` picks another instantiation); `std::function` by value or by const
#   reference; the constructors `= default` or `{}`.
# What the bytes fix and what is chosen in GetLabeledKeyPos:
# the throw's column (11, one level in) puts it after the switch, so each arm
# returns; the arms' order (left, centre, right) is the target's block order (br_table 3 1 0 2); the arms assign a
# temporary SPoint to the named result, because with SPoint an aggregate (primitives.h) only that evaluates both
# coordinates before the first store, as the target does (a constructor SPoint(TPosition, TPosition) would give the
# same code from return SPoint(...)). The names of the three distances, of the parameters and of the enumerator are
# chosen; the alignment is formatted as an int (the argument type 3 the throw stores).
CFORMBUILDER_SRCS := src/api/gui/cformbuilder.cpp src/api/gui/cmtformbuilder.cpp src/api/gui/cpaperformbuilder.cpp
UENUX2_SRCS += $(CFORMBUILDER_SRCS)
# no caller of the unit's members is reconstructed yet: 31-uenux2-cformbuilder-roots.cpp gives each the calls it has in the
# target, and says which they are
$(ROOT)/$(APP)/31-uenux2-cformbuilder-roots.o: $(ROOT)/src/units/31-uenux2-cformbuilder-roots.cpp $(ROOT)/src/units/31-uenux2-cformbuilder.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h) $(wildcard $(ROOT)/src/ecourna/api/*.hpp) $(wildcard $(ROOT)/src/ecourna/api/exception/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/31-uenux2-cformbuilder-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/31-uenux2-cformbuilder-roots.o
