#include "app/vota/eleitor/cinspecionaurna.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CInspecionaUrna::~CInspecionaUrna() = default;

void CInspecionaUrna::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
    CLogVota::GetInst().LogaInspecaoIniciada();
}

} // namespace vota
