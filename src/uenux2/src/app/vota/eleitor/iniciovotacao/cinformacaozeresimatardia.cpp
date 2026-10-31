#include "app/vota/eleitor/iniciovotacao/cinformacaozeresimatardia.h"

#include "api/gui/cinteractiveform.h"

namespace vota {

CInformacaoZeresimaTardia::~CInformacaoZeresimaTardia() = default;

void CInformacaoZeresimaTardia::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota
