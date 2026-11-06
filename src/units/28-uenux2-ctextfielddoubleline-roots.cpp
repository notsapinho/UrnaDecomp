// Roots: the CTextFieldDoubleLine ctor has three callers in the target (fns 1192, 3068 and 4185, each a
// std::make_shared<CTextFieldDoubleLine>). All three pass the text colour 2, which binaryen's dead-argument elimination
// folds into the ctor, and they pass different background colours (1, 0 and a parameter of 3068), points, maxX and
// fonts, which stay parameters. 1192 (vota::AdicionaNomeCargo, unit 110's ctelasvota.cpp:
// src/units/378-uenux2-ctelasvota-criatela.mk) is in the link and passes 1, so the stand-in that passed 1 for it went;
// CampoDuasLinhasB stands for 3068 and 4185 with the colour 2 and the background colour 0, a second call site beside
// 1192's, and is address-taken from a static constructor. Compiled with APP_CXXFLAGS, like unit 14's roots, which make
// the same make_shared calls.
#include <memory>

#include "api/gui/ctextfielddoubleline.h"

namespace {

__attribute__((noinline)) std::shared_ptr<api::IFormField<api::IScreen>> CampoDuasLinhasB(api::TPosition x, api::TPosition y1, api::TPosition y2,
                                                                                           api::TPosition maxX, const api::SharedIText& text,
                                                                                           const api::SFont& font)
{
    const api::SPoint linha1{x, y1};
    const api::SPoint linha2{x, y2};
    return std::make_shared<api::CTextFieldDoubleLine>(linha1, linha2, maxX, text, font, static_cast<api::TColor>(2), static_cast<api::TColor>(0));
}

void* volatile w3659_sink;

struct SW3659Roots {
    SW3659Roots()
    {
        w3659_sink = reinterpret_cast<void*>(&CampoDuasLinhasB);
    }
} w3659_roots;

} // namespace
