// vota::CPedeDigital (/home/rubio/tse/uenux2/src/app/vota/operador/confirmaidentidade/cpededigital.cpp). The
// reconstruction's note, not TSE's text. The file's records are StartState's (lines 115, 120, 125), FinishState's (131,
// 132), ProcessTick's (162 to 164) and three private members' (234, 262, 279): StartState, FinishState and
// ObtemEstadoPosReconhecimentoBiometrico are written at theirs, and the other record lines stay blank. The functions
// with no record (the form helpers, the constructor, GetInst and the statics, the destructor, ProcessInput) take lines
// of choice, in the order of their use bands (src/units/282-uenux2-confirmaidentidade-estados.mk).
#include "app/vota/operador/confirmaidentidade/cpededigital.h"

#include "api/gui/capplication.h"
#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/hwil/ifingerscanner.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"
#include "app/vota/operador/confirmaidentidade/cdigitalnaoreconhecida.h"
#include "app/vota/operador/confirmaidentidade/cdigitalreconhecida.h"
#include "app/vota/operador/cthreadoperador.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaLeitura()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBuzz(52, 5);
    builder.AddTextField("Solicite que o(a) eleitor(a)", api::SPoint{20, 1}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField(&comum::CEleitorDadoNomeParaUrna::Text, api::SPoint{20, 2}, "{:2}", api::ALINHAMENTO_CENTRO);
    builder.AddTextField("posicione POLEGAR ou INDICADOR no sensor", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaAguarde()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField("Por favor, aguarde.", api::SPoint{1, 2}, api::ALINHAMENTO_CENTRO);
    return builder.GetInteractiveForm("", true);
}

} // namespace

CPedeDigital::CPedeDigital()
    : comum::CAppState(EVENTO_ENTRADA | EVENTO_TICK)
    , m_tickLeitura(CThreadOperador::GetInst().AddStoppedTick(30000))
    , m_tickTimeout(CThreadOperador::GetInst().AddStoppedTick(15000))
    , m_tickVerificacao(CThreadOperador::GetInst().AddStoppedTick(50))
    , m_form(MontaTelaLeitura())
    , m_formAguarde(MontaTelaAguarde())
    , m_contexto(api::CriaContextoAplicacao(2, "Captura da digital do eleitor", "Falha na captura da digital",
                                            "Ocorreu um erro durante captura da digital do eleitor."))
{
}

CPedeDigital& CPedeDigital::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeDigital());
    }
    return *s_inst;
}

std::unique_ptr<CPedeDigital> CPedeDigital::s_inst;
std::mutex CPedeDigital::s_mutex;

// (original lines 76-104: content not recovered)
#line 105
CPedeDigital::~CPedeDigital() = default;

void CPedeDigital::StartState()
{
    api::CApplication::PushContext(m_contexto);
    CLogVota::GetInst().LogaSolicitaDigital(
        CControlaReconhecimento::GetTentativa(),
        comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetNumTentativasHabilitacao());

    if (!comum::CConfiguracaoEleicao::GetInst().HabilitaBiometria()) {
        throw CUeVotaError(EUE_VOTA_BIOMETRIA_DESATIVADA,
                           "Biometria desativada na configuração da eleição, fluxo indevido.");
    }
    m_form->Slot2();

    api::CPolySingleton<api::IFingerScanner>::instance().Slot7(2);
    CThreadOperador::GetInst().StartTick(m_tickLeitura);
    CThreadOperador::GetInst().StartTick(m_tickTimeout);
    CThreadOperador::GetInst().StartTick(m_tickVerificacao);

    api::CPolySingleton<api::IFingerScanner>::instance().Slot3();
    m_pNextState = this;
}

void CPedeDigital::FinishState()
{
    api::CPolySingleton<api::IFingerScanner>::instance().Slot7(0);
    api::CPolySingleton<api::IFingerScanner>::instance().Slot6();
    api::CApplication::s_contextos.Pop(m_contexto);
}


void CPedeDigital::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        CLogVota::GetInst().LogaHabilitacaoCanceladaReconhecimentoBiometrico();
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
    }
}

// (original lines 145-231: content not recovered)
#line 232
void CPedeDigital::ObtemEstadoPosReconhecimentoBiometrico(const bool reconhecido)
{
    auto& digitais = api::CPolySingleton<api::IFingerScanner>::instance();
    if (reconhecido) {
        digitais.Slot7(1);
        m_pNextState = &CDigitalReconhecida::GetInst();
    } else {
        digitais.Slot7(3);
        m_pNextState = &CDigitalNaoReconhecida::GetInst();
    }
    api::CSystem::Dorme(1000);
}




































} // namespace vota
