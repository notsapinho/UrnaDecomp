#pragma once

// api::CQRCodeGuard (a note of the reconstruction, not TSE's text): owns the QRcode libqrencode's QRcode_encodeString
// returns, for the lifetime of a local. Evidence: the record cqrcodeguard.cpp 23:15 names the constructor and its
// parameter, `api::CQRCodeGuard::CQRCodeGuard(const std::string &)` (target fn 5502). The layout is what the bodies
// give: 5502 stores 0 at +0, then the encoder's result there, and stores no vptr, so the class has no vtable; its two
// callers, fns 10967 (CQRCodeImage::GetData) and 2772 (CQRCodeImagePaper::MontaImagem), hold the object in their frame,
// read the QR code's width (+4) and data (+8) through +0 with no call, and end with a direct call of QRcode_free (fn
// 1254) on +0. So the destructor is inline (a reading: out of line, its two callers would keep it a function, since
// binaryen inlines only a function with one call site, and they would call it, not QRcode_free). Chosen: the header's
// path (the class's name in lower case, beside the .cpp the record names), the member's name, the accessor (an
// operator-> here: no evidence names one), the deleted copies, and that the destructor is defined in the class.
// src/units/204-uenux2-cqrcodeguard.mk says how the constructor's arguments to QRcode_encodeString are read.

#include <string>

#include <qrencode.h>

namespace api {

class CQRCodeGuard {
public:
    explicit CQRCodeGuard(const std::string& texto);
    ~CQRCodeGuard() { QRcode_free(m_qrcode); }

    CQRCodeGuard(const CQRCodeGuard&) = delete;
    CQRCodeGuard& operator=(const CQRCodeGuard&) = delete;

    const QRcode* operator->() const { return m_qrcode; }

private:
    QRcode* m_qrcode;
};

} // namespace api
