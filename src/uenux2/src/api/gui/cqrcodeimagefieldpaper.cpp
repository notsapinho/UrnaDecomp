// api::CQRCodeImageFieldPaper. The reconstruction's file: no record names it.
//   the constructor from a QrcodeData, which binaryen inlines into fn 2775, its one caller (no target function)
//   10963  Draw(IPaper&) const   (the class's only virtual member defined out of line, so the vtable is here)
//   10962 / 10961  the destructors (complete / deleting; implicit, emitted with the vtable)

#include "api/gui/cqrcodeimagefieldpaper.h"

#include "api/gui/ipaper.h"

namespace api {

CQRCodeImageFieldPaper::CQRCodeImageFieldPaper(const CQRCodeImagePaper::QrcodeData& qrcode)
    : m_qrcode(qrcode)
{
}

void CQRCodeImageFieldPaper::Draw(IPaper& paper) const
{
    paper.PrintQRCode(m_qrcode.imagem, m_qrcode.tamanho, m_qrcode.escala);
}

} // namespace api
