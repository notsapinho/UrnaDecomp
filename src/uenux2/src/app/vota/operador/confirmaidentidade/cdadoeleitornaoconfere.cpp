#include "app/vota/operador/confirmaidentidade/cdadoeleitornaoconfere.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"
#include "app/vota/operador/confirmaidentidade/cverificadadoeleitor.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CDadoEleitorNaoConfere::~CDadoEleitorNaoConfere() = default;

void CDadoEleitorNaoConfere::StartState()
{
    m_pNextState = this;
    if (CControlaReconhecimento::AtingiuLimiteVerificacoes()) {
        m_formLimite->Slot2();
    } else {
        m_form->Slot2();
    }
}

void CDadoEleitorNaoConfere::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        if (CControlaReconhecimento::AtingiuLimiteVerificacoes()) {
            CLogVota::GetInst().LogaHabilitacaoCanceladaConfirmacaoDado();
            m_pNextState = &CPedeIdentidade::GetInst();
        } else {
            CControlaReconhecimento::AvancaVerificacao();
            m_pNextState = &CVerificaDadoEleitor::GetInst();
        }
    }
}

} // namespace vota
