#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenuvisualizarcandidatos.h"

#include <any>

#include "api/gui/cinputmenufield.h"
#include "api/gui/cinteractiveform.h"
#include "api/hwil/iinput.h"
#include "api/pattern/cpolysingleton.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatosporcargo.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatosporpartido.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.h"
#include "app/vota/log/clogvota.h"

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

// (original lines 36-42: content not recovered)
#line 43
void CMenuVisualizarCandidatos::StartState()
{
    CLogVota::GetInst().loga("Opção de visualização de candidatos selecionada");
    comum::CAppState* const porCargo = &CMenuFiltrarCandidatosPorCargo::GetInst();
    comum::CAppState* const porPartido = &CMenuFiltrarCandidatosPorPartido::GetInst();
    comum::CAppState* const porNumero = &CMenuFiltrarCandidatosPorNumero::GetInst();
    const TOpcaoMenuCandidatos opcaoCargo(porCargo, porPartido);
    const TOpcaoMenuCandidatos opcaoPartido(porPartido, porCargo);
    const TOpcaoMenuCandidatos opcaoNumero(porCargo, porNumero);
    const auto [form, menuFiltro] = TelaMenuVisualizacaoCandidatos(opcaoCargo, opcaoPartido, opcaoNumero);
    for (;;) {
        form->Slot2();
        switch (menuFiltro->Read(api::CPolySingleton<api::IInputKbd>::instance())) {
            case api::INPUT_CONFIRMA: {
                const auto [primeiro, segundo] =
                    std::any_cast<TOpcaoMenuCandidatos>(menuFiltro->GetItemSelecionado()->GetDado());
                SetNextState(primeiro);
                m_pNextState->SetNextState(segundo);
                segundo->SetNextState(&CVisualizarCandidatos::GetInst());
                CVisualizarCandidatos::GetInst().LimpaFiltros();
                return;
            }
            case api::INPUT_CORRIGE:
                m_pNextState = &CMaisInformacoes::GetInst();
                return;
            default:
                break;
        }
    }
}

} // namespace vota
