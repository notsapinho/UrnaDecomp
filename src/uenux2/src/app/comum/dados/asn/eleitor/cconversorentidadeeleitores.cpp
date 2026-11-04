// Reconstruction: comum::asn::CConversorEntidadeEleitores's slot 2 (target fn 11411) and what it calls (fragment 310).
#include "app/comum/dados/asn/eleitor/cconversorentidadeeleitores.h"

#include <algorithm>
#include <format>
#include <iterator>

#include "app/comum/asn/cconversorcabecalhoentidade.h"
#include "app/comum/asn/cconversorseguranca.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "app/comum/dados/md/cdataje.h"

namespace comum::asn {
namespace {

md::CEleitorIdentidade MontaEleitorIdentidade(const ModuloTiposEleitorais::IdentificadorEleitor& identificador)
{
    switch (identificador.currentSelection()) {
        case ModuloTiposEleitorais::IdentificadorEleitor::numeroInscricao0:
            return md::CEleitorIdentidade(identificador.get_numeroInscricao(), ecourna::app::dados::TipoIDInscricaoEleitoral);
        case ModuloTiposEleitorais::IdentificadorEleitor::numeroCPF1:
            return md::CEleitorIdentidade(identificador.get_numeroCPF(), ecourna::app::dados::TipoIDCPF);
        default:
            return md::CEleitorIdentidade(identificador.get_identificacaoLivre(), ecourna::app::dados::TipoIDNumeroLivre);
    }
}

} // namespace
md::CEleitor::ENecessidadeEspecial CConversorEntidadeEleitores::ConverteNecessidadeEspecial(ModuloEleitores::EleitorUrna eleitor)
{
    const ModuloEleitores::NecessidadeEspecial necessidade = eleitor.get_necessidade();
    switch (necessidade) {
        case ModuloEleitores::NecessidadeEspecial::semNecessidade:
            return md::CEleitor::SEM_NECESSIDADE;
        case ModuloEleitores::NecessidadeEspecial::necessitaAudio:
            return md::CEleitor::NECESSITA_AUDIO;
        default:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7898, std::format("Tipo de necessidade inválido: {}", necessidade.asInt()));
    }
}

// (original lines 42-44: content not recovered)
#line 45
std::vector<md::CEleitorIdentidade> GetInscricoesEleitor(ModuloEleitores::EleitorSequencia eleitor)
{
    const ModuloEleitores::EleitorUrna::identificacaoEleitor::value_type identificacoes = eleitor.get_eleitor().get_identificacaoEleitor();
    if (identificacoes.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7899, "Inscrição não encontrada");
    }

    std::vector<md::CEleitorIdentidade> inscricoes;
    std::transform(identificacoes.begin(), identificacoes.end(), std::back_inserter(inscricoes), MontaEleitorIdentidade);

    // (original lines 55-73: content not recovered)
#line 74
    const auto duplicada = std::adjacent_find(inscricoes.begin(), inscricoes.end());
    if (duplicada != inscricoes.end()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7900, std::format("Identidade duplicada ({}) para o eleitor ({})", static_cast<int>(duplicada->GetTipo()), duplicada->GetIdentificador()));
    }
    return inscricoes;
}


CConversorEntidadeEleitores::TDado CConversorEntidadeEleitores::DoDesconverte(const TEntidade& entidade, const TVisitor& visitante) const
{
    CConversorCabecalhoEntidade conversorCabecalho;
    const md::CCabecalhoEntidade cabecalho = conversorCabecalho.Desconverte(entidade.get_cabecalho());
    const ModuloTiposEleitorais::IdentificacaoSecaoEleitoral& identificacao = entidade.get_identificacao();
    const TMunicipioID municipio = identificacao.get_municipioZona().get_municipio().getValue();
    const TZonaID zona = identificacao.get_municipioZona().get_zona().getValue();
    const TSecaoID secao = identificacao.get_secao().getValue();
    CConversorSeguranca conversorSeguranca;
    std::vector<uebyte> chave;
    if (entidade.seguranca_isPresent()) {
        const md::CSeguranca seguranca = conversorSeguranca.Desconverte(entidade.get_seguranca());
        chave.assign(seguranca.GetChave().begin(), seguranca.GetChave().end());
    }

    std::vector<md::CEleitor> eleitores;
    if (entidade.eleitores_isPresent()) {
        const ModuloEleitores::EntidadeEleitores::eleitores::value_type& lista = entidade.get_eleitores();
        const std::map<md::CEleitorIdentidade, md::CIndexer> biometrias = visitante.GetIdentidades();
        for (const ModuloEleitores::EleitorSequencia& eleitor : lista) {
            const int sequencial = eleitor.get_sequencial().getValue();
            const std::vector<md::CEleitorIdentidade> inscricoes = GetInscricoesEleitor(eleitor);
            const md::CEleitor::ENecessidadeEspecial necessidade = ConverteNecessidadeEspecial(eleitor.get_eleitor());
            const std::string nome = std::string(eleitor.get_eleitor().get_nome()).substr(0, 40);
            std::string nomeSocial = "";
            if (eleitor.get_eleitor().nomeSocial_isPresent()) {
                nomeSocial = std::string(eleitor.get_eleitor().get_nomeSocial()).substr(0, 40);
            }
            const md::CTransferenciaTemporaria transferencia = DesconverteTransferenciaTemporaria(eleitor);
            const md::CDataJE dataNascimento(eleitor.get_eleitor().get_dataNascimento());

            auto biometria = biometrias.end();
            for (const md::CEleitorIdentidade& inscricao : inscricoes) {
                const auto encontrada = biometrias.find(inscricao);
                if (encontrada != biometrias.end()) {
                    biometria = encontrada;
                    break;
                }
            }

            if (eleitor.get_eleitor().biometria_isPresent() && biometria != biometrias.end()) {
                eleitores.emplace_back(sequencial, secao, inscricoes, necessidade, nome, nomeSocial, transferencia,
                                       dataNascimento.GetData(), chave, biometria->second);
            } else {
                eleitores.emplace_back(sequencial, secao, inscricoes, necessidade, nome, nomeSocial, transferencia,
                                       dataNascimento.GetData());
            }
        }
    }

    if (entidade.seguranca_isPresent()) {
        const md::CSeguranca seguranca = conversorSeguranca.Desconverte(entidade.get_seguranca());
        return md::CEntidadeEleitores(cabecalho, municipio, zona, secao, seguranca, eleitores);
    }
    return md::CEntidadeEleitores(cabecalho, municipio, zona, secao, eleitores);
}

// (original lines 139-188: content not recovered)
#line 189
md::CTransferenciaTemporaria::ETransferenciaTemporaria CConversorEntidadeEleitores::DesconverteTipoTransferenciaTemporaria(const ModuloEleitores::EleitorSequencia& eleitor) const
{
    using TipoTransferencia = ModuloEleitores::EleitorSequencia::tipoTransferenciaTemporaria::value_type;
    if (eleitor.tipoTransferenciaTemporaria_isPresent()) {
        switch (eleitor.get_tipoTransferenciaTemporaria()) {
            case TipoTransferencia::votoEmTransito:
            case TipoTransferencia::servidorEmServico:
            case TipoTransferencia::eleitorConvocado:
            case TipoTransferencia::justicaEleitoral:
                return md::CTransferenciaTemporaria::TRANSFERENCIA_VOTO_EM_TRANSITO;
            case TipoTransferencia::presoProvisorio:
                return md::CTransferenciaTemporaria::TRANSFERENCIA_PRESO_PROVISORIO;
            case TipoTransferencia::acessibilidade:
                return md::CTransferenciaTemporaria::TRANSFERENCIA_ACESSIBILIDADE;
            case TipoTransferencia::oficio:
                return md::CTransferenciaTemporaria::TRANSFERENCIA_OFICIO;
            case TipoTransferencia::indigenaQuilombola:
                return md::CTransferenciaTemporaria::TRANSFERENCIA_INDIGENA_QUILOMBOLA;
            case TipoTransferencia::situacaoRua:
                return md::CTransferenciaTemporaria::TRANSFERENCIA_SITUACAO_RUA;
            case TipoTransferencia::unknownEnumeration_:
                throw CUeComumDadosError(EUE_COMUM_DADOS_7901, std::format("Tipo de transferência inválido: {}", eleitor.get_tipoTransferenciaTemporaria().asInt()));
        }
    }
    return md::CTransferenciaTemporaria::SEM_TRANSFERENCIA;
}

// (original lines 216-225: content not recovered)
#line 226
md::CTransferenciaTemporaria CConversorEntidadeEleitores::DesconverteTransferenciaTemporaria(const ModuloEleitores::EleitorSequencia& eleitor) const
{
    const md::CTransferenciaTemporaria::ETransferenciaTemporaria tipo = DesconverteTipoTransferenciaTemporaria(eleitor);
    if (tipo == md::CTransferenciaTemporaria::SEM_TRANSFERENCIA) {
        return md::CTransferenciaTemporaria(tipo);
    }
    if (eleitor.get_eleitor().domicilio_isPresent()) {
        const ModuloEleitores::DomicilioEleitoral& domicilio = eleitor.get_eleitor().get_domicilio();
        return md::CTransferenciaTemporaria(tipo, domicilio.get_uf(), domicilio.get_codigoMunicipio().getValue());
    }
    throw CUeComumDadosError(EUE_COMUM_DADOS_7902, "Eleitor de voto em trânsito sem informações de domicílio eleitoral.");
}

} // namespace comum::asn
