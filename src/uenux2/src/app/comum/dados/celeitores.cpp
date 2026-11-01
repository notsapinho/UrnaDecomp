#include "app/comum/dados/celeitores.h"

#include <algorithm>
#include <format>

#include "app/comum/asn/util.h"
#include "app/comum/dados/celeitordadoshabilitacao.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/pattern/singleton.hpp"

namespace comum {

// (original lines 13-40: content not recovered)
#line 41
std::unique_ptr<CEleitores> CEleitores::s_instance;
std::mutex CEleitores::s_mutex;

SINGLETON_IMPL_GET_INST(CEleitores, s_mutex, s_instance)

CEleitores::~CEleitores() = default;

// (original lines 48-201: content not recovered)
#line 202
// <stubs>
// f6734 · 6461 B · unmatched · name unknown
// void f6734(i32) { ... }
// </stubs>

// (original lines 207-297: content not recovered)
#line 298
// <stubs>
// f5761 · 3007 B · unmatched · name unknown
// void f5761(i32, i32) { ... }
// </stubs>

// (original lines 303-430: content not recovered)
#line 431
void CEleitores::MarcaEleitorFoiHabilitado(const CEleitorDadosHabilitacao& dados)
{
    CEleitorDetalhe* detalhe = GetCurrent();
    if (detalhe == nullptr) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7842, "Item inexistente");
    }

    if (!detalhe->TemDadosDinamicos()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7843, "Dados dinâmicos não carregados");
    }

    // (original lines 442-443: content not recovered)
#line 444
    if (detalhe->GetDinamico().GetEstadoComparecimento() != 3) {
        detalhe->MarcaHabilitado(dados);
    } else {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7844, "Eleitor já votou");
    }
}

// (original lines 451-733: content not recovered)
#line 734
void CEleitores::ValidaIdentidadesEleitor(const md::CEleitorDecorator& eleitor) const
{
    const std::vector<md::CEleitorIdentidade>& identidades = eleitor.GetIdentidades();
    if (std::none_of(identidades.begin(), identidades.end(), [this](const md::CEleitorIdentidade& identidade) { return identidade.GetTipo() == m_tipoIdentificadorPrincipal; })) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7852, std::format("Identificador principal ({}) ausente para o eleitor ({})", m_tipoIdentificadorPrincipal, eleitor.GetIdentidadePorTipo(eleitor.GetTipoIdentificador()).GetIdentificador()));
    }
}

// (original lines 742-751: content not recovered)
#line 752
std::string CEleitorDadoNomeParaUrna::Text(const std::string& formato)
{
    const CEleitorDetalhe* detalhe = CEleitores::GetInst().GetCurrent();
    if (detalhe == nullptr) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7854, "Não posicionado no eleitor corretamente");
    }
    const md::CEleitorDecorator& eleitor = detalhe->GetEleitor();
    std::string nome = (eleitor.GetNomeUrna().empty() ? eleitor.GetNome() : eleitor.GetNomeUrna()).substr(0, 40);
    return std::vformat(formato, std::make_format_args(nome));
}

// (original lines 763-767: content not recovered)
#line 768
std::string CEleitorDadoSequencial::Text(const std::string& formato)
{
    const CEleitorDetalhe* detalhe = CEleitores::GetInst().GetCurrent();
    if (detalhe == nullptr) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7855, "Não posicionado no eleitor corretamente");
    }
    int sequencial = detalhe->GetEleitor().GetSequencial();
    return std::vformat(formato, std::make_format_args(sequencial));
}

// (original lines 778-779: content not recovered)
#line 780
std::string CEleitorDadoSecao::Text(const std::string& formato)
{
    const CEleitorDetalhe* detalhe = CEleitores::GetInst().GetCurrent();
    if (detalhe == nullptr) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7856, "Não posicionado no eleitor corretamente");
    }
    ueword secao = detalhe->GetEleitor().GetSecao();
    return std::vformat(formato, std::make_format_args(secao));
}

// (original lines 790-791: content not recovered)
#line 792
std::string CEleitorDadoTTE::Text()
{
    const CEleitorDetalhe* detalhe = CEleitores::GetInst().GetCurrent();
    if (detalhe == nullptr) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7857, "Não posicionado no eleitor corretamente");
    }
    if (!detalhe->GetEleitor().IsTTE()) {
        return "";
    }
    return "Transferência Temporária";
}

} // namespace comum
