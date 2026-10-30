// Pending: api::CQRCodeImage's members that cannot be written yet. The class's vtable (fns 10966, 10964, 10967) needs its
// key function, so this object emits the vtable, and with it the implicit destructors, which are the compiler's code for
// the class definition and match from here (src/units/README.md "Pending members"). They move with the vtable when the
// key function lands in cqrcodeimage.cpp.
//
//   GetData, fn 10967, 1751 B: reads the +4 value, calls the std::function at +8 and holds
//     `static std::vector<uebyte> api::CQRCodeImage::MontaImagem(const TPosition, const std::string &)` inlined, whose throw
//     is the record at cqrcodeimage.cpp line 36, column 15. It waits for api::CQRCodeGuard (fn 5502, 13815 B,
//     cqrcodeguard.cpp), and for fn 3661, 423 B, which it calls three times and no evidence names.
#include "api/gui/cqrcodeimage.h"

namespace api {

std::vector<uint8_t> CQRCodeImage::GetData() const
{
    __builtin_trap();
}

} // namespace api
