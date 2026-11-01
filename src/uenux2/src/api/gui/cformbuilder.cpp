// api::CFormBuilder (/home/rubio/tse/uenux2/src/api/gui/cformbuilder.cpp). Three lines are records of the target:
// AddStatusHeader's 292 and 305 (target fn 502; columns 30 and 24, each the start of a CPolySingleton instance() call
// whose default argument makes the record) and the throw of the static GetLabeledKeyPos at 372 (target fn 5544, column
// 11).
//   203   CFormBuilder()
//   426   AddField                 written, differs at the tree's -O3: src/units/31-uenux2-cformbuilder.mk has the measurement
//   202, 1191  AddTextField        over a CFixedText, over a CDataText of a function
//   3068  AddDoubleLineField
//   5547  AddImage
//   2244, 2245, 3680  AddLine, AddFill, AddRect
//   502   AddStatusHeader          written, differs: the fragment has the measurement. The members of its lambda's
//         CDataText, 11107 (GetText) and 11109 and 11108 (the control block's D2 and D0), match from this object
// FONTE_PADRAO is the SFont {20, 0} at .rodata 520920 that 502 passes twice; its name and its being a constant of this
// file are chosen (its one other reader, fn 3678, is not written). GeraNome has no target function: binaryen inlined it
// into 426, which shows its second prologue. The order of the definitions above line 290 is read from band 1
// (src/units/31-uenux2-cformbuilder.mk); their lines are a choice.

#include "api/gui/cformbuilder.h"

#include <algorithm>
#include <format>

#include "api/gui/capplication.h"
#include "api/gui/cdatatext.h"
#include "api/gui/cdatatextfmt.h"
#include "api/gui/cfillfield.h"
#include "api/gui/cfixedtext.h"
#include "api/gui/cimagefield.h"
#include "api/gui/cdsimagefield.h"
#include "api/gui/clinefield.h"
#include "api/gui/crectfield.h"
#include "api/gui/cpowerinformation.h"
#include "api/gui/ctextfield.h"
#include "api/gui/ctextfieldblinking.h"
#include "api/gui/ctextfieldupdate.h"
#include "api/gui/iscreen.h"
#include "api/gui/ctextfielddoubleline.h"
#include "api/gui/eueguierror.h"
#include "api/hwil/ipower.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/cdatetime.h"

namespace api {

namespace {

// distâncias, em pixels, do rótulo de uma tecla às bordas da área em que ela é desenhada
constexpr TPosition MARGEM_ESQUERDA = 23;
constexpr TPosition MARGEM_DIREITA = 19;
constexpr TPosition DISTANCIA_BASE = 47;

const SFont FONTE_PADRAO{20, 0};


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

CFormBuilder::SharedField CFormBuilder::AddBlinkingTextField(const std::string& texto, const SPoint& posicao,
                                                             const SFont& fonte, ETextAlignment alinhamento)
{
    const auto text = std::make_shared<CFixedText>(texto, alinhamento);
    SharedField campo = std::make_shared<CTextFieldBlinking>(posicao, text, fonte, static_cast<TColor>(2),
                                                             static_cast<TColor>(3), static_cast<TColor>(1));
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

// (original lines 170-289: content not recovered)
#line 290
void CFormBuilder::AddStatusHeader(StatusHeaderFields campos)
{
    const auto larguraTela = CPolySingleton<IScreen>::instance().GetWidth();
    const bool comIcone = (campos & STATUS_ICONE_BATERIA) != 0;
    if (campos & STATUS_DATA_HORA) {
        AddTextFieldUpdate(&CDateTime::FormatCurrentDateTime, SPoint(5, 5), std::chrono::milliseconds(500), FONTE_PADRAO,
                           "A DD/MM/YYYY hh:mm:ss", ALINHAMENTO_ESQUERDA);
    }

    // (original lines 299-303: content not recovered)
#line 304
    if (campos & STATUS_CARGA_BATERIA) {
        auto& ipower = CPolySingleton<IPower>::instance();
        AddTextFieldUpdate(
            [&ipower]() -> std::string {
                if (ipower.Fonte() == 2) {
                    return "";
                }
                return std::format("{: >3}%", ipower.BatLevel());
            },
            SPoint(larguraTela - (comIcone ? 70 : 55), 5), std::chrono::milliseconds(1000), FONTE_PADRAO,
            ALINHAMENTO_DIREITA);
    }

    if (comIcone) {
        const std::shared_ptr<IObservable<SharedIImage>> bateria =
            std::make_shared<BatteryIconDataSource<CPowerInformation::IconOrientation::Horizontal>>();
        const SPoint posicao(larguraTela - 55, 5);
        const SharedField campo(new CDSImageField(posicao, bateria, ANCHOR_TOP_LEFT));
        m_campos.push_back(campo);
    }

    if (campos & STATUS_MODO) {
        const std::string modo = CApplication::GetDescricaoModo();
        if (!modo.empty()) {
            AddTextField(modo, SPoint(static_cast<TPosition>(larguraTela * 0.53), 5), SFont{20, 1}, ALINHAMENTO_CENTRO,
                         static_cast<TColor>(3), static_cast<TColor>(1));
        }
    }
}

// (original lines 334-347: content not recovered)
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
