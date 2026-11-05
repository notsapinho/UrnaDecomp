#include "app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.h"

#include <vector>

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenuvisualizarcandidatos.h"
#include "app/vota/euevotaerror.h"

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

void CVisualizarCandidatos::LimpaFiltros()
{
    m_cargo.reset();
    m_partido.reset();
    m_candidato.reset();
}

// (original lines 43-114: content not recovered)
#line 115
void CVisualizarCandidatos::StartState()
{
    m_pNextState = &CMenuVisualizarCandidatos::GetInst();
    std::vector<const comum::md::CCandidatura*> candidaturas;
    for (const comum::md::CCandidatura& candidatura : m_candidaturas) {
        if (m_candidato && *m_candidato != 0 && candidatura.GetCandidatoID() != *m_candidato) {
            continue;
        }
        if (m_cargo && *m_cargo != 0 && candidatura.GetCargoID() != *m_cargo) {
            continue;
        }
        if (m_partido && *m_partido != 0 && candidatura.GetPartidoID() != *m_partido) {
            continue;
        }
        candidaturas.push_back(&candidatura);
    }
    if (candidaturas.empty()) {
        throw CUeVotaError(EUE_VOTA_VISUALIZAR_CANDIDATOS_SEM_CANDIDATURA, "Nenhuma candidatura a ser exibida");
    }
    const size_t total = candidaturas.size();
    auto atual = candidaturas.begin();
    while (true) {
        const CFormInterativoTelaVota tela =
            CTelasVota::CriaTelaVisualizacaoCandidato(**atual, atual - candidaturas.begin() + 1, total);
        if (tela->GetEntradas().size() != 1) {
            throw CUeVotaError(EUE_VOTA_VISUALIZAR_CANDIDATOS_NUMERO_INPUTS_INVALIDO, "Número de inputs inválido");
        }
        tela->Slot2();
        const api::IInputField<api::IScreen>* campo = tela->GetEntradas().at(0);
        switch (tela->WaitAndRead()) {
        case api::INPUT_CORRIGE:
            return;
        case api::INPUT_SEM_TECLA:
            switch (campo->GetUltimaTecla()) {
            case '4':
                atual = atual == candidaturas.begin() ? candidaturas.end() - 1 : atual - 1;
                break;
            case '6':
                atual = atual == candidaturas.end() - 1 ? candidaturas.begin() : atual + 1;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

} // namespace vota
