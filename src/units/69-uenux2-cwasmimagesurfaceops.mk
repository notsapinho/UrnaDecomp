# uenux2 simulador::CWasmScreen and simulador::CWasmImageSurfaceOps, the wasm build's api::IScreen and
# api::IImageSurfaceOps, in src/uenux2/mock/app/simulador/wasm/cwasmscreen.cpp (+ cwasmscreen.h, cwasmimagesurfaceops.h),
# with the api::IScreen interface's 39 slots (src/uenux2/src/api/gui/iscreen.h), the api::IImageSurfaceOps interface
# (src/uenux2/src/api/gui/iimagesurfaceops.h) and IImage's third slot, GetData (iimage.h).
# CWasmScreen (iscreen.h and cwasmscreen.h say what each body shows):
# - slots 2 to 12: GetFontMetrics of a font (9265) and of a text (9261, IScreen's slot 3, whose record names it), Clear
#   (9254), Clear of a rectangle (9243), FillRect (9232), DrawPixel (9223), DrawLine (9213), DrawRect (9205), DrawCircle
#   (9194), DrawRoundRect (9184), DrawGrayGradient (9175);
# - slots 15, 16, 19, 21, 23, 25, 26, 29 to 31, 33, 34: DrawTriangle (9165), DrawPolygon (9155), DrawText from a point
#   (9115), DrawText inside a clip (9090), DrawImagePlaceholder (9068), DrawImage into a rectangle (9049), DrawMovie (9038),
#   SetColors (9013), GetWidth (8959), GetHeight (8953), Clear of a screen (9004), GetImageSurfaceOps (8945);
# - slot 27, Refresh (9022), which logs and calls simulador::EmitEvent (fn 3533, unit 99's wasmjs.cpp), a call clang
#   would inline were the function in this TU. The string as an explicit std::string temporary gives the same function; a
#   named local does not;
# - slot 32, GetTextWidth (9009), and the file-static ParaUtf8 it calls (5098), which converts the text's Latin-1 to UTF-8
#   for js_measure_text_width and js_text; its second caller is slot 20 (9104).
# - slot 20, DrawText into a rectangle (9104), is written and differs: its log line's `substr(0, 40)` on a temporary is
#   C++23's `substr() &&` in the target, and its std::string appends stay calls, which the tree's -O3 and -std=c++23
#   give. At those flags 97 of 747 rows differ (`pnpm wasm score`; 224 over 794 at -std=c++20), the order of the screen
#   rectangle's selects.
# - slots 22 and 24, DrawImage (9079, 9058), DrawMovie's shape over ImageSize. Same functions: the data held by `const
#   std::vector<uint8_t>&` or `const auto`, `!largura || !altura` for the two tests. Not free: 9058 scales the natural
#   width before the height; the other order differs.
# - slots 17 and 18, FillPath and DrawPath (9146, 9125), match, and the scaling they share, a private member
#   EscalaCaminho (fn 5113, whose name is chosen; it reads m_escalaX and m_escalaY, and its push_back is target fn 2670,
#   which matches), is written and `differs`. The tree's -O3 inlines `tipos.push_back` as the target does (at cost 225,
#   docs/reference/facts/levels.md V2). 9146 and 9125 differed from the target in the call of 5113 alone (13 over 307
#   and 13 over 313 rows, all operand-only), and a `callers+content` hand line of splat/symbol_addrs.txt names 5113 for
#   them: both are named by vtable alone, so they cast no call votes. On copies of the symbol file and the match list
#   without that line and the two match lines, the scan (twice, beside a control that moves nothing) reads 9146 and
#   9125 `unresolved` and 5113 `no-candidate`, and both copies build to the target's sha256. At -O2 their two
#   push_backs stayed calls of one vector<int> body, a twin of vector<long>'s in roots_boost.o, which equals target fn
#   543 by bytes; at -O3 543 still matches, from roots_boost.o.
#   5113 itself differs (70 over 264 rows at the tree's flags): for MOVE_TO, LINE_TO and ARC the target reads every
#   value of the command before its first store and stores the type (and an arc's two angles) before the scaled
#   coordinates; ours reads its last product's pair at that product's store, and stores the type (and the angles)
#   after the products. The CLOSE case is the target's. The `SPathCommand` aggregate (cstepsprogressbar.h) stands in for a header whose constructors, if any,
#   are not known. Measured alone (try-tu --single, which scored the body written before as the whole link did, 86 over
#   273): the products written `m_escalaX * comando.x`, which reads x before the scale as the target does, 75 over 264;
#   with that, CLOSE built as a value-initialized SPathCommand whose type is then set (a zero over the whole temporary,
#   padding included, then the type, as the target has), 70 over 264, the written form. Further from the target: the
#   products the other way round (81, and 86 with CLOSE an aggregate, the body written before); the aggregates built
#   with the products in place, no locals (101, and 97 with the scale first); named SPathCommand locals built with
#   braces (101); one SPathCommand per command, default-initialized and assigned field by field (304), or per case,
#   assigned type last (116), or with the products in locals first (96).
# - slot 12 of CWasmImageSurfaceOps, ImageSize (3493): the member tests for no data and calls TamanhoImagem, a
#   file-static helper clang inlines, with the GIF, PNG and JPEG reading. Written in the member itself, every form tried
#   left one thing (11 over 256 rows, 5 of them operand-only): the target tests the size against 12, the guard of the
#   JPEG loop, before bytes[1] == 0xD8, and those forms after it (writing that test ahead lets LLVM thread the short
#   path past bytes[0] and drops the target's test of 4). Through the helper the test comes first and the function
#   matches; cwasmresource.cpp (unit 127) has the same helper, which simulador::CWasmResource's slot 4 (fn 8605) holds
#   with the same test order. Both target functions hold the code, so neither copy is a call; two file-static copies,
#   one per file, are chosen over one internal function in a shared header, which nothing shows. std::equal is measured:
#   std::memcmp, over a const or a plain array, folds the signature into the compare, where the target stores it to the
#   frame and loads it back. Each of these also brought the rows closer: one exit with both sizes in locals, altura
#   declared first, `i += 2` before the length is read, and largura assigned first.
# - pending, in 69-uenux2-cwasmimagesurfaceops-pending.cpp with what it waits for: Refresh of a rectangle (slot 28: 9018).
# - matched: the destructors in slots 0 and 1, CWasmScreen's implicit D2 (5071, one function with api::IScreen's D2,
#   which holds slot 0 of both vtables) and D0 (8963), over IScreen's inline destructor (api/gui/iscreen.h, defined in
#   api/gui/iform.h after CFormStack), and the function that destructor calls, api::CFormStack<api::IScreen>::Limpa
#   (5069), which this object emits: cwasmscreen.cpp includes iform.h. Limpa's body is evidence: it hides the form on
#   top of the stack and pops it until the stack is empty (the target stores the new end on each pass), unlocks the
#   stack's mutex and calls Notifica (2651); its name and its place in CFormStack are chosen. 5071 and 8963 are named by
#   vtable alone and cast no votes; the scan's content pass finds 5069, whose re-pointed bytes occur once (a
#   `callers+content` hand line, weighed as docs/reference/splat.md "Reviewing a match" says, carried nothing).
#   IScreenMT's destructor has the same shape over CFormStack<IScreenMT>'s Limpa (3461, unit 78's fragment).
# - the constructor, which fn 8302 (unit 188) calls, matches no function of its own. Its being out of line is evidence
#   (the data order, below); binaryen inlines it into 8302, its one caller, so no match checks it. It differs from
#   8302's in two known places: 8302 builds the log as std::string("CWasmScreen this=") and then
#   appends to_string's result, where the written `"CWasmScreen this=" + std::to_string(...)` compiles to an insert;
#   and 8302 stores 480 and 640 at +34 and +32 as two 16-bit stores, where ours is one 32-bit store.
# CWasmImageSurfaceOps:
# - ImageRect(width, height, point, anchor), slot 14 (target fn 9289), and the class's other slots of its own: Slot2 to
#   Slot7 (9365, 9362, 9356, 9348, 9339, 9333), CopyBytes (slot 8, 9328), Slot9 (9322), Slot10 (9317), FreeBytes (slot
#   11, 9307). iimagesurfaceops.h says what each body shows.
# - the base's inline defaults, emitted with the vtable: ImageSize(const IImage&), slot 13 (8998), and ImageRect from
#   bytes, an IImage and a shared IImage, slots 15 to 17 (8994, 8991, 8985).
# - std::__shared_ptr_emplace<std::vector<unsigned char>> (D2 8833, D0 8823, __on_zero_shared 5047), libc++'s code for
#   the make_shared of slots 2, 5 and 9.
# std::vector<double>'s range insert (fn 2662), which FillPath and DrawPath call, came from src/app/roots_uenux2.cpp: the
# target's copy has TBAA, this object's had none while its directory built with -fno-strict-aliasing (24 over 434 rows), and
# as the first definer on the link line this object would take it from RHVoice's speech_processor, and 2209 and 5255 with
# it. With the directory's strict aliasing (src/Makefile UENUX2_TBAA_DIRS) this object's copy is roots_uenux2.o's (pnpm wasm score
# on the two objects: 0 over 468 rows); the root is not measured again.
# The constructor, called from fn 8302 (unit 188), stores both vtables, so this unit has no roots.
#
# The file is a choice, and the TU is not: the class shares one object with simulador::CWasmScreen. No record names
# either class's file; ledger/tu-clusters.tsv's class-convention guess puts stretches 131, 206 and 956 in a
# cwasmimagesurfaceops.cpp and 130, 132 and 205 in a cwasmscreen.cpp. Three readings say one TU:
# - data order (docs/reference/facts/link-order.md L7 item 15): CWasmScreen's vtable @1528816, this class's vtable
#   @1528980, typeinfos 1529060 (this class), 1529072 (api::IImageSurfaceOps) and 1529080 (CWasmScreen). One object's
#   data lies together, so a separate object could not put this class's between CWasmScreen's vtable and typeinfo.
# - fns 9058 and 9079, CWasmScreen's members, call 3493 directly with `this` the frame's own local (9058: f3493(l5, l5,
#   l5 + 4)), not p0 + 44. LLVM's dead-argument pass replaces an unused argument with poison at the call sites of a
#   function whose body is the one the link keeps: a strong definition in the same module. A probe of that shape, in
#   the tree's flags, prints `ptr nonnull align 4 poison` in its IR and the frame's local in its object; the same caller
#   with the callee in another TU, or inline in the class, passes this + 4.
# - the uses-1 band: this class's strong members (9365 to 9307, then 9289) run before CWasmScreen's slots (9265 to
#   9004), and the inline defaults (8998 to 8985) after them, where clang defers inline functions
#   (docs/reference/facts/reading.md R8). The band has slot 14 before slot 13 for that reason.
# So these members are in cwasmscreen.cpp, the name those stretches give the object; the name itself is the guess's.
# cwasmimagesurfaceops.h is rule 4's chosen path (how-to step 3): nothing shows whether the class head has its own
# header or sits in CWasmScreen's. A separate cwasmimagesurfaceops.cpp gives the same bytes for this unit's functions;
# it would not for 9058 and 9079, whose `this` needs the callee in their TU.
#
# The data say the same of CWasmScreen's slot 20 and of the colour switch: the 37 colour strings that only 9104's fill
# indexes (entries 1 to 37, where 9104 has ruled out 0; no other function loads 1529444) lie at 1529448 (148 B), and the
# 38 that every drawing member indexes right after them, at 1529596 (152 B), as this object's two `.Lswitch.table`
# segments lie, 148 B then 152 B, both named after 9104's symbol. And the constructor: a strong one in this object gives the target's data order
# (CWasmScreen's vtable before this class's); one inline in the class and unused here does not. Where it sits among the
# strong members is chosen: the probes do not tell the places apart.
# CWasmScreen's slots 2 to 33 run 9265 to 9004 in the uses-1 band in slot order but for 30 and 31, so the file defines
# them in slot order; 8963, 8959, 8953 and 8945 follow every one of them, so slots 30, 31 and 34 are inline in the class
# and the deleting destructor implicit.
#
# CWasmScreen's names and types, chosen except where said: no record names a member but slot 3, so every other member
# name is chosen, from what the body does and from the strings it logs ("Clear(full)" in slot 4, "Refresh()" in slot
# 27, "Write '...'" in slot 20); slot 2 shares slot 3's name because both measure a font. The int and TPosition
# parameters are what the bodies' extensions show: a radius is an int narrowed to a coordinate before it is scaled (the
# extend16 in 9194 and 9184), a line width is scaled as an int (none in 9213), and the widths js_round_rect,
# js_gray_gradient and js_image get are narrowed to 16 bits. The IText, SFont, IImage and CMovie parameters are what
# the fields' Draws pass (iscreen.h). The constructor's two TPosition parameters, the two data members at +4 and +8, every member and local
# name, the file-static helpers (Cor, Ponto, Ancora, Normaliza, Retangulo, ParaUtf8, TipoCaminho, Le16) and their linkage are chosen.
# CMovie's two accessors (cmovie.h) are chosen; that the frame is read with at() is the target's (`call 234`, the
# vector's out_of_range).
# Forms measured for CWasmScreen, by the object's disassembly against this source's (call targets masked):
# - the same object: Ancora declared inline; `if (pontos.size() <= 1)` for `< 2` in DrawPolygon; Normaliza filling an
#   SRect member by member; the colour switch written as a `static const char* const` array of 38 strings behind the
#   same `> 37` test gives the same code with the data offsets moved, but one table, not the target's two.
# - not free: DrawRect's corners as `api::SPoint{x, y}` aggregates or as two named points assigned member by member
#   (DrawRect differs); DrawLine's width scaled through the TPosition helper (DrawLine differs); DrawMovie computing the
#   corners in its body instead of through Retangulo's TPosition parameters, or scaling the position before the size
#   (DrawMovie differs). In the whole link (splat-remap against the plain link): the anchor switch written in DrawMovie's
#   body, on int or TPosition locals, with `-= w / 2` or `+= w / -2`, re-points with `differs` (the operands of its adds
#   swap), and so do js_round_rect and js_gray_gradient declared with int widths (9184 and 9175: a shift pair for the
#   target's extend16). In a lone link, DrawPolygon's loop before the size test, or over `i + 1 < size()`, differs.
#
# Names and types, all chosen (no record, symbol or string names a member, parameter or alias): every member of
# api::IImageSurfaceOps, IImage::GetData, the IImageSurfaceSource class of slots 3, 6 and 10's parameter, the
# SharedBytes alias, the unused parameters' `int`, and the uint8_t* of slots 3, 4, 6, 7, 9 and 10, whose bodies show
# one i32 (only slots 8 and 11 show a pointer, the `new` and the free). The class names are RTTI's. The members' const
# is chosen too: no body reads this, and without const every body compiles the same.
#
# IImageSurfaceSource is a class this unit invents. What the target shows: 9362, 9339 and 9317 call [vtable+12] on the
# object itself with it as `this`, type (i32)->(i32), so the parameter is a polymorphic object, and its slot 2 and
# destructors are not shown at all. Nothing calls slots 2 to 11, so no caller gives the argument's class, and no RTTI
# class fits by role, which is a reading, not a proof. Its destructor pair is a choice: three plain slots and no
# destructor give the same object.
#
# Forms measured, by the object's disassembly against this source's (call targets masked), or by the whole link where
# it says so:
# - ImageRect: width and height as int give the same object. Cases 4 and 8 give the same object with their two
#   statements either way round, and a `default:` label or none too, and so does a named SRect returned. Cases 5 and 7
#   are not free: x first, then y, gives the target's y, then x (docs/reference/facts/codegen.md C1), and the other
#   order differs. Hence x first in every case, a choice for 4 and 8. Width and height as int, or x and y as int with
#   TPosition parameters, give the same code; both int give the target's sums with their operands swapped, `(w / -2) +
#   x` for its `x + (w / -2)`, the shape of the int arithmetic in 9058. So one side at least is TPosition, and both is
#   chosen. The two sums in locals are a choice as well: written inside the aggregate, they give the same object.
#   std::min(x, direita) and std::max(x, direita) in that operand order are the target's: swapped, one or both, the
#   object differs, and with both swapped the whole link re-points with `differs` (at +0xb4).
# - the SRect aggregate stands in for a header that is not the original's: fns 1916 and 11067 end in the same
#   four-select store run, so the real SRect probably has a normalising constructor. One that takes left, top, right
#   and bottom and applies std::min and std::max in its initializers gives this object, cmp-identical, with `return
#   SRect(x, y, x + largura, y + altura);`, and so the operand order above would live there. primitives.h is not this
#   unit's, and every landed `SRect{...}` would go through that constructor, so it stays an aggregate.
# - CopyBytes: `if (!dados.empty())`, `if (dados.size() != 0)` around the std::copy, std::copy_n, std::copy over data()
#   pointers and a guarded std::memcpy give the same object; an unguarded std::memcpy does not.
# - slots 13 and 15 to 17 defined inline in CWasmImageSurfaceOps instead of the base give the same bodies.
# - the parameter types: `const X*` for every reference parameter, void* for the uint8_t* of slots 3, 4, 6, 7, 9 and 10,
#   and const SharedBytes& read with get() in slots 4 and 7 give the same code under other symbols.
# - the class's destructor defined in the class, `virtual ~CWasmImageSurfaceOps() = default;`, gives the same object.
# Paths relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on the source and every uenux2
# header.
CWASMIMAGESURFACEOPS_SRCS := mock/app/simulador/wasm/cwasmscreen.cpp
UENUX2_SRCS += $(CWASMIMAGESURFACEOPS_SRCS)
# the pending members (69-uenux2-cwasmimagesurfaceops-pending.cpp) give the vtables trapping bodies, compiled with the
# unit's flags; the header set is the generic rule's
$(ROOT)/$(APP)/69-uenux2-cwasmimagesurfaceops-pending.o: $(ROOT)/src/units/69-uenux2-cwasmimagesurfaceops-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/69-uenux2-cwasmimagesurfaceops.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/69-uenux2-cwasmimagesurfaceops-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/69-uenux2-cwasmimagesurfaceops-pending.o
