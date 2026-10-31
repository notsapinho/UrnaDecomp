#include "app/vota/eleitor/iniciovotacao/cregeraresumozeresima.h"

#include "app/vota/eleitor/iniciovotacao/creimprimindozeresima.h"

namespace vota {

CRegeraResumoZeresima::CRegeraResumoZeresima()
{
}

CRegeraResumoZeresima& CRegeraResumoZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CRegeraResumoZeresima());
    }
    return *s_inst;
}

CRegeraResumoZeresima::~CRegeraResumoZeresima() = default;

std::unique_ptr<CRegeraResumoZeresima> CRegeraResumoZeresima::s_inst;
std::mutex CRegeraResumoZeresima::s_mutex;

comum::CAppState* CRegeraResumoZeresima::GetProximoEstado()
{
    return &CReimprimindoZeresima::GetInst();
}

} // namespace vota
