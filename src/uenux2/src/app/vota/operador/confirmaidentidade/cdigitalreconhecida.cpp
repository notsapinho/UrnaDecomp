// vota::CDigitalReconhecida (/home/rubio/tse/uenux2/src/app/vota/operador/confirmaidentidade/cdigitalreconhecida.cpp).
// This comment is the reconstruction's. The file's one record is StartState's (line 47, column 22, the default
// argument of CPolySingleton's instance); every other line is a choice, in the order of the use band where it gives
// one (src/units/282-uenux2-confirmaidentidade-estados.mk).
#include "app/vota/operador/confirmaidentidade/cdigitalreconhecida.h"

#include <format>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/ctextsource.h"
#include "api/hwil/ifingermatcher.h"
#include "api/ipc/cmessagequeue.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.h"

namespace vota {

CDigitalReconhecida::~CDigitalReconhecida() = default;

std::unique_ptr<CDigitalReconhecida> CDigitalReconhecida::s_inst;
std::mutex CDigitalReconhecida::s_mutex;

// (original lines 29-43: content not recovered)
#line 44
void CDigitalReconhecida::StartState()
{
    m_pNextState = this;
    auto& digitais = api::CPolySingleton<api::IFingerMatcher>::instance();
    if (m_bMostraScore) {
        *m_score = std::format("Score: {}", digitais.Slot4());
    }
    m_form->Slot2();
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>>
MontaTelaDigitalReconhecida(std::shared_ptr<std::string> score)
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBuzz(52, 5);
    builder.AddTextField("ELEITOR(A) RECONHECIDO(A)", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(api::CTextSource(score), api::SPoint{40, 1}, "%s", api::ALINHAMENTO_DIREITA);
    builder.AddTextField("Não assinar o caderno de votação", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: prosseguir", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

CDigitalReconhecida::CDigitalReconhecida()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_bMostraScore(comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetExibirScoreBiometria())
    , m_score(std::make_shared<std::string>(" "))
    , m_form(MontaTelaDigitalReconhecida(m_score))
{
}

CDigitalReconhecida& CDigitalReconhecida::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CDigitalReconhecida());
    }
    return *s_inst;
}

void CDigitalReconhecida::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        if (IsAudioAtivado()) {
            SetNextState(&CHabilitaAudioEleitor::GetInst());
        } else {
            CThreadEleitor::GetInst().GetMensagens().Post(1);
            SetNextState(&CMostraEleitorVotando::GetInst());
        }
        impl::IInformacaoThreadOperador::GetInst().SetBiometriaEleitor();
        CLogVota::GetInst().LogaTipoHabilitacaoEleitor(1);
    }
}

} // namespace vota
