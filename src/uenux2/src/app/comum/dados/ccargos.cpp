// Reconstruction notes: comum::CCargos's GetInst, Next, GetCurrent, GetCurrentCargoID, GetCurrentEleicao and
// GetCurrentEleicaoID (target fns 273, 1708, 332, 1938, 2836 and 2835), each throw on its record's line, with Reset and
// IsFim (fns 2269 and 602), and the free NomeEleicaoCorrente (fn 11556), which has no record: its line, after the last
// record's, is a choice (src/units/88-uenux2-app-comum-dados-md-processoeleitoral.mk says what the band shows). The lines
// left blank hold the file's other members, whose records are lines 25, 93 and 249.
#include "app/comum/dados/ccargos.h"

#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/pattern/singleton.hpp"
namespace comum {

// (original lines 13-23: content not recovered)
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

// <stubs>
// f5604 · 22805 B · unmatched · name unknown
// void f5604(i32, i32, i32) { ... }
// </stubs>






































































































































































std::string NomeEleicaoCorrente()
{
    return CCargos::GetInst().GetCurrentEleicao().GetNome();
}

} // namespace comum
