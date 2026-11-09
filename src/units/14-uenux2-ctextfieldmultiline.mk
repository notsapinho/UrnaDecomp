# uenux2 api::CTextFieldMultiLine in src/uenux2/src/api/gui/ctextfieldmultiline.cpp, its class head in
# ctextfieldmultiline.h, with the gui headers it needs (primitives.h, itext.h, iformfield.h, eueguierror.h, cfixedtext.h,
# iscreen.h, api/pattern/cpolysingleton.h); paths relative to src/uenux2. Every member of the class's vtable is written:
#   5498  the constructor (its throw is the record 71:15); GetTypeName (10921, in the class: the header says why) and the
#         implicit D0 and D2 (10922, 10923), emitted with the vtable; Move (one of the four functions of fn 2783,
#         90-uenux2-api-gui.mk).
#   10925 Draw (slot 2) and 10924 Rect (slot 8) match. Their one call each, of GetTextLines, re-points through 5497's
#         generated line (evidence:srcloc-anchor, its record 116:21, which 5497 alone loads), now that our body is the
#         target's. The callers+content hand line for func:5497 that held them while 5497 differed is gone: with it put
#         back on a copy of splat/symbol_addrs.txt, a scan over the same match list moves no row (11620 match rows both
#         ways).
#         Draw advances y before SRect::Union: the target reads m_alturaLinha for the sum before that call and again at
#         the loop's test after it. With the sum after the union Draw scores 12 over 276 rows at --depth 0, before it 2
#         over 270, both operand rows (the CFixedText vtable's address).
#         Spellings the bytes do not decide, each compiled from one path and `cmp`-equal to the other's object: Draw's
#         centring `m_rect.left + (m_rect.right - (larguraLinha + m_rect.left)) / 2` against `m_rect.left + (m_rect.right
#         - m_rect.left - larguraLinha) / 2` (and `... - larguraLinha - m_rect.left ...`, `(m_rect.right - m_rect.left
#         - larguraLinha) / 2 + m_rect.left`), its loop's test `m_rect.bottom < m_alturaLinha + y` against `y +
#         m_alturaLinha > m_rect.bottom`, and Rect's four `!= 0` written out or left implicit: the written forms are
#         chosen. Rect's four tests themselves and `std::min(m_rect.bottom, y)` are the bytes': `if (m_desenhado)` and
#         the swapped operands give other objects.
#   5497  GetTextLines matches. The search for the last space whose prefix fits is a function of its own, UltimoEspaco,
#         which GetTextLines calls once and clang inlines (it has no target index). What the target's rows show of that
#         loop: it carries the size and the data pointer the find computed into the next pass's substr (no reload of the
#         pointer, no size byte masked with 255), a later find that fails goes straight to the push of the cut, and only
#         the exit of a width test that fails tests corte against npos. Written in GetTextLines' own body (the find in
#         the loop's test as below, each prefix's width through a lambda, the character search as below) it scores 143
#         over 925 rows (pnpm wasm score at the default depth, on a whole link with this object swapped in, its .js
#         beside the wasm); as a function it gives the target's rows. Why, a reading of the TU's -mllvm -print-after-all
#         dumps: in GetTextLines' body the loop's first LoopRotate moves only the find's position test to the latch, the
#         find itself turning at the late LoopRotate, after the last JumpThreading; in UltimoEspaco that first rotation
#         happens in its own pipeline, and GetTextLines' LoopRotate turns the find after the inlining, before its
#         JumpThreading (its dump shows the two memchr calls then). The forms below are compared on the object
#         (wasm-objdump -d of GetTextLines with the call and global.get indices masked, every object compiled from one
#         path); a count is of the lines that differ:
#         - UltimoEspaco takes the line as a parameter: a lambda in GetTextLines that takes it as its parameter gives the
#           same code, one that reads the captured linha differs (96).
#         - its loop has the find in its test, from a start position: `while ((espaco = linha.find(' ', inicio)) !=
#           npos && ... <= largura)`; `while (true)` with the find at the top and one break gives the same code. The
#           next find at the end of the body (the earlier form) differs (112), and so do a for over the finds (112) and
#           the find from corte + 1 (454).
#         - the character search is `while (tamanho < linha.size())` with the cut set in the else of the width test: the
#           target sets corte = tamanho - 1 straight from the width test, with no test of tamanho against the size it
#           reloads after the call, and lays the increment's block before the cut's. A for with continue gives the same
#           code. The earlier form, the test after the loop, differs (297), and so do a for with the cut set before a
#           break and a while with the break first (63 each).
#         - find(' '), since the target calls memchr and subtracts, the char overload's code: find(" ") differs (333).
#         - const int largura = m_rect.Width(), read before GetText, since the target loads m_rect.left and .right
#           before its first call: const TPosition largura differs (18), m_rect.right - m_rect.left + 1 written out
#           differs (9).
#         - return linhas when not even one character fits (corte == 0): the target's br_table sends that case out of
#           both loops to the function's exit.
#         The frame's top slot, above texto, is the substr temporaries' (getline's widen locale shares it), where an
#         inlined callee's local goes (docs/reference/facts/codegen.md C5); UltimoEspaco's substr is such a local. The
#         character search's width written in place, through a lambda (the earlier form's larguraPrefixo) or through a
#         file-local LarguraPrefixo(IScreen&, const std::string&, size_t, const SFont&) that UltimoEspaco calls too
#         gives the same code (the first two `cmp`-equal objects, the third the same GetTextLines): in place is chosen.
#         UltimoEspaco's parameter order, and largura there as a TPosition, give the same GetTextLines too.
#   GetTextLines instantiates std::getline (fn 1917) in this object, which links ahead of app/asn1/AVNDecoder.o, the
#   object 1917 matched from before. At uenux2's -O3 with strict aliasing (api/ is in UENUX2_TBAA_DIRS) the copy is
#   byte-identical, so 1917 still matches, from this object now, and so do its callers 2649, 5055, 8877, 8878, 8883 and
#   8884 (splat/scan.tsv's rows unchanged): the earlier note that this instance cost seven matches no longer holds.
#   Draw's CFixedText likewise brings CFixedText's GetText (1139), D0 (7666) and D2 (7706) from this object, ahead of
#   app/uenux2/src/app/vota/operador/outrasopcoes/cinputfieldmt.cpp.o, whose copies they were; all three still match,
#   from ctelasvota.cpp.o since units 441 and 443 (its screens build a CFixedText first in link order).
# Chosen, as no evidence gives them: every local and parameter name, the data members' names (ctextfieldmultiline.h),
# UltimoEspaco's name, that it is a free function (it reads no class state) rather than the lambda above (its internal
# linkage is the bytes': with external linkage GetTextLines differs, 669 lines, and `static` gives the same object as
# the anonymous namespace), its parameters' order and types, its place (the lines before GetTextLines, which no record
# holds), Move's place in the file, and Draw and Rect after GetTextLines, whose line its record fixes. Draw before Rect
# is the band's order (ledger/ordinals.tsv, uses 1).
UENUX2_SRCS += src/api/gui/ctextfieldmultiline.cpp
# No roots. The ctor's two target callers, 2782 (api::CFormBuilder::AddTextFieldMultiLine, unit 31) and 12055 (through
# vota::AdicionaTextoMultiLinha, ctelasvota.cpp, unit 37), are in the link, so binaryen keeps the ctor and drops its
# two constant TColor arguments as the target's wasm-opt did; the stand-in that called it for 12055 went. The 36
# target callers of the CBaseError<EUeGuiError> ctor thunk (fn 406) are in the link too since fn 13550 (fragment 391)
# matched, so the roots file's two CUeGuiError throw sites, which kept binaryen from inlining that thunk into this
# file's throw, went with it (the link without them moved no row).
