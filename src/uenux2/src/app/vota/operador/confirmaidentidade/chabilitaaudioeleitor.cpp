#include "app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/ipc/cmessagequeue.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"

namespace vota {

CHabilitaAudioEleitor::~CHabilitaAudioEleitor() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddBuzz(51, 10);
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Este eleitor necessita de áudio", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Coloque o fone de ouvido na urna", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: continuar", api::SPoint{1, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CHabilitaAudioEleitor::CHabilitaAudioEleitor()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CHabilitaAudioEleitor& CHabilitaAudioEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CHabilitaAudioEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CHabilitaAudioEleitor> CHabilitaAudioEleitor::s_inst;
std::mutex CHabilitaAudioEleitor::s_mutex;

void CHabilitaAudioEleitor::StartState()
{
    CLogVota::GetInst().LogaPedidoConexaoFone();
    m_form->Slot2();
    m_pNextState = this;
}

void CHabilitaAudioEleitor::ProcessInput()
{
    const api::EInputResult resultado = m_form->Read();
    const bool audioCadastro = impl::IInformacaoThreadOperador::GetInst().IsAudioAtivadoCadastro();
    if (resultado == api::INPUT_CONFIRMA) {
        SetAudioAtivadoMesario(false);
        api::CPriorityMessageQueue<api::SMessage>& fila = CThreadEleitor::GetInst().GetMensagens();
        if (audioCadastro) {
            fila.Post(8);
        } else {
            fila.Post(9);
        }
        CThreadEleitor::GetInst().GetMensagens().Post(1);
        m_pNextState = &CMostraEleitorVotando::GetInst();
        if (audioCadastro) {
            CLogVota::GetInst().LogaAudioAtivadoConformeCadastro();
        }
    }
}

} // namespace vota
