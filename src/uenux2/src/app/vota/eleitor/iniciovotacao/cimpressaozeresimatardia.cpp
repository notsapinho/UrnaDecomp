#include "app/vota/eleitor/iniciovotacao/cimpressaozeresimatardia.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CImpressaoZeresimaTardia::~CImpressaoZeresimaTardia() = default;

void CImpressaoZeresimaTardia::StartState()
{
    CLogVota::GetInst().LogaMesarioIndagadoHorarioUrna();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota
