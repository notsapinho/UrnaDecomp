#include "app/vota/operador/leidentidade/celeitorjavotou.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CEleitorJaVotou::~CEleitorJaVotou() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField(&comum::CEleitorDadoNomeParaUrna::Text, api::SPoint{1, 1}, "{:2}", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("JÁ VOTOU", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: prosseguir", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CEleitorJaVotou::CEleitorJaVotou()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CEleitorJaVotou& CEleitorJaVotou::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorJaVotou());
    }
    return *s_inst;
}

std::unique_ptr<CEleitorJaVotou> CEleitorJaVotou::s_inst;
std::mutex CEleitorJaVotou::s_mutex;

void CEleitorJaVotou::StartState()
{
    CLogVota::GetInst().LogaEleitorJaVotou();
    m_form->Slot2();
    m_pNextState = this;
}

void CEleitorJaVotou::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
    }
}

} // namespace vota
