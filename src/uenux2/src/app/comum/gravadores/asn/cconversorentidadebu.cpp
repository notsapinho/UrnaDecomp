// Reconstruction: comum::asn::CConversorEntidadeBU::DoConverte (target fn 10273), with what binaryen and clang inline into
// it from this file: the anonymous helpers CriaVotosVotavel, CriaVotosCargo, CriaResultadoVotacao,
// CriaResultadoVotacaoPorEleicao and CriaResultadosVotacoes, and the class's static ConverteTipoVoto, ConverteTipoCargo,
// ConverteDadosVota and ConverteDadosSA. The throws are records of the target, so their lines are fixed (87, 110, 132,
// 164, 175, 232, 284 and 299); where each function starts, the blank lines and the place of ConverteDadosVota and
// ConverteDadosSA, which have no record, are a choice. The fragment that compiles this file has the rest.

#include "app/comum/gravadores/asn/cconversorentidadebu.h"

#include <format>
#include <string>
#include <vector>

#include "app/comum/asn/cconversorcabecalhoentidade.h"
#include "app/comum/asn/cconversorcodigocargoconsulta.h"
#include "app/comum/asn/util.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/gravadores/asn/cassinavotavelbu.h"
#include "app/comum/gravadores/asn/cconversorhistoricovotoimpresso.h"
#include "app/comum/gravadores/asn/cconversorurna.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"
#include "ecourna/app/dados/asn/cconversordetalhamentocomparecimento.hpp"

// The two throws print the post's and the vote's type through a handle (table slots 2954 and 2776, both target fn 536,
// the body every comum::SFormatoEnum instance shares), as relatorios/cgeradorbuqrcode.cpp does for the post's type.
template <>
struct std::formatter<comum::md::CCargo::ETipo> : comum::SFormatoEnum {};
template <>
struct std::formatter<comum::md::CVoto::ETipo> : comum::SFormatoEnum {};

namespace comum::asn {

namespace {

using TCargoID = md::TCargoID;

// The chained hash's last value, which each votable's hash covers and each election's result carries and signs. Its exit
// destructor (fn 10274, table slot 4476) heads the run of this object's slots, the vtable's four (4477 to 4480: 174,
// 144, 10273, 10272), where GetInst's statics' destructors (4466, 4467) lie in util.cpp's run; that the vector is a file
// static, and its name, are chosen.
std::vector<uebyte> s_ultimoHash;

// (original lines 43-58: content not recovered)
#line 59
ModuloBoletimUrna::TotalVotosVotavel CriaVotosVotavel(const md::CVotosVotavel& votosVotavel, const TCargoID codigoCargo,
    const ueword ordem)
{
    ModuloBoletimUrna::TotalVotosVotavel votos;
    const ModuloBoletimUrna::TipoVoto::NamedNumber tipo = CConversorEntidadeBU::ConverteTipoVoto(votosVotavel.GetTipo());
    const ueword quantidade = votosVotavel.GetQuantidade();
    votos.set_tipoVoto(tipo);
    votos.set_quantidadeVotos(quantidade);
    TCandidatoID codigo = 0;
    TPartidoID partido = 0;
    if (votosVotavel.TemIdentificacao()) {
        ModuloBoletimUrna::IdentificacaoVotavel identificacao;
        codigo = votosVotavel.GetIdentificacao().GetCodigo();
        partido = votosVotavel.GetIdentificacao().GetPartido();
        identificacao.set_codigo(codigo);
        identificacao.set_partido(partido);
        votos.set_identificacaoVotavel() = identificacao;
    } else {
        votos.omit_identificacaoVotavel();
    }
    votos.set_ordemGeracaoHash(ordem);
    s_ultimoHash = votosVotavel.TemIdentificacao()
        ? CAssinaVotavelBu::GetInst().CalculaHashVotavel(s_ultimoHash, ordem, codigoCargo, tipo, quantidade,
              codigo, partido)
        : CAssinaVotavelBu::GetInst().CalculaHashVotavel(s_ultimoHash, ordem, codigoCargo, tipo, quantidade);
    votos.set_hash() =
        std::vector<char>(s_ultimoHash.begin(), s_ultimoHash.end());
    if (!votos.isValid() || !votos.isStrictlyValid()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8603, "Entidade inválida");
    }
    return votos;
}

// (original lines 92-96: content not recovered)
#line 97
ModuloBoletimUrna::TotalVotosCargo CriaVotosCargo(const md::CVotosCargo& votosCargo)
{
    const CConversorCodigoCargoConsulta conversorCodigo;
    ModuloBoletimUrna::TotalVotosCargo votos;
    votos.set_codigoCargo() = conversorCodigo.Converte(votosCargo.GetCodigoCargo());
    votos.set_ordemImpressao(votosCargo.GetOrdemImpressao());
    ModuloBoletimUrna::TotalVotosCargo::votosVotaveis::value_type votosVotaveis;
    ueword ordem = 0;
    for (const md::CVotosVotavel& votosVotavel : votosCargo.GetVotosVotaveis()) {
        votosVotaveis.push_back(CriaVotosVotavel(votosVotavel, votosCargo.GetCodigoCargo(), ++ordem));
    }
    votos.set_votosVotaveis() = votosVotaveis;
    if (!votos.isValid() || !votos.isStrictlyValid()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8604, "Entidade inválida");
    }
    return votos;
}

// (original lines 115-120: content not recovered)
#line 121
ModuloBoletimUrna::ResultadoVotacao CriaResultadoVotacao(const md::CResultadoVotacao& resultadoVotacao)
{
    ModuloBoletimUrna::ResultadoVotacao resultado;
    resultado.set_tipoCargo(CConversorEntidadeBU::ConverteTipoCargo(resultadoVotacao.GetTipoCargo()));
    resultado.set_qtdComparecimento(resultadoVotacao.GetQtdComparecimento());
    ModuloBoletimUrna::ResultadoVotacao::totaisVotosCargo::value_type totais;
    for (const md::CVotosCargo& votosCargo : resultadoVotacao.GetTotaisVotosCargo()) {
        totais.push_back(CriaVotosCargo(votosCargo));
    }
    resultado.set_totaisVotosCargo() = totais;
    if (!resultado.isValid() || !resultado.isStrictlyValid()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8605, "Entidade inválida");
    }
    return resultado;
}

// (original lines 137-145: content not recovered)
#line 146
ModuloBoletimUrna::ResultadoVotacaoPorEleicao CriaResultadoVotacaoPorEleicao(
    const md::CResultadoVotacaoPorEleicao& resultadoPorEleicao)
{
    ModuloBoletimUrna::ResultadoVotacaoPorEleicao resultado;
    resultado.set_idEleicao(resultadoPorEleicao.GetIdEleicao());
    resultado.set_qtdEleitoresAptos(resultadoPorEleicao.GetQtdEleitoresAptos());
    resultado.set_qtdEleitoresAptosSecao(resultadoPorEleicao.GetQtdEleitoresAptosSecao());
    resultado.set_qtdEleitoresAptosTTE(resultadoPorEleicao.GetQtdEleitoresAptosTTE());
    ModuloBoletimUrna::ResultadoVotacaoPorEleicao::resultadosVotacao::value_type resultados;
    for (const md::CResultadoVotacao& resultadoVotacao : resultadoPorEleicao.GetResultadosVotacao()) {
        resultados.push_back(CriaResultadoVotacao(resultadoVotacao));
    }
    resultado.set_resultadosVotacao() = resultados;
    resultado.set_ultimoHashVotosVotavel() =
        std::vector<char>(s_ultimoHash.begin(), s_ultimoHash.end());
    const std::vector<uebyte> assinatura = CAssinaVotavelBu::GetInst().Assinar(s_ultimoHash);
    resultado.set_assinaturaUltimoHashVotosVotavel() = std::vector<char>(assinatura.begin(), assinatura.end());
    if (!resultado.isValid() || !resultado.isStrictlyValid()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8606, "Entidade inválida");
    }
    return resultado;
}

// (original lines 169-171: content not recovered)
#line 172
void CriaResultadosVotacoes(ModuloBoletimUrna::EntidadeBoletimUrna& entidade, const md::CEntidadeBU& dado)
{
    if (dado.GetCabecalho().GetTipo() != md::TIPO_CABECALHO_PLEITO) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8607, "Erro no hash encadeado: Tipo de identificador do cabeçalho da entidade BU precisa ser um pleito.");
    }
    const uedword pleito = dado.GetCabecalho().GetCodigo();
    const TMunicipioID municipio = dado.GetMunicipio();
    const TZonaID zona = dado.GetZona();
    const TSecaoID secao = dado.GetSecao();
    const std::string codigoCarga = dado.GetUrna().GetCorrespondencia().GetCarga().GetCodigoCarga();
    ModuloBoletimUrna::EntidadeBoletimUrna::resultadosVotacaoPorEleicao::value_type resultados;
    for (const md::CResultadoVotacaoPorEleicao& resultado : dado.GetResultadosVotacaoPorEleicao()) {
        const uedword eleicao = resultado.GetIdEleicao();
        s_ultimoHash =
            CAssinaVotavelBu::GetInst().CalculaHashInicial(pleito, eleicao, municipio, zona, secao, codigoCarga);
        resultados.push_back(CriaResultadoVotacaoPorEleicao(resultado));
    }
    entidade.set_resultadosVotacaoPorEleicao() = resultados;
}

} // namespace

// (original lines 194-204: content not recovered)
#line 205
CConversorEntidadeBU::TEntidade CConversorEntidadeBU::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    const CConversorCabecalhoEntidade conversorCabecalho;
    const ModuloTiposEleitorais::CabecalhoEntidade cabecalho = conversorCabecalho.Converte(dado.GetCabecalho());
    entidade.set_cabecalho() = cabecalho;
    entidade.set_fase() = Utils::ConverteFase(dado.GetFase());
    const CConversorUrna conversorUrna;
    const ModuloTiposResultadosEcoUrna::Urna urna = conversorUrna.Converte(dado.GetUrna());
    entidade.set_urna() = urna;
    entidade.set_identificacaoSecao().set_municipioZona().set_municipio(dado.GetMunicipio());
    entidade.set_identificacaoSecao().set_municipioZona().set_zona(dado.GetZona());
    entidade.set_identificacaoSecao().set_local(dado.GetLocal());
    entidade.set_identificacaoSecao().set_secao(dado.GetSecao());
    entidade.set_dataHoraEmissao() = Utils::ConverteDataHoraJE(dado.GetDataHoraEmissao());
    entidade.set_qtdEleitoresCompareceram(dado.GetQtdEleitoresCompareceram());
    if (dado.TemDetalhamentoComparecimento()) {
        const ecourna::app::dados::asn::CConversorDetalhamentoComparecimento conversorDetalhamento;
        entidade.set_detalhamentoComparecimento() = conversorDetalhamento.Converte(dado.GetDetalhamentoComparecimento());
    } else {
        entidade.omit_detalhamentoComparecimento();
    }
    if (dado.TemDadosVota()) {
        entidade.set_dadosSecaoSA().select_dadosSecao(ConverteDadosVota(dado.GetDadosVota()));
    } else if (dado.TemDadosSA()) {
        entidade.set_dadosSecaoSA().select_dadosSA(ConverteDadosSA(dado.GetDadosSA()));
    } else {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8608, "Objeto de dados do BU mal formado");
    }
    CriaResultadosVotacoes(entidade, dado);
    const std::vector<std::string>& codigosCarga = dado.GetHistoricoCodigosCarga();
    if (codigosCarga.size() > 0) {
        ModuloRegistroDigitalVoto::HistoricoCodigosCarga historico;
        for (std::size_t i = 0; i < codigosCarga.size(); ++i) {
            historico.push_back(ASN1::GeneralString(codigosCarga[i]));
        }
        entidade.set_historicoCodigosCarga() = historico;
    }
    const std::vector<md::CHistoricoVotoImpresso>& historicoVotoImpresso = dado.GetHistoricoVotoImpresso();
    if (!historicoVotoImpresso.empty()) {
        TEntidade::historicoVotoImpresso::value_type historico;
        const CConversorHistoricoVotoImpresso conversorHistorico;
        for (std::size_t i = 0; i < historicoVotoImpresso.size(); ++i) {
            historico.push_back(conversorHistorico.Converte(historicoVotoImpresso[i]));
        }
        entidade.set_historicoVotoImpresso() = historico;
    } else {
        entidade.omit_historicoVotoImpresso();
    }
    return entidade;
}

// (original lines 257-265: content not recovered)
#line 266
ModuloBoletimUrna::TipoVoto::NamedNumber CConversorEntidadeBU::ConverteTipoVoto(md::CVoto::ETipo tipo)
{
    switch (tipo) {
        case md::CVoto::LEGENDA:
            return ModuloBoletimUrna::TipoVoto::legenda;
        case md::CVoto::NOMINAL:
            return ModuloBoletimUrna::TipoVoto::nominal;
        case md::CVoto::BRANCO:
        case md::CVoto::BRANCO_APOS_SUSPENSAO:
            return ModuloBoletimUrna::TipoVoto::branco;
        case md::CVoto::NULO:
        case md::CVoto::NULO_APOS_SUSPENSAO:
        case md::CVoto::NULO_POR_REPETICAO:
            return ModuloBoletimUrna::TipoVoto::nulo;
        case md::CVoto::NULO_CARGO_SEM_CANDIDATO:
        case md::CVoto::NULO_APOS_SUSPENSAO_CARGO_SEM_CANDIDATO:
            return ModuloBoletimUrna::TipoVoto::cargoSemCandidato;
    }
    throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8609, std::format("Tipo inválido: {}", tipo));
}

// (original lines 287-288: content not recovered)
#line 289
ModuloTiposEleitorais::TipoCargoConsulta::NamedNumber CConversorEntidadeBU::ConverteTipoCargo(md::CCargo::ETipo tipo)
{
    switch (tipo) {
        case md::CCargo::MAJORITARIO:
            return ModuloTiposEleitorais::TipoCargoConsulta::majoritario;
        case md::CCargo::PROPORCIONAL:
            return ModuloTiposEleitorais::TipoCargoConsulta::proporcional;
        case md::CCargo::CONSULTA:
            return ModuloTiposEleitorais::TipoCargoConsulta::consulta;
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8610, std::format("Tipo inválido: {}", tipo));
    }
}

ModuloBoletimUrna::DadosSecao CConversorEntidadeBU::ConverteDadosVota(const md::CDadosBUVota& dados)
{
    ModuloBoletimUrna::DadosSecao dadosSecao;
    dadosSecao.set_dataHoraAbertura() = Utils::ConverteDataHoraJE(dados.GetDataHoraAbertura());
    dadosSecao.set_dataHoraEncerramento() = Utils::ConverteDataHoraJE(dados.GetDataHoraEncerramento());
    if (dados.TemDataHoraDesligamentoVotoImpresso()) {
        dadosSecao.set_dataHoraDesligamentoVotoImpresso() =
            Utils::ConverteDataHoraJE(dados.GetDataHoraDesligamentoVotoImpresso());
    } else {
        dadosSecao.omit_dataHoraDesligamentoVotoImpresso();
    }
    return dadosSecao;
}

ModuloBoletimUrna::DadosSA CConversorEntidadeBU::ConverteDadosSA(const md::CDadosBUSA& dados)
{
    ModuloBoletimUrna::DadosSA dadosSA;
    dadosSA.set_juntaApuradora(dados.GetJuntaApuradora());
    dadosSA.set_turmaApuradora(dados.GetTurmaApuradora());
    if (dados.GetNumeroInternoUrnaOrigem() != 0) {
        dadosSA.set_numeroInternoUrnaOrigem(dados.GetNumeroInternoUrnaOrigem());
    } else {
        dadosSA.omit_numeroInternoUrnaOrigem();
    }
    return dadosSA;
}
} // namespace comum::asn
