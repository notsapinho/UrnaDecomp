#include "app/vota/eleitor/curnainspecionada.h"

#include "api/gui/iform.h"
#include "app/vota/eleitor/caguardamensagem.h"

namespace vota {

CUrnaInspecionada::~CUrnaInspecionada() = default;

void CUrnaInspecionada::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
}

void CUrnaInspecionada::ProcessKey(uebyte tecla)
{
    if (tecla == 13) {
        m_formConfirmacao->Slot2();
        m_pNextState = &CAguardaMensagem::GetInst();
    }
}

} // namespace vota
