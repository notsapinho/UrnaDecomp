# uenux2 api::CStepsProgressBar::~CStepsProgressBar: the D2 (target fn 3665, vtable @1581868 slot 0) and the D0 (fn
# 10973, slot 1), with GetTypeName (10969, slot 7) and Rect (10968, slot 8), in src/uenux2/src/api/gui/cstepsprogressbar.cpp,
# the file the constructor's std::source_location record names (cstepsprogressbar.cpp:428:15
# api::CStepsProgressBar::CStepsProgressBar(const uedword, const std::vector<std::string> &, const SRect &, const TColor
# x7)). The constructor is written there, its throw on the record's line (code 5014,
# EUE_GUI_STEPSPROGRESSBAR_SEM_SEGMENTOS in api/gui/eueguierror.h, its name chosen), and has no target function of its
# own: binaryen inlined it into its one caller, fn 13550 (slot 2 of vota::CPreShowProgressBar, fragment 391's,
# matched), behind a second prologue (the caller reads the C1's returned `this`, codegen.md C6). Read from
# 13550: the base value-initialized (its data at +4 to +24 cleared before the vptr store, codegen.md C9:
# `: IFormField<IScreen>()`), the vector copied, the rect and the seven colours stored, the throw when the given steps
# are empty, then the current step clamped to their number, stored and the form refreshed when it changed: SetPassoAtual
# (its name and its being public chosen), with `std::min<uedword>(m_passos.size(), passo)`, whose operand order is the
# target's select's (the other order swaps it: 13550 303 over 1033 rows against 297 over 1028, fragment 391's). The
# setter written in the constructor's body, or Invalidate's statements in its place, give the constructor the same code
# (the object's disassembly compared). No record falls in the destructor, GetTypeName or Rect, so their lines
# (after the constructor's) are a choice; their order (destructor, then GetTypeName, then Rect) follows the four
# members that share a use band in the target, where the D0 comes first and Rect last (the solver's ordinals in
# ledger/ordinals.tsv: 10973 4279, Move 10970 4281, 10969 4282, 10968 4283). The destructor is user-declared and
# defined out of line: the D0 10973 is `f3665(p0); f136(p0)`, the call to the D2 that clang gives only for an
# out-of-line destructor (one defined in the class would have the D2's body inlined into the D0). Declared first of
# the class's virtual members, it is the key function, so cstepsprogressbar.o emits the vtable, the D2 and the D0.
# The class header (api/gui/cstepsprogressbar.h, the file chosen) has the layout the inlined constructor stores and
# Draw (fn 5504) and the D2 read: IFormFieldBase<IScreen> (+0 .. +24), the current step +24, the steps' texts
# (std::vector<std::string>) +28, the SRect +40 (what Rect returns), seven TColors +48 .. +72, a flag +76, an SFont
# +80 and the segments Draw builds +88 (a std::vector of 28-byte elements: a std::vector of 56-byte path commands, an
# SPoint, a std::string). The D2 destroys +88, then +28, then the IFormFieldBase<IScreen> part (its vptr store and
# m_nome). The member, parameter and type names are not evidenced. Move (10970) is here, over SRect::Move, with the
# segments' clear.
#
# Draw (5504, slot 2) is written with what it reaches, and only part of it matches. Its callees in this file are 5505,
# 5506 and 5507 (`pnpm wasm fn ../target/vota_web_wasm.wasm 5504 --ledger ../ledger`), and it passes table slots 3442 and
# 3443 to 5507 (its i32.const at +0x2c8 and +0x385), which hold fns 10972 and 10971 (`wasm-objdump -x -j Elem
# target/vota_web_wasm.wasm`). Read from their bodies: 5507 tries the font sizes from the largest down to 10 with a layout
# strategy passed as a function pointer, 10972 and 10971 are the two strategies (the steps in equal parts on one line;
# widths in proportion to the texts), and 5506 divides the bar into equal parts for 10972 and for Draw's fallback. They
# are in cstepsprogressbar.cpp before line 428, in an anonymous namespace (Tenta, CabeEmUmaLinha, CabeProporcional,
# Divide, and Escolhe, CriaContorno and Fecha, which have no target function: Draw inlines them), with the private
# Recalcula, which Draw calls and inlines. Chosen, and measured against no matching Draw: every name, the structs
# SDisposicao and SSegmento's names, the lines, and the header's additions for them (SPathCommand's two constructors:
# with them unit 69's 5113, EscalaCaminho, went from 70 over 264 rows to 38 over 256 with its products in locals, and
# it matches with each command built in the 7-argument constructor's braces, so a change of the constructors is
# measured on 5113; Recalcula, m_font mutable). Measured by `pnpm wasm score` in the whole link:
# - 5507 (Tenta) and 5505 (std::vector<SSegmento>::__swap_out_circular_buffer, which Recalcula's reserve and push_back
#   bring) differ in call and data operands only, and match.
# - Divide (5506) matches, through three forms, each measured on the function's disassembly in compiles with the
#   unit's flags and then in the whole link:
#   - its area loop is a `while`. With a `for` (an int or size_t counter) the cases are laid out 1, the rest, then 0:
#     the MIR (`-mllvm -print-after-all`) shows LLVM's branch folder moving case 0's block, `return {}`, to the end,
#     next to the return block, which the loop's last block does not fall through to (a reading of why). The forms of
#     the two special cases tried with it (two ifs, an else if, a switch with or without a default, the returns as
#     std::vector<SRect>()) all keep that order, as the whole rest as the switch's default did before; the two tests the
#     other way round give 0, the rest, then 1, and one vector returned from every path the rest, 1, then 0. The
#     `while` gives the target's 0, 1, then the rest; a `do`/`while` gives the same br_table.
#   - `base` is read before `topo`: the target loads the top (+2), then the bottom (+6), after the length check, and the
#     other order of the two reads gives the other order of the loads.
#   - each area is built in place, `areas.emplace_back(x, topo, x + l - 1, base)`, through SRect's normalizing
#     constructor (primitives.h): the target narrows the corner x + l - 1 to TPosition in emplace_back's fast and slow
#     paths both, after a zero extension of x and of l (two `i32.and 65535`), and of the forms tried only that one gives
#     them. Building the area with SRect::Normalized stores it as one 64-bit word; std::min and std::max in
#     emplace_back's arguments narrow the corner once (no mask), and so do x and l as int or ueword with them (one
#     mask or none).
# - CabeEmUmaLinha (10972) 23 over 274 rows (same 251, replaced 12 [9 operand-only], inserted 6, deleted 5), with the
#   two side terms added into one TPosition, `lados`: in the target's loop the indent is added to seta and 2 * margem
#   kept apart (`seta + (i != n - 1 ? recuo : 0)`), where the terms subtracted one by one gave `seta + 2 * margem`
#   hoisted out of the loop and 52 over 280. Its one difference left is where `+ 1` and `- 2 * margem` go: the target
#   computes `1 - 2 * margem` once, after the first height test, from the 2 * margem that test uses, and the width as
#   `(1 - 2m + right) - (left + lados)`; ours is `right - (2m + left + lados) + 1`. -mllvm -print-after-all on the TU's
#   compile line shows ReassociatePass building `(1 - 2m) + right` and LICM hoisting `1 - 2m`, then InstCombine folding
#   it back into `right + 1`; and the backend alone (the TU's line with -Xclang -disable-llvm-passes, on the IR edited
#   by hand) gives a sum that adds the 1 last for each shape tried, `(1 - 2m) + right` written in the IR included. So, a
#   reading, the target's `1 - 2m` is a value InstCombine left as it was, as it leaves one with a second use. No source
#   form read on the optimized IR keeps it as the target does: `1 - 2 * margem` written as an int local or in place
#   folds into the sum, and as a TPosition local it stays, but zero-extended and computed before the loop (64 over 289
#   in the whole link); and margem, alturaUtil or recuo before the loop, 2 * margem as a TPosition of its own, the area
#   by value or read before the height test, the width as right - left + 1 or with a margin taken off each edge, or the
#   margins moved to the text's side of the comparison keep no `1 - 2m`. In the whole link, before `lados`: the two side
#   terms as if statements 81 over 294; a margin taken off each side as two TPosition edges 44 over 283; `right - left +
#   1 - margem - seta - margem - recuo` builds 1 - 2m first, but from a second 2 * margem as a multiply by 65534 or-ed
#   with 1, 64 over 288. The remainder is not explained.
# - CabeProporcional (10971) 558 over 1261 rows (same 703, replaced 216 [155 operand-only], inserted 131, deleted 211),
#   with two forms that give its frame and its order (that the original was written so is a reading): the text's
#   width and height declared at the top and set to 0 in the loop, as CabeEmUmaLinha's are (the target's frame holds
#   them at +14 and +12 and the font at +0, as CabeEmUmaLinha's does; declared in the loop they were at +6 and +4 and
#   the font at +8, 626 over 1269); and the margin, the height test and the indent computed in the loop after
#   GetFontMetrics (the target computes them after the first call), which before the loop read 665 over 1295. The target
#   builds its areas by the same loop as Divide (the same two masks), but building them in place here took the function
#   to 726 over 1260, so it keeps SRect::Normalized, and the rest of the function differs. The remainder is not
#   explained.
# - Draw (5504) 259 over 5481 rows (same 5222, replaced 159 [153 operand-only], inserted 42, deleted 58), from 1196 over
#   5696, with three forms, measured one on another at 99aac87a (this file and the headers it includes from api/gui/ are
#   the same since) and together again on this link: Recalcula's text point built from two TPosition locals in the
#   segment's braces, SPoint(x, y), which stores y at +82 and x at +80 as the target does (1162 over 5684; the named
#   SPoint copied into the braces stored one i32 of x | y << 16, and `{x, y}` gives the same link as SPoint(x, y));
#   CriaContorno's 28 path commands pushed as temporaries, push_back(SPathCommand(...)), which store all seven fields
#   from +48 down in the fast path as the target does, where emplace_back stored +24 ... +0 and then +32, +40, +48 in
#   both paths (318 over 5536); and one DrawText call after the two arms of `i < m_passoAtual`, its colour chosen as a
#   `const TColor*` in each arm, where the target loads it from a selected member address (one call per arm read 318).
#   What is left, not explained (a masked diff of pnpm wasm fn's folded readouts): the font size's floor of 10, a max on
#   the sign-extended size in the target and `altura < 17 ? 10 : ...` in ours; m_font's store, one i64.store of size | 1
#   << 32 at +80 in the target, an i32.store at +84 and an i32.store16 at +80 in ours; the place of margem's max(1, size
#   / 4) and of one f64.add; and the text's emptiness, which the target tests in each arm before the merge and ours
#   after it. They stay written: Draw is a vtable slot, 5505 and 5507 match through it, and Draw's operands for the
#   table slots of 10972 and 10971 re-point only once those match (its scan row is `unresolved` at +0x2c6, 10972's
#   slot). Its name holds by a `vtable-slot` hand line since 13550, its one direct caller, matched (fragment 391 says
#   why); the line goes once Draw matches.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CSTEPSPROGRESSBAR_SRCS := src/api/gui/cstepsprogressbar.cpp
UENUX2_SRCS += $(CSTEPSPROGRESSBAR_SRCS)
# No roots: the destructor's target callers, the D0 10973 and fn 13550 (fragment 391's), are both in the link;
# the roots file's stand-in for 13550 (DestroiBarrasPassos) went with it.
