// vota::CDigitalNaoReconhecidaDecBiometria
// (app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidadecbiometria.cpp, the class name in lower case). This
// comment is the reconstruction's: no record names this file or its functions, so every line is a choice
// (src/units/282-uenux2-confirmaidentidade-estados.mk).
#include "app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidadecbiometria.h"

#include <format>
#include <string>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/cverificadadoeleitor.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CDigitalNaoReconhecidaDecBiometria::~CDigitalNaoReconhecidaDecBiometria() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBeep(1);
    builder.AddTextField(&comum::CEleitorDadoNomeParaUrna::Text, api::SPoint{1, 1}, "{:2}", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Eleitor(a) não reconhecido(a)", api::SPoint{1, 2}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("Dados biométricos inválidos", api::SPoint{1, 3}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("CORRIGE: cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: prosseguir", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CDigitalNaoReconhecidaDecBiometria::CDigitalNaoReconhecidaDecBiometria()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CDigitalNaoReconhecidaDecBiometria& CDigitalNaoReconhecidaDecBiometria::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CDigitalNaoReconhecidaDecBiometria());
    }
    return *s_inst;
}

std::unique_ptr<CDigitalNaoReconhecidaDecBiometria> CDigitalNaoReconhecidaDecBiometria::s_inst;
std::mutex CDigitalNaoReconhecidaDecBiometria::s_mutex;

bool TemErroDecifracaoBiometria()
{
    return !EhTreinamentoMesario() &&
           comum::CEleitores::GetInst().GetCurrentBiometriaEleitor().GetErroDecifracao() > 0;
}

void LogaErroDecifracaoBiometria()
{
    if (TemErroDecifracaoBiometria()) {
        CLogVota::GetInst().logaErro(
            std::format("Erro ao decifrar a biometria do eleitor - Código ({})",
                        comum::CEleitores::GetInst().GetCurrentBiometriaEleitor().GetErroDecifracao()));
    }
}

void CDigitalNaoReconhecidaDecBiometria::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    LogaErroDecifracaoBiometria();
}

void CDigitalNaoReconhecidaDecBiometria::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        SetNextState(&CVerificaDadoEleitor::GetInst());
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
