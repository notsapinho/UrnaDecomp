// vota::CPedeIdentidade (the records' file). The reconstruction's notes are in cpedeidentidade.h and
// src/units/161-uenux2-app-vota-operador-identidade.mk.
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/iform.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CPedeIdentidade::~CPedeIdentidade() = default;






















































void CPedeIdentidade::FinishState()
{
    CThreadOperador::GetInst().StopTick(m_tickIdentidade);
    CThreadOperador::GetInst().StopTick(m_tickEspera);
    CThreadOperador::GetInst().StopTick(m_tickAviso);
}

} // namespace vota
