#include "app/comum/dados/celeitores.h"

#include <algorithm>
#include <format>
#include <functional>
#include <iterator>

#include "api/io/asn/cfileasn.h"
#include "app/comum/asn/util.h"
#include "app/comum/dados/asn/eleitor/cconversorimpedido.h"
#include "app/comum/dados/carregaarquivo.h"
#include "app/comum/dados/celeitordadoshabilitacao.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "app/comum/dados/md/eleitor/cimpedido.h"
#include "app/comum/relatorios/cgeradorbuqrcode.h"
#include "ecourna/api/pattern/singleton.hpp"

namespace comum {

// (original lines 20-40: content not recovered)
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

std::vector<md::CEleitorDecorator> CEleitores::GetEleitoresEstaticos(const std::string& diretorio)
{
    const std::function<std::vector<md::CEleitor>(const std::string&)> leitor = [](const std::string& arquivo) {
        api::CFile entrada(arquivo, "rb");
        std::vector<md::CEleitor> eleitores = LeEleitores(entrada);
        entrada.Close();
        return eleitores;
    };
    const std::vector<std::string> caminhos = MontaCaminhos(diretorio, m_lista2);
    std::vector<md::CEleitor> eleitores = LeArquivos(caminhos, leitor);
    const std::vector<std::string> outrosCaminhos = MontaCaminhos(diretorio, m_lista1);
    const std::vector<md::CEleitor> outros = LeArquivos(outrosCaminhos, leitor);
    if (!outros.empty()) {
        eleitores.insert(eleitores.end(), outros.begin(), outros.end());
    }

    std::vector<md::CEleitorDecorator> decorados;
    decorados.reserve(eleitores.size());
    std::transform(eleitores.begin(), eleitores.end(), std::back_inserter(decorados), [this](const md::CEleitor& eleitor) {
        return md::CEleitorDecorator(eleitor, m_tipoIdentificadorPrincipal);
    });
    std::sort(decorados.begin(), decorados.end());
    return decorados;
}

std::vector<md::CImpedido> CEleitores::GetEleitoresImpedidos(const std::vector<std::string>& arquivos)
{
    const std::function<std::vector<md::CImpedido>(const std::string&)> leitor = [](const std::string& arquivo) {
        return CarregaArquivo<asn::CConversorImpedido>(arquivo);
    };
    return LeArquivos(arquivos, leitor);
}

// (original lines 121-201: content not recovered)
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

md::CBiometriaEleitor CEleitores::GetCurrentBiometriaEleitor() const
{
    return GetCurrent()->GetBiometria();
}

// (original lines 507-559: content not recovered)
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

ueword CEleitores::QuantidadeHabilitacaoBiometrica() const
{
    return std::count_if(m_registros.begin(), m_registros.end(), [](const Container::value_type& registro) {
        const CEleitorDetalhe& detalhe = registro.second;
        return detalhe.TemDadosDinamicos() && detalhe.GetDinamico().GetTipoHabilitacao() == 1 &&
               detalhe.GetDinamico().GetEstadoComparecimento() == 3;
    });
}

ueword CEleitores::QuantidadeHabilitacaoBiografica() const
{
    return std::count_if(m_registros.begin(), m_registros.end(), [](const Container::value_type& registro) {
        const CEleitorDetalhe& detalhe = registro.second;
        return detalhe.TemDadosDinamicos() && detalhe.GetDinamico().GetTipoHabilitacao() == 2 &&
               detalhe.GetDinamico().GetEstadoComparecimento() == 3;
    });
}

// (original lines 667-703: content not recovered)
#line 704
CEleitorDetalhe CEleitores::LoadEleitorDetalhe(const md::CEleitorDecorator& eleitor, const std::vector<md::CImpedido>& impedidos,
    size_t& indice, const md::CEleitorDinamico* dinamico) const
{
    md::ETipoImpedimento impedimentoP1 = md::IMPEDIMENTO_SEM_IMPEDIMENTO;
    md::ETipoImpedimento impedimentoP2 = md::IMPEDIMENTO_SEM_IMPEDIMENTO;
    if (indice < impedidos.size()) {
        const md::CImpedido& impedido = impedidos[indice];
        if (eleitor.GetIdentidadePorTipo(eleitor.GetTipoIdentificador()) == impedido.GetEleitor()) {
            ++indice;
            impedimentoP1 = impedido.GetImpedimentoP1();
            if (impedido.TemImpedimentoP2()) {
                impedimentoP2 = impedido.GetImpedimentoP2();
            }
        } else if (eleitor.GetIdentidadePorTipo(eleitor.GetTipoIdentificador()) > impedido.GetEleitor()) {
            const std::string mensagem = std::format("CEleitores::LoadEleitorDetalhe - ({}-{} > {}-{}). {} com marcação de impedido não encontrado nas listas de eleitores e de tte", eleitor.GetIdentidadePorTipo(eleitor.GetTipoIdentificador()).GetIdentificador(), eleitor.GetIdentidadePorTipo(eleitor.GetTipoIdentificador()).GetTipo(), impedido.GetEleitor().GetIdentificador(), impedido.GetEleitor().GetTipo(), impedido.GetEleitor().GetIdentificador());
            throw CUeComumDadosError(EUE_COMUM_DADOS_7851, mensagem);
        }
    }
    if (dinamico == nullptr) {
        return CEleitorDetalhe(eleitor, impedimentoP1, impedimentoP2);
    }
    return CEleitorDetalhe(eleitor, *dinamico, impedimentoP1, impedimentoP2);
}

// (original lines 728-733: content not recovered)
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
