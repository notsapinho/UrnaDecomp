#include "app/vota/eleitor/comum/ctelascargo.h"

#include <algorithm>
#include <format>

#include "app/vota/euevotaerror.h"

namespace vota {

// (original lines 10-19: content not recovered)
#line 20
std::string NomeTela(const ETelaVotacao tela)
{
    switch (tela) {
    case ETelaVotacao::TELA_INICIAL:
        return "Tela Inicial";
    case ETelaVotacao::TELA_COMPLETA:
        return "Tela Completa";
    case ETelaVotacao::TELA_CONFERENCIA_VOTO_NOMINAL:
        return "Tela de Conferência de Voto Nominal";
    case ETelaVotacao::TELA_VOTO_BRANCO:
        return "Tela de Voto Branco";
    case ETelaVotacao::TELA_CONFERENCIA_VOTO_BRANCO:
        return "Tela de Conferência de Voto Branco";
    case ETelaVotacao::TELA_VOTO_PROPORCIONAL_NULO_INCOMPLETO:
        return "Tela de Voto Proporcional Nulo Incompleto";
    case ETelaVotacao::TELA_VOTO_NULO:
        return "Tela de Voto Nulo";
    case ETelaVotacao::TELA_CONFERENCIA_VOTO_NULO:
        return "Tela de Conferência de Voto Nulo";
    case ETelaVotacao::TELA_PARTIDO:
        return "Tela de Partido";
    case ETelaVotacao::TELA_VOTO_LEGENDA_INCOMPLETO:
        return "Tela de Voto Legenda Incompleto";
    case ETelaVotacao::TELA_CONFERENCIA_VOTO_LEGENDA:
        return "Tela de Conferência de Voto Legenda";
    case ETelaVotacao::TELA_CANDIDATO_INEXISTENTE:
        return "Tela de Candidato Inexistente";
    case ETelaVotacao::TELA_CONFERENCIA_CANDIDATO_INEXISTENTE:
        return "Tela de Conferência de Candidato Inexistente";
    case ETelaVotacao::TELA_CANDIDATO_INAPTO:
        return "Tela de Candidato Inapto";
    case ETelaVotacao::TELA_CONFERENCIA_CANDIDATO_INAPTO:
        return "Tela de Conferência de Candidato Inapto";
    case ETelaVotacao::TELA_CANDIDATO_REPETIDO:
        return "Tela de Candidato Repetido";
    case ETelaVotacao::TELA_CONFERENCIA_CANDIDATO_REPETIDO:
        return "Tela de Conferência de Candidato Repetido";
    case ETelaVotacao::TELA_CARGO_SEM_CANDIDATO:
        return "Tela de Cargo sem Candidato";
    }
    throw CUeVotaError(EUE_VOTA_TELA_INVALIDA, std::format("Tela inválida {}", static_cast<int>(tela)));
}

CTelasCargo::CTelasCargo(const comum::TCargoID id, const TMapa& telas) : m_id(id), m_telas(telas)
{
    const std::string prefixo = std::format("Cargo {} ", id);
    if (m_telas.empty()) {
        throw CUeVotaError(EUE_VOTA_CARGO_SEM_TELAS, prefixo + "não foi passada nenhuma tela");
    }
    const auto nula = std::find_if(m_telas.begin(), m_telas.end(),
                                   [](const TMapa::value_type& par) { return !par.second; });
    if (nula != m_telas.end()) {
        throw CUeVotaError(EUE_VOTA_CARGO_TELA_NULA, prefixo + "tela nula [" + NomeTela(nula->first) + "]");
    }
}

CFormInterativoTelaVota CTelasCargo::GetTela(const ETelaVotacao tela) const
{
    const auto it = m_telas.find(tela);
    if (it == m_telas.end()) {
        throw CUeVotaError(EUE_VOTA_CARGO_NAO_POSSUI_TELA,
                           std::format("Cargo {} não possui [{}]", m_id, NomeTela(tela)));
    }
    return it->second;
}





} // namespace vota
