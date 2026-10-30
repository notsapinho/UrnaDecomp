// Roots: api::CFillField, api::CRectField and api::CTextRectField are built only with std::make_shared in the target
// (the __shared_ptr_emplace vptrs 1578224, 1578184 and 1578344), by fns 2245, 3680 and 7787, and 5546, none of them
// reconstructed. These stand-ins build them the same way, so each class's vtable is kept by the vptr store of its
// constructor, as in the target, and the control blocks are the target's: __shared_ptr_emplace<CFillField>'s D2 and D0
// (fns 11124, 11123), <CRectField>'s (11126, 11125) and <CTextRectField>'s (11118, 11117). Fn 5546 builds its text with
// std::make_shared<CFixedText>, alignment 2, and its stand-in does too: <CFixedText>'s D2 and D0 (11120, 11119).
// CFillField's and CTextRectField's constructors have one caller, as in the target, and binaryen inlines them.
// CRectField's (fn 5501) has two, as in the target, and both pass the colour 2, which every target caller passes
// (binaryen folds the parameter). The bodies differ, so binaryen does not merge the two. The colours 20 and 2 are the
// constants fn 5546 stores. Compiled with APP_CXXFLAGS, like the other stand-ins.
#include <memory>
#include <string>

#include "api/gui/cfillfield.h"
#include "api/gui/cfixedtext.h"
#include "api/gui/crectfield.h"
#include "api/gui/ctextrectfield.h"

namespace {

using SharedField = std::shared_ptr<api::IFormField<api::IScreen>>;

__attribute__((noinline)) SharedField CampoPreenchido(const api::SRect& rect, api::TColor cor)
{
    return std::make_shared<api::CFillField>(rect, cor);
}

__attribute__((noinline)) SharedField CampoRetanguloA(const api::SRect& rect)
{
    return std::make_shared<api::CRectField>(rect, static_cast<api::TColor>(2));
}

__attribute__((noinline)) SharedField CampoRetanguloB(api::TPosition x, api::TPosition y)
{
    const api::SRect rect{x, y, static_cast<api::TPosition>(x + 1), static_cast<api::TPosition>(y + 1)};
    return std::make_shared<api::CRectField>(rect, static_cast<api::TColor>(2));
}

__attribute__((noinline)) SharedField CampoTextoRetangulo(const std::string& texto, const api::SRect& rect, const api::SFont& font)
{
    const api::SharedIText text = std::make_shared<api::CFixedText>(texto, api::ALINHAMENTO_CENTRO);
    return std::make_shared<api::CTextRectField>(rect, static_cast<api::TColor>(20), text, font, static_cast<api::TColor>(2));
}

void* volatile u90_sink;

struct SU90Roots {
    SU90Roots()
    {
        u90_sink = reinterpret_cast<void*>(&CampoPreenchido);
        u90_sink = reinterpret_cast<void*>(&CampoRetanguloA);
        u90_sink = reinterpret_cast<void*>(&CampoRetanguloB);
        u90_sink = reinterpret_cast<void*>(&CampoTextoRetangulo);
    }
} u90_roots;

} // namespace
