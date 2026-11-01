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
# - Draw 1162 over 5684 rows, CabeProporcional 665 over 1295, CabeEmUmaLinha 52 over 280, Divide 48 over 446. Their
#   remainder is not explained. They stay written: Draw is a vtable slot, and 5505 and 5507 match through it.
# - Divide: the target lays out its cases as 0, 1, then the rest. `if (partes == 0) ... if (partes == 1) ...`, an else
#   if, a switch with or without a default, the whole rest as the switch's default, and the returns written as
#   std::vector<SRect>() all give case 1, the rest, then case 0; the two tests the other way round give case 0, the rest,
#   then case 1 (by the function's disassembly in compiles with the unit's flags, whose order the link kept for the
#   form written). Building each area with SRect::Normalized gives the target's order but stores the area as one 64-bit
#   word where the target stores four 16-bit fields.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CSTEPSPROGRESSBAR_SRCS := src/api/gui/cstepsprogressbar.cpp
UENUX2_SRCS += $(CSTEPSPROGRESSBAR_SRCS)
# the destructor's caller other than the deleting destructor (fn 13550) is not reconstructed yet:
# 41-uenux2-cstepsprogressbar-roots.cpp gives it a second direct caller and takes its address
$(ROOT)/$(APP)/41-uenux2-cstepsprogressbar-roots.o: $(ROOT)/src/units/41-uenux2-cstepsprogressbar-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/41-uenux2-cstepsprogressbar.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/41-uenux2-cstepsprogressbar-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/41-uenux2-cstepsprogressbar-roots.o
