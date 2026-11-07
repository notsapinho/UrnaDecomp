#include "app/comum/dados/cconfiguracaoeleicao.h"

#include <algorithm>
#include <format>

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/pattern/singleton.hpp"

namespace comum {

// (original lines 11-32: content not recovered)
#line 33
std::unique_ptr<CConfiguracaoEleicao> CConfiguracaoEleicao::s_instance;
std::mutex CConfiguracaoEleicao::s_mutex;

SINGLETON_IMPL_GET_INST(CConfiguracaoEleicao, s_mutex, s_instance)


CConfiguracaoEleicao::~CConfiguracaoEleicao() = default;

std::vector<md::TEleicaoID> CConfiguracaoEleicao::GetIDsEleicoes() const
{
    std::vector<md::TEleicaoID> ids;
    for (const md::CEleicaoPE& eleicao : m_pleito.GetEleicoes()) {
        ids.push_back(eleicao.GetID());
    }
    return ids;
}

namespace {

bool ComparaOrdemImpressao(const md::CCargo& a, const md::CCargo& b)
{
    return a.GetOrdemImpressao() < b.GetOrdemImpressao();
}

} // namespace

std::vector<md::CCargo> CConfiguracaoEleicao::GetCargos(const TEleicaoID eleicao, const bool ordenados) const
{
    if (m_pleito.ExisteEleicao(eleicao)) {
        std::vector<md::CCargo> cargos = m_pleito.GetEleicao(eleicao).GetCargos();
        if (ordenados) {
            std::vector<md::CCargo> resultado = cargos;
            std::sort(resultado.begin(), resultado.end(), ComparaOrdemImpressao);
            return resultado;
        }
        return cargos;
    }
    return {};
}

std::vector<CCargos::TCargoEleicao> CConfiguracaoEleicao::GetCargosEleicoes() const
{
    std::vector<CCargos::TCargoEleicao> cargos;
    for (const md::CEleicaoPE& eleicao : m_pleito.GetEleicoes()) {
        for (const md::CCargo& cargo : eleicao.GetCargos()) {
            cargos.push_back({eleicao.GetID(), cargo.GetID()});
        }
    }
    return cargos;
}

std::vector<md::CCargo> CConfiguracaoEleicao::GetTodosCargos() const
{
    std::vector<md::CCargo> cargos;
    for (const md::CEleicaoPE& eleicao : m_pleito.GetEleicoes()) {
        for (const md::CCargo& cargo : eleicao.GetCargos()) {
            cargos.push_back(cargo);
        }
    }
    return cargos;
}

// (original lines 95-284: content not recovered)
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

const md::CSituacoesEleicoes& CConfiguracaoEleicao::GetSituacoesEleicoes(const TEleicaoID eleicao) const
{
    return m_pleito.GetSituacoesEleicoes(eleicao);
}

} // namespace comum
