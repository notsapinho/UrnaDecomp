// vota::CDigitalNaoReconhecidaPorTempo (app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidaportempo.cpp, the
// class name in lower case). This comment is the reconstruction's: no record names this file or its functions, so every
// line is a choice (src/units/282-uenux2-confirmaidentidade-estados.mk).
#include "app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidaportempo.h"

#include <format>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/ctextsource.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"
#include "app/vota/operador/confirmaidentidade/cpededigital.h"
#include "app/vota/operador/confirmaidentidade/cverificadadoeleitor.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CDigitalNaoReconhecidaPorTempo::~CDigitalNaoReconhecidaPorTempo() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela(std::shared_ptr<std::string> tentativa)
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBeep(1);
    builder.AddTextField(&comum::CEleitorDadoNomeParaUrna::Text, api::SPoint{1, 1}, "{:2}", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Eleitor(a) não reconhecido(a)", api::SPoint{20, 2}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField(api::CTextSource(tentativa), api::SPoint{20, 3}, "%s", api::ALINHAMENTO_CENTRO);
    builder.AddTextField("CORRIGE: cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: retornar", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CDigitalNaoReconhecidaPorTempo::CDigitalNaoReconhecidaPorTempo()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_tentativa(std::make_shared<std::string>("Tentativa x de x"))
    , m_form(MontaTela(m_tentativa))
{
}

CDigitalNaoReconhecidaPorTempo& CDigitalNaoReconhecidaPorTempo::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CDigitalNaoReconhecidaPorTempo());
    }
    return *s_inst;
}

std::unique_ptr<CDigitalNaoReconhecidaPorTempo> CDigitalNaoReconhecidaPorTempo::s_inst;
std::mutex CDigitalNaoReconhecidaPorTempo::s_mutex;

void CDigitalNaoReconhecidaPorTempo::StartState()
{
    m_pNextState = this;
    *m_tentativa = std::format("Tentativa {} de {}", CControlaReconhecimento::GetInst().GetTentativa(),
                               CControlaReconhecimento::GetInst().GetLimiteTentativas());
    CLogVota::GetInst().LogaTimeoutReconhecimentoDedo(CControlaReconhecimento::GetTentativa(),
                                                      CControlaReconhecimento::GetLimiteTentativas());
    m_form->Slot2();
}

void CDigitalNaoReconhecidaPorTempo::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        if (CControlaReconhecimento::AtingiuLimiteTentativas()) {
            SetNextState(&CVerificaDadoEleitor::GetInst());
        } else {
            CControlaReconhecimento::AvancaTentativa();
            SetNextState(&CPedeDigital::GetInst());
        }
        break;
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaHabilitacaoCanceladaReconhecimentoBiometrico();
        SetNextState(&CCancelaHabilitacaoEleitor::GetInst());
        break;
    default:
        break;
    }
}

} // namespace vota
