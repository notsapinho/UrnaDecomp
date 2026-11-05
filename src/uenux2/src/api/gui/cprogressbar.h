#pragma once

#include <string>

#include "api/gui/iformfield.h"
#include "api/gui/primitives.h"
#include "ecourna/api/uetypes.hpp"

namespace api {

class IScreen;

// api::CProgressBar (RTTI: si_class of api::IFormField<api::IScreen>; vtable @1581760 [5509, 10978, 10977, 218, 218,
// 4118, 3037, 10975, 10974, 10976]). The constructor's records (cprogressbar.cpp:52, 58 and 67, column 15, in fn 5545,
// the std::make_shared that inlines it) give its signature, and the layout is what that constructor stores: the three
// uedwords at +24, +28 and +32 (the value, which fns 3667, a setter, and 5508, an increment, clamp between the limits
// at +28 and +32 before they mark the form to redraw), the SRect argument at +36, the inner rectangle the constructor
// derives from it at +44 (fn 2768: the rect moved in by 1, 1, -3, -3), the four TColors at +52 to +64, the
// std::string at +68, the TFontSize at +80, the uebyte at +82 and the last TColor at +84 (88 bytes, the 100-byte
// make_shared block less its 12-byte header). Draw (fn 10977) gives the colours and the uebyte their roles: it clears
// the rectangle at +36 with the colour at +56, fills the bar with +52, writes the text in +60 where it lies over the bar
// (on +52 where the bar's end cuts it) and in +64 off it, and draws the border in +84, as wide as the uebyte at +82; the
// string at +68 is the text, its "%p" and "%v" replaced by the percentage and the value (MontaTexto). The members are
// named for those roles.
// Both callers pass 0 for the first two uedwords, so which of the two is the value and which the lower limit is chosen
// here, as is every member and parameter name. The destructor is declared out of line (the deleting one, fn 10978,
// calls it) and first, so it is the key function and cprogressbar.cpp emits the vtable; the other members are declared
// in the order the target emits them (D0 10978, then Draw 10977, Move 10976, GetTypeName 10975, Rect 10974: reverse
// index order in their use band). SetValor (fn 3667) and Incrementa (fn 5508) are the setter and the increment above;
// their names and Limita's are chosen. MontaTexto, which builds Draw's text, has no target function of its own:
// binaryen inlined it into Draw, its one caller. Its name and its place among the private members are chosen; it is a
// member by docs/how-to-decompile.md step 3's rule (it reads the value, the limits and the text, private here), a
// choice as well (src/units/40-uenux2-cprogressbar.mk).
// The constructor is written in cprogressbar.cpp at its records: it value-initializes its base, tests the limits and
// the rectangle's width and height against twice the border's width, sets the value through SetValor, and gives a
// font size of 0 one from the height; binaryen inlines it into fn 5545, its one caller. The fragment has what its
// code shows and the forms measured.
/**
 * Barra de progresso desenhada na tela, entre um limite inferior e um superior.
 */
class CProgressBar : public IFormField<IScreen> {
public:
    CProgressBar(const uedword valor, const uedword limiteInferior, const uedword limiteSuperior, const SRect& rect,
                 TColor corBarra, TColor corFundo, TColor corTextoBarra, TColor corTexto, const std::string& texto,
                 TFontSize tamanhoFonte, uebyte larguraBorda, const TColor corBorda);

    ~CProgressBar() override;

    void Draw(IScreen& screen) const override;

    void Move(const SPoint& posicao) override;

    std::string GetTypeName() const override;

    SRect Rect() const override;

    void SetValor(const uedword valor);

    void Incrementa();

    uedword GetLimiteInferior() const { return m_limiteInferior; }

    uedword GetLimiteSuperior() const { return m_limiteSuperior; }

private:
    void Limita();

    std::string MontaTexto() const;

    uedword m_valor;
    uedword m_limiteInferior;
    uedword m_limiteSuperior;
    SRect m_rect;
    SRect m_rectBarra;
    TColor m_corBarra;
    TColor m_corFundo;
    TColor m_corTextoBarra;
    TColor m_corTexto;
    std::string m_texto;
    TFontSize m_tamanhoFonte;
    uebyte m_larguraBorda;
    TColor m_corBorda;
};

} // namespace api
