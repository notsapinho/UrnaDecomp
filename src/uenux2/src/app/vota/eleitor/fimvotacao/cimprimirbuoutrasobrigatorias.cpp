#include "app/vota/eleitor/fimvotacao/cimprimirbuoutrasobrigatorias.h"

namespace vota {

CImprimirBUOutrasObrigatorias::CImprimirBUOutrasObrigatorias()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CImprimirBUOutrasObrigatorias& CImprimirBUOutrasObrigatorias::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImprimirBUOutrasObrigatorias());
    }
    return *s_inst;
}

std::unique_ptr<CImprimirBUOutrasObrigatorias> CImprimirBUOutrasObrigatorias::s_inst;
std::mutex CImprimirBUOutrasObrigatorias::s_mutex;

} // namespace vota
