// api::CQRCodeImage's constructor, fn 3662 (a note of the reconstruction). No record names it: its vptr store says
// whose it is. The class's file is evidence: its vtable @1582024, 3 slots, ends at 1582044, this file's record 36:15,
// so the key function, GetData, is here. That the constructor is here, after line 36, is a choice. Line 36 is
// MontaImagem's throw, inlined into fn 10967 and not written, so it stays blank.

#include "api/gui/cqrcodeimage.h"

namespace api {





























CQRCodeImage::CQRCodeImage(const TPosition tamanho, const std::function<std::string()>& fonte)
    : m_tamanho(tamanho)
    , m_fonte(fonte)
{
}

} // namespace api
