#include "app/vota/eleitor/fimvotacao/cimprimindobim.h"

namespace vota {

CImprimindoBim::CImprimindoBim()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CImprimindoBim& CImprimindoBim::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImprimindoBim());
    }
    return *s_inst;
}

std::unique_ptr<CImprimindoBim> CImprimindoBim::s_inst;
std::mutex CImprimindoBim::s_mutex;

} // namespace vota
