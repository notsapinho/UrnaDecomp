#include "app/vota/eleitor/fimvotacao/ciniciobu.h"

namespace vota {

CInicioBU::CInicioBU()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CInicioBU& CInicioBU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CInicioBU());
    }
    return *s_inst;
}

std::unique_ptr<CInicioBU> CInicioBU::s_inst;
std::mutex CInicioBU::s_mutex;

} // namespace vota
