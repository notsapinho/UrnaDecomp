#include "app/vota/eleitor/ciniciodeciclo.h"

namespace vota {

CIniciodeCiclo::CIniciodeCiclo()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CIniciodeCiclo& CIniciodeCiclo::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CIniciodeCiclo());
    }
    return *s_inst;
}

std::unique_ptr<CIniciodeCiclo> CIniciodeCiclo::s_inst;
std::mutex CIniciodeCiclo::s_mutex;

} // namespace vota
