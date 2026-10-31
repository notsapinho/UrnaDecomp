#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenuvisualizarcandidatos.h"

namespace vota {

CMenuVisualizarCandidatos::CMenuVisualizarCandidatos()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CMenuVisualizarCandidatos& CMenuVisualizarCandidatos::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMenuVisualizarCandidatos());
    }
    return *s_inst;
}

std::unique_ptr<CMenuVisualizarCandidatos> CMenuVisualizarCandidatos::s_inst;
std::mutex CMenuVisualizarCandidatos::s_mutex;

} // namespace vota
