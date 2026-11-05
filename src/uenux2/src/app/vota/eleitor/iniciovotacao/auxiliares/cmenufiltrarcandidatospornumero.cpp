#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.h"

namespace vota {

CMenuFiltrarCandidatosPorNumero::CMenuFiltrarCandidatosPorNumero()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CMenuFiltrarCandidatosPorNumero::~CMenuFiltrarCandidatosPorNumero() = default;

CMenuFiltrarCandidatosPorNumero& CMenuFiltrarCandidatosPorNumero::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMenuFiltrarCandidatosPorNumero());
    }
    return *s_inst;
}

std::unique_ptr<CMenuFiltrarCandidatosPorNumero> CMenuFiltrarCandidatosPorNumero::s_inst;
std::mutex CMenuFiltrarCandidatosPorNumero::s_mutex;

void CMenuFiltrarCandidatosPorNumero::StartState()
{
    m_form = TelaFiltragemCandidatosPorNumero(CVisualizarCandidatos::GetInst().GetCargo());
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota
