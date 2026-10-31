#include "app/vota/eleitor/iniciovotacao/testeteclado/cesperaretestar.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/cthreadeleitor.h"

namespace vota::testeteclado {

namespace {

api::CDateTime s_fimEspera(0);

} // namespace

CEsperaRetestar::~CEsperaRetestar() = default;

void CEsperaRetestar::StartState()
{
    m_segundosEspera += 5;
    m_pNextState = this;
    s_fimEspera = api::CDateTime::Now() + m_segundosEspera;
    CThreadEleitor::GetInst().StartTick(m_tickEspera);
    m_form->Slot2();
}

} // namespace vota::testeteclado
