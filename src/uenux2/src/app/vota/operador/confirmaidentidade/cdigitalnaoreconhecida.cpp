// vota::CDigitalNaoReconhecida (/home/rubio/tse/uenux2/src/app/vota/operador/confirmaidentidade/
// cdigitalnaoreconhecida.cpp, its record's file). This comment is the reconstruction's. The file's one record is
// StartState's (line 82, column 22: the default argument of CPolySingleton's instance), where StartState's call of it
// sits. Every other line is a choice, in the order of the use band where it gives one
// (src/units/282-uenux2-confirmaidentidade-estados.mk): the statics before StartState, ProcessInput after it.
#include "app/vota/operador/confirmaidentidade/cdigitalnaoreconhecida.h"

#include <format>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/ctextsource.h"
#include "api/hwil/ifingermatcher.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"
#include "app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidadecbiometria.h"
#include "app/vota/operador/confirmaidentidade/cpededigital.h"
#include "app/vota/operador/confirmaidentidade/cverificadadoeleitor.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CDigitalNaoReconhecida::~CDigitalNaoReconhecida() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela(std::shared_ptr<std::string> tentativa,
                                                                                std::shared_ptr<std::string> score)
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBeep(1);
    builder.AddTextField(&comum::CEleitorDadoNomeParaUrna::Text, api::SPoint{1, 1}, "{:2}", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Eleitor(a) não reconhecido(a)", api::SPoint{1, 2}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField(api::CTextSource(tentativa), api::SPoint{1, 3}, "%s", api::ALINHAMENTO_CENTRO);
    builder.AddTextField(api::CTextSource(score), api::SPoint{1, 3}, "%s", api::ALINHAMENTO_DIREITA);
    builder.AddTextField("CORRIGE: cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: prosseguir", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CDigitalNaoReconhecida::CDigitalNaoReconhecida()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_bMostraScore(comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetExibirScoreBiometria())
    , m_tentativa(std::make_shared<std::string>("Tentativa x de x"))
    , m_score(std::make_shared<std::string>(" "))
    , m_form(MontaTela(m_tentativa, m_score))
{
}

CDigitalNaoReconhecida& CDigitalNaoReconhecida::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CDigitalNaoReconhecida());
    }
    return *s_inst;
}

std::unique_ptr<CDigitalNaoReconhecida> CDigitalNaoReconhecida::s_inst;
std::mutex CDigitalNaoReconhecida::s_mutex;

// (original lines 69-72: content not recovered)
#line 73
void CDigitalNaoReconhecida::StartState()
{
    m_pNextState = this;
    if (TemErroDecifracaoBiometria()) {
        m_pNextState = &CDigitalNaoReconhecidaDecBiometria::GetInst();
        return;
    }
    *m_tentativa = std::format("Tentativa {} de {}", CControlaReconhecimento::GetInst().GetTentativa(),
                               CControlaReconhecimento::GetInst().GetLimiteTentativas());
    auto& digitais = api::CPolySingleton<api::IFingerMatcher>::instance();
    if (m_bMostraScore) {
        *m_score = std::format("Score: {}", digitais.Slot4());
    }
    CLogVota::GetInst().LogaTentativaReconhecimentoDedo(CControlaReconhecimento::GetTentativa(),
                                                        CControlaReconhecimento::GetLimiteTentativas());
    m_form->Slot2();
}

void CDigitalNaoReconhecida::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        if (CControlaReconhecimento::AtingiuLimiteTentativas()) {
            m_pNextState = &CVerificaDadoEleitor::GetInst();
        } else {
            CControlaReconhecimento::AvancaTentativa();
            m_pNextState = &CPedeDigital::GetInst();
        }
        break;
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaHabilitacaoCanceladaReconhecimentoBiometrico();
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
        break;
    default:
        break;
    }
}

} // namespace vota
