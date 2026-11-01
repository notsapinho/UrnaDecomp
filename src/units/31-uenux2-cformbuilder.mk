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
#   CPaperFormBuilder  193, 604 (AddTextField), 198 (AddNewLine), 1264 (AddCut), 2775 (AddQRCode); the member template AddTextField<FONTE>
#                      in cpaperformbuilder.h, below the classes so that line 51 stays in IFormImpressao: its instance
#                      over CPadDS<CToUpperDS<CCargoDSNome>> (5613) is unit 139's, whose fragment says what shows it
#   binaryen's         3890, the one body of 435, 1072 and 198; 1400, vector<shared_ptr<IFormField<...>>>::emplace_back(const
#                      value_type&), one body of the media's instantiations, under the first in the link
#   the getters        5550 (CFormBuilder::GetForm), 1694 and 301 (CMTFormBuilder::GetForm and GetInteractiveForm, each
#                      inlining a private overload that takes the pre-show) and 5515 (CPaperFormBuilder::GetForm): they
#                      build the forms of api/gui/iform.h and api/gui/cinteractiveform.h, whose code these objects emit,
#                      and src/units/120-uenux2-iform.mk has their notes. Their names are chosen. GetForm sits after
#                      the adders of cformbuilder.cpp, a choice; in cmtformbuilder.cpp GetForm comes before the adders
#                      and GetInteractiveForm after them, the order of their first uses in the target's data
#                      (IForm<IScreenMT>'s vtable @1579936 before the adders' control blocks @1580040 to @1580240, and
#                      CInteractiveForm<IScreenMT, IInputMT>'s @1580280 after them)
#
# 426, AddField, is written and `differs` (docs/how-to-decompile.md step 5). At -O2 it scored 292 over 449 rows: clang
# inlines std::string::append into operator+, and one loop compares the name. The target calls append (fn 160) and holds
# two copies of that loop, one for a long name and one for a short one, which only -O3's loop unswitching gives. At the
# tree's -O3 it is 18 over 334 rows, 14 of them operand-only; the other four are one add's operand order, n + (it !=
# end), which the object has and our link swaps (the object alone at -O3 in the -O2 link, by
# docs/reference/facts/workflow.md W13, gave the same 18). -O2 with -std=c++23 changes nothing (292 over 449), and -O3 with -std=c++23 gives the same
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
# - AddQRCode (2775) builds a std::shared_ptr<CQRCodeImageFieldPaper> (its control block's type, @1581500) and copies it
#   into a SharedField before push_back: the target increments the count in both of the vector's paths. Measured in the
#   link (pnpm wasm score): with CQRCodeImageFieldPaper's constructor inline, push_back of the first pointer scores 118
#   over 270 rows and emplace_back of it 84 over 265; with the constructor out of line (unit 53), push_back of it 103
#   over 263, and the copy first gives operand-only rows. The name AddQRCode is chosen.
# - AddRect from two points calls an AddRect of a SRect that clang inlines: 3680's frame has the temporary of the AddField
#   call above the rectangle, which puts the temporary in a callee (an inlined callee's allocas come first), and 2245's has
#   them the other way. Written in one function, 3680 scores 12 over 94 with the frame the other way, and four spellings
#   of that one function give the same frame. The inner one is a plain member, above its caller: with `inline` 18 of band
#   1's 136 pairs below are inverted, and clang still inlines it. So 7787's own make_shared<CRectField> is not a call of it.
# - RectEntre reads the four coordinates into locals before it builds the SRect: 2245 and 3680 store it +6, +4, +2, +0, which
#   docs/reference/facts/codegen.md C1 gives for values read first. Written as `SRect{std::min(canto.x, oposto.x), ...}`, 2245
#   scores 38 over 121 and 3680 36 over 105. SRect is an aggregate of ours (api/gui/primitives.h), so these locals stand in
#   for whatever the original reads them with: its header's form is not recovered.
# - The order of the definitions, by the use bands of ledger/ordinals.tsv. The members of the control blocks and of the
#   CDataText instantiations an adder brings are linkonce and have one use each, and each takes its place at its first
#   mention, so a run of consecutive target indices in band 1 orders the adders that mention them (docs/how-to-decompile.md
#   step 3, "The order of two members", over every matched row of each object). Inverted pairs of band 1: 0 of 136 in
#   cformbuilder.cpp.o, 0 of 3 in cpaperformbuilder.cpp.o, 38 of 231 in cmtformbuilder.cpp.o. Each of the 38 involves 12301-12323,
#   the class members of CDataText<std::function> and of CDataTextFmt of a function, which can be another object's copies, a
#   reading, and band 2's two pairs against 6404 stay inverted with them. The other bands' pairs in one object agree: 203
#   above 202, 2245 above 2244, 5419 above 5409.
#
# Chosen, the bytes do not decide:
# - Every adder's name, GeraNome, RectEntre and that it is a free function of the file, every parameter name, the name and
#   the file of CMTFormBuilder, and that the classes share no base. Which overloads share a name. That the private members
#   are private. IFormFieldBase's GetName and SetName (api/gui/iformfield.h), name and being members: 426 reads and assigns
#   the string at +12 of the field, in line. That the adders are plain members of the .cpp files and not templates of a
#   header: each has one body in the target either way, and this is the form no stand-in has to instantiate. The lines of
#   cformbuilder.cpp's definitions above 348.
# - The colours 2 and 1 of 1191, the 2 of 3068 and 3680, the alignment 0 of 3068, 5409 and 5419, the EStyle 1 of 604 and the
#   anchor 1 of 5547 are constants in the body or defaults of a parameter: binaryen folds a parameter every caller passes
#   (docs/how-to-decompile.md step 2), and each is written as the first, but for the alignment of 5409 and 5419, a default
#   argument. ANCHOR_TOP_RIGHT is api/gui/iimage.h's name for 1.
# - In each pair below the two forms give the function's rows, by the function's disassembly with the object-local numbers
#   masked: the private CMTFormBuilder::AddTextField, or its statements written in place, or the member `inline`, which only
#   band 1 tells apart (cmtformbuilder.cpp's header has the count); `text`
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
#
# CPaperFormBuilder::Build (target fn 357, cpaperformbuilder.cpp): the form of GetForm (fn 5515), after which the
# builder's vector is emptied, a clear() as the target's loop shows (each pointer released from the last, the end then
# set to the start). The target passes its own result to 5515, which `return form;` of a named local gives by copy
# elision. 16 target functions call it (2890, 3699, 3872, 3873, 5579, 5580, 5970, 5971, 5977, 11253, 11256, 11908,
# 11946, 12005, 12105, 12110), none reconstructed: the stand-in FormPapelC calls it twice. In the whole link it scores
# 1 over 51 rows (`pnpm wasm score`), the one row its call of 5515. Its name is chosen: 5515 has GetForm, and the
# screens' builders, whose getters empty the vector themselves (unit 120's fragment), give no name for this split.
CFORMBUILDER_SRCS := src/api/gui/cformbuilder.cpp src/api/gui/cmtformbuilder.cpp src/api/gui/cpaperformbuilder.cpp
UENUX2_SRCS += $(CFORMBUILDER_SRCS)
# no caller of the unit's members is reconstructed yet: 31-uenux2-cformbuilder-roots.cpp gives each the calls it has in the
# target, and says which they are
$(ROOT)/$(APP)/31-uenux2-cformbuilder-roots.o: $(ROOT)/src/units/31-uenux2-cformbuilder-roots.cpp $(ROOT)/src/units/31-uenux2-cformbuilder.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h) $(wildcard $(ROOT)/src/ecourna/api/*.hpp) $(wildcard $(ROOT)/src/ecourna/api/exception/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/31-uenux2-cformbuilder-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/31-uenux2-cformbuilder-roots.o
