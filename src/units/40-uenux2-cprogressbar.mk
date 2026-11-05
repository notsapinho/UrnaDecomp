# uenux2 api::CProgressBar::~CProgressBar (target fn 5509, the base-object destructor in slot 0 of the CProgressBar
# vtable @1581760, and fn 10978, the deleting one in slot 1), Draw (fn 10977, slot 2), Rect (fn 10974, slot 8) and
# GetTypeName (10975, slot 7) in src/uenux2/src/api/gui/cprogressbar.cpp, the file the constructor's three
# std::source_location records name (cprogressbar.cpp:52, 58 and 67, column 15: api::CProgressBar::CProgressBar(const
# uedword, const uedword, const uedword, const SRect &, TColor, TColor, TColor, TColor, const std::string &, TFontSize,
# uebyte, const TColor)). The constructor is not reconstructed: binaryen inlined it into std::make_shared's fn 5545
# (component libc++, no stub), so lines 11-77 stay blank for it, its records' lines among them (the four includes Draw
# needs, <cmath>, <format>, api/gui/cfixedtext.h and ecourna/api/util/cstringutils.hpp, and a blank line between them
# took five blank lines of that run, above the first record: a layout of ours); no record falls in the destructor,
# Draw, MontaTexto or Rect, so their lines (78 on) are a choice. The class header (api/gui/cprogressbar.h) has the
# layout that constructor stores: the destructor destroys the std::string at +68, then IFormFieldBase<IScreen>'s part
# (its vptr, m_nome at +12). The destructor is out of line (the deleting one calls it), declared first, so it is the
# key function and cprogressbar.o emits the vtable. Move (10976) is here, over SRect::Move, and SetValor and Incrementa
# (3667, 5508, chosen names, with the chosen helper Limita): the increment and the setter differ only in the setter's
# first test. Limita's statements in place give the same object code; std::clamp differs (27 lines). `m_valor == valor`
# is the operand order the link gives the target's compare. Incrementa's two target callers, 2369 and 12101, are in the
# link. GetTypeName (10975, `return "CProgressBar";`) is defined between Move and Rect, and Draw between the destructor
# and Move, the order of their target indices in the use band (10978, 10977, 10976, 10975, 10974), which names.tsv's
# ld_index follows (Draw 6733, between the D0's 6732 and Move's 6735). Paths relative to src/uenux2; the generic uenux2
# rule depends on the source and every uenux2 header.
#
# Draw (10977): the evidence is the target's rows (`pnpm wasm fn ../target/vota_web_wasm.wasm 10977`); what it gives,
# the forms measured and the choices:
# - Its first statement builds the text through MontaTexto (a chosen name and a private const member: the class header
#   says why), which binaryen inlined, its one caller being Draw: a second prologue (g0 - 432) right after Draw's own
#   (g0 - 64), its result Draw's local at +52. MontaTexto returns "" when the text at +68 is empty (the target writes
#   the empty string's two bytes, +0 and +11; `return std::string();` zeroes all twelve, 34 over 917 rows, three of them
#   no operand), else the percentage, 100 when the limits are equal and (value - lower) * 100 / (upper - lower)
#   otherwise (i32.div_u), and Replace(Replace(m_texto, "%p", std::format("{}%", percentual)), "%v", std::format("{}",
#   m_valor)): ecourna's copying CStringUtils::Replace (fn 2677) twice; the format strings are "{}%" (3 bytes at
#   438313) and "{}" (the tail of the literal at 8090), each with one unsigned argument (__arg_t 6). One full
#   expression: the target destroys its five temporaries at its end, in reverse order; the first Replace's result in a
#   named local destroys "%p" and its format before the second Replace (167 over 943 rows).
# - Draw reads all four edges of the bar's rectangle at +44, the value and the limits before it clears the rectangle at
#   +36 with slot 5 (the target loads them ahead of that call_indirect). The bar's height, `bottom + 1 - y`, keeps
#   bottom + 1, which the filled rectangle's corner shares, as the target does; `bottom - y + 1` computes the height
#   apart (measured alone with try-tu --single, one edit apart: 192 over 947 rows against 44 over 920). The filled width
#   is std::trunc of a double, the target's f64.trunc before i32.trunc_sat_f64_s: without std::trunc that row goes (32
#   over 917), and std::floor gives f64.floor (32 over 917). The filled part is slot 6 (FillRect) of the normalized
#   rectangle from the bar's corner to its filled end, in +52, when it is wider than 0.
# - The text, when there is one: SFont{m_tamanhoFonte, 0}, slot 3 (GetFontMetrics) into two TPosition locals, the area
#   one pixel past the text on each side around the bar's centre, then the CFixedText, centred (the 2 at +4): the target
#   reads the text's size before it stores the CFixedText's vptr, and the CFixedText built before the area gives 149
#   over 966 rows. The text goes from (the centre's x, the area's top + 2): in +64 on 0 through slot 19 when the bar
#   ends at or left of the area, in +60 on 0 when the bar reaches its right edge, else in two parts through slot 21,
#   clipped at the bar's end by SRect::Right and Left (fns 5487, 5488) on a copy of the area, +60 on +52 and then +64 on
#   0. `fim >= area.right` gives the target's compare, its right edge first; `area.right <= fim` swaps the operands (34
#   over 918 rows, one inserted and one deleted).
# - The border: slot 9 (DrawRect) of m_rect.Adjust(b, b, -b, -b) with b the uebyte at +82 halved (fn 2768's call
#   passes the half twice, then its negation twice), in +84, the uebyte its width.
# Draw scores 31 over 917 rows against the plain link (`pnpm wasm score ../target/vota_web_wasm.wasm 10977
# ../build/out/wasm/vota_web/vota_web_wasm.wasm <ours>`), every one an operand: calls, data, and the table slot 148
# against ours 91, both __allocating_buffer<char>::__prepare_write (fn 7324); it matches. The scores above are the same
# command's on a link of each variant, unless they say alone. Draw is reached only through the vtable, which
# 40-uenux2-cprogressbar-roots.cpp keeps.
CPROGRESSBAR_SRCS := src/api/gui/cprogressbar.cpp
UENUX2_SRCS += $(CPROGRESSBAR_SRCS)
# nothing reconstructed references the vtable yet: 40-uenux2-cprogressbar-roots.cpp takes its address, which keeps
# every slot in the table as the target has them
$(ROOT)/$(APP)/40-uenux2-cprogressbar-roots.o: $(ROOT)/src/units/40-uenux2-cprogressbar-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/40-uenux2-cprogressbar.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/40-uenux2-cprogressbar-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/40-uenux2-cprogressbar-roots.o
