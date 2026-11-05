#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatosporpartido.h"

#include <any>
#include <set>

#include "api/gui/cinputmenufield.h"
#include "api/gui/cinteractiveform.h"
#include "api/hwil/iinput.h"
#include "api/pattern/cpolysingleton.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenuvisualizarcandidatos.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.h"

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


void CMenuFiltrarCandidatosPorPartido::StartState()
{
    const auto [form, selecao] = TelaFiltragemCandidatosPorPartido(CVisualizarCandidatos::GetInst().GetPartidos());
    form->Slot2();
    for (;;) {
        switch (selecao->Read(api::CPolySingleton<api::IInputKbd>::instance())) {
            case api::INPUT_CORRIGE:
                m_pNextState = &CMenuVisualizarCandidatos::GetInst();
                return;
            case api::INPUT_CONFIRMA: {
                const comum::TPartidoID partido =
                    std::any_cast<comum::TPartidoID>(selecao->GetItemSelecionado()->GetDado());
                CVisualizarCandidatos::GetInst().SetPartido(partido);
                return;
            }
            default:
                break;
        }
    }
}

} // namespace vota
