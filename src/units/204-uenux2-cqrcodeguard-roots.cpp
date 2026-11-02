// Roots of unit 204: reach api::CQRCodeGuard's constructor (fn 5502) the way the target does. The target calls it
// directly from two functions, so binaryen keeps it out of line (src/units/README.md "Companion files"). One of them,
// fn 10967 (api::CQRCodeImage::GetData, unit 79), is in the link; w204_dado stands for the other, fn 2772
// (api::CQRCodeImagePaper::MontaImagem, not written): it builds the guard on its frame from a text, as 2772 does, reads
// the QR code's width and data through it and destroys it, which calls QRcode_free as 2772 does. It goes when 2772 is in
// the link.
#include <string>

#include "api/gui/cqrcodeguard.h"

namespace {

__attribute__((noinline)) unsigned char w204_dado(const std::string& texto)
{
    const api::CQRCodeGuard guarda(texto);
    return guarda->data[guarda->width];
}

const void* volatile w204_sink;

struct SW204Roots {
    SW204Roots()
    {
        w204_sink = reinterpret_cast<const void*>(&w204_dado);
    }
} w204_roots;

} // namespace
