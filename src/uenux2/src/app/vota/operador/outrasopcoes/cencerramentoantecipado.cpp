// vota::CEncerramentoAntecipado (app/vota/operador/outrasopcoes/cencerramentoantecipado.cpp, the class name in lower
// case). This comment is the reconstruction's: no record names this file or its functions, so every line is a choice;
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk has the evidence.
#include "app/vota/operador/outrasopcoes/cencerramentoantecipado.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"
#include "app/vota/operador/outrasopcoes/cconfirmaencerramento.h"

namespace vota {

CEncerramentoAntecipado::~CEncerramentoAntecipado() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Encerramento de votação antecipado?", api::SPoint{1, 2}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("CORRIGE: retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: encerrar", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CEncerramentoAntecipado::CEncerramentoAntecipado()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CEncerramentoAntecipado& CEncerramentoAntecipado::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEncerramentoAntecipado());
    }
    return *s_inst;
}

std::unique_ptr<CEncerramentoAntecipado> CEncerramentoAntecipado::s_inst;
std::mutex CEncerramentoAntecipado::s_mutex;

void CEncerramentoAntecipado::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
}

void CEncerramentoAntecipado::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CORRIGE:
        m_pNextState = &CPedeIdentidade::GetInst();
        break;
    case api::INPUT_CONFIRMA:
        m_pNextState = &CConfirmaEncerramento::GetInst();
        break;
    default:
        break;
    }
}

} // namespace vota
