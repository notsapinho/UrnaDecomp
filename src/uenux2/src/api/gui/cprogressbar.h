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
// make_shared block less its 12-byte header). Both callers pass 0 for the first two uedwords, so which of the two is
// the value and which the lower limit is chosen here, as is every member and parameter name. The destructor is
// declared out of line (the deleting one, fn 10978, calls it) and first, so it is the key function and
// cprogressbar.cpp emits the vtable; the other members are declared in the order the target emits them (D0 10978,
// then Draw 10977, Move 10976, GetTypeName 10975, Rect 10974: reverse index order in their use band). SetValor (fn 3667)
// and Incrementa (fn 5508) are the setter and the increment above; their names and Limita's are chosen.
/**
 * Barra de progresso desenhada na tela, entre um limite inferior e um superior.
 */
class CProgressBar : public IFormField<IScreen> {
public:
    CProgressBar(const uedword valor, const uedword limiteInferior, const uedword limiteSuperior, const SRect& rect, TColor corFundo,
                 TColor corBorda, TColor corBarra, TColor corTexto, const std::string& texto, TFontSize tamanhoFonte, uebyte margem,
                 const TColor corTextoBarra);

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

    uedword m_valor;
    uedword m_limiteInferior;
    uedword m_limiteSuperior;
    SRect m_rect;
    SRect m_rectBarra;
    TColor m_corFundo;
    TColor m_corBorda;
    TColor m_corBarra;
    TColor m_corTexto;
    std::string m_texto;
    TFontSize m_tamanhoFonte;
    uebyte m_margem;
    TColor m_corTextoBarra;
};

} // namespace api
