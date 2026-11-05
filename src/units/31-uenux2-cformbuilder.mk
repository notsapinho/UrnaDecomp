# uenux2 api::CFormBuilder, and its siblings for the other media, api::CMTFormBuilderBase with api::CMTFormBuilder over
# it, and api::CPaperFormBuilder, in
# src/uenux2/src/api/gui/. cformbuilder.cpp is the file the records name: GetLabeledKeyPos (target fn 5544, line 372 col
# 11, the CUeGuiError 4914 throw) and AddStatusHeader (fn 502, lines 292 and 305, written, below). No record names the
# other two .cpp files, whose paths are chosen, each the class's in lower case beside cformbuilder.cpp; cpaperformbuilder.h
# is a record's. Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
#
# Target functions, all matched but two:
#   CFormBuilder       203 (constructor, one body with CMTFormBuilder's), 202 and 1191 (AddTextField), 3068 (AddDoubleLineField),
#                      5547 (AddImage), 2244 (AddLine), 2245 (AddFill), 3680 (AddRect), and 426 (AddField), written and differs;
#                      3678 and 2243 (AddLabeledKey, over a key's name and over a key) and 2782 (AddTextFieldMultiLine), below;
#                      1265 (AddBlinkingTextField, below); 3058 (AddTextFieldUpdate over std::string (*)(const std::string&),
#                      a template of cformbuilder.h, which says why; the scan's content pass finds it, no vote names it); 502 (AddStatusHeader), written and differs, below,
#                      with the members of its lambda's CDataText: 11107 (GetText), 11109 and 11108 (the control block's
#                      D2 and D0)
#   CMTFormBuilderBase 180, 619, 651, 1152, 5409, 5419 (AddTextField), 435 (AddLed), 1072 (AddBeep), 941 (AddBuzz), 728
#                      (AddClock), 3674 (AddField); CMTFormBuilder, over it, 203 (its out-of-line constructor) and 395
#                      (AddInputControl), with 3673, api::IInputField<IScreenMT>'s constructor (api/gui/iinputfield.h),
#                      whose copy this object emits: the input fields, below. cmtformbuilder.h has why two classes: six
#                      of GetForm's seven target callers build the builder in their frame with no constructor call,
#                      where 10204 and GetInteractiveForm's 49 call 203
#   CPaperFormBuilder  193, 604 (AddTextField), 198 (AddNewLine), 1264 (AddCut), 2775 (AddQRCode); the member template AddTextField<FONTE>
#                      in cpaperformbuilder.h, below the classes so that line 51 stays in IFormImpressao: its instance
#                      over CPadDS<CToUpperDS<CCargoDSNome>> (5613) is unit 139's, whose fragment says what shows it
#   binaryen's         3890, the one body of 435, 1072 and 198; 1400, vector<shared_ptr<IFormField<...>>>::emplace_back(const
#                      value_type&), one body of the media's instantiations, under the first in the link
#   the getters        5550 (CFormBuilder::GetForm) and 11140 (its overload of a name alone, below), 1694 and 301
#                      (CMTFormBuilderBase::GetForm and CMTFormBuilder::GetInteractiveForm, each
#                      inlining a private overload that takes the pre-show) and 5515 (CPaperFormBuilder::GetForm): they
#                      build the forms of api/gui/iform.h and api/gui/cinteractiveform.h, whose code these objects emit,
#                      and src/units/120-uenux2-iform.mk has their notes. Their names are chosen. GetForm sits after the
#                      adders of cformbuilder.cpp but AddLabeledKey's two and AddTextFieldMultiLine, which follow
#                      GetLabeledKeyPos by their bands, a choice; in cmtformbuilder.cpp GetForm comes before the adders
#                      and GetInteractiveForm after them, the order of their first uses in the target's data
#                      (IForm<IScreenMT>'s vtable @1579936 before the adders' control blocks @1580040 to @1580240, and
#                      CInteractiveForm<IScreenMT, IInputMT>'s @1580280 after them)
#
# 11140, CFormBuilder::GetForm(const std::string&): the form of the fields added over a new api::CPreShowClearScreen
# (vptr 1577896; its vtable and typeinfo lie in this file's data, so this object emits them and PreShow, fn 11139, first
# in the link, and so CPreShowClearScreen's control block, whose __get_deleter, fn 11138, matches from here), through
# GetForm(preShow, nome). Its target body is a thunk of binaryen's fn 6117, the body of 11140 and vota::GetFormulario
# (fn 886, unit 165). Its one target caller is fn 1255, comum::TelaRegistroMesarios, and what keeps it out of line is
# unit 247's (that fragment has the measurements). Chosen: its being an overload, its name, its line after the first
# GetForm (11140's ld_index, 4508, is below 11139's, 4514, in band 1, as the target's order wants).
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
# 502, AddStatusHeader, is written and `differs` (docs/how-to-decompile.md step 5). It holds what only it reaches: the
# lambda's CDataText (11107 to 11109 match from this object), the table slot of api::CDateTime::FormatCurrentDateTime
# (fn 10870, unit 125), and the constructors of api::CDSImageField (unit 55) and BatteryIconDataSource<Horizontal> (unit
# 164), which binaryen inlines into it as into the target. In the whole link it scores 91 over 977 rows (pnpm wasm
# score against our fn), 62 of the 63 replaced rows operand-only. What is left, not explained:
# - in the icon's field, the target lays the paths of m_campos.push_back that throw (__throw_length_error,
#   __throw_bad_array_new_length) right after the push, ours at the end of the function; and the unlock of
#   IObservable::Attach's mutex (Attach is inlined with the CDSImageField constructor) takes the mutex's address at the
#   call, ours before;
# - two blocks more in our copy of BatteryIconDataSource<Horizontal>'s constructor, whose <Vertical> copy matches in
#   5904 (unit 153);
# - one add's operand order in the charge's x, larguraTela - 70 or - 55: the target adds the width to the selected
#   constant, ours the constant to the width, with x a named local or written in the call alike (91 rows each way).
# What the bytes fixed, each measured in the link:
# - comIcone: the target computes campos & 4 once, before the charge's field, and reads it there and for the icon;
#   with the bit tested in both places our link computes it in each branch of the charge's test (106 over 986 rows);
# - the icon's SPoint a named local: the target builds it before the CDSImageField's allocation, and a temporary in
#   the new-expression comes after it (the allocation is sequenced first), which our link showed;
# - the lambda's empty text, `return ""`: the target stores two bytes, where `return {}` zeroes twelve (11107 then
#   differs in 3 rows);
# - SharedField(new CDSImageField(...)) pushed with m_campos.push_back, not AddField: the target builds the pointer
#   block @1578376 and calls no AddField there, so the icon's field gets no generated name;
# - the two CPolySingleton instance() calls on the records' lines, the record's columns 30 and 24 being where each
#   call starts.
# Chosen: every local's name and how each record's column is shared out (const auto larguraTela, auto& ipower), the
# lambda's capture by reference, every line but the records' (and the blank runs between), the font's name
# FONTE_PADRAO, and SFont{20, 1} for the mode's text, a temporary as the target builds it on the stack.
#
# 3678 and 2243, AddLabeledKey over a key's name and over a key, and 2782, AddTextFieldMultiLine, match; the scan's
# content pass names each (source `content`), as no vote reaches them. Their target callers are screens, none written
# but 653, 12055, 6569 and 1588 (3678's 653, 2243 and 7787; 2243's 6569, 7787 and 12055; 2782's 1588, 3074, 7787 and
# 12040): the
# roots say which stand-in stands for which. Each measured in the link (`pnpm wasm score`, and `pnpm wasm
# splat-remap`, which reads 3678 and 2782 IDENTICAL, and 2243 unresolved on its one call, of 3678, whose name only that
# match gives):
# - 3678 passes 5544 the screen's area, api::CApplication::s_areaTela (capplication.h lists its readers), through
#   CApplication::GetAreaTela, out of line in capplication.cpp, which binaryen inlines into it. With 3678 naming the
#   static itself, our link folds 5544's area parameter, which the target keeps: 5544, matched, then scores 96 over
#   244 rows (5 inserted, 5 deleted), and 3678 15 over 264 with 2 deleted.
# - The colours. The target's 3678 takes none. Written as constants of the body (2 over 1), 3678 scores 27 over 264
#   rows and splat-remap stops at body byte 164, the target's local.tee 0. With the text colour a parameter whose
#   default every caller here leaves, it matches, with the background a parameter too or a constant of the body: the two
#   give one plain link (sha256 c3f8a83f01c01a68... both). Both parameters is the choice.
# - With both positions and the second field temporaries, 3678's frame is the target's.
# - 2243 is KeyName (744, api/hwil/iinput.h) and a call of 3678; 744's copy linked from this object until unit 110's
#   ctelasvota.cpp.o, ahead of it in link order, gave one (12903 calls KeyName), still matching.
#   653 (unit 120) holds that code behind a second prologue: AddKeyLabel, written after 2243, which only 653 calls and
#   binaryen inlines there (cformbuilder.h says why it is a function apart from 2243; unit 120's fragment has the
#   measurements). Which of the two is the 3-parameter AddLabeledKey and which the other is chosen, and so are
#   AddKeyLabel's class, file and place after 2243 (KeyName is api/hwil/iinput.h's inline: the code pins no TU but
#   that it is not 653's).
# - 2782 has AddTextField's shape over the CTextFieldMultiLine constructor (5498, unit 14). Its CFixedText control
#   block's vptr, 1578304, is the one 202 and 1265 store; its CTextFieldMultiLine control block's, 1539360, which only
#   2782, 12055 and that block's members 12298 and 12300 hold, is no neighbour of it, so the target's copy of that block
#   is another object's (a reading). 12298 and 12300 link from ctelasvota.cpp.o now (its AdicionaTextoMultiLinha makes
#   that block too), still matching.
# - The three are defined after GetLabeledKeyPos, by their use bands (docs/how-to-decompile.md step 3, "The order of
#   two members", on build/out/wasm-map/vota_web/names.tsv's ld_index): 3678 links after AddRect (band 3), 2243 after
#   AddFill and AddLine (band 5), 2782 after AddDoubleLineField and 3058 (band 4), which AddStatusHeader mentions
#   first, and 3678's call of GetLabeledKeyPos places 5544 there, which band 2 puts after GetForm (5550). Written
#   above GetForm, 2782's pair with 3058 and 5544's with 5550 read inverted. Their order among themselves and their
#   lines are chosen. Band 2's other pairs, 5547 with 5550 and each with 6404, read inverted in both placements and
#   involve nothing the three mention; band 1 lists 12298 and 12300 out of order: another object's copies, which say
#   nothing (step 3).
#
# 1265, AddBlinkingTextField: AddTextField's shape over a api::CTextFieldBlinking, whose constructor binaryen inlines
# here with its timer's lambda (unit 44 has the class). Its name, and the colours 2 and 3 over 1 as constants of the body
# rather than parameters every caller passes the same (binaryen's dead-argument elimination would fold them: the
# target's wasm type has none), are chosen. It matches since api::ITimerScheduler::CreateTimer takes its callback by
# reference (api/util/itimerscheduler.h): with the callback by value it was 30 over 308 rows, 24 of them operand-only,
# the one difference the place of the 500 ms interval's store, which the target makes before it builds the
# std::function (`pnpm wasm score` against our fn). TelaA and TelaB give it its two call sites.
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
#   scores 38 over 121 and 3680 36 over 105. SRect was an aggregate of ours when this was measured; it has
#   a normalizing constructor now (api/gui/primitives.h), which this brace form calls, and cformbuilder.cpp.o is the same
#   object with it. These locals stand in for whatever the original reads them with: its header's form is not recovered.
# - The order of the definitions, by the use bands of ledger/ordinals.tsv. The members of the control blocks and of the
#   CDataText instantiations an adder brings are linkonce and have one use each, and each takes its place at its first
#   mention, so a run of consecutive target indices in band 1 orders the adders that mention them (docs/how-to-decompile.md
#   step 3, "The order of two members", over every matched row of each object). Inverted pairs of band 1: 0 of 136 in
#   cformbuilder.cpp.o, 0 of 3 in cpaperformbuilder.cpp.o, 38 of 231 in cmtformbuilder.cpp.o. Each of the 38 involves 12301-12323,
#   the class members of CDataText<std::function> and of CDataTextFmt of a function, which can be another object's copies, a
#   reading, and band 2's two pairs against 6404 stay inverted with them. The other bands' pairs in one object agree: 203
#   above 202, 2245 above 2244, 5419 above 5409.
#
# The MT builder's input fields: 3674 (AddField), 395 (AddInputControl) and 3673. 395 allocates the field's 64 bytes,
# builds the CControlValidation and its control block, calls 3673 and releases the validation before the field's vptr
# store, the order `new CInputFieldControl<IScreenMT>` gives with api/gui/cinputfieldcontrol.h's constructor, which 395
# holds inlined in its own frame. It then copies the field into a SharedField and passes that to 3674, which holds
# vector::emplace_back with its slow path. The target keeps 3674 a call in its three callers, 395, 1151 and 5410, and
# 1151 is another object's code (its control block's vtable @1588176 lies in app/vota/operador/outrasopcoes/
# cescolheopcao.cpp's data; unit 121 writes it there as vota::AdicionaCampoNumerico). What fixes the form, each measured:
# - Nothing outside this file keeps 3674 a call. At the tree's flags (-Rpass=inline -Rpass-missed=inline on
#   cmtformbuilder.cpp), emplace_back goes into AddField (cost=310, threshold=325) and AddField, which has no inline
#   hint, stays out of AddInputControl (cost=270, threshold=250); 3673 stays out of line (cost=340, threshold=250) and
#   CInputFieldControlBase<IScreenMT>'s constructor goes in (cost=240, threshold=250). Written with no AddField, as
#   m_campos.push_back(campo) in AddInputControl, push_back(&&) stays out of it too (cost=270, threshold=250).
# - AddField is defined before AddInputControl. In use band 3 the target links 3674 before 3673, and an object lists a
#   linkonce function at its first mention: with AddInputControl calling m_campos.push_back(campo) and no AddField, the
#   object lists AddInputControl, 3673's constructor, then push_back(&&), the other order; with AddField first, AddField,
#   AddInputControl and the constructor link in that order (ld_index 4473, 4474, 4475), and band 3 holds no pair of
#   this object out of order.
# - AddField's body, emplace_back(std::move(campo)) or push_back(std::move(campo)): the two give one plain link
#   (sha256 7dace76cda976fb7... both, at this unit's landing). With push_back, clang inlines AddField into
#   AddInputControl and binaryen into its one other caller, the roots' EntradaMT, and the link map names the body
#   libc++'s vector::push_back(value_type&&) (build/out/wasm-map/vota_web/names.tsv); with emplace_back it names it
#   AddField, the name the match line takes. emplace_back is the choice.
# - AddInputControl's `campo` const or not, and AddInputControl a member or a free function of api that takes the
#   builder by reference: each pair gives 395's function, its disassembly compared with the object-local numbers
#   masked. A member by choice: it reaches the vector only through AddField.
# - 3673 matches with api::ITimerScheduler::CreateTimer taking its callback by reference, as api/util/itimerscheduler.h
#   has it now; unit 120's fragment scored it 12 over 211 rows with the callback by value.
# The roots' ControleMT gives 395 its second call site; 3674 and 3673 have their three target callers in the link,
# 395, 1151 and 5410, so EntradaMT, the roots' stand-in for 5410, went with 5410's landing. 1151, which builds an
# api::CInputFieldMT over a CNumberValidation ("0123456789") and pushes it through 3674, is unit 121's (cescolheopcao.cpp,
# vota::AdicionaCampoNumerico; src/units/121-uenux2-datasources.mk has its evidence). And 5410's code:
# - 5410 ("ELEITOR(A) PODE VOTAR", callers 1256 and 5399) holds behind a second prologue code that builds a
#   CInputFieldControl<IScreenMT> with std::make_shared and calls 3674; its block's vtable (@1580748) lies in this
#   object's data, so that code is a member of this file that binaryen inlined, a reading. It is written so:
#   AddInputControl(int teclas) (name, overload and parameter chosen after api::CInteractiveFormBuilder's), which 5410,
#   vota::MontaTelaEleitorPodeVotar in unit 161's ccontrolareconhecimento.cpp, calls with 4, the default of
#   CInputFieldControl's constructor. 5410 differs (unit 161's fragment has the rows); 395, 3674 and 3673 still match.
#
# Chosen, the bytes do not decide:
# - Every adder's name, GeraNome, RectEntre and that it is a free function of the file, every parameter name, the name and
#   the files of CMTFormBuilderBase and CMTFormBuilder, which members are the derived class's (cmtformbuilder.h lists
#   them), and that the media's classes share no base. Which overloads share a name. That the private members
#   are private. IFormFieldBase's GetName and SetName (api/gui/iformfield.h), name and being members: 426 reads and assigns
#   the string at +12 of the field, in line. That the adders are plain members of the .cpp files and not templates of a
#   header: each has one body in the target either way, and this is the form no stand-in has to instantiate. The lines of
#   cformbuilder.cpp's definitions above 348.
# - The colours 2 and 1 of 1191, the 2 of 3068 and 3680, the alignment 0 of 3068, 5409 and 5419, the EStyle 1 of 604 and the
#   anchor 1 of 5547 are constants in the body or defaults of a parameter: binaryen folds a parameter every caller passes
#   (docs/how-to-decompile.md step 2), and each is written as the first, but for the alignment of 5409 and 5419, a default
#   argument. ANCHOR_TOP_RIGHT is api/gui/iimage.h's name for 1.
# - In each pair below the two forms give the function's rows, by the function's disassembly with the object-local
#   numbers masked: the private CMTFormBuilderBase::AddTextField, or its statements written in place, or the member
#   `inline`, which only band 1 tells apart (cmtformbuilder.cpp's header has the count); `text` and `campo` const or
#   not; `m_campos.push_back(campo)` or `emplace_back(campo)` in the four adders with a const local (not in the text
#   adders, whose non-const `campo` picks another instantiation); `std::function` by value or by const reference; the
#   constructors `= default` or `{}`.
# What the bytes fix and what is chosen in GetLabeledKeyPos:
# the throw's column (11, one level in) puts it after the switch, so each arm
# returns; the arms' order (left, centre, right) is the target's block order (br_table 3 1 0 2); each arm returns
# SPoint(...) through SPoint's constructor (primitives.h), which evaluates both coordinates before the first store, as
# the target does; while SPoint was an aggregate only a temporary assigned to a named result did, and with the
# constructor that form scores 33 over 245 rows (6 inserted, 7 deleted), return SPoint(...) 15 over 239, every row an
# operand (pnpm wasm score in the link). The names of the three distances, of the parameters and of the enumerator are
# chosen; the alignment is formatted as an int (the argument type 3 the throw stores).
#
# CPaperFormBuilder::Build (target fn 357, cpaperformbuilder.cpp): the form of GetForm (fn 5515), after which the
# builder's vector is emptied, a clear() as the target's loop shows (each pointer released from the last, the end then
# set to the start). The target passes its own result to 5515, which `return form;` of a named local gives by copy
# elision. 16 target functions call it (2890, 3699, 3872, 3873, 5579, 5580, 5970, 5971, 5977, 11253, 11256, 11908,
# 11946, 12005, 12105, 12110); 11256 and 2890 (unit 156), 12005 (unit 246), 11908 (unit 176's, written), 3872, 3873,
# 5579, 5977, 3699, 5580, 5970 and 5971 (fragment 325's) and 11253 (unit 139's, written) are in the link and the
# stand-in FormPapelC calls it twice for the other three, 11946, 12105 and 12110. In the whole link it scores 1 over
# 51 rows (`pnpm wasm score`), the one row its call of 5515. Its name is chosen: 5515 has GetForm, and the screens'
# builders, whose getters empty the vector themselves (unit 120's fragment), give no name for this split.
#
# CPaperFormBuilder::Show (target fn 3671, cpaperformbuilder.cpp), written with unit 246: its name and parameters are
# its lambda's RTTI, api::CPaperFormBuilder::Show(const std::string &, const std::string &, bool)::$_0 (vtable @1581356,
# right after cpaperformbuilder.h's record 1581300, so this file's object). It prints through api::CLp::GetInst() (fn
# 3876, unit 219) and CLp::Imprime (fn 3875) an api::CSubReport of copies of the two strings and the bool (fn 3660),
# with a lambda that captures this and calls GetForm (fn 5515) and slot 2 of the form (fn 10997, the lambda's call), and
# then empties the vector (the same clear() loop as Build's). Every target caller (5591, 5592, 11902) passes true, which
# binaryen's dead-argument elimination folds (fn 3671 is (i32 i32 i32)->(), and fn 3660 gets 1). pnpm wasm score against
# the link: 11 over 229 rows, operand-only; matched by the scan's content pass, with the lambda's std::function slots
# 10995, 10996, 10997, 10999 and 11000, which step 8 names by the lambda's vtable. Its declaration in
# cpaperformbuilder.h takes the blank line between the header's two include groups, so that GetRenderForm keeps line 51,
# record 1581300's. Its three target callers are in the link (5592, unit 287's, 5591, unit 296's, and 11902, unit
# 176's), and the stand-in fragment 246's roots held for 11902 went with it. Chosen: the parameters' names; the lambda's capture spelled `[this]` (`[&]` captures the same by the
# language's rules, not compiled here); the header line the declaration takes (any line above 51 would do); Show's place
# last in the file (it is the file's only function with 3 uses in ledger/ordinals.tsv, so no band neighbour orders it).
CFORMBUILDER_SRCS := src/api/gui/cformbuilder.cpp src/api/gui/cmtformbuilder.cpp src/api/gui/cpaperformbuilder.cpp
UENUX2_SRCS += $(CFORMBUILDER_SRCS)
# 31-uenux2-cformbuilder-roots.cpp gives each member whose target callers are not all in the link the calls it has in
# the target, and says which they stand for (502, AddStatusHeader, here, calls 3058 and 202, and 2243 calls 3678); 728,
# 941, 5409 and 5419 have every target caller in the link and no call there
$(ROOT)/$(APP)/31-uenux2-cformbuilder-roots.o: $(ROOT)/src/units/31-uenux2-cformbuilder-roots.cpp $(ROOT)/src/units/31-uenux2-cformbuilder.mk $(ROOT)/src/Makefile $(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h) $(wildcard $(ROOT)/src/uenux2/src/api/util/*.h) $(wildcard $(ROOT)/src/ecourna/api/*.hpp) $(wildcard $(ROOT)/src/ecourna/api/exception/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/31-uenux2-cformbuilder-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/31-uenux2-cformbuilder-roots.o
