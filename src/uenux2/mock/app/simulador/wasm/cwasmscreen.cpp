// simulador::CWasmImageSurfaceOps's members. No record names this file, and CWasmScreen's own members are not
// reconstructed yet; src/units/69-uenux2-cwasmimagesurfaceops.mk says why they are here.
#include "cwasmimagesurfaceops.h"

#include <algorithm>
#include <memory>

namespace simulador {

api::SharedBytes CWasmImageSurfaceOps::Slot2(const api::IImage& imagem, int, int) const
{
    return std::make_shared<std::vector<uint8_t>>(imagem.GetData());
}

uint8_t* CWasmImageSurfaceOps::Slot3(const api::IImageSurfaceSource& fonte, int, int) const
{
    return fonte.GetBytes();
}

uint8_t* CWasmImageSurfaceOps::Slot4(uint8_t* const& bytes, int, int) const
{
    return bytes;
}

api::SharedBytes CWasmImageSurfaceOps::Slot5(const api::IImage& imagem, int) const
{
    return std::make_shared<std::vector<uint8_t>>(imagem.GetData());
}

uint8_t* CWasmImageSurfaceOps::Slot6(const api::IImageSurfaceSource& fonte, int) const
{
    return fonte.GetBytes();
}

uint8_t* CWasmImageSurfaceOps::Slot7(uint8_t* const& bytes, int) const
{
    return bytes;
}

uint8_t* CWasmImageSurfaceOps::CopyBytes(const std::vector<uint8_t>& dados) const
{
    uint8_t* copia = new uint8_t[dados.size()];
    std::copy(dados.begin(), dados.end(), copia);
    return copia;
}

api::SharedBytes CWasmImageSurfaceOps::Slot9(uint8_t* const&) const
{
    return std::make_shared<std::vector<uint8_t>>();
}

api::SharedBytes CWasmImageSurfaceOps::Slot10(const api::IImageSurfaceSource& fonte) const
{
    return Slot9(fonte.GetBytes());
}

void CWasmImageSurfaceOps::FreeBytes(uint8_t* bytes) const
{
    delete[] bytes;
}

api::SRect CWasmImageSurfaceOps::ImageRect(api::TPosition largura, api::TPosition altura, const api::SPoint& posicao,
                                           api::EAnchorPoint ancora) const
{
    api::TPosition x = posicao.x;
    api::TPosition y = posicao.y;

    switch (ancora) {
    case api::ANCHOR_TOP_RIGHT:
        x -= largura;
        break;
    case api::ANCHOR_TOP_CENTER:
        x -= largura / 2;
        break;
    case api::ANCHOR_MIDDLE_LEFT:
        y -= altura / 2;
        break;
    case api::ANCHOR_MIDDLE_RIGHT:
        x -= largura;
        y -= altura / 2;
        break;
    case api::ANCHOR_CENTER:
        x -= largura / 2;
        y -= altura / 2;
        break;
    case api::ANCHOR_BOTTOM_LEFT:
        y -= altura;
        break;
    case api::ANCHOR_BOTTOM_RIGHT:
        x -= largura;
        y -= altura;
        break;
    case api::ANCHOR_BOTTOM_CENTER:
        x -= largura / 2;
        y -= altura;
        break;
    default:
        break;
    }

    const api::TPosition direita = x + largura;
    const api::TPosition base = y + altura;
    return api::SRect{std::min(x, direita), std::min(y, base), std::max(x, direita), std::max(y, base)};
}

} // namespace simulador

// <stubs>
// f9265 · 36 B · unmatched · placement: link order · name unknown
// void f9265(i32, i32, i32, i32) { ... }

// f9261 · 45 B · unmatched · placement: link order · name unknown
// void f9261(i32, i32, i32, i32, i32) { ... }

// f9254 · 39 B · unmatched · placement: link order · name unknown
// void f9254(i32, i32) { ... }

// f9243 · 19 B · unmatched · placement: link order · name unknown
// void f9243(i32, i32, i32) { ... }

// f9232 · 181 B · unmatched · placement: link order · name unknown
// void f9232(i32, i32, i32) { ... }

// f9223 · 73 B · unmatched · placement: link order · name unknown
// void f9223(i32, i32, i32) { ... }

// f9213 · 111 B · unmatched · placement: link order · name unknown
// void f9213(i32, i32, i32, i32, i32) { ... }

// f9205 · 290 B · unmatched · placement: link order · name unknown
// void f9205(i32, i32, i32, i32) { ... }

// f9194 · 90 B · unmatched · placement: link order · name unknown
// void f9194(i32, i32, i32, i32, i32) { ... }

// f9184 · 202 B · unmatched · placement: link order · name unknown
// void f9184(i32, i32, i32, i32, i32) { ... }

// f9175 · 130 B · unmatched · placement: link order · name unknown
// void f9175(i32, i32) { ... }

// f9165 · 65 B · unmatched · placement: link order · name unknown
// void f9165(i32, i32, i32, i32, i32, i32) { ... }

// f9155 · 114 B · unmatched · placement: link order · name unknown
// void f9155(i32, i32, i32, i32) { ... }

// f9146 · 617 B · unmatched · placement: link order · name unknown
// void f9146(i32, i32, i32) { ... }

// f9125 · 627 B · unmatched · placement: link order · name unknown
// void f9125(i32, i32, i32, i32) { ... }

// f9115 · 294 B · unmatched · placement: link order · name unknown
// void f9115(i32, i32, i32, i32, i32, i32, i32) { ... }

// f9104 · 1420 B · unmatched · placement: link order · name unknown
// void f9104(i32, i32, i32, i32, i32, i32, i32) { ... }

// f9090 · 46 B · unmatched · placement: link order · name unknown
// void f9090(i32, i32, i32, i32, i32, i32, i32) { ... }

// f9079 · 435 B · unmatched · placement: link order · name unknown
// void f9079(i32, i32, i32, i32) { ... }

// f9068 · 292 B · unmatched · placement: link order · name unknown
// void f9068(i32, i32, i32, i32) { ... }

// f9058 · 476 B · unmatched · placement: link order · name unknown
// void f9058(i32, i32, i32, i32, i32) { ... }

// f9049 · 277 B · unmatched · placement: link order · name unknown
// void f9049(i32, i32, i32, i32) { ... }

// f9038 · 392 B · unmatched · placement: link order · name unknown
// void f9038(i32, i32, i32, i32) { ... }

// f9022 · 134 B · unmatched · placement: link order · name unknown
// void f9022(i32) { ... }

// f9018 · 1621 B · unmatched · placement: link order · name unknown
// void f9018(i32, i32) { ... }

// f9013 · 16 B · unmatched · placement: link order · name unknown
// void f9013(i32, i32, i32) { ... }

// f9009 · 144 B · unmatched · placement: link order · name unknown
// ? f9009(i32, i32, i32) { ... }

// f9004 · 17 B · unmatched · placement: link order · name unknown
// void f9004(i32, i32, i32) { ... }

// f8963 · 20 B · unmatched · placement: link order · name unknown
// void f8963(i32) { ... }

// f8959 · 7 B · unmatched · placement: link order · name unknown
// ? f8959(i32) { ... }

// f8953 · 7 B · unmatched · placement: link order · name unknown
// ? f8953(i32) { ... }

// f8945 · 7 B · unmatched · placement: link order · name unknown
// ? f8945(i32) { ... }
// </stubs>
