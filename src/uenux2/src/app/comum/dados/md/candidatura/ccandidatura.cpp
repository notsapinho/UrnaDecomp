#include "app/comum/dados/md/candidatura/ccandidatura.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 9-29: content not recovered)
#line 30
CCandidatura::CCandidatura(const TCargoID cargo, const TPartidoID partido, const TCandidatoID candidato,
    const CDadosCandidato& titular, const std::vector<CDadosCandidato>& suplentes)
    : m_cargo(cargo), m_partido(partido), m_candidato(candidato), m_titular(titular), m_suplentes(suplentes)
{


    if (m_cargo >= 100) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7991, "Número do cargo inválido");
    }
    if (m_partido >= 100) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7992, "Partido inválido");
    }
    if (m_candidato >= 100000) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7993, "Número do candidato inválido");
    }
    if (m_titular.GetOrdem() != 0) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7994, "Titular é suplente");
    }
    if (m_suplentes.size() > 9) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7995, "Quantidade de suplentes inválida");
    }
    for (size_t i = 0; i < m_suplentes.size(); ++i) {
        const signed char ordem = m_suplentes[i].GetOrdem();

        if (ordem != static_cast<signed char>(i + 1)) {
            throw CUeComumDadosError(EUE_COMUM_DADOS_7996,
                std::format("Ordem de suplente errada ({} [{}])", ordem, m_suplentes.at(i).GetNomeUrna()));
        }
    }
}


const CDadosCandidato& CCandidatura::GetSuplente(uebyte ordem) const
{
    if (ordem == 0 || ordem > m_suplentes.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7997, std::format("Suplente inexistente: {}", ordem));
    }
    return m_suplentes[ordem - 1];
}

} // namespace comum::md
