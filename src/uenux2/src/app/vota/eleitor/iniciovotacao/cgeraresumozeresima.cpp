#include "app/vota/eleitor/iniciovotacao/cgeraresumozeresima.h"

#include "app/vota/eleitor/iniciovotacao/cimprimindozeresima.h"

namespace vota {

CGeraResumoZeresima::CGeraResumoZeresima()
{
}

CGeraResumoZeresima& CGeraResumoZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CGeraResumoZeresima());
    }
    return *s_inst;
}

CGeraResumoZeresima::~CGeraResumoZeresima() = default;

std::unique_ptr<CGeraResumoZeresima> CGeraResumoZeresima::s_inst;
std::mutex CGeraResumoZeresima::s_mutex;

comum::CAppState* CGeraResumoZeresima::GetProximoEstado()
{
    return &CImprimindoZeresima::GetInst();
}

} // namespace vota
