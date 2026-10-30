#pragma once

#include <cstdint>
#include <vector>

#include "api/gui/iimagesurfaceops.h"

namespace simulador {

// RTTI names the class, an si_class of api::IImageSurfaceOps (vtable @1528980); it has no data member (fn 8302 stores
// its vptr at CWasmScreen's +44, the last word of a 48-byte object). The path is chosen, the class's name in lower
// case: no record names it. The class is not final: slot 10 (fn 9317) calls slot 9 through the vtable. The destructor
// is implicit or defined in the class (slots 0 and 1 are 174 and 144; both give one object, implicit is chosen). Its
// members are in cwasmscreen.cpp, as 69-uenux2-cwasmimagesurfaceops.mk says; api/gui/iimagesurfaceops.h has the slots.
class CWasmImageSurfaceOps : public api::IImageSurfaceOps {
public:
    virtual api::SharedBytes Slot2(const api::IImage& imagem, int, int) const override;
    virtual uint8_t* Slot3(const api::IImageSurfaceSource& fonte, int, int) const override;
    virtual uint8_t* Slot4(uint8_t* const& bytes, int, int) const override;
    virtual api::SharedBytes Slot5(const api::IImage& imagem, int) const override;
    virtual uint8_t* Slot6(const api::IImageSurfaceSource& fonte, int) const override;
    virtual uint8_t* Slot7(uint8_t* const& bytes, int) const override;
    virtual uint8_t* CopyBytes(const std::vector<uint8_t>& dados) const override;
    virtual api::SharedBytes Slot9(uint8_t* const& bytes) const override;
    virtual api::SharedBytes Slot10(const api::IImageSurfaceSource& fonte) const override;
    virtual void FreeBytes(uint8_t* bytes) const override;
    virtual api::SPoint ImageSize(const std::vector<uint8_t>& dados) const override;
    virtual api::SRect ImageRect(api::TPosition largura, api::TPosition altura, const api::SPoint& posicao,
                                 api::EAnchorPoint ancora) const override;
};

} // namespace simulador
