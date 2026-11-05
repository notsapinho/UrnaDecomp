#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatosporpartido.h"

namespace vota {

CMenuFiltrarCandidatosPorPartido::CMenuFiltrarCandidatosPorPartido()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CMenuFiltrarCandidatosPorPartido& CMenuFiltrarCandidatosPorPartido::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMenuFiltrarCandidatosPorPartido());
    }
    return *s_inst;
}

std::unique_ptr<CMenuFiltrarCandidatosPorPartido> CMenuFiltrarCandidatosPorPartido::s_inst;
std::mutex CMenuFiltrarCandidatosPorPartido::s_mutex;

} // namespace vota
