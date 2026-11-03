#include "app/vota/operador/aguardaeleitor/cdesabilitaaudioeleitor.h"

#include <unistd.h>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CDesabilitaAudioEleitor::~CDesabilitaAudioEleitor() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddBuzz(51, 10);
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Retire o fone de ouvido da urna", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CDesabilitaAudioEleitor::CDesabilitaAudioEleitor()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CDesabilitaAudioEleitor& CDesabilitaAudioEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CDesabilitaAudioEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CDesabilitaAudioEleitor> CDesabilitaAudioEleitor::s_inst;
std::mutex CDesabilitaAudioEleitor::s_mutex;

void CDesabilitaAudioEleitor::StartState()
{
    CLogVota::GetInst().LogaPedidoDesconexaoFone();
    m_form->Slot2();
    m_pNextState = this;
}

void CDesabilitaAudioEleitor::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        CThreadEleitor::GetInst().GetMensagens().Post(10);
        while (CEstadoAudio::GetInst().Ativo()) {
            usleep(300);
        }
        CLogVota::GetInst().LogaAudioDesativadoFimVotacao();
        m_pNextState = &CPedeIdentidade::GetInst();
    }
}

} // namespace vota
