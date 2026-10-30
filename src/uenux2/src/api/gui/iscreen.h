#pragma once

// api::IScreen (/home/rubio/tse/uenux2/src/api/gui/iscreen.h): the screen the forms draw on. RTTI gives the class (no
// base) and its vtable (@1529092, 39 slots, ledger/vtables.json): slot 1 is the trap an abstract class's deleting
// destructor gets, slot 3 is GetFontMetrics (target fn 8938, here: its throw is the record at line 69, column 15),
// slots 13, 37 and 38 hold the empty fn 218 and the other 33 __cxa_pure_virtual. Only slot 3 has a name from a record:
// every other member name and every parameter type no body fixes is chosen, from what simulador::CWasmScreen's
// overrides (vtable @1528816, the one implementation) and the fields' Draws that call them show; the comments say what.
// Slot 2 is declared above slot 3, as the vtable's order needs; that it sits right under the destructor, above the
// file's lines 40 to 61, which are not recovered, is chosen. CWasmScreen overrides slot 3 (fn 9261), so no target
// function calls this GetFontMetrics: it is reached only through IScreen's vtable. Slot 0, the destructor (fn 5071),
// stores the vptr and calls fn 5069, a function of no parameters that walks a global list and that nothing names;
// `= default` below does not, so 5071 and CWasmScreen's deleting destructor (8963) are not reconstructed.

#include <cstdint>
#include <string>
#include <vector>

#include "api/gui/eueguierror.h"
#include "api/gui/iimage.h"
#include "api/gui/primitives.h"

namespace api {

class CMovie;
class IImageSurfaceOps;
class IText;
struct SPathCommand;

/**
 * Tela onde os formulários são desenhados.
 */
class IScreen {
public:
    virtual ~IScreen() = default;

    // slot 2: the width and height of a character of a font, as bytes (fn 9265, with no text to measure)
    virtual void GetFontMetrics(uint8_t& largura, uint8_t& altura, const SFont& font) = 0;

    // (original lines 40-61: content not recovered)
#line 62
    /**
     * Obtém a largura e a altura que @p texto ocupa escrito com a fonte @p font.
     *
     * @throw CUeGuiError se a tela não implementa a medida
     */
    virtual void GetFontMetrics(TPosition& largura, TPosition& altura, const SFont& font, const std::string& texto)
    {
        throw CUeGuiError(EUE_GUI_METODO_NAO_IMPLEMENTADO, "Método não implementado");
    }

    // slots 4 to 12: what they do is read from CWasmScreen's bodies (fns 9254 to 9175). api::CLineField::Draw (fn 11068)
    // calls slot 8 with a width of 1, and api::CTextBox::Draw (fn 10958) slots 5, 6 and 9.
    virtual void Clear(TColor cor) = 0;
    virtual void Clear(const SRect& rect, TColor cor) = 0;
    virtual void FillRect(const SRect& rect, TColor cor) = 0;
    virtual void DrawPixel(const SPoint& ponto, TColor cor) = 0;
    virtual void DrawLine(const SPoint& inicio, const SPoint& fim, TColor cor, int largura) = 0;
    virtual void DrawRect(const SRect& rect, TColor cor, int largura) = 0;
    virtual void DrawCircle(const SPoint& centro, int raio, TColor cor, int largura) = 0;
    virtual void DrawRoundRect(const SRect& rect, int raio, TColor cor, int largura) = 0;
    virtual void DrawGrayGradient(const SRect& rect) = 0;
    // slot 13 is IScreen's own empty fn 218: table slot 558 in both vtables, so one symbol, inherited. Slot 14 is pure,
    // and CWasmScreen's override is fn 218 at table slot 559, its own. fn 218 takes `this` alone; nothing shows more.
    virtual void Slot13() {}
    virtual void Slot14() = 0;

    // slots 15 and 16: lines between the corners (fns 9165, 9155)
    virtual void DrawTriangle(const SPoint& a, const SPoint& b, const SPoint& c, TColor cor, int largura) = 0;
    virtual void DrawPolygon(const std::vector<SPoint>& pontos, TColor cor, int largura) = 0;

    // slots 17 and 18: a path, filled and stroked (fns 9146, 9125, which api::CStepsProgressBar::Draw calls)
    virtual void FillPath(const std::vector<SPathCommand>& caminho, TColor cor) = 0;
    virtual void DrawPath(const std::vector<SPathCommand>& caminho, TColor cor, int largura) = 0;

    // slots 19 to 21: a text from a point, in a rectangle, and from a point inside a clip, in a colour over a background.
    // The first two return the rectangle drawn: their first wasm parameter is the result's. The fields' Draws pass the
    // text and font as here (fns 10952, 10958, 10977); slot 21's override ignores the clip (fn 9090).
    virtual SRect DrawText(const SPoint& posicao, const IText& texto, const SFont& font, TColor cor, TColor fundo) = 0;
    virtual SRect DrawText(const SRect& rect, const IText& texto, const SFont& font, TColor cor, TColor fundo) = 0;
    virtual void DrawText(const SPoint& posicao, const SRect& recorte, const IText& texto, const SFont& font, TColor cor,
                          TColor fundo) = 0;

    // slots 22 to 26: the image members. api::CImageField::Draw (fn 11102) calls 22 and 24, api::CMovieField::Draw
    // (fn 11064) calls 26. Nothing calls 23, and its override reads only the point and the anchor (fn 9068), so its
    // second parameter is the slot's neighbour's by choice.
    virtual void DrawImage(const SPoint& posicao, const IImage& imagem, EAnchorPoint ancora) = 0;
    virtual void DrawImagePlaceholder(const SPoint& posicao, const IImage& imagem, EAnchorPoint ancora) = 0;
    virtual void DrawImage(const SPoint& posicao, const IImage& imagem, const SPoint& tamanho, EAnchorPoint ancora) = 0;
    virtual void DrawImage(const SPoint& posicao, const IImage& imagem, const SRect& rect) = 0;
    virtual void DrawMovie(const SPoint& posicao, const CMovie& filme, EAnchorPoint ancora) = 0;

    // slots 27 and 28: the whole screen and a rectangle of it changed (fns 9022, 9018: CWasmScreen logs "Refresh()" and
    // emits "vota:screen" with {"refreshed":true}, the rectangle's with "partial":true and its corners and size)
    virtual void Refresh() = 0;
    virtual void Refresh(const SRect& rect) = 0;

    // slot 29 keeps two TColor (fn 9013; api::CTextBox::Draw, fn 10958, passes its two colours both ways round); slots
    // 30 and 31 return the screen's logical size (fns 8959, 8953: 640 and 480 from the constructor); slot 32 measures a
    // text (fn 9009; GetFontMetrics calls it); slot 33 clears the screen whatever its first parameter (fn 9004)
    virtual void SetColors(TColor cor, TColor fundo) = 0;
    virtual TPosition GetWidth() const = 0;
    virtual TPosition GetHeight() const = 0;
    virtual int GetTextWidth(const std::string& texto, const SFont& font) = 0;
    virtual void Clear(int tela, TColor cor) = 0;

    // slot 34: the image operations (fn 8945 returns the member at +44); the callers are listed in iimagesurfaceops.h
    virtual const IImageSurfaceOps& GetImageSurfaceOps() const = 0;
    // slots 35 and 36 are pure, and CWasmScreen's overrides are fn 218 at table slots 580 and 581, its own; 37 and 38
    // are IScreen's own fn 218, table slots 582 and 583 in both vtables (inherited). Nothing shows what they do.
    virtual void Slot35() = 0;
    virtual void Slot36() = 0;
    virtual void Slot37() {}
    virtual void Slot38() {}
};

} // namespace api
