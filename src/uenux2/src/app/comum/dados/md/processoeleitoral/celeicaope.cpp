// Reconstruction notes: comum::md::CEleicaoPE's ValidaOrdem and GetCargos (target fns 3714 and 2257), on their records'
// lines 70 and 144. The constructor, with its ValidaNome and ValidaCargos, is inlined into fn 11371, which is not
// written; its records are lines 63, 79, 87 and 92. GetIDsCargos and PossuiCargoCandidato (fns 5654 and 5653) have no
// record: their file and their place, after GetCargos, are a choice
// (src/units/88-uenux2-app-comum-dados-md-processoeleitoral.mk says what the band shows).
#include "app/comum/dados/md/processoeleitoral/celeicaope.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 14-66: content not recovered)
#line 67
void CEleicaoPE::ValidaOrdem(std::set<uebyte>& ordens, uebyte ordem, const std::string& nome) const
{
    if (!ordens.insert(ordem).second) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8153, std::format("Ordem de {} com valor {} repetido", nome, ordem));
    }
}

// (original lines 74-140: content not recovered)
#line 141
const TVectorCargo& CEleicaoPE::GetCargos() const
{
    if (m_cargos.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8154, "Eleição não tem cargos definidos.");
    }
    return m_cargos;
}

std::set<TCargoID> CEleicaoPE::GetIDsCargos() const
{
    std::set<TCargoID> ids;
    for (size_t i = 0; i < m_cargos.size(); ++i) {
        ids.insert(m_cargos[i].GetID());
    }
    return ids;
}

bool CEleicaoPE::PossuiCargoCandidato() const
{
    for (size_t i = 0; i < m_cargos.size(); ++i) {
        if (m_cargos[i].HasDetalheCandidato()) {
            return true;
        }
    }
    return false;
}

} // namespace comum::md
