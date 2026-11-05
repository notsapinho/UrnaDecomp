#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatosporcargo.h"

namespace vota {

CMenuFiltrarCandidatosPorCargo::CMenuFiltrarCandidatosPorCargo()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CMenuFiltrarCandidatosPorCargo& CMenuFiltrarCandidatosPorCargo::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMenuFiltrarCandidatosPorCargo());
    }
    return *s_inst;
}

std::unique_ptr<CMenuFiltrarCandidatosPorCargo> CMenuFiltrarCandidatosPorCargo::s_inst;
std::mutex CMenuFiltrarCandidatosPorCargo::s_mutex;

} // namespace vota
