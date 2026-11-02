# uenux2 api::CStepsProgressBar::~CStepsProgressBar: the D2 (target fn 3665, vtable @1581868 slot 0) and the D0 (fn
# 10973, slot 1), with GetTypeName (10969, slot 7) and Rect (10968, slot 8), in src/uenux2/src/api/gui/cstepsprogressbar.cpp,
# the file the constructor's std::source_location record names (cstepsprogressbar.cpp:428:15
# api::CStepsProgressBar::CStepsProgressBar(const uedword, const std::vector<std::string> &, const SRect &, const TColor
# x7)). The constructor is not reconstructed: it is inlined into fn 13550 (slot 2 of vota::CPreShowProgressBar), which
# keeps its stub, so line 428 stays free for it. No record falls in the destructor, GetTypeName or Rect, so their lines
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
# SDisposicao and SSegmento's names, the lines, and the header's additions for them (SPathCommand's two constructors,
# which take unit 69's 5113, EscalaCaminho, from 70 over 264 rows to 38 over 256; Recalcula, m_font mutable). Measured by `pnpm wasm score` in the whole link:
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
# - CabeEmUmaLinha (10972) 52 over 280 rows. Its one difference is how the available width is grouped: the target
#   computes `1 - 2 * margem` once, from the 2 * margem the height test uses, and the width as `(1 - 2m + right) - (left
#   + seta + recuo)`, where ours is `(right + 1) - (left + recuo + 2m)`. Not the target's grouping, by the optimized IR
#   (`-S -emit-llvm`): the width through Width() or right - left + 1, as int or TPosition, its terms in ten orders or
#   grouped in parentheses, the two side terms in one variable, margem and recuo before the loop, the area read first in
#   the loop. In the whole link: the two side terms as if statements 81 over 294; a margin taken off each side as two
#   TPosition edges 44 over 283; `right - left + 1 - margem - seta - margem - recuo` builds 1 - 2m first, but from a
#   second 2 * margem as a multiply by 65534 or-ed with 1, 64 over 288. The remainder is not explained.
# - CabeProporcional (10971) 665 over 1295 rows: the target builds its areas by the same loop as Divide (the same two
#   masks), but building them in place here takes the function to 726 over 1260, so it keeps SRect::Normalized, and
#   the rest of the function differs. Draw 1162 over 5684 rows. Their remainder is not explained. They stay written:
#   Draw is a vtable slot, 5505 and 5507 match through it, and Draw's operands for the table slots of 10972 and 10971
#   re-point only once those match (its scan row is `unresolved` at +0x2c6, 10972's slot).
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CSTEPSPROGRESSBAR_SRCS := src/api/gui/cstepsprogressbar.cpp
UENUX2_SRCS += $(CSTEPSPROGRESSBAR_SRCS)
# the destructor's caller other than the deleting destructor (fn 13550) is not reconstructed yet:
# 41-uenux2-cstepsprogressbar-roots.cpp gives it a second direct caller and takes its address
$(ROOT)/$(APP)/41-uenux2-cstepsprogressbar-roots.o: $(ROOT)/src/units/41-uenux2-cstepsprogressbar-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/41-uenux2-cstepsprogressbar.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/41-uenux2-cstepsprogressbar-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/41-uenux2-cstepsprogressbar-roots.o
