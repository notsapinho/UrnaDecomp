#include "app/vota/eleitor/caguardamensagem.h"

namespace vota {

CAguardaMensagem::CAguardaMensagem()
    : comum::CAppState(EVENTO_TECLA)
{
}

CAguardaMensagem& CAguardaMensagem::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CAguardaMensagem());
    }
    return *s_inst;
}

std::unique_ptr<CAguardaMensagem> CAguardaMensagem::s_inst;
std::mutex CAguardaMensagem::s_mutex;

void CAguardaMensagem::StartState()
{
    m_pNextState = this;
}

} // namespace vota
