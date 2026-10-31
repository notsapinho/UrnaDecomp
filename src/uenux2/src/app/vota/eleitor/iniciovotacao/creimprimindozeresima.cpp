#include "app/vota/eleitor/iniciovotacao/creimprimindozeresima.h"

namespace vota {

CReimprimindoZeresima::CReimprimindoZeresima()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CReimprimindoZeresima& CReimprimindoZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CReimprimindoZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CReimprimindoZeresima> CReimprimindoZeresima::s_inst;
std::mutex CReimprimindoZeresima::s_mutex;

} // namespace vota
