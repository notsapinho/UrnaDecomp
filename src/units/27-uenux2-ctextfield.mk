# uenux2 api::CTextField ctor (target fn 1918), Draw (10952), GetTypeName (10947) and its implicit destructors (10950,
# 10948, emitted with the vtable) in src/uenux2/src/api/gui/ctextfield.cpp, with the class header ctextfield.h and the
# 4964 enumerator of eueguierror.h; paths relative to src/uenux2.
# Draw sits above Rect's line 55, in the band's order (uses 1, 10947-10952: Draw, Rect, the destructors, GetTypeName, which alone sits out of that order, above Draw); no
# record falls in it, so its lines are a choice. Same object code, by the function's disassembly with the object-local
# numbers masked: `m_apagar == true`, and m_apagar as an unsigned char compared with 1 (no loop tells a bool from a byte,
# docs/reference/facts/reading.md R14), so the bool is a choice. A local SRect for DrawText's result differs in the whole
# link too (120 B against 114), so the assignment from the call is evidence.
# Move (target fn 2241, slot 9) is binaryen's one body for five functions, each written in its class's file: the Move of
# this class, CImageField, CImageFieldUpdate, CTextFieldBlinking and CTextFieldUpdate (the vtables of six classes hold it:
# api::CDSImageField inherits CImageField's). Binaryen keeps the first in link order, this one, so the match line names
# it. It reads api::IForm<IScreen> through IsVisible and Refresh. Its place below Rect's line 55 is a choice: a shared
# body has no place in a band. Forms that give Move's object code, by the function's disassembly in a compile with the
# unit's flags: the body in an `if (posicao.x != m_posicao.x || posicao.y != m_posicao.y)` instead of the early return, x
# and y read into locals before the test, and `if (m_form == nullptr || !m_form->IsVisible()) return;` before the
# notification. So the early return and the test's spelling are choices. A SPoint operator== changes the object: it adds
# a mask on the second compare, as 65-uenux2-ctextbox.mk says, and primitives.h declares none.
# Rect (target fn 10951, slot 8) is a thunk of fn 3889 with its record as the argument: binaryen forms 3889 from this
# class's, CTextFieldUpdate's and CTextFieldBlinking's Rect, written alike in each class's file, so no file holds it
# alone (10913 and 10943 are the other two thunks). The instance call at col 21 is the record's; the local's type and
# name that put it there are a choice. The target reads the point once, as one 32-bit load after instance() and before
# GetText, and shifts it: a local read by its members gives two 16-bit loads (62 of 160 rows in a whole link), and a
# local whose address goes to an inlined callee gives the target's, which is why AlinhaPosicao (api/gui/itext.h, a chosen
# name) takes it by reference. Same object code: largura and altura declared on one line or above `tela`, and that
# callee as a file-static function with an if chain. Other bytes: the chain written in place (62 lines), and locals for
# the four coordinates with a braced SRect in place of SRect::Normalized (10 lines).
UENUX2_SRCS += src/api/gui/ctextfield.cpp
