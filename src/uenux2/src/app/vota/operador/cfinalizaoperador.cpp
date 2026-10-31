#include "app/vota/operador/cfinalizaoperador.h"

namespace vota {

CFinalizaOperador::CFinalizaOperador()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CFinalizaOperador& CFinalizaOperador::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CFinalizaOperador());
    }
    return *s_inst;
}

std::unique_ptr<CFinalizaOperador> CFinalizaOperador::s_inst;
std::mutex CFinalizaOperador::s_mutex;

} // namespace vota
