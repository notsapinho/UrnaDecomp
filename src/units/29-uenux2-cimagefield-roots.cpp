// Roots: the CImageField ctor has five direct callers in the target (fns 502, 4129, 5547, 6561 and 6689). Four build
// the field with std::make_shared<CImageField> (the __shared_ptr_emplace<api::CImageField> vptr 1537564, then the ctor
// at +12), 502 is the CDSImageField ctor inlined into its caller; they pass the anchors 0 and 1 and keep the ctor's
// result (a ctor returns this in the wasm ABI). None is reconstructed, so these two stand-ins build it the same way,
// with different bodies (wasm-opt would merge identical ones and inline the ctor into the survivor) and different
// anchors (so binaryen's dead-argument elimination folds no parameter), and are address-taken from a static
// constructor. As unit 14's roots do, this TU includes the class header for make_shared: the control block it
// instantiates, __shared_ptr_emplace<api::CImageField> (D0 12639 and D2 12640 in the target), is this object's own,
// since no source of the unit instantiates it, and it moves to the real callers' objects when they land. The ctor's
// destructors (fns 11099 and 11098) have no direct caller in the target: they are reached through the vtable the ctor
// stores. Compiled with APP_CXXFLAGS, like the other stand-ins.
#include <memory>

#include "api/gui/cimagefield.h"

namespace {

__attribute__((noinline)) std::shared_ptr<api::IFormField<api::IScreen>> CampoImagemA(const api::SPoint& posicao,
                                                                                       const api::SharedIImage& imagem)
{
    return std::make_shared<api::CImageField>(posicao, imagem, api::ANCHOR_TOP_LEFT);
}

__attribute__((noinline)) std::shared_ptr<api::IFormField<api::IScreen>> CampoImagemB(api::TPosition x, api::TPosition y,
                                                                                       const api::SharedIImage& imagem)
{
    const api::SPoint posicao{x, y};
    return std::make_shared<api::CImageField>(posicao, imagem, api::ANCHOR_TOP_RIGHT);
}

void* volatile w2242_sink;

struct SW2242Roots {
    SW2242Roots()
    {
        w2242_sink = reinterpret_cast<void*>(&CampoImagemA);
        w2242_sink = reinterpret_cast<void*>(&CampoImagemB);
    }
} w2242_roots;

} // namespace
