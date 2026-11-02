#include "app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "api/ipc/cmessagequeue.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"

namespace vota {

CHabilitaAudioEleitor::~CHabilitaAudioEleitor() = default;

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

// <stubs>
// f2743 · 882 B · unmatched · placement: link order · name unknown
// ? f2743() { ... }
// </stubs>
