#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatosporcargo.h"

#include <any>

#include "api/gui/cinputmenufield.h"
#include "api/gui/cinteractiveform.h"
#include "api/hwil/iinput.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenuvisualizarcandidatos.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.h"

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

// (original lines 34-37: content not recovered)
#line 38
void CMenuFiltrarCandidatosPorCargo::StartState()
{
    const bool todos = m_pNextState != &CMenuFiltrarCandidatosPorNumero::GetInst();
    const auto [form, selecao] = TelaFiltragemCandidatosPorCargo(todos, CVisualizarCandidatos::GetInst().GetCargos());
    form->Slot2();
    for (;;) {
        switch (selecao->Read(api::CPolySingleton<api::IInputKbd>::instance())) {
            case api::INPUT_CORRIGE:
                m_pNextState = &CMenuVisualizarCandidatos::GetInst();
                return;
            case api::INPUT_CONFIRMA: {
                const comum::md::TCargoID cargo =
                    std::any_cast<comum::md::TCargoID>(selecao->GetItemSelecionado()->GetDado());
                CVisualizarCandidatos::GetInst().SetCargo(cargo);
                return;
            }
            default:
                break;
        }
    }
}

} // namespace vota
