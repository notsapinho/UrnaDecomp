#include "app/comum/dados/cconfiguracaoeleicao.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/pattern/singleton.hpp"

namespace comum {

// (original lines 10-32: content not recovered)
#line 33
std::unique_ptr<CConfiguracaoEleicao> CConfiguracaoEleicao::s_instance;
std::mutex CConfiguracaoEleicao::s_mutex;

SINGLETON_IMPL_GET_INST(CConfiguracaoEleicao, s_mutex, s_instance)


CConfiguracaoEleicao::~CConfiguracaoEleicao() = default;

// (original lines 41-284: content not recovered)
#line 285
const md::CEleicaoPE& CConfiguracaoEleicao::GetEleicao(const TEleicaoID eleicao) const
{
    const md::TVectorEleicaoPE& eleicoes = m_pleito.GetEleicoes();
    for (size_t i = 0; i < eleicoes.size(); ++i) {
        if (eleicoes[i].GetID() == eleicao) {
            return eleicoes[i];
        }
    }
    throw CUeComumDadosError(EUE_COMUM_DADOS_7826, std::format("Eleição não encontrada {}", eleicao));
}

// (original lines 296-302: content not recovered)
#line 303
const md::CCargo& CConfiguracaoEleicao::GetCargo(const TCargoID cargo) const
{
    const md::TVectorEleicaoPE& eleicoes = m_pleito.GetEleicoes();
    for (size_t i = 0; i < eleicoes.size(); ++i) {
        const md::TVectorCargo& cargos = eleicoes[i].GetCargos();
        for (size_t j = 0; j < cargos.size(); ++j) {
            if (cargos[j].GetID() == cargo) {
                return cargos[j];
            }
        }
    }


    throw CUeComumDadosError(EUE_COMUM_DADOS_7827, std::format("Cargo não encontrado {}", cargo));
}

} // namespace comum
