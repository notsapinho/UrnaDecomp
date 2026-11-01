#include "app/vota/eleitor/iniciovotacao/cgerazeresima.h"

#include "app/vota/eleitor/iniciovotacao/cgeraresumozeresima.h"

namespace vota {

CGeraZeresima::CGeraZeresima()
{
}

CGeraZeresima& CGeraZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CGeraZeresima());
    }
    return *s_inst;
}

CGeraZeresima::~CGeraZeresima() = default;

std::unique_ptr<CGeraZeresima> CGeraZeresima::s_inst;
std::mutex CGeraZeresima::s_mutex;

comum::CAppState* CGeraZeresima::GetProximoEstado()
{
    return &CGeraResumoZeresima::GetInst();
}

} // namespace vota
