#include "app/vota/operador/csincronismooperador.h"

namespace vota {

CSincronismoOperador::CSincronismoOperador()
    : comum::CAppState(EVENTO_TECLA)
    , m_bSincronizado(false)
{
}

CSincronismoOperador& CSincronismoOperador::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CSincronismoOperador());
    }
    return *s_inst;
}

std::unique_ptr<CSincronismoOperador> CSincronismoOperador::s_inst;
std::mutex CSincronismoOperador::s_mutex;

} // namespace vota
