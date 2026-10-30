// api::CQRCodeImage's constructor, target fn 3662. This note is the reconstruction's, not TSE's text. No record names the
// constructor: it stores the class's vptr (vtable @1582024), and it is in this file for that reason, as a member defined
// out of line. Its place in the file is a choice. Line 36 is the record of MontaImagem's throw (fn 10967 holds it inlined),
// which is not written, so the line stays blank and the constructor comes after it.

#include "api/gui/cqrcodeimage.h"

namespace api {





























CQRCodeImage::CQRCodeImage(const TPosition tamanho, const std::function<std::string()>& fonte)
    : m_tamanho(tamanho)
    , m_fonte(fonte)
{
}

} // namespace api
