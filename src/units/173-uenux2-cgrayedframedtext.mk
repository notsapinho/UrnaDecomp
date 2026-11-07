# uenux2 api/gui: api::CGrayedFramedText::MaskText (target fn 5534, record cgrayedframedtext.cpp 29:15), in the file its
# record names, with the 4918 enumerator of EUeGuiError. It calls CFramedText's DrawChar (5537), FillCell (5536) and
# DrawFrame (2779), unit 92's (api/gui/cframedtext.cpp), passing DrawChar the text's colour 2 (unit 92's fragment says
# why that is a parameter). Its lines but the throw's are a choice. Evidence: the second loop
# starts from the text's size, read again after the first loop, with an index of its own; one index shared by both loops
# gave 75 over 157 rows (the throw after the loops, a second epilogue), the two loops 10 over 131, all operand rows until
# DrawChar had its name (`pnpm wasm score` in the plain link).
# The constructor (fn 5535) is written, at lines 20 to 23 (a choice): CFramedText's constructor over the font and the
#   alignment its two target callers, 3060 and 4185, pass alike, folded by binaryen (the SFont {40, 0} at 474880, among
#   ctelasvota.cpp's constants, FONTE_NUMERO there, and the alignment 0), so cgrayedframedtext.h declares them as
#   parameters. Both its callers are in the link, 3060 (vota::AdicionaCampoNumero<api::CGrayedFramedText>) and 4185
#   (vota::AdicionaDadosCandidato, through AdicionaCampoNumero over comum::CCandidaturasDSNumero), written with
#   ctelasvota.cpp's screens (src/units/378-uenux2-ctelasvota-criatela.mk), and it matches, out of line as the target's
#   two callers keep it; with 3060 its one caller, binaryen had inlined it there. The constructor's vptr store is in the
#   link, so the roots file that took the vtable's address went.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
API_GUI173_SRCS := src/api/gui/cgrayedframedtext.cpp
UENUX2_SRCS += $(API_GUI173_SRCS)
