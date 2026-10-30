#pragma once

#include <string>
#include <tuple>

#include "api/gui/iformfield.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;

/**
 * Campo de texto desenhado em duas linhas, cada uma a partir do seu ponto.
 */
class CTextFieldDoubleLine : public IFormField<IScreen> {
public:
    CTextFieldDoubleLine(const SPoint& linha1, const SPoint& linha2, TPosition maxX, const SharedIText& text, const SFont& font, TColor corTexto,
                         TColor corFundo);

    std::string GetTypeName() const override;

    void Draw(IScreen& screen) const override;

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

private:
    std::tuple<std::string, std::string> GetTextLines() const;

    SRect CalcLineRect(const std::string& linha, SPoint posicao) const;

    SPoint m_linha1;
    SPoint m_linha2;
    TPosition m_maxX;
    SharedIText m_text;
    SFont m_font;
    TColor m_corTexto;
    TColor m_corFundo;
};

} // namespace api
