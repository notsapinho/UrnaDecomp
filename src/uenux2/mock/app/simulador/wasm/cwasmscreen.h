#pragma once

// simulador::CWasmScreen, the wasm build's api::IScreen: it draws on the page's canvas through the JavaScript functions
// js_* (src/web/wasm_shim.cpp). RTTI names the class, an si_class of api::IScreen (vtable @1528816, 39 slots); no record
// names a file of it, so this header's path is chosen, the class's name in lower case. iscreen.h says what each slot
// does. The layout is read from the constructor binaryen inlined into fn 8302 (`f137(48)`, then the stores below) and
// from the members' bodies:
//   +4, +8    1 (a byte) and 0, which no reconstructed function reads: their types and names are chosen, and so is
//             their place in this class rather than in api::IScreen (both give the same layout)
//   +16, +24  the canvas's width over 640 and height over 480, by which every member scales a logical coordinate
//   +32, +34  640 and 480, the logical size slots 30 and 31 return (fns 8959, 8953)
//   +36, +40  2 and 0, the two colours slot 29 keeps (fn 9013)
//   +44       the CWasmImageSurfaceOps slot 34 returns (fn 8945)
// Every member name is chosen (iscreen.h). Slots 14, 35 and 36 are this class's: fn 218 at table slots 559, 580, 581,
// where IScreen's vtable has __cxa_pure_virtual; 13, 37 and 38 are IScreen's (slots 558, 582, 583 in both vtables).
// 14, 30, 31, 34, 35, 36 are in the class: 8959, 8953 and 8945 follow every strong member in the uses-1 band, where
// clang defers inline functions (reading.md R8); for 14, 35, 36 (fn 218, shared) it is chosen. The destructor is
// implicit: slot 0 is IScreen's (fn 5071), slot 1 the deleting one around it (8963); the class destroys nothing itself.

#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

#include "api/gui/iscreen.h"
#include "cwasmimagesurfaceops.h"

namespace simulador {

class CWasmScreen : public api::IScreen {
public:
    CWasmScreen(api::TPosition largura, api::TPosition altura);

    void GetFontMetrics(uint8_t& largura, uint8_t& altura, const api::SFont& font) override;
    void GetFontMetrics(api::TPosition& largura, api::TPosition& altura, const api::SFont& font,
                        const std::string& texto) override;
    void Clear(api::TColor cor) override;
    void Clear(const api::SRect& rect, api::TColor cor) override;
    void FillRect(const api::SRect& rect, api::TColor cor) override;
    void DrawPixel(const api::SPoint& ponto, api::TColor cor) override;
    void DrawLine(const api::SPoint& inicio, const api::SPoint& fim, api::TColor cor, int largura) override;
    void DrawRect(const api::SRect& rect, api::TColor cor, int largura) override;
    void DrawCircle(const api::SPoint& centro, int raio, api::TColor cor, int largura) override;
    void DrawRoundRect(const api::SRect& rect, int raio, api::TColor cor, int largura) override;
    void DrawGrayGradient(const api::SRect& rect) override;
    void Slot14() override {}
    void DrawTriangle(const api::SPoint& a, const api::SPoint& b, const api::SPoint& c, api::TColor cor,
                      int largura) override;
    void DrawPolygon(const std::vector<api::SPoint>& pontos, api::TColor cor, int largura) override;
    void FillPath(const std::vector<api::SPathCommand>& caminho, api::TColor cor) override;
    void DrawPath(const std::vector<api::SPathCommand>& caminho, api::TColor cor, int largura) override;
    api::SRect DrawText(const api::SPoint& posicao, const api::IText& texto, const api::SFont& font, api::TColor cor,
                        api::TColor fundo) override;
    api::SRect DrawText(const api::SRect& rect, const api::IText& texto, const api::SFont& font, api::TColor cor,
                        api::TColor fundo) override;
    void DrawText(const api::SPoint& posicao, const api::SRect& recorte, const api::IText& texto, const api::SFont& font,
                  api::TColor cor, api::TColor fundo) override;
    void DrawImage(const api::SPoint& posicao, const api::IImage& imagem, api::EAnchorPoint ancora) override;
    void DrawImagePlaceholder(const api::SPoint& posicao, const api::IImage& imagem, api::EAnchorPoint ancora) override;
    void DrawImage(const api::SPoint& posicao, const api::IImage& imagem, const api::SPoint& tamanho,
                   api::EAnchorPoint ancora) override;
    void DrawImage(const api::SPoint& posicao, const api::IImage& imagem, const api::SRect& rect) override;
    void DrawMovie(const api::SPoint& posicao, const api::CMovie& filme, api::EAnchorPoint ancora) override;
    void Refresh() override;
    void Refresh(const api::SRect& rect) override;
    void SetColors(api::TColor cor, api::TColor fundo) override;
    api::TPosition GetWidth() const override { return m_largura; }
    api::TPosition GetHeight() const override { return m_altura; }
    int GetTextWidth(const std::string& texto, const api::SFont& font) override;
    void Clear(int tela, api::TColor cor) override;
    const api::IImageSurfaceOps& GetImageSurfaceOps() const override { return m_ops; }
    void Slot35() override {}
    void Slot36() override {}

private:
    // a logical coordinate on the canvas, rounded up (every drawing member)
    int EscalaX(api::TPosition valor) const { return static_cast<int>(std::ceil(m_escalaX * valor)); }
    int EscalaY(api::TPosition valor) const { return static_cast<int>(std::ceil(m_escalaY * valor)); }
    // a line width, scaled as an int (slots 8 to 11)
    int Espessura(int valor) const { return static_cast<int>(std::ceil(m_escalaX * valor)); }

    bool m_campo4 = true;
    int m_campo8 = 0;
    double m_escalaX;
    double m_escalaY;
    api::TPosition m_largura = 640;
    api::TPosition m_altura = 480;
    api::TColor m_cor = static_cast<api::TColor>(2);
    api::TColor m_fundo = static_cast<api::TColor>(0);
    CWasmImageSurfaceOps m_ops;
};

} // namespace simulador
