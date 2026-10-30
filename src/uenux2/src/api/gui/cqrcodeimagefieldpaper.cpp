// api::CQRCodeImageFieldPaper. The reconstruction's file: no record names it.
//   10963  Draw(IPaper&) const   (the class's only virtual member defined out of line, so the vtable is here)
//   10962 / 10961  the destructors (complete / deleting; implicit, emitted with the vtable)

#include "api/gui/cqrcodeimagefieldpaper.h"

#include "api/gui/ipaper.h"

namespace api {

void CQRCodeImageFieldPaper::Draw(IPaper& paper) const
{
    paper.PrintQRCode(m_qrcode.imagem, m_qrcode.tamanho, m_qrcode.escala);
}

} // namespace api

// <stubs>
// f2775 · 543 B · unmatched · placement: link order · name unknown
// void f2775(i32, i32) { ... }
// </stubs>
