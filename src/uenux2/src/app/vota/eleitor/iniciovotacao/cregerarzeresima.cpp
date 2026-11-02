#include "app/vota/eleitor/iniciovotacao/cregerarzeresima.h"

#include "app/vota/eleitor/iniciovotacao/cregeraresumozeresima.h"
#include "app/vota/eleitor/iniciovotacao/crelvotautil.h"

namespace vota {

CRegerarZeresima::CRegerarZeresima()
{
}

CRegerarZeresima& CRegerarZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CRegerarZeresima());
    }
    return *s_inst;
}

CRegerarZeresima::~CRegerarZeresima() = default;

std::unique_ptr<CRegerarZeresima> CRegerarZeresima::s_inst;
std::mutex CRegerarZeresima::s_mutex;

void CRegerarZeresima::AposGeracao()
{
    CRelVotaUtil::CortaPapel();
}

comum::CAppState* CRegerarZeresima::GetProximoEstado()
{
    return &CRegeraResumoZeresima::GetInst();
}

} // namespace vota
