#include "app/vota/eleitor/iniciovotacao/creimprimindoresumozeresima.h"

namespace vota {

CReimprimindoResumoZeresima::CReimprimindoResumoZeresima()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CReimprimindoResumoZeresima& CReimprimindoResumoZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CReimprimindoResumoZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CReimprimindoResumoZeresima> CReimprimindoResumoZeresima::s_inst;
std::mutex CReimprimindoResumoZeresima::s_mutex;

} // namespace vota
