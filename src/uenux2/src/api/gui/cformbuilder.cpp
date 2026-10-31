// api::CFormBuilder (/home/rubio/tse/uenux2/src/api/gui/cformbuilder.cpp). The throw of the static GetLabeledKeyPos
// (target fn 5544) is a record of the target (line 372, column 11), so its position in this file is fixed. The file's
// other records, AddStatusHeader's throws at lines 292 and 305 (target fn 502, not reconstructed), fall on blank lines.
//   203   CFormBuilder()
//   426   AddField                 written, differs at the tree's -O3: src/units/31-uenux2-cformbuilder.mk has the measurement
//   202, 1191  AddTextField        over a CFixedText, over a CDataText of a function
//   3068  AddDoubleLineField
//   5547  AddImage
//   2244, 2245, 3680  AddLine, AddFill, AddRect
// GeraNome has no target function: binaryen inlined it into 426, which shows its second prologue. The order of the
// definitions above line 348 is read from band 1 (src/units/31-uenux2-cformbuilder.mk); their lines are a choice.

#include "api/gui/cformbuilder.h"

#include <algorithm>
#include <format>

#include "api/gui/cdatatext.h"
#include "api/gui/cfillfield.h"
#include "api/gui/cfixedtext.h"
#include "api/gui/cimagefield.h"
#include "api/gui/clinefield.h"
#include "api/gui/crectfield.h"
#include "api/gui/ctextfield.h"
#include "api/gui/iscreen.h"
#include "api/gui/ctextfielddoubleline.h"
#include "api/gui/eueguierror.h"

namespace api {

namespace {

// distâncias, em pixels, do rótulo de uma tecla às bordas da área em que ela é desenhada
constexpr TPosition MARGEM_ESQUERDA = 23;
constexpr TPosition MARGEM_DIREITA = 19;
constexpr TPosition DISTANCIA_BASE = 47;

// o retângulo cujos cantos opostos são @p canto e @p oposto
SRect RectEntre(const SPoint& canto, const SPoint& oposto)
{
    const TPosition x1 = canto.x;
    const TPosition y1 = canto.y;
    const TPosition x2 = oposto.x;
    const TPosition y2 = oposto.y;
    return SRect{std::min(x1, x2), std::min(y1, y2), std::max(x1, x2), std::max(y1, y2)};
}

} // namespace

CFormBuilder::CFormBuilder() = default;

std::string CFormBuilder::GeraNome(const IFormField<IScreen>& campo) const
{
    std::string nome;
    unsigned int sufixo = 1;
    bool repetido;
    do {
        nome = campo.GetTypeName() + std::to_string(sufixo);
        repetido = std::find_if(m_campos.begin(), m_campos.end(), [&nome](const SharedField& outro) {
            return outro->GetName() == nome;
        }) != m_campos.end();
        sufixo += repetido;
    } while (repetido);
    return nome;
}

void CFormBuilder::AddField(SharedField campo)
{
    campo->SetName(GeraNome(*campo));
    m_campos.push_back(campo);
}

CFormBuilder::SharedField CFormBuilder::AddDoubleLineField(std::string (*fonte)(), const SPoint& linha1, const SPoint& linha2,
                                                           TPosition maxX, const SFont& font, TColor corFundo)
{
    const auto text = std::make_shared<CDataText<std::string (*)()>>(fonte);
    SharedField campo = std::make_shared<CTextFieldDoubleLine>(linha1, linha2, maxX, text, font, static_cast<TColor>(2), corFundo);
    AddField(campo);
    return campo;
}

CFormBuilder::SharedField CFormBuilder::AddImage(SharedIImage imagem, const SPoint& posicao)
{
    SharedField campo = std::make_shared<CImageField>(posicao, imagem, ANCHOR_TOP_RIGHT);
    AddField(campo);
    return campo;
}

CFormBuilder::SharedField CFormBuilder::AddTextField(std::string (*fonte)(), const SPoint& posicao, const SFont& font,
                                                     ETextAlignment alinhamento)
{
    const auto text = std::make_shared<CDataText<std::string (*)()>>(fonte, alinhamento);
    SharedField campo = std::make_shared<CTextField>(posicao, text, font, static_cast<TColor>(2), static_cast<TColor>(1));
    AddField(campo);
    return campo;
}

CFormBuilder::SharedField CFormBuilder::AddRect(const SRect& rect)
{
    SharedField campo = std::make_shared<CRectField>(rect, static_cast<TColor>(2));
    AddField(campo);
    return campo;
}

CFormBuilder::SharedField CFormBuilder::AddRect(const SPoint& canto, const SPoint& oposto)
{
    return AddRect(RectEntre(canto, oposto));
}

CFormBuilder::SharedField CFormBuilder::AddFill(const SPoint& canto, const SPoint& oposto, TColor cor)
{
    SharedField campo = std::make_shared<CFillField>(RectEntre(canto, oposto), cor);
    AddField(campo);
    return campo;
}

CFormBuilder::SharedField CFormBuilder::AddLine(const SPoint& inicio, const SPoint& fim, TColor cor)
{
    SharedField campo = std::make_shared<CLineField>(inicio, fim, cor);
    AddField(campo);
    return campo;
}

CFormBuilder::SharedField CFormBuilder::AddTextField(const std::string& texto, const SPoint& posicao, const SFont& fonte,
                                                     ETextAlignment alinhamento, TColor corTexto, TColor corFundo)
{
    const auto text = std::make_shared<CFixedText>(texto, alinhamento);
    SharedField campo = std::make_shared<CTextField>(posicao, text, fonte, corTexto, corFundo);
    AddField(campo);
    return campo;
}

std::shared_ptr<IForm<IScreen>> CFormBuilder::GetForm(const std::shared_ptr<IPreShow<IScreen>>& preShow, const std::string& nome)
{
    std::shared_ptr<IForm<IScreen>> form(new IForm<IScreen>(m_campos, preShow));
    if (!nome.empty()) {
        form->SetName(nome);
    }
    m_campos.clear();
    return form;
}

// (original lines 143-347: content not recovered)
#line 348
/**
 * Posição do rótulo de uma tecla desenhada em @p area: junto à borda esquerda,
 * junto à direita ou no centro, conforme @p alinhamento, e acima da base,
 * deslocada de @p deslocamento.
 *
 * @throw CUeGuiError se o alinhamento for desconhecido
 */
SPoint CFormBuilder::GetLabeledKeyPos(const SRect& area, ETextAlignment alinhamento, TPosition deslocamento)
{
    SPoint posicao;
    switch (alinhamento) {
    case ALINHAMENTO_ESQUERDA:
        posicao = SPoint(area.left + MARGEM_ESQUERDA, area.bottom + deslocamento - DISTANCIA_BASE);
        return posicao;
    case ALINHAMENTO_CENTRO: {
        const TPosition largura = area.right - area.left + 1;
        posicao = SPoint(area.left + largura / 2, area.bottom + deslocamento - DISTANCIA_BASE);
        return posicao;
    }
    case ALINHAMENTO_DIREITA:
        posicao = SPoint(area.right - MARGEM_DIREITA, area.bottom + deslocamento - DISTANCIA_BASE);
        return posicao;
    }

    throw CUeGuiError(EUE_GUI_GETLABELEDKEYPOS_ALINHAMENTO_DESCONHECIDO, std::format("Alinhamento desconhecido ({})", static_cast<int>(alinhamento)));
}

} // namespace api
