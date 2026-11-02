// api::CQRCodeGuard's constructor, fn 5502 (a note of the reconstruction, not TSE's text). Its throw is the record at
// line 23, column 15; every other line is a choice. binaryen inlined QRcode_encodeString and the library functions it
// alone calls into 5502, whose body gives the arguments (fragment 204 says how). The store of 0 before the call is
// evidence; that it is a mem-initializer is chosen (a default member initializer or an assignment gives that store).

#include "api/gui/cqrcodeguard.h"

#include "api/gui/eueguierror.h"

namespace api {

// (original lines 12-17: content not recovered)
#line 18
CQRCodeGuard::CQRCodeGuard(const std::string& texto)
    : m_qrcode(nullptr)
{
    m_qrcode = QRcode_encodeString(texto.c_str(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);
    if (m_qrcode == nullptr) {
        throw CUeGuiError(EUE_GUI_QRCODEGUARD_FALHA_AO_CRIAR, "Não foi possível criar o QR code");
    }
}

} // namespace api
