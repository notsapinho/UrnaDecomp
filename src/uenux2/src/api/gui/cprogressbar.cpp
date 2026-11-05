#include "api/gui/cprogressbar.h"

#include <cmath>
#include <format>

#include "api/gui/cfixedtext.h"
#include "api/gui/iform.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace api {

// (original lines 12-32: content not recovered)
#line 33
CProgressBar::CProgressBar(const uedword valor, const uedword limiteInferior, const uedword limiteSuperior,
                           const SRect& rect, TColor corBarra, TColor corFundo, TColor corTextoBarra, TColor corTexto,
                           const std::string& texto, TFontSize tamanhoFonte, uebyte larguraBorda, const TColor corBorda)
    : IFormField<IScreen>()
    , m_valor(limiteInferior)
    , m_limiteInferior(limiteInferior)
    , m_limiteSuperior(limiteSuperior)
    , m_rect(rect)
    , m_rectBarra(rect.Adjust(1, 1, -3, -3))
    , m_corBarra(corBarra)
    , m_corFundo(corFundo)
    , m_corTextoBarra(corTextoBarra)
    , m_corTexto(corTexto)
    , m_texto(texto)
    , m_tamanhoFonte(tamanhoFonte)
    , m_larguraBorda(larguraBorda)
    , m_corBorda(corBorda)
{
    if (limiteInferior >= limiteSuperior) {
        throw CUeGuiError(EUE_GUI_PROGRESSBAR_LIMITES_INVALIDOS,
                          std::format("Limite inferior ({}) >= limite superior ({})", limiteInferior, limiteSuperior));
    }


    if (rect.right - rect.left <= 2 * larguraBorda) {
        throw CUeGuiError(EUE_GUI_PROGRESSBAR_LARGURA_INSUFICIENTE,
                          std::format("Largura da barra ({}) não comporta a margem ({})", rect.right - rect.left, larguraBorda));
    }

    // (original lines 62-65: content not recovered)
#line 66
    if (rect.bottom - rect.top <= 2 * larguraBorda) {
        throw CUeGuiError(EUE_GUI_PROGRESSBAR_ALTURA_INSUFICIENTE,
                          std::format("Altura da barra ({}) não comporta a margem ({})", rect.bottom - rect.top, larguraBorda));
    }

    SetValor(valor);

    if (m_tamanhoFonte == 0) {
        m_tamanhoFonte = static_cast<TFontSize>(std::floor((m_rect.bottom - (m_rect.top + 2 * m_larguraBorda)) * 0.8));
    }
}

CProgressBar::~CProgressBar() = default;

void CProgressBar::Draw(IScreen& screen) const
{
    const std::string texto = MontaTexto();
    const TPosition x = m_rectBarra.left;
    const TPosition y = m_rectBarra.top;
    const TPosition largura = m_rectBarra.Width();
    const TPosition altura = m_rectBarra.bottom + 1 - y;
    const int preenchido = static_cast<int>(std::trunc(static_cast<double>(largura * (m_valor - m_limiteInferior)) /
                                                       (m_limiteSuperior - m_limiteInferior)));

    screen.Clear(m_rect, m_corFundo);

    if (preenchido > 0) {
        screen.FillRect(SRect(x, y, x + preenchido, y + altura), m_corBarra);
    }

    if (!texto.empty()) {
        const SFont font{m_tamanhoFonte, 0};
        TPosition larguraTexto;
        TPosition alturaTexto;
        screen.GetFontMetrics(larguraTexto, alturaTexto, font, texto);

        const TPosition centroX = x + largura / 2;
        const TPosition centroY = y + altura / 2;
        const SRect area(centroX - larguraTexto / 2 - 1, centroY - alturaTexto / 2 - 1, centroX + larguraTexto / 2 + 1,
                         centroY + alturaTexto / 2 + 1);
        const TPosition fim = x + preenchido;
        const CFixedText fixo(texto, ALINHAMENTO_CENTRO);
        const SPoint posicao(centroX, area.top + 2);

        if (fim <= area.left) {
            screen.DrawText(posicao, fixo, font, m_corTexto, static_cast<TColor>(0));
        } else if (fim >= area.right) {
            screen.DrawText(posicao, fixo, font, m_corTextoBarra, static_cast<TColor>(0));
        } else {
            SRect recorte = area;
            recorte.Right(fim);
            screen.DrawText(posicao, recorte, fixo, font, m_corTextoBarra, m_corBarra);
            recorte = area;
            recorte.Left(fim);
            screen.DrawText(posicao, recorte, fixo, font, m_corTexto, static_cast<TColor>(0));
        }
    }

    const TPosition borda = m_larguraBorda / 2;
    screen.DrawRect(m_rect.Adjust(borda, borda, -borda, -borda), m_corBorda, m_larguraBorda);
}

std::string CProgressBar::MontaTexto() const
{
    if (m_texto.empty()) {
        return "";
    }

    uedword percentual = 100;
    if (m_limiteSuperior != m_limiteInferior) {
        percentual = (m_valor - m_limiteInferior) * 100 / (m_limiteSuperior - m_limiteInferior);
    }

    return ecourna::api::util::CStringUtils::Replace(
        ecourna::api::util::CStringUtils::Replace(m_texto, "%p", std::format("{}%", percentual)), "%v",
        std::format("{}", m_valor));
}

void CProgressBar::Move(const SPoint& posicao)
{
    if (posicao.x == m_rect.left && posicao.y == m_rect.top) {
        return;
    }

    m_rect.Move(posicao);

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

std::string CProgressBar::GetTypeName() const
{
    return "CProgressBar";
}

SRect CProgressBar::Rect() const
{
    return m_rect;
}

void CProgressBar::Limita()
{
    if (m_valor < m_limiteInferior) {
        m_valor = m_limiteInferior;
    } else if (m_valor > m_limiteSuperior) {
        m_valor = m_limiteSuperior;
    }
}

void CProgressBar::SetValor(const uedword valor)
{
    if (m_valor == valor) {
        return;
    }

    m_valor = valor;
    Limita();

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

void CProgressBar::Incrementa()
{
    ++m_valor;
    Limita();

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

} // namespace api
