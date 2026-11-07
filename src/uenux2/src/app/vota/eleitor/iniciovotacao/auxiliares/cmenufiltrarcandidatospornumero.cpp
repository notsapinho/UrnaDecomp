#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.h"

#include "api/gui/capplication.h"
#include "api/gui/cinteractiveform.h"
#include "api/util/cwait.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenuvisualizarcandidatos.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.h"
#include "ecourna/api/util/cstringutils.hpp"

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

void CMenuFiltrarCandidatosPorNumero::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA: {
        const comum::TCandidatoID numero =
            ecourna::api::util::CStringUtils::ToInt32(m_form->GetEntradas().at(0)->GetTexto());
        const comum::md::TCargoID cargo = CVisualizarCandidatos::GetInst().GetCargo();
        if (comum::CCandidaturas::GetInst().Busca(cargo, numero) != nullptr) {
            CVisualizarCandidatos::GetInst().SetCandidato(numero);
            m_pNextState = &CVisualizarCandidatos::GetInst();
            break;
        }
        auto& form = *m_form;
        for (auto* entrada : form.GetEntradas()) {
            entrada->Clear();
        }
        form.SetFocus(0);
        api::MostraMensagemTemporaria("Candidato não encontrado!", api::CWait(2000));
        break;
    }
    case api::INPUT_CORRIGE:
        m_pNextState = &CMenuVisualizarCandidatos::GetInst();
        break;
    default:
        m_pNextState = this;
        break;
    }
}

} // namespace vota
