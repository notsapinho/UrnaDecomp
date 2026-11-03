// Reconstruction notes: comum::CCargos's GetInst, Next, GetCurrent, GetCurrentCargoID, GetCurrentEleicao,
// GetCurrentEleicaoID (273, 1708, 332, 1938, 2836, 2835) and FiltraPorAbrangencia (in 7377), each throw on its record's
// line, with Reset and IsFim (2269, 602), RemoveFiltro (3784), OrdenaPorAquisicao (in 7377), OrdenaPorImpressao (3782),
// the comparators at table slots 2357 and 2358 (11559, 11558), the free NomeEleicaoCorrente (11556) and
// GetCurrentEleicaoVersaoPacote (record 93, inlined into fn 5604). Line 25 is a record of a member not written; where
// the members with no record start is chosen, in the order the use bands give (unit 88's fragment).
#include "app/comum/dados/ccargos.h"

#include <algorithm>
#include <format>

#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "app/comum/dados/md/processoeleitoral/csituacoeseleicoes.h"
#include "ecourna/api/pattern/singleton.hpp"
namespace comum {

// (original lines 18-23: content not recovered)
#line 24
SINGLETON_IMPL_GET_INST(CCargos, s_mutex, s_instancia)

std::unique_ptr<CCargos> CCargos::s_instancia;
std::mutex CCargos::s_mutex;

// (original lines 29-35: content not recovered)
#line 36
void CCargos::Reset()
{
    m_atual = 0;
}

CCargos::~CCargos() = default;

void CCargos::Next()
{
    if (m_atual == m_cargos.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7815, "Operação inválida.");
    }
    ++m_atual;
}


bool CCargos::IsFim() const
{
    return m_atual >= m_cargos.size();
}
const md::CCargo& CCargos::GetCurrent() const
{
    if (m_atual >= m_cargos.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7816, "Cargo não posicionado.");
    }
    const TCargoID cargo = m_cargos[m_atual].second;
    return CConfiguracaoEleicao::GetInst().GetCargo(cargo);
}

comum::TCargoID CCargos::GetCurrentCargoID() const
{
    if (m_atual >= m_cargos.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7817, "Cargo não posicionado.");
    }
    return m_cargos[m_atual].second;
}

const md::CEleicaoPE& CCargos::GetCurrentEleicao() const
{
    if (m_atual >= m_cargos.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7818, "Cargo não posicionado.");
    }
    const TEleicaoID eleicao = m_cargos[m_atual].first;
    return CConfiguracaoEleicao::GetInst().GetEleicao(eleicao);
}

comum::TEleicaoID CCargos::GetCurrentEleicaoID() const
{
    if (m_atual >= m_cargos.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7819, "Cargo não posicionado.");
    }
    return m_cargos[m_atual].first;
}

std::string CCargos::GetCurrentEleicaoVersaoPacote() const
{
    if (m_atual >= m_cargos.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7820, "Cargo não posicionado.");
    }
    const TEleicaoID eleicao = m_cargos[m_atual].first;
    return CConfiguracaoEleicao::GetInst().GetPleito().GetVersaoPacoteEleicao(eleicao);
}

// (original lines 99-109: content not recovered)
#line 110
std::map<TCargoID, md::CCargo> CCargos::GetMapaCargos() const
{
    const std::vector<TCargoEleicao>::const_iterator fim = m_todos.end();
    std::map<TCargoID, md::CCargo> cargos;
    for (std::vector<TCargoEleicao>::const_iterator item = m_todos.begin(); item != fim; ++item) {
        const md::CCargo& cargo = CConfiguracaoEleicao::GetInst().GetCargo(item->second);
        cargos.insert({cargo.GetID(), cargo});
    }
    return cargos;
}

// (original lines 121-204: content not recovered)
#line 205
void CCargos::RemoveFiltro()
{
    m_cargos = m_todos;
}

// (original lines 210-228: content not recovered)
#line 229
void CCargos::FiltraPorAbrangencia(md::ETipoAbrangencia abrangencia)
{
    std::vector<TCargoEleicao> cargos;
    if (abrangencia == md::ABRANGENCIA_MUNICIPAL) {
        cargos = m_todos;
    } else for (const auto& item : m_todos) {
        const md::CCargo& cargo = CConfiguracaoEleicao::GetInst().GetCargo(item.second);
        switch (abrangencia) {
        case md::ABRANGENCIA_FEDERAL:
            if (cargo.GetAbrangencia() == md::ABRANGENCIA_FEDERAL) {
                cargos.push_back({item.first, cargo.GetID()});
            }
            break;
        case md::ABRANGENCIA_ESTADUAL:
            if (cargo.GetAbrangencia() == md::ABRANGENCIA_ESTADUAL ||
                cargo.GetAbrangencia() == md::ABRANGENCIA_FEDERAL) {
                cargos.push_back({item.first, cargo.GetID()});
            }
            break;
        default:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7821,
                                     std::format("Tipo de abrangência inválido: {}", static_cast<int>(abrangencia)));
        }
    }
    m_cargos = cargos;
}

namespace {

bool ComparaOrdemAquisicao(const CCargos::TCargoEleicao& primeiro, const CCargos::TCargoEleicao& segundo)
{
    const uebyte eleicaoPrimeiro =
        CConfiguracaoEleicao::GetInst().GetSituacoesEleicoes(primeiro.first).GetOrdemAquisicao();
    const uebyte eleicaoSegundo =
        CConfiguracaoEleicao::GetInst().GetSituacoesEleicoes(segundo.first).GetOrdemAquisicao();
    const int ordem = eleicaoPrimeiro < eleicaoSegundo ? -1 : (eleicaoPrimeiro > eleicaoSegundo ? 1 : 0);
    switch (ordem) {
    case -1:
        return true;
    case 1:
        return false;
    default:
        break;
    }
    const md::CCargo& cargoPrimeiro = CConfiguracaoEleicao::GetInst().GetCargo(primeiro.second);
    const md::CCargo& cargoSegundo = CConfiguracaoEleicao::GetInst().GetCargo(segundo.second);
    return cargoPrimeiro.GetOrdemAquisicao() < cargoSegundo.GetOrdemAquisicao();
}

bool ComparaOrdemImpressao(const CCargos::TCargoEleicao& primeiro, const CCargos::TCargoEleicao& segundo)
{
    const uebyte eleicaoPrimeiro =
        CConfiguracaoEleicao::GetInst().GetSituacoesEleicoes(primeiro.first).GetOrdemImpressao();
    const uebyte eleicaoSegundo =
        CConfiguracaoEleicao::GetInst().GetSituacoesEleicoes(segundo.first).GetOrdemImpressao();
    const int ordem = eleicaoPrimeiro < eleicaoSegundo ? -1 : (eleicaoPrimeiro > eleicaoSegundo ? 1 : 0);
    switch (ordem) {
    case -1:
        return true;
    case 1:
        return false;
    default:
        break;
    }
    const md::CCargo& cargoPrimeiro = CConfiguracaoEleicao::GetInst().GetCargo(primeiro.second);
    const md::CCargo& cargoSegundo = CConfiguracaoEleicao::GetInst().GetCargo(segundo.second);
    return cargoPrimeiro.GetOrdemImpressao() < cargoSegundo.GetOrdemImpressao();
}

} // namespace

void CCargos::OrdenaPorAquisicao()
{
    std::sort(m_cargos.begin(), m_cargos.end(), ComparaOrdemAquisicao);
    Reset();
}

void CCargos::OrdenaPorImpressao()
{
    std::sort(m_cargos.begin(), m_cargos.end(), ComparaOrdemImpressao);
    Reset();
}

std::string NomeEleicaoCorrente()
{
    return CCargos::GetInst().GetCurrentEleicao().GetNome();
}

} // namespace comum
