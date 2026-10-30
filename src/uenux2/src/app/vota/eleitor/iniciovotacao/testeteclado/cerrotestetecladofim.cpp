#include "app/vota/eleitor/iniciovotacao/testeteclado/cerrotestetecladofim.h"

#include "api/gui/iform.h"

namespace vota::testeteclado {

CErroTesteTecladoFim::~CErroTesteTecladoFim() = default;

void CErroTesteTecladoFim::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

} // namespace vota::testeteclado
