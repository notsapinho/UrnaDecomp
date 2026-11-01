# uenux2 api::CMenuValidation::isValidChar (target fn 10899, slot 3 of the vtable @1583300) in
# src/uenux2/src/api/gui/cinputmenufield.cpp, the file the class's records name, with the class header
# api/gui/cinputmenufield.h (its path chosen), which reads the text at +24 of IInputField<IScreen> through
# api/gui/cinputfield.h and iinputfield.h, unit 92's. The body inlines IInputValidation::isValidChar (the memchr) and then builds the text plus the character:
# `text + std::string(1, c)`, libc++'s operator+(const string&, string&&), whose insert(0, ...) is fn 499 and whose
# move the words at +16 show. isValid (10900) is the key function, so cinputmenufield.cpp emits the vtable and the implicit
# deleting destructor (one body with the other validations', 2980); slot 0 is the base's destructor. It holds
# matchesExactly and matchesPartially, the records' at 198:5 and 210:5: the first inlined by clang, in its frame, the second
# by binaryen, with its second stack prologue. Each searches with std::find_if and tests the iterator: the target tests
# `it != end` after the loop. std::any_of scored 63 over 326 rows, and a for loop that returns differs in 19 lines; an
# if on `it == end` around the beep gives the same object code. The prefix test is rfind(text, 0) == 0: its min of the two
# sizes and its reverse search are in the body, and starts_with and compare differ in 184 and 183 lines. What the two helpers read
# of the menu is CMenuItem's +65 and +68 and the list at +140, cinputmenufield.h has the head; its names are chosen.
# Forms that give 10899's object code, by the function's disassembly in a compile with the unit's flags: an early `return
# false` before the call, an `if` around it, and `m_validChars.find(c) == std::string::npos` for the base's member. So
# those are choices. Forms that do not: the text in a named local (another frame), `text + c`, `text + digito` with a named
# string, `texto += c`. The roots' make_shared also brings the control block's D0 and D2 (10891, 10892), which match from
# there until fn 3675 lands.
#
# api::CInputMenuField (vtable @1583356, cinputmenufield.h has its layout and slots) in the same file: the destructor (D2
# 5491, D0 10898: out of line, the D0 calls the D2 and frees this, so it is the key function and the file emits the
# vtable), Rect (10896), Read (10894, record 419:21, the beep), GetTypeName (10893), and the private SelecionaItem (5489,
# Read calls it twice), LimpaSelecao (clang inlines it at its four sites) and CMenuItem::Pisca (inlined by binaryen into
# Read, its one caller: the blink of the chosen item, two toggles with a 100 ms sleep each), with
# std::__destroy_at<CMenuItem> (5490), CMenuItem's implicit destructor inlined into libc++'s helper, which the list's
# clear in the destructor calls. Move (10895, record 278:21, the `IScreen& tela = CPolySingleton<IScreen>::instance()`
# line) is pending: 84-uenux2-cinputmenufield-pending.cpp says what it waits for.
# The private Reposiciona (2770; callers 1693, 3675, 10895) is not written: below.
# The u=1 band of ledger/ordinals.tsv runs 10900, 10899, 10898, 10897, 10896, 10895, 10894, 10893 and the u=2 band 5491,
# 5490, 5489: the definitions follow that order (D0 and Rect before Move's record line, Read's after it, GetTypeName last),
# and names.tsv's ld_index agrees in the plain link. Names chosen: SelecionaItem, Reposiciona, LimpaSelecao, Desloca,
# Pisca, every data member and local; the loop counter of Pisca and the friendship of the two classes are choices.
# Measured, by the function's disassembly in a compile with the unit's flags and by `pnpm wasm score` in the plain link:
# - Move, while it was written (84-uenux2-cinputmenufield-pending.cpp has its source, a trap now since 2770 is not
#   written): the new x and y in locals before the loop (`const TPosition x = posicao.x; m_posicao.x = x; ...`) give the
#   target's loop, which adds them to the item's position read as one 32-bit word with 4-byte alignment; reading
#   m_posicao.x in the loop reloads it after each SRect::Move call (18 lines differ), and the item's position read through a
#   getter that returns a reference keeps a 2-byte alignment. A copy `const SPoint origem = m_posicao` before the loop gives
#   the same object code as the locals. The arithmetic is CMenuItem::Desloca, which reads its own m_posicao. The screen's
#   call is slot 5, IScreen::Clear(const SRect&, TColor), as in the target. Score 4 over 117 rows, all operand-only, and
#   Move was `unresolved self-voted`: its call of Reposiciona (2770) had a name only from Move's own vote, so Move waits
#   for 2770's body or for 1693 or 3675, 2770's other callers.
# - Read: the CONFIRMA case with the beep in an `else` after the blink places the beep after SEM_TECLA's SelecionaItem;
#   the beep first in the `else` with its `break`, and Clear and the return after the `if`, gives the target's order,
#   with the beep at column 21, and the same object code as the beep after the `if` with no `else` (column 17). The two
#   toggles written in Read leave a `br_if` around the last sleep where the target has an `if` and a branch out: the blink
#   out of line in CMenuItem::Pisca, which binaryen inlines, gives the target's shape (17 over 358 rows, one deleted,
#   against 14 over 358, all operand-only). Written in Read, a loop of two and the two toggles written out gave the same
#   object code; Pisca's loop of two is a choice measured only through Read's match.
# - The destructor (5491) matches since src/api/ builds with strict aliasing: libc++'s list clear,
#   `__f->__prev_->__next_ = __l->__next_; __l->__next_->__prev_ = __f->__prev_;`, reloads `__f->__prev_` after the first
#   store with -fno-strict-aliasing, and the target keeps it in a local, which strict aliasing gives (the function's
#   disassembly in two compiles of the file, with the flag and without it: only the destructor and libc++'s std::format
#   helpers differ). With the flag it scored 13 over 76 rows (2 inserted, 2 deleted); src/Makefile UENUX2_TBAA_DIRS takes
#   it off this directory (docs/reference/facts/app-flags.md F6).
# - Reposiciona (2770) is not written: it is no slot, its remainder (the frame) is not explained, and no matched caller
#   needs it (docs/how-to-decompile.md step 5). Written, it differed, 25 over 107 rows: the target puts the rectangle
#   Adjust returns at +4 of its frame and the point built from it at +12, stores that point's y before its x, and writes
#   the mask's position with the 7 added as one 32-bit store of both coordinates. As written, the rectangle was at +8
#   and the point at +4, in order; the rectangle in an inner scope with its two edges in locals reverses the stores and
#   lets the mask's position share the rectangle's slot, but keeps the rectangle above the point; `posicao.x += 7` and
#   an assignment of the whole point both give a 16-bit store of x. The body as written:
#       const SRect itens = m_rectItens.Adjust(0, 0, 0, 5);
#       m_rectInstrucao.Move(SPoint{itens.left, itens.bottom});
#       SPoint posicao{m_rectInstrucao.right, static_cast<TPosition>(m_rectInstrucao.top - 1)};
#       if (!m_instrucao.empty()) {
#           posicao.x += 7;
#       }
#       m_mask.Move(posicao);
#       Invalidate();
#
# CMenuItem's members in the same file: GetTextoFormatado (fn 5492, a chosen name), UpdateRect (3657, record 49:21, its
# instance() line), Draw (record 74:21; binaryen inlines it into CInputMenuField::Draw, its one caller, whose body shows
# its second prologue) and SetSearchText (3655, record 142:19, the throw), with CInputMenuField::Draw (10897, slot 2)
# between the D0 and Rect (the u=1 band's order). 5492 builds the item's text from its format string (+96, else the
# menu's at +160): a static std::regex("%[ST]"), a std::sregex_token_iterator over the format with the submatches {-1, 0},
# and std::for_each over the tokens with a lambda that appends the search text for "%S", the text for "%T" and the token
# otherwise; then it returns the result plus " ". The library instances it brings are target fns 1202 (the iterator's
# copy constructor), 3137 (its ==), 4307 (its constructor), 6970 (its ++) and 6939 (std::sregex_iterator's ++).
# UpdateRect measures that text with IScreen::GetFontMetrics (slot 3; the target stores nothing to the width and the
# height before the call, so they are not initialized) and stores SRect::Normalized of the position and the position
# plus the metrics (the height plus 1). SetSearchText returns when the text is the same, throws
# EUE_GUI_MENUITEM_BUSCA_REPETIDA (4929, eueguierror.h) when another item of the menu has it, assigns it, calls
# UpdateRect, gives the menu's SetLength (slot 12) the longest search text and refreshes the menu; the target reads
# m_menu again after UpdateRect and after SetLength, so the body names m_menu at each use. Chosen: the name
# GetTextoFormatado, the iterator type (std::sregex_token_iterator over the string, whose __wrap_iter<const char*>
# names the six instances; std::cregex_* over const char* gives the same bytes), the lambdas, std::find_if and std::max_element (their loops are inlined; a hand loop was not
# tried), CMenuItem::Draw's local corTexto (the target reads m_habilitado before the FillRect call), and the lines of
# the members with no record (GetTextoFormatado's, 28 to 45).
# Measured, by `pnpm wasm score` in the whole link with the companions below and src/app/roots_regex.cpp:
# - 5492, 3655, 3657, 10897, 1202, 3137, 6970 and 6939 differ in call and data operands only (5492 34 over 660 rows,
#   3655 11 over 322, 3657 5 over 109, 10897 14 over 284). In the scan all but 5492 match, with two more instances
#   this file brings, 6897 (std::deque<std::__state<char>>::clear) and 6942 (std::ssub_match's compare).
# - 5492 is `unresolved self-voted`: the guard of its static (1839284) has no reader but 5492 in the target
#   (`/usr/bin/grep -rlE 'i32\.const 1839284($|[^0-9])' build/out/splat/pieces/asm`). The static's exit destructor,
#   10901 (17 B, `f6096(p0, 1839244, 1839276)`: a thunk into binaryen's merge 6096, whose other caller is 14464), reads
#   the regex object, not the guard; our object's destructor of the static inlines ~basic_regex instead. So 5492 waits
#   for another reader of the guard's name. Its callers 3657 and 10897 match on its `call` name.
# - 3655 with "]" as the message's last literal differed there: our "]" re-pointed to the tail of "appl [ %d ]"
#   (target 319759). The target's data at 439956 hold "]!" (the bytes `]!\0`, right before the string at 439959), only 3655
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
#   object without strict aliasing (a reading); 6999, its other target caller, is not written.
# - std::regex's internals: with this file in the link and no tree root, its copies (uenux2's flags) took 56 rows that
#   ecourna's objects gave, and 8 of them left `match` (3135 and 6770 left the link; 3524, 4239, 5186, 5188, 13875 and
#   14268 differed). src/app/roots_regex.cpp, a tree root at ECOURNA_CXXFLAGS ahead of both trees, holds those copies;
#   with it the 59 regex rows of splat/scan.tsv's matches (Boost's aside) score operand-only.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CINPUTMENUFIELD_SRCS := src/api/gui/cinputmenufield.cpp
UENUX2_SRCS += $(CINPUTMENUFIELD_SRCS)
# The companions read cinputmenufield.h, which includes headers of api/gui, api/hwil, api/util and api/pattern and
# ecourna's: the set the generic rule uses. $(UENUX2_HDRS) is not set yet when src/Makefile reads the fragments
CINPUTMENUFIELD_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
# Move is not reconstructed: 84-uenux2-cinputmenufield-pending.cpp gives the vtable a trapping body, with the unit's
# flags
$(ROOT)/$(APP)/84-uenux2-cinputmenufield-pending.o: $(ROOT)/src/units/84-uenux2-cinputmenufield-pending.cpp $(ROOT)/src/units/84-uenux2-cinputmenufield.mk $(ROOT)/src/Makefile $(CINPUTMENUFIELD_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/84-uenux2-cinputmenufield-pending.cpp -o $(R)
# fn 3675, which builds both objects in the target, is not reconstructed: the roots file does its make_shared of the
# validation, takes CInputMenuField's vtable and holds the stand-ins for fns 1693, 11884 and 11888, and 6999 and 6958
$(ROOT)/$(APP)/84-uenux2-cinputmenufield-roots.o: $(ROOT)/src/units/84-uenux2-cinputmenufield-roots.cpp $(ROOT)/src/units/84-uenux2-cinputmenufield.mk $(ROOT)/src/Makefile $(CINPUTMENUFIELD_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/84-uenux2-cinputmenufield-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/84-uenux2-cinputmenufield-pending.o $(APP)/84-uenux2-cinputmenufield-roots.o
