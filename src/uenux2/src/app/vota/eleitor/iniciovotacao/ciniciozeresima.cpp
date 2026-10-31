#include "app/vota/eleitor/iniciovotacao/ciniciozeresima.h"

namespace vota {

CInicioZeresima::CInicioZeresima()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CInicioZeresima& CInicioZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CInicioZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CInicioZeresima> CInicioZeresima::s_inst;
std::mutex CInicioZeresima::s_mutex;

} // namespace vota
