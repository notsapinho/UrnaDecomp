// Roots: api::CRectField and api::CTextRectField are built only with std::make_shared in the target (the
// __shared_ptr_emplace vptrs 1578184 and 1578344), by fns 3680 and 7787, and 5546. 3680 is api::CFormBuilder::AddRect
// and 2245, which builds api::CFillField, AddFill: both are written, so they have no stand-in here, and CFillField's
// constructor needs its one caller. 5546, the only builder of CTextRectField, is api::CFormBuilder::AddTextRectField
// (unit 31), in the link: the stand-in that built CTextRectField and its <CFixedText> text for it went. CampoRetangulo
// builds the CRectField 7787 builds the same way, so that class's vtable is kept by the vptr store of its constructor,
// as in the target. CRectField's constructor (fn 5501) has two callers, as in the target, 3680 and the stand-in for
// 7787, and both pass the colour 2, which every target caller passes (binaryen folds the parameter). Compiled with
// APP_CXXFLAGS, like the other stand-ins.
#include <memory>

#include "api/gui/crectfield.h"

namespace {

using SharedField = std::shared_ptr<api::IFormField<api::IScreen>>;

__attribute__((noinline)) SharedField CampoRetangulo(api::TPosition x, api::TPosition y)
{
    const api::SRect rect{x, y, static_cast<api::TPosition>(x + 1), static_cast<api::TPosition>(y + 1)};
    return std::make_shared<api::CRectField>(rect, static_cast<api::TColor>(2));
}

void* volatile u90_sink;

struct SU90Roots {
    SU90Roots()
    {
        u90_sink = reinterpret_cast<void*>(&CampoRetangulo);
    }
} u90_roots;

} // namespace
