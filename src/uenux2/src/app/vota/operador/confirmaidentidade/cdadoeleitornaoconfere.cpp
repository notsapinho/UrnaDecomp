#include "app/vota/operador/confirmaidentidade/cdadoeleitornaoconfere.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"

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

} // namespace vota
