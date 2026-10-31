#include "app/vota/eleitor/cdefinerotaposreinicio.h"

namespace vota {

CDefineRotaPosReinicio::CDefineRotaPosReinicio()
    : comum::CAppState(EVENTO_TECLA | EVENTO_ENTRADA | EVENTO_TICK)
    , m_pEstado(nullptr)
{
}

CDefineRotaPosReinicio& CDefineRotaPosReinicio::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CDefineRotaPosReinicio());
    }
    return *s_inst;
}

std::unique_ptr<CDefineRotaPosReinicio> CDefineRotaPosReinicio::s_inst;
std::mutex CDefineRotaPosReinicio::s_mutex;

void CDefineRotaPosReinicio::StartState()
{
    m_pNextState = this;
}

void CDefineRotaPosReinicio::ProcessInput()
{
    if (m_pEstado != nullptr) {
        m_pEstado->ProcessInput();
    }
}

} // namespace vota
