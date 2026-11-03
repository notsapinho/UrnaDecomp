#include "app/comum/dados/celeitores.h"

#include <algorithm>
#include <format>
#include <functional>

#include "api/io/asn/cfileasn.h"
#include "app/comum/asn/util.h"
#include "app/comum/dados/asn/eleitor/cconversorimpedido.h"
#include "app/comum/dados/celeitordadoshabilitacao.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "app/comum/dados/md/eleitor/cimpedido.h"
#include "app/comum/relatorios/cgeradorbuqrcode.h"
#include "ecourna/api/pattern/singleton.hpp"

namespace comum {

// (original lines 18-40: content not recovered)
#line 41
std::unique_ptr<CEleitores> CEleitores::s_instance;
std::mutex CEleitores::s_mutex;

SINGLETON_IMPL_GET_INST(CEleitores, s_mutex, s_instance)

CEleitores::~CEleitores() = default;

CEleitorDetalhe* CEleitores::LocalizaEleitor(const md::CEleitorIdentidade& identidade)
{
    const auto it = m_identidades.find(identidade);
    if (it == m_identidades.end()) {
        return nullptr;
    }
    return Find(it->second);
}

CEleitorDetalhe* CEleitores::LocalizaEleitor(const std::string& identificador, ecourna::app::dados::ETipoIdentificadorEleitor tipo)
{
    const md::CEleitorIdentidade identidade(identificador, tipo);
    return LocalizaEleitor(identidade);
}

namespace {

template <typename T>
std::vector<T> LeArquivos(const std::vector<std::string>& arquivos, std::function<std::vector<T>(const std::string&)> leitor)
{
    std::vector<T> lidos;
    for (const std::string& arquivo : arquivos) {
        const std::vector<T> doArquivo = leitor(arquivo);
        lidos.insert(lidos.end(), doArquivo.begin(), doArquivo.end());
    }
    return lidos;
}

} // namespace

std::vector<std::string> MontaCaminhos(const std::string& diretorio, const std::vector<std::string>& nomes)
{
    std::vector<std::string> caminhos;
    caminhos.reserve(nomes.size());
    for (const std::string& nome : nomes) {
        caminhos.push_back(diretorio + nome);
    }
    return caminhos;
}

std::vector<md::CImpedido> CEleitores::GetEleitoresImpedidos(const std::vector<std::string>& arquivos)
{
    const std::function<std::vector<md::CImpedido>(const std::string&)> leitor = [](const std::string& arquivo) {
        asn::CConversorImpedido conversor;
        return conversor.Desconverte(api::CFileASN::ReadFromFile<ModuloImpedidos::EntidadeImpedidos>(arquivo));
    };
    return LeArquivos(arquivos, leitor);
}

// (original lines 97-201: content not recovered)
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


void CEleitores::MarcaVotou()
{
    CEleitorDetalhe* detalhe = GetCurrent();
    if (detalhe == nullptr) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7845, "Item inexistente");
    }

    if (!detalhe->TemDadosDinamicos()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7846, "Dados dinâmicos não carregados");
    }

    if (detalhe->GetDinamico().GetEstadoComparecimento() != 3) {
        detalhe->MarcaVotou();
        m_qtdVotaram++;
    }
}

// (original lines 469-492: content not recovered)
#line 493
md::ETipoAbrangencia CEleitores::GetCurrentAbrangenciaEleitor() const
{
    const CEleitorDetalhe* detalhe = CEleitores::GetInst().GetCurrent();
    if (detalhe == nullptr) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7847, "Não posicionado no eleitor corretamente");
    }
    return detalhe->GetEleitor().GetAbrangencia(m_uf, m_municipio);
}

// (original lines 502-559: content not recovered)
#line 560
namespace {

std::vector<md::ETipoAbrangencia> AbrangenciasAPartirDe(md::ETipoAbrangencia abrangencia)
{
    std::vector<md::ETipoAbrangencia> abrangencias;
    for (int tipo = abrangencia; tipo <= md::ABRANGENCIA_FEDERAL; ++tipo) {
        abrangencias.push_back(static_cast<md::ETipoAbrangencia>(tipo));
        if (tipo == md::ABRANGENCIA_FEDERAL) {
            break;
        }
    }
    return abrangencias;
}
} // namespace

std::map<md::ETipoAbrangencia, SQtdeAptos> CEleitores::QuantidadeAptosPorAbrangencia() const
{
    std::map<md::ETipoAbrangencia, SQtdeAptos> quantidades;
    for (md::ETipoAbrangencia abrangencia : AbrangenciasAPartirDe(md::ABRANGENCIA_MUNICIPAL)) {
        quantidades[abrangencia] = SQtdeAptos{};
    }
    for (const Container::value_type& registro : m_registros) {
        const CEleitorDetalhe& detalhe = registro.second;
        if (detalhe.SemImpedimento()) {
            const md::CEleitorDecorator& eleitor = detalhe.GetEleitor();
            const md::ETipoAbrangencia abrangenciaEleitor = eleitor.GetAbrangencia(m_uf, m_municipio);
            const bool tte = eleitor.IsTTE();
            for (md::ETipoAbrangencia abrangencia : AbrangenciasAPartirDe(abrangenciaEleitor)) {
                if (!tte) {
                    ++quantidades[abrangencia].m_qtdeAptosDaSecao;
                } else {
                    ++quantidades[abrangencia].m_qtdeAptosTTE;
                }
            }
        }
    }
    return quantidades;
}

// (original lines 599-623: content not recovered)
#line 624
CEleitores::SQuantidadeAptos CEleitores::QuantidadeAptos() const
{
    SQuantidadeAptos quantidade{};
    for (const Container::value_type& registro : m_registros) {
        const CEleitorDetalhe& detalhe = registro.second;
        if (detalhe.SemImpedimento()) {
            if (!detalhe.GetEleitor().IsTTE()) {
                ++quantidade.m_semTransferencia;
            } else {
                ++quantidade.m_comTransferencia;
            }
        }
    }
    return quantidade;
}

ueword CEleitores::QuantidadeHabilitacaoSemBiometria() const
{
    return std::count_if(m_registros.begin(), m_registros.end(), [](const Container::value_type& registro) {
        const CEleitorDetalhe& detalhe = registro.second;
        return detalhe.TemDadosDinamicos() && detalhe.GetDinamico().GetTipoHabilitacao() == 0 &&
               detalhe.GetDinamico().GetEstadoComparecimento() == 3;
    });
}

// (original lines 649-733: content not recovered)
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
