// Roots: api::CTextFieldUpdate's constructor (target fn 3658) has three callers in the target, fns 502, 3058 and 5936,
// each a std::make_shared<CTextFieldUpdate> (awk -F'\t' '$2==3658' ledger/callgraph.tsv). 502 and 3058 are in the link
// (api::CFormBuilder's AddStatusHeader and AddTextFieldUpdate, unit 31), 5936 is not, and these stand for it. All three
// pass the text colour 2 and the background colour 1, which binaryen's dead-argument elimination folds into the
// constructor (its wasm type has no parameter for them), and they pass different points, texts, intervals and fonts,
// which stay parameters. These two stand-ins give it the same call shape, with the colours 2 and 1 and the rest varied,
// and bodies that differ, so wasm-opt cannot merge them into one caller; they are address-taken from a static
// constructor. The constructor stores the vtable, which keeps the destructors, Show and Hide in the table as the target
// has them. Compiled with APP_CXXFLAGS, like unit 28's roots, which make the same make_shared calls.
#include <chrono>
#include <memory>

#include "api/gui/ctextfieldupdate.h"

namespace {

__attribute__((noinline)) std::shared_ptr<api::IFormField<api::IScreen>> CampoAtualizadoA(
    const api::SPoint& posicao, const api::SharedIText& text, const std::chrono::milliseconds& intervalo, const api::SFont& font)
{
    return std::make_shared<api::CTextFieldUpdate>(posicao, text, intervalo, font, static_cast<api::TColor>(2),
                                                   static_cast<api::TColor>(1));
}

__attribute__((noinline)) std::shared_ptr<api::IFormField<api::IScreen>> CampoAtualizadoB(api::TPosition x, api::TPosition y,
                                                                                         const api::SharedIText& text,
                                                                                         const api::SFont& font)
{
    const api::SPoint posicao{x, y};
    const std::chrono::milliseconds intervalo{500};
    return std::make_shared<api::CTextFieldUpdate>(posicao, text, intervalo, font, static_cast<api::TColor>(2),
                                                   static_cast<api::TColor>(1));
}

void* volatile w3658_sink;

struct SW3658Roots {
    SW3658Roots()
    {
        w3658_sink = reinterpret_cast<void*>(&CampoAtualizadoA);
        w3658_sink = reinterpret_cast<void*>(&CampoAtualizadoB);
    }
} w3658_roots;

} // namespace
