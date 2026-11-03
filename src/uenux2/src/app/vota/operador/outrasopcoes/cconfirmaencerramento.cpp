// vota::CConfirmaEncerramento (app/vota/operador/outrasopcoes/cconfirmaencerramento.cpp, the class name in lower case).
// This comment is the reconstruction's: no record names this file or its functions, so every line is a choice;
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk has the evidence.
#include "app/vota/operador/outrasopcoes/cconfirmaencerramento.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"
#include "app/vota/operador/outrasopcoes/cfimaquisicaovotos.h"

namespace vota {

CConfirmaEncerramento::~CConfirmaEncerramento() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Encerramento da Votação", api::SPoint{1, 2}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("CORRIGE: cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: encerrar", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CConfirmaEncerramento::CConfirmaEncerramento()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CConfirmaEncerramento& CConfirmaEncerramento::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConfirmaEncerramento());
    }
    return *s_inst;
}

std::unique_ptr<CConfirmaEncerramento> CConfirmaEncerramento::s_inst;
std::mutex CConfirmaEncerramento::s_mutex;

void CConfirmaEncerramento::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
}

void CConfirmaEncerramento::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaEncerramentoAbortado();
        m_pNextState = &CPedeIdentidade::GetInst();
        break;
    case api::INPUT_CONFIRMA: {
        CLogVota::GetInst().LogaEncerramentoConfirmado();
        comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
        appInfo.GetVota().MarcaFimAquisicao();
        appInfo.GetVota().SetEstadoVota(comum::EAVFIMAQUISICAOVOTOS);
        CSincronizaVota::SincronizaEstadoGeralVota();
        m_pNextState = &CFimAquisicaoVotos::GetInst();
        break;
    }
    default:
        break;
    }
}

} // namespace vota
