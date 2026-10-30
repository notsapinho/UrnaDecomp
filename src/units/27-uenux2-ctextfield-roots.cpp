// Roots: the CTextField ctor has six callers in the target (fns 202, 1191, 1192, 2028, 6528 and 12055, each a
// std::make_shared<CTextField>); five pass the colours 2 and 1, and 202 passes its own arguments, so binaryen's
// dead-argument elimination keeps both TColor parameters. These two stand-ins give the ctor two call sites of those two
// kinds (their bodies differ, so wasm-opt does not merge them into one caller and inline the ctor) and are address-taken
// from a static constructor. The CBaseError<EUeGuiError> ctor thunk (fn 406) already has the callers of units 14, 19
// and 22 and 14's roots. Compiled as uenux2 code.
#include <memory>

#include "api/gui/ctextfield.h"

namespace {

__attribute__((noinline)) std::shared_ptr<api::IFormField<api::IScreen>> CampoTextoA(const api::SPoint& posicao, const api::SharedIText& text,
                                                                                     const api::SFont& font, api::TColor corTexto,
                                                                                     api::TColor corFundo)
{
    return std::make_shared<api::CTextField>(posicao, text, font, corTexto, corFundo);
}

__attribute__((noinline)) std::shared_ptr<api::IFormField<api::IScreen>> CampoTextoB(api::TPosition x, api::TPosition y, const api::SharedIText& text,
                                                                                     const api::SFont& font)
{
    const api::SPoint posicao{x, y};
    return std::make_shared<api::CTextField>(posicao, text, font, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
}

void* volatile w1918_sink;

struct SW1918Roots {
    SW1918Roots()
    {
        w1918_sink = reinterpret_cast<void*>(&CampoTextoA);
        w1918_sink = reinterpret_cast<void*>(&CampoTextoB);
    }
} w1918_roots;

} // namespace
