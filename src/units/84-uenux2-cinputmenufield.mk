# uenux2 api::CMenuValidation::isValidChar (target fn 10899, slot 3 of the vtable @1583300) in
# src/uenux2/src/api/gui/cinputmenufield.cpp, the file the class's records name, with the class header
# api/gui/cinputmenufield.h (its path chosen), which reads the text at +24 of IInputField<IScreen> through
# api/gui/cinputfield.h and iinputfield.h, unit 92's. The body inlines IInputValidation::isValidChar (the memchr) and
# then builds the text plus the character: `text + std::string(1, c)`, libc++'s operator+(const string&, string&&),
# whose insert(0, ...) is fn 499 and whose move the words at +16 show. isValid (10900) is the key function, so
# cinputmenufield.cpp emits the vtable and the implicit deleting destructor (one body with the other validations',
# 2980); slot 0 is the base's destructor. It holds matchesExactly and matchesPartially, the records' at 198:5 and 210:5:
# the first inlined by clang, in its frame, the second by binaryen, with its second stack prologue. Each searches with
# std::find_if and tests the iterator: the target tests `it != end` after the loop. std::any_of scored 63 over 326 rows,
# and a for loop that returns differs in 19 lines; an if on `it == end` around the beep gives the same object code. The
# prefix test is rfind(text, 0) == 0: its min of the two sizes and its reverse search are in the body, and starts_with
# and compare differ in 184 and 183 lines. What the two helpers read of the menu is CMenuItem's +65 and +68 and the list
# at +140, cinputmenufield.h has the head; its names are chosen. Forms that give 10899's object code, by the function's
# disassembly in a compile with the unit's flags: an early `return false` before the call, an `if` around it, and
# `m_validChars.find(c) == std::string::npos` for the base's member. So those are choices. Forms that do not: the text
# in a named local (another frame), `text + c`, `text + digito` with a named string, `texto += c`. The control block's
# D0 and D2 (10891, 10892) match from this file's object, whose fn 3675 builds the validation with std::make_shared.
#
# api::CInputMenuField (vtable @1583356, cinputmenufield.h has its layout and slots) in the same file: the destructor
# (D2 5491, D0 10898: out of line, the D0 calls the D2 and frees this, so it is the key function and the file emits the
# vtable), Rect (10896), Read (10894, record 419:21, the beep), GetTypeName (10893), and the private SelecionaItem
# (5489, Read calls it twice), LimpaSelecao (clang inlines it at its four sites) and CMenuItem::Pisca (inlined by
# binaryen into Read, its one caller: the blink of the chosen item, two toggles with a 100 ms sleep each), with
# std::__destroy_at<CMenuItem> (5490), CMenuItem's implicit destructor inlined into libc++'s helper, which the list's
# clear in the destructor calls. Move (10895, record 278:21, the `IScreen& tela = CPolySingleton<IScreen>::instance()`
# line) and the private Reposiciona (2770; callers 1693, 3675, 10895) match too: below. The u=1 band
# of ledger/ordinals.tsv runs 10900, 10899, 10898, 10897, 10896, 10895, 10894, 10893 and the u=2 band 5491, 5490, 5489:
# the definitions follow that order (D0 and Rect before Move's record line, Read's after it, GetTypeName last), and
# names.tsv's ld_index agrees in the plain link. Names chosen: SelecionaItem, Reposiciona, LimpaSelecao, Desloca, Pisca,
# every data member and local; the loop counter of Pisca and the friendship of the two classes are choices. Measured, by
# the function's disassembly in a compile with the unit's flags and by `pnpm wasm score` in the plain link:
# - Move: the new x and y in locals before the loop (`const TPosition x = posicao.x; m_posicao.x = x; ...`) give the
#   target's loop, which adds them to the item's position read as one 32-bit word with 4-byte alignment; reading
#   m_posicao.x in the loop reloads it after each SRect::Move call (18 lines differ), and the item's position read
#   through a getter that returns a reference keeps a 2-byte alignment. A copy `const SPoint origem = m_posicao` before
#   the loop gives the same object code as the locals. The arithmetic is CMenuItem::Desloca, which reads its own
#   m_posicao. The screen's call is slot 5, IScreen::Clear(const SRect&, TColor), as in the target. Score 4 over 117
#   rows, all operand-only, while its call of Reposiciona (2770) had a name only from Move's own vote (`unresolved
#   self-voted`). At 16b8f99f Move matches, that name held by the calls of 3675 and Move (`evidence:call
#   by:3675,10895`); since 2770 matches, by 2770's own pair (`pair-addr`).
# - Read: the CONFIRMA case with the beep in an `else` after the blink places the beep after SEM_TECLA's SelecionaItem;
#   the beep first in the `else` with its `break`, and Clear and the return after the `if`, gives the target's order,
#   with the beep at column 21, and the same object code as the beep after the `if` with no `else` (column 17). The two
#   toggles written in Read leave a `br_if` around the last sleep where the target has an `if` and a branch out: the
#   blink out of line in CMenuItem::Pisca, which binaryen inlines, gives the target's shape (17 over 358 rows, one
#   deleted, against 14 over 358, all operand-only). Written in Read, a loop of two and the two toggles written out gave
#   the same object code; Pisca's loop of two is a choice measured only through Read's match.
# - The destructor (5491) matches since src/api/ builds with strict aliasing: libc++'s list clear,
#   `__f->__prev_->__next_ = __l->__next_; __l->__next_->__prev_ = __f->__prev_;`, reloads `__f->__prev_` after the
#   first store with -fno-strict-aliasing, and the target keeps it in a local, which strict aliasing gives (the
#   function's disassembly in two compiles of the file, with the flag and without it: only the destructor and libc++'s
#   std::format helpers differ). With the flag it scored 13 over 76 rows (2 inserted, 2 deleted); src/Makefile
#   UENUX2_TBAA_DIRS takes it off this directory (docs/reference/facts/app-flags.md F6).
# - Reposiciona (2770) matches with the instruction's corner from a helper and the mask's position assigned whole. The
#   target's 16-byte frame holds the rectangle Adjust returns at +4, the point Move takes at +12, above it (its y stored
#   before its x), and the mask's position at +4, in the rectangle's slot; when the instruction text is not empty it
#   stores that position again as one 32-bit word, x + 7 and the y it holds. As written before (`const SRect itens =
#   m_rectItens.Adjust(0, 0, 0, 5); m_rectInstrucao.Move(SPoint{itens.left, itens.bottom});`, then `posicao.x += 7`)
#   the rectangle was at +8 above the point at +4, the mask's position in the point's slot and x stored alone as 16
#   bits: 18 over 106 rows in the plain link (10 operand-only, 7 deleted). The first object a function creates takes
#   the highest offset (docs/reference/facts/codegen.md C5); in `m_rectInstrucao.Move(CantoInferiorEsquerdo(
#   m_rectItens.Adjust(0, 0, 0, 5)))` the point, the call's result, is created before the rectangle, its argument, and
#   both end with the statement, so the mask's position, created after them, takes the rectangle's slot (a reading; the
#   offsets are the measurement). CantoInferiorEsquerdo returns `SPoint(rect.left, rect.bottom)` of a `const SRect&`,
#   and clang inlines it. Measured by the function's disassembly in compiles of the file at the unit's flags: the same
#   function with the helper in an anonymous namespace, `static` or external (an external one also stays in the object),
#   as a lambda called in place, as an SRect member returning `SPoint(left, bottom)` called on Adjust's result
#   (`m_rectItens.Adjust(0, 0, 0, 5).CantoInferiorEsquerdo()`, the member added to a copy of primitives.h), and with the
#   point a named `const SPoint` initialized from the helper and passed to Move; other frames with the helper taking the
#   SRect by value (the mask's position at +12), with no helper and the point declared first and set from the rectangle
#   in an inner scope (the corner stored as one 32-bit word), and with the corner's move and the mask's in a member
#   helper that takes the rectangle from Reposiciona (the mask's position at +12, in the point's slot). `posicao =
#   SPoint(posicao.x + 7, posicao.y)` gives the 32-bit store, and so do `SPoint(m_rectInstrucao.right + 7,
#   m_rectInstrucao.top - 1)` and `SPoint{static_cast<TPosition>(posicao.x + 7), posicao.y}` (the same function);
#   `posicao.x += 7` stores x alone, and the two points as the arms of a conditional initializer give a select of the
#   two x and two 16-bit stores. In the whole link 2 over 106 rows, both operands (a constant the scan reads as data and
#   a callee), then `match`. Chosen: the helper, its name, its internal linkage (an anonymous namespace), its being a
#   free function (it reads no state of the class) and the first of the three forms of the 7.
# - AddItem (1693, records 320:15 and 339:15, the two throws, 326:21, the instance() line), with NextItemPosition
#   (record 298:21) and CMenuItem's constructor, both held in it in the link (NextItemPosition behind a second
#   stack-pointer prologue), matches with the room left under the menu written as `std::min(alturaTela -
#   alturaInstrucao, m_posicao.y + m_alturaMaxima - alturaInstrucao)`: the instruction's height a TPosition local used
#   in both arms, after the screen's height held in a TPosition local (an int there gives the same function, and so does
#   the limit held in a `const int limite`), so that the instruction's rectangle is read after GetHeight's call, as in
#   the target. The target computes the room as `min + ~(bottom - top)`, and the height written once, before this form,
#   gave `min + top + ~bottom` (the same value): 36 over 628 rows in the plain link, 31 operand-only, the other five
#   (one replaced, two inserted, two deleted) from that expression. The matched form's final IR holds the height as the
#   16-bit `(bottom + 1) - top`, zero-extended into the int subtraction from the minimum (`-mllvm -print-after-all` on
#   the object's compile), so the target's not is the backend's (a reading). Measured now by NextItemPosition's
#   disassembly in compiles of the file at the unit's flags: the TPosition height used in both arms but declared before
#   GetHeight's call gives the target's not with the two loads ahead of the call; an int height used in both arms, an
#   int height used once, or the limit as the bottom of an SRect built from it give `top + ~bottom` (the last with a
#   select of its own); `bottom - top` in an int used in both arms with the 1 taken after the minimum, or a TPosition
#   height used once, give `top - bottom` with the 1 and the 5 joined; std::max(height, 0) loads the edges as signed and
#   adds a select. Measured on the way before, in
#   the plain link:
#   196 over 656 with the rectangles read as members, a reference kept from emplace_back and a default std::string; 80
#   over 647 with the last item's and the widest one's rectangles through CMenuItem::GetRect, which returns it by value
#   (the target loads each as one 64-bit word and shifts, which the by-value copy gives; the members give 16-bit loads),
#   `return m_itens.back()` at the end (the target reads the list's last node again) and the item's format string
#   constructed from "" (two byte stores, where a default std::string zeroes 12 bytes); 36 over 628 with the room held
#   in a TPosition before the 5 is taken off. The instruction's height in a TPosition local of its own, or cast to
#   TPosition in the expression, gives 82 over 648 and 80 over 647; written as `- (bottom - top) - 1`, the 1 and the 5
#   fold into one constant (the object's code). Fifteen more forms of that statement, each compiled at the unit's flags
#   (tools/round/try-tu.sh --symbols) and read in the object's NextItemPosition: the difference in an int or TPosition
#   local, the rectangle copied to a local, a lambda that returns the height as TPosition, static_cast<TPosition> of the
#   height or of the difference, `bottom + 1 - top`, `- 1 - (bottom - top)`, `-(height) + min`, `+ ~(bottom - top)`
#   written out, std::min<int>, the minimum in a named int, `limite -=` in a second statement: each gives `top + ~bottom`,
#   `top - bottom` with the constants joined, or the two loads ahead of GetHeight's call, none the target's
#   `~(bottom - top)` after it (an InstCombine fold of a one-use subtraction, a reading). AddItem's name came from its
#   callers' calls (step 8's `call by:11881,11884,11888` at 16b8f99f), each caller named on its own (11881 by its
#   vtable, 11884 and 11888 by their records), and from its own records' anchor since it matches. The callers+content
#   hand line on the four records only it loads (298, 320, 326, 339), needed while 11881's vote was the only one, went
#   once 11888 matched: with it out the scan run twice moved no row and the build verified, and with every line of the
#   name out 11881, 11888, 12893 and 12894 are unresolved (docs/reference/splat.md "Reviewing a match").
# - The constructor, CMenuValidation's constructor, GetInstructionTextRect (record 251:21) and SetInstructionText
#   (record 477:9), which binaryen inlines into AddInputMenuField (3675), defined in api/gui/cinteractiveformbuilder.cpp
#   (unit 120's fragment has why: with it in this file it scored 162 over 528 rows, CMenuValidation's constructor's
#   stores off the control block where the target makes them off the object; there it matches). Measured with 3675 in
#   this file: CMenuValidation's constructor inline in the class, 235 over 535; the items' rectangle from the parameter
#   rather than read back from m_posicao, 243 over 538 (the target loads the position once, as a 32-bit word, and shifts
#   it). INSTRUCAO_PADRAO_MENU, the default instruction string the constructor copies (.bss 1832432, which only 3675,
#   11662 and 14478 address): cinputmenufield.h has what the target shows of it, its copy the executable TU's (a
#   reading). Measured in a whole link with it an inline variable of cinputmenufield.h and
#   src/uenux2/wasm/vota_web/vota_web_wasm.cpp including that header (steps 7 to 9, on this file as landed): 11662
#   matches from that TU's -Oz copy, 14478 votes the object's name too (with 3675, then), and twelve rows of other
#   units match (2688, 2689, 3525, 3526, 5143, 5166, 5189, 5190, 8592, 9385, 9394, 9518; why not read), but that TU then
#   instantiates api::CFormStack<IScreenMT>'s statics too (api/gui/iform.h), and 8177, their target destructor (an -O3
#   copy, after the executable TU's .bss), leaves `match`. So the variable stays an inline variable of this file (a
#   choice), and its name comes from a callers+content hand line in splat/symbol_addrs.txt (14478 builds it from the
#   literal at 444366 and 11662 destroys it); without the line 3675 is unresolved self-voted (the removal check). 11662
#   waits for the header that brings the variable into the executable TU without CFormStack<IScreenMT>, and for that
#   TU's first table references: measured at 16b8f99f with 2770 and 1693 matched, the variable defined in that TU
#   alone for the measurement (at the top of its `namespace api`, above the gap whose #line gives line 280, so no record
#   moved), 11662 matches from its copy and takes table slot 1, as the target's does, and 8177 stays `match`, but
#   the TU's next first references then put its own static's destructor at slot 2 (10620's, renamed from `.4` to
#   `.8`), simulador::PushKey at slot 3 and std::string's constructor at slot 4, which the target holds at slot 3, so
#   988's addr pair falls (docs/reference/facts/splat.md S10 item 28) and 1227, 1524, 3363, 4760, 5152, 7833, 7850,
#   8046, 8327, 9405, 8887 and 8890 leave `match` (10175, 9726 and 998 go from differs to unresolved; steps 7 to 9 on
#   that link). The target's PushKey (9649) is at slot 105. Since the executable TU's votaInit (unit 170) is written,
#   the variable is in api/gui/instrucaomenu.h (unit 440's notes), which this file and that TU include, and not
#   cinputmenufield.h: 11662 matches from that TU's copy at slot 1, std::string's constructor is slot 3, and 2688,
#   2689, 3525, 3526, 5143, 5166, 5189, 5190, 9385, 9394 and 9518 match with it (8592 is api::CFormStack<api::IScreen>'s
#   s_forms's exit destructor, still out); the callers+content hand line on the variable's name went, carrying
#   nothing once 14478 votes it too (its removal moves no row, and the splat build verifies). The four of
#   AddItem's default argument's lambda (`__func`, vtable @1539468: 12277, 12279, 12283, 12285), std::any's copy
#   assignment (1763), std::__throw_bad_any_cast (3861) and std::bad_any_cast::what (8110, libc++'s any.o) match with
#   vota::CMenuVisualizarCandidatos::StartState (11881) in the link, which their target callers or holders are: the
#   lambda's members and 1763 come from comum/ctelasvota.cpp.o, whose TelaMenuVisualizacaoCandidatos uses the default
#   argument and the copy assignment, 3861 from cmenuvisualizarcandidatos.cpp.o (11881's std::any_cast).
#
# CMenuItem's members in the same file: GetTextoFormatado (fn 5492, a chosen name), UpdateRect (3657, record 49:21, its
# instance() line), Draw (record 74:21; binaryen inlines it into CInputMenuField::Draw, its one caller, whose body shows
# its second prologue) and SetSearchText (3655, record 142:19, the throw), with CInputMenuField::Draw (10897, slot 2)
# between the D0 and Rect (the u=1 band's order). 5492 builds the item's text from its format string (+96, else the
# menu's at +160): a static std::regex("%[ST]"), a std::sregex_token_iterator over the format with the submatches {-1,
# 0}, and std::for_each over the tokens with a lambda that appends the search text for "%S", the text for "%T" and the
# token otherwise; then it returns the result plus " ". The library instances it brings are target fns 1202 (the
# iterator's copy constructor), 3137 (its ==), 4307 (its constructor), 6970 (its ++) and 6939 (std::sregex_iterator's
# ++). UpdateRect measures that text with IScreen::GetFontMetrics (slot 3; the target stores nothing to the width and
# the height before the call, so they are not initialized) and stores SRect::Normalized of the position and the position
# plus the metrics (the height plus 1). SetSearchText returns when the text is the same, throws
# EUE_GUI_MENUITEM_BUSCA_REPETIDA (4929, eueguierror.h) when another item of the menu has it, assigns it, calls
# UpdateRect, gives the menu's SetLength (slot 12) the longest search text and refreshes the menu; the target reads
# m_menu again after UpdateRect and after SetLength, so the body names m_menu at each use. Chosen: the name
# GetTextoFormatado, the iterator type (std::sregex_token_iterator over the string, whose __wrap_iter<const char*> names
# the six instances; std::cregex_* over const char* gives the same bytes), the lambdas, std::find_if and
# std::max_element (their loops are inlined; a hand loop was not tried), CMenuItem::Draw's local corTexto (the target
# reads m_habilitado before the FillRect call), the lines of the members with no record (GetTextoFormatado's, 28 to
# 45), and the blank line the include of api/gui/cformbuilder.h (AddInputMenuField's) took: the one after
# `namespace api {` in cinputmenufield.cpp (no record moves). Measured, by `pnpm wasm score` in the whole link with the
# companions below and src/app/roots_regex.cpp:
# - 5492, 3655, 3657, 10897, 1202, 3137, 6970 and 6939 differ in call and data operands only (5492 34 over 660 rows,
#   3655 11 over 322, 3657 5 over 109, 10897 14 over 284). In the scan all but 5492 match, with two more instances
#   this file brings, 6897 (std::deque<std::__state<char>>::clear) and 6942 (std::ssub_match's compare).
# - 5492 is `unresolved self-voted`: the guard of its static (1839284) has no reader but 5492 in the target
#   (`/usr/bin/grep -rlE 'i32\.const 1839284($|[^0-9])' build/out/splat/pieces/asm`). The static's exit destructor,
#   10901 (17 B, `f6096(p0, 1839244, 1839276)`: a thunk into binaryen's merge 6096, whose other caller is 14464), reads
#   the regex object, not the guard; our object's destructor of the static inlines ~basic_regex instead. So 5492 waited
#   for another reader of the guard's name. Its callers 3657 and 10897 match on its `call` name. Since unit 97 wrote fn
#   6999, whose static std::regex's exit destructor (14464) merges with 10901 into 6096 as in the target, 10901 and 6096
#   match, and 5492 matches with the token iterator's copies of src/app/roots_cbasetype.cpp (the link's rows are in
#   src/units/97-uenux2-cvotacaostateaudio.mk).
# - 3655 with "]" as the message's last literal differed there: our "]" re-pointed to the tail of "appl [ %d ]" (target
#   319759). The target's data at 439956 hold "]!" (the bytes `]!\0`, right before the string at 439959), only 3655
#   loads it, and that literal is written.
# - 5492 with the iterators as prvalues in the call of std::for_each, before the stand-in for 6999: 994 over 1364 rows,
#   a 560-byte frame where the target's is 768, and 3 calls of the iterator's copy constructor where the target makes 5;
#   named iterators passed by value give the target's 5.
# - 10897 with `SPoint{m_rectInstrucao.left, m_rectInstrucao.top}` passed to DrawText: 20 over 288 rows, two 16-bit
#   copies where the target copies the corner as one 32-bit word. A copy of the rectangle into a local first gives the
#   target's copy, and so does a helper that returns the SPoint by value (the same object code, by the function's
#   disassembly in a compile with the unit's flags); a named SPoint local gives the two copies.
# - 4307 differs, 15 over 227 rows: the target stores the submatch vector's end right after operator new, ours later. A
#   compile of this file with -fno-strict-aliasing puts that store right after operator new too (the function's
#   disassembly in the two objects; the rest of the function was not compared), so its target copy reads as one from an
#   object without strict aliasing (a reading). It matches from src/app/roots_cbasetype.cpp, compiled without strict
#   aliasing; 6999, its other target caller, is written (unit 97).
# - std::regex's internals: with this file in the link and no tree root, its copies (uenux2's flags) took 56 rows that
#   ecourna's objects gave, and 8 of them left `match` (3135 and 6770 left the link; 3524, 4239, 5186, 5188, 13875 and
#   14268 differed). src/app/roots_regex.cpp, a tree root at ECOURNA_CXXFLAGS ahead of both trees, held those copies;
#   with it the 59 regex rows of splat/scan.tsv's matches (Boost's aside) scored operand-only. Measured since (unit 97's
#   fragment): the copies over const char* and the token iterator's are uenux2's without strict aliasing, which
#   src/app/roots_cbasetype.cpp holds for the token iterator and app/comum/dados/cqrcodeds.cpp's object (fragment 299,
#   built without it, ahead of this file's) gives for the parser; the std::string constructor's chain, which
#   roots_regex.cpp held, comes from ecourna's icompressor.cpp.o since its caller 5821 is in the link (unit 06's
#   fragment).
#
# CMenuItem::SetFormatString (record 156:9) and CInputMenuField::SetFormatString (record 468:9), each record the
# CPolySingleton<IScreen>::instance() of its member, are written at those lines and have no target function of their
# own: vota::CMenuFiltrarCandidatosPorPartido::StartState (11884, unit 104's) holds both, inlined by binaryen, each
# behind a 16-byte stack prologue of its own (docs/how-to-decompile.md step 3), CMenuItem's on the "Todos" item with the
# format `%S - %T` and the menu's with `%S` after it. Evidence, 11884's body: each returns when the new format equals
# the member's (the item's +96, the menu's +160; memcmp takes the argument's data first), assigns it, and has the screen
# (slot 6) fill a rectangle in colour 1: the item a copy of its rectangle (+56, one 64-bit load into the frame, which
# GetRect's by-value result gives; m_rect passed by reference gave its address, unit 104's fragment has the score), then
# UpdateRect (3657); the menu its Rect() (slot 8); then each invalidates the menu (IFormFieldBase's Invalidate,
# inlined). 11884 matches with them. SetSearchText's lines after its record (143 to 150) hold its tail with the length
# update on one line, so that SetFormatString's record lands on its body's fourth line: the layout is a choice, and the
# object's functions other than the two new ones compile as before (compared by function, relocated operands masked; the
# static initializers' local numbers moved, which renamed 7753's match line to its libc++ locale.o qualifier at step 9).
# Chosen: the parameters' names and the two members' lines around their records (152 to 160, the first three of them
# SetSearchText's tail's before its re-lay and the rest a blank run, and 464 to 471, in a blank run).
#
# No roots: the file that stood for 11884's calls of 3655, 3675 and 3861 went with 11884 in the link.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CINPUTMENUFIELD_SRCS := src/api/gui/cinputmenufield.cpp
UENUX2_SRCS += $(CINPUTMENUFIELD_SRCS)
