// Reconstruction notes, not TSE's text: the file-static GetNomeCargoComGenero (target fn 5803) and
// GetNomeAbreviadoCargo (inlined into fn 2268), CCargoDSNome's call operator (inlined into fn 11247),
// CCargoDSNomeSexoCandidato's (fn 2268) and CCargoDSLabelRelatorio's three labels (fns 5802, 11555, 5801), each throw on
// its record's line. The blank lines hold what is not recovered. src/units/129-uenux2-ccargods.mk says what the bytes
// decide.
#include "app/comum/dados/ccargods.h"

#include <format>

#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccandidaturasds.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum {

namespace {

// (original lines 19-20: content not recovered)
#line 21
std::string GetNomeCargoComGenero(const std::string& funcao, md::CSexo::ESexo sexo, uebyte suplente)
{
    const CCargos& cargos = CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7806, std::format("O cargo não foi posicionado corretamente para {}", funcao));
    }
    if (suplente == 0) {
        return cargos.GetCurrent().GetNome(sexo);
    }
    return cargos.GetCurrent().GetNomeSuplente(suplente, sexo);
}

// (original lines 33-36: content not recovered)
#line 37
std::string GetNomeAbreviadoCargo(const std::string& funcao, uebyte suplente)
{
    const CCargos& cargos = CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7807, std::format("O cargo não foi posicionado corretamente para {}", funcao));
    }
    const md::CCargo& cargo = cargos.GetCurrent();
    if (suplente == 0) {
        return cargo.GetNomeAbreviado();
    }
    return cargo.GetDetalheCandidato().GetSuplente(suplente).GetNomes().GetNomeAbreviado();
}

} // namespace

std::string CCargoDSNome::operator()() const
{
    return GetNomeCargoComGenero(__PRETTY_FUNCTION__, m_sexo, 0);
}

// (original lines 57-60: content not recovered)
#line 61
std::string CCargoDSNomeSexoCandidato::operator()() const
{
    const CCandidaturas& candidaturas = CCandidaturas::GetInst();
    if (candidaturas.IsFim()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7808, "O candidato não foi posicionado corretamente");
    }


    const CCargos& cargos = CCargos::GetInst();

    if (cargos.IsFim()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7809, "O cargo não foi posicionado corretamente");
    }

    // (original lines 75-76: content not recovered)
#line 77
    if (candidaturas.GetCurrent()->GetCargoID() != cargos.GetCurrent().GetID()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7810, "Cargo e candidato não foram posicionados corretamente");
    }

    const CCandidaturasDSSexo fonteSexo(m_suplente);
    const md::CSexo::ESexo sexo = fonteSexo();
    const std::string nome = GetNomeCargoComGenero(__PRETTY_FUNCTION__, sexo, m_suplente);
    if (m_abreviaNomeLongo && nome.size() >= 19) {
        return GetNomeAbreviadoCargo(__PRETTY_FUNCTION__, m_suplente);
    }
    return nome;
}

// (original lines 90-93: content not recovered)
#line 94
std::string CCargoDSLabelRelatorio::HeaderDetalhe()
{
    const CCargos& cargos = CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7811, "O cargo não foi posicionado corretamente");
    }
    if (cargos.GetCurrent().IsConsulta()) {
        return "Resposta                Num resp Votos";
    }
    return "Nome do candidato       Num cand Votos";
}

// (original lines 106-108: content not recovered)
#line 109
std::string CCargoDSLabelRelatorio::HeaderDetalheZE()
{
    const CCargos& cargos = CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7812, "O cargo não foi posicionado corretamente");
    }
    if (cargos.GetCurrent().IsConsulta()) {
        return "Resposta                      Num resp";
    }
    return "Nome do candidato             Num cand";
}

// (original lines 121-123: content not recovered)
#line 124
std::string CCargoDSLabelRelatorio::TotalVotoNominal()
{
    const CCargos& cargos = CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7813, "O cargo não foi posicionado corretamente");
    }
    if (cargos.GetCurrent().IsConsulta()) {
        return "Total de votos Válidos            {:04}\n";
    }
    return "Total de votos Nominais           {:04}\n";
}

} // namespace comum
