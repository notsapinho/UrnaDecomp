# uenux2 api::CTextFieldDoubleLine ctor (target fn 3659) and GetTypeName (10926) in
# src/uenux2/src/api/gui/ctextfielddoubleline.cpp, the file the ctor's three std::source_location records name (lines
# 40, 43 and 46, col 15: the CUeGuiError 4967, 4968 and 4969 throws), with the class header
# (api/gui/ctextfielddoubleline.h) and the three enumerators of api/gui/eueguierror.h. Paths relative to src/uenux2;
# the generic uenux2 rule depends on the source and every uenux2 header. Draw (10931) and Rect (10929) are here too, Rect
# with CalcLineRect, which clang inlines twice: both copies are in its frame, with no second prologue. GetTextLines (5499,
# record 68:21) matches, and Draw and Rect call it through its own generated line (evidence:srcloc-anchor, the record
# 68:21, which it alone loads). What the bytes decide in it, each form put back alone on this body and scored with pnpm
# wasm score at the default depth on a whole link with the object swapped in, its .js beside the wasm (this body: 24
# over 1437 rows, every one a call or data operand; splat-remap IDENTICAL on such a link):
# - the first character moved off a word too long for the line is kept apart from the words moved before it by a
#   space, and the character's concatenation is written in both arms: if (separa) { linha2 = " " + linha2; linha2 =
#   linha1[linha1.size() - 1] + linha2; } else { linha2 = linha1[linha1.size() - 1] + linha2; }. One concatenation
#   after an if (separa) that only prepends the space scores 360 over 1489; its object makes 4
#   __init_copy_ctor_external calls, 5 operator new and 2 __throw_out_of_range, the target 3, 6 and 1.
# - the space prepended as the literal " ": ' ' + linha2 scores 116 over 1447 (fields of both lines loaded again after
#   the copy into the new string, where the target keeps the values it read before it).
# - that arm's last character as linha1[linha1.size() - 1]: linha1.back() there scores 30 over 1440 (linha1's three
#   loads after the free in another order). back() at the three other places gives the same function (below), so []
#   there is chosen, the arm's spelling.
# - m_linha2.x, m_maxX and m_linha1.x read in that order before GetText (the target loads +28, +24, +32): the orders
#   x1 x2 maxX, x1 maxX x2 and x2 x1 maxX score 30 over 1440, maxX first with either order of the other two 40 over
#   1441, and the two widths computed at the top, in either order, 40 over 1441.
# - the work in GetTextLines' own body, with two returns: a file-local Quebra(IScreen&, std::string&, std::string&,
#   const SFont&, TPosition) holding the split and both loops scores 456 over 1484, and one return, the split and its
#   loops inside an if of the first width test, 267 over 1469.
# Forms that give the same function (its disassembly in each form's object differs only in the two data offsets the
# variant file's own name moves): std::make_tuple(linha1, linha2) or std::tuple<std::string, std::string>(linha1,
# linha2) for the braces, and separa = false at the end of the space's arm rather than after the erase; the braces and
# the place after the erase are chosen. The literal "" for the second string is evidence: a default string
# stores 12 bytes of 0, the target two bytes. The layout is the ctor's stores (60 B, the
# 72 B make_shared blocks of its callers); the member and parameter names are chosen, after the messages ("maxX",
# "linha 1", "linha 2"). The implicit destructors emitted with the vtable are 10928/10927, 12 B thunks into bodies
# binaryen merges with CTextRectField's (6022, 6021), which form since unit 90 brought that class.
# Move (target fn 5527, slot 9) is binaryen's one body for this class's and CLineField's, written in each class's file;
# binaryen keeps the first in link order, this one, so the match line names it. Its place below line 133 is a choice.
# The two deltas are read before the first store: `m_linha2.x += posicao.x - m_linha1.x` written in place reads y again
# after that store, which the target does not. Forms that give the object code of the delta locals after the test, by
# the function's disassembly in a compile with the unit's flags: the deltas before the test, tested with `dx == 0 && dy ==
# 0` or around the body with `dx != 0 || dy != 0`; a SPoint of the two deltas; the four coordinates in locals; the x compare
# spelled `m_linha1.x == posicao.x`; a free SPoint operator== for the test. So all of those are choices. A lone link
# (tools/round/try-tu.sh --single) of any of them scores 12 over 68: the y pair's two loads come out swapped there and four
# rows are the library callee, and the whole link matches.
CTEXTFIELDDOUBLELINE_SRCS := src/api/gui/ctextfielddoubleline.cpp
UENUX2_SRCS += $(CTEXTFIELDDOUBLELINE_SRCS)
# No roots: the ctor's three target callers, 1192, 3068 and 4185 (unit 378's vota::AdicionaDadosCandidato, through
# AdicionaTextoDuasLinhas, ctelasvota.cpp), are in the link. They pass the text colour 2, which binaryen's dead-argument
# elimination folds into the ctor as the target's did, and the background colours 1, a parameter and 0, which stay a
# parameter; the stand-in that stood for 4185 went with its file.
