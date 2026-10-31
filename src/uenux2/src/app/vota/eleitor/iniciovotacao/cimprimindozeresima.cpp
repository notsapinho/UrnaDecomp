#include "app/vota/eleitor/iniciovotacao/cimprimindozeresima.h"

namespace vota {

CImprimindoZeresima::CImprimindoZeresima()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CImprimindoZeresima& CImprimindoZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImprimindoZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CImprimindoZeresima> CImprimindoZeresima::s_inst;
std::mutex CImprimindoZeresima::s_mutex;

} // namespace vota
