#include "app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.h"

namespace vota {

CVisualizarCandidatos::CVisualizarCandidatos()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CVisualizarCandidatos::~CVisualizarCandidatos() = default;

CVisualizarCandidatos& CVisualizarCandidatos::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CVisualizarCandidatos());
    }
    return *s_inst;
}

std::unique_ptr<CVisualizarCandidatos> CVisualizarCandidatos::s_inst;
std::mutex CVisualizarCandidatos::s_mutex;

comum::md::TCargoID CVisualizarCandidatos::GetCargo() const
{
    return m_cargo.value_or(0);
}

















































































































} // namespace vota
