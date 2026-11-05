// comum::CMenuBase (app/comum/informacao/cmenubase.cpp, a chosen path: cmenubase.h says why). No record names a line
// of this file; the reconstruction's notes are in cmenubase.h and src/units/59-uenux2-cmenubase.mk.

#include "app/comum/informacao/cmenubase.h"

#include <format>

#include "api/gui/cformbuilder.h"
#include "api/gui/cframedtext.h"
#include "api/gui/cinputfield.h"
#include "api/gui/coptionvalidation.h"
#include "app/comum/informacao/citemmenu.h"

namespace comum {

namespace {

const api::SFont FONTE_PERGUNTA{20, 0};

void AdicionaCampoOpcao(api::CFormBuilder& form, const std::shared_ptr<api::IInputValidation>& validacao,
                        const api::SPoint& posicao)
{
    const std::shared_ptr<api::IInputField<api::IScreen>> campo(new api::CInputField<api::CFramedText>(
        validacao, 1, true, true, false, false, false, posicao, FONTE_PERGUNTA, api::ALINHAMENTO_ESQUERDA));
    form.AddField(campo);
}

} // namespace

CMenuBase::CMenuBase(api::CFormBuilder& form)
    : m_form(form)
{
}

void CMenuBase::AdicionaItem(std::shared_ptr<CItemMenu> item)
{
    m_itens.push_back(item);
    if (item->Slot2()) {
        AdicionaOpcao(item->GetChave());
    }
}

void CMenuBase::AdicionaOpcao(unsigned int chave)
{
    m_opcoes += std::format("{}", chave);
}

std::string FormataItem(const CItemMenu& item)
{
    return std::format("[{}] - {}", item.GetChave(), item.GetTexto());
}

void CMenuBase::AdicionaPergunta(int x, int y)
{
    m_form.AddTextField("Escolha a sua opção:",
                        api::SPoint{static_cast<api::TPosition>(x), static_cast<api::TPosition>(y)}, FONTE_PERGUNTA,
                        api::ALINHAMENTO_ESQUERDA, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    const std::shared_ptr<api::IInputValidation> validacao(new api::COptionValidation(m_opcoes));
    AdicionaCampoOpcao(m_form, validacao,
                       api::SPoint{static_cast<api::TPosition>(x + 208), static_cast<api::TPosition>(y - 2)});
}

void CMenuBase::MontaMenu()
{
    for (const std::shared_ptr<CItemMenu>& item : m_itens) {
        m_form.AddTextField(FormataItem(*item), item->GetPosicao(), item->GetFonte(), api::ALINHAMENTO_ESQUERDA,
                            static_cast<api::TColor>(item->Slot2() ? 2 : 5), static_cast<api::TColor>(1));
    }
    const std::shared_ptr<CItemMenu> ultimo = m_itens.back();
    const api::SPoint posicao = ultimo->GetPosicao();
    AdicionaPergunta(posicao.x, posicao.y + 2 * ultimo->GetFonte().size);
}

} // namespace comum
