// comum::asn::Utils (/home/rubio/tse/uenux2/src/app/comum/asn/util.cpp). Every throw is a record of the target, so each
// sits on its record's line and column; the lines between them are blank where the original is not recovered. The
// switches' forms and the enumerators are chosen, and 96-uenux2-app-comum-asn.mk lists what the bytes do and do not
// decide, with the members of this file that are not written.
#include "app/comum/asn/util.h"

#include <format>

#include "app/comum/asn/euecomumasnerror.h"
#include "ecourna/api/util/cstringutils.hpp"
namespace comum::asn {

using ecourna::api::util::CStringUtils;

// (original lines 15-24: content not recovered)
#line 25
api::CDate Utils::DesconverteDataJE(const ModuloTiposEleitorais::DataJE& data)
{
    const std::string ano = data.substr(0, 4);
    const std::string mes = data.substr(4, 2);
    const std::string dia = data.substr(6, 2);
    return api::CDate(CStringUtils::ToByte(dia), CStringUtils::ToByte(mes), CStringUtils::ToWord(ano));
}

// (original lines 33-34: content not recovered)
#line 35
api::CDateTime Utils::DesconverteDataHoraJE(const ModuloTiposEleitorais::DataHoraJE& dataHora)
{
    const std::string strData = dataHora.substr(0, 8);
    const api::CDate data = DesconverteDataJE(ModuloTiposEleitorais::DataJE(strData));

    if (dataHora.substr(8, 1) != "T") {
        throw CUeComumAsnError(EUE_COMUM_ASN_FORMATO_DATA_INVALIDO, "Formato de data inválido.");
    }

    const std::string strHora = dataHora.substr(9, 6);
    const api::CTime hora = DesconverteHoraJE(ModuloTiposEleitorais::HoraJE(strHora));
    return api::CDateTime(data, hora);
}

api::CTime Utils::DesconverteHoraJE(const ModuloTiposEleitorais::HoraJE& hora)
{
    return api::CTime(hora);
}

ModuloTiposEleitorais::DataJE Utils::ConverteDataJE(const api::CDate& data)
{
    const std::string strData = data.Format("YYYYMMDD");
    return ModuloTiposEleitorais::DataJE(strData).c_str();
}

ModuloTiposEleitorais::DataHoraJE Utils::ConverteDataHoraJE(const api::CDateTime& dataHora)
{
    const std::string strData = dataHora.GetData().Format("YYYYMMDD");
    const std::string strHora = dataHora.GetHora().Format("hhmmss");
    return ModuloTiposEleitorais::DataHoraJE(strData + "T" + strHora).c_str();
}

// (original lines 67-76: content not recovered)
#line 77
md::CIDEleitoral Utils::DesconverteIdEleitoral(const ModuloTiposEleitorais::IDEleitoral& id)
{
    switch (id.currentSelection()) {
        case ModuloTiposEleitorais::IDEleitoral::idProcessoEleitoral0:
            return md::CIDEleitoral::CriaProcessoEleitoral(id.get_idProcessoEleitoral().getValue());
        case ModuloTiposEleitorais::IDEleitoral::idPleito1:
            return md::CIDEleitoral::CriaPleito(id.get_idPleito().getValue());
        case ModuloTiposEleitorais::IDEleitoral::idEleicao2:
            return md::CIDEleitoral::CriaEleicao(id.get_idEleicao().getValue());
        default:
            break;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_TIPO_ID_INVALIDO, "Tipo de id inválido.");
}

ModuloTiposEleitorais::Fase Utils::ConverteFase(const EUrnaFase& fase)
{
    switch (fase) {
        case FASE_OFICIAL:
            return ModuloTiposEleitorais::Fase::oficial;
        case FASE_SIMULADO:
            return ModuloTiposEleitorais::Fase::simulado;
        case FASE_TREINAMENTO:
            return ModuloTiposEleitorais::Fase::treinamento;
        default:
            throw CUeComumAsnError(EUE_COMUM_ASN_FASE_INVALIDA_CONVERTE, std::format("Fase inválida: {}", fase));
    }
}

EUrnaFase Utils::DesconverteFase(const ModuloTiposEleitorais::Fase& fase)
{
    switch (fase) {
        case ModuloTiposEleitorais::Fase::oficial:
            return FASE_OFICIAL;
        case ModuloTiposEleitorais::Fase::simulado:
            return FASE_SIMULADO;
        case ModuloTiposEleitorais::Fase::treinamento:
            return FASE_TREINAMENTO;
        default:
            throw CUeComumAsnError(EUE_COMUM_ASN_FASE_INVALIDA_DESCONVERTE, std::format("Fase inválida: {}", fase.asInt()));
    }
}

// (original lines 120-160: content not recovered)
#line 161
ModuloTiposPacotes::TipoPacote Utils::ConverteTipoPacote(const md::ETipoPacote& tipo)
{
    switch (tipo) {
        case md::PACOTE_ELEITORES:
            return ModuloTiposPacotes::TipoPacote::pacoteEleitores;
        case md::PACOTE_MUNICIPIOS_ZONAS:
            return ModuloTiposPacotes::TipoPacote::pacoteMunicipiosZonas;
        case md::PACOTE_IMPEDIDOS:
            return ModuloTiposPacotes::TipoPacote::pacoteImpedidos;
        case md::PACOTE_CANDIDATOS_TRE:
            return ModuloTiposPacotes::TipoPacote::pacoteCandidatosTRE;
        case md::PACOTE_FOTOS_CANDIDATOS_TRE:
            return ModuloTiposPacotes::TipoPacote::pacoteFotosCandidatosTRE;
        case md::PACOTE_CORRESPONDENCIA:
            return ModuloTiposPacotes::TipoPacote::pacoteCorrespondencia;
        case md::PACOTE_SECOES:
            return ModuloTiposPacotes::TipoPacote::pacoteSecoes;
        case md::PACOTE_NOTIFICACAO_PACOTE:
            return ModuloTiposPacotes::TipoPacote::pacoteNotificacaoPacote;
        case md::PACOTE_CONFIGURACAO_PROCESSO_ELEITORAL:
            return ModuloTiposPacotes::TipoPacote::pacoteConfiguracaoProcessoEleitoral;
        case md::PACOTE_VALIDACAO_CANDIDATOS:
            return ModuloTiposPacotes::TipoPacote::pacoteValidacaoCandidatos;
        case md::PACOTE_ALTERACAO_CANDIDATURA_TRE:
            return ModuloTiposPacotes::TipoPacote::pacoteAlteracaoCandidaturaTRE;
        case md::PACOTE_RESULTADO_TOTALIZACAO:
            return ModuloTiposPacotes::TipoPacote::pacoteResultadoTotalizacao;
        case md::PACOTE_RESPOSTA_VERSAO_PACOTE:
            return ModuloTiposPacotes::TipoPacote::pacoteRespostaVersaoPacote;
        case md::PACOTE_JUNTAS:
            return ModuloTiposPacotes::TipoPacote::pacoteJuntas;
        case md::PACOTE_ELEICOES_SEGUNDO_TURNO:
            return ModuloTiposPacotes::TipoPacote::pacoteEleicoesSegundoTurno;
        case md::PACOTE_PARAMETROS_URNA:
            return ModuloTiposPacotes::TipoPacote::pacoteParametrosUrna;
        case md::PACOTE_NOTIFICACAO_IMPORTACAO:
            return ModuloTiposPacotes::TipoPacote::pacoteNotificacaoImportacao;
        case md::PACOTE_PRESTACAO_CONTAS:
            return ModuloTiposPacotes::TipoPacote::pacotePrestacaoContas;
        case md::PACOTE_SOLICITACAO_ESTADO_SISTEMA:
            return ModuloTiposPacotes::TipoPacote::pacoteSolicitacaoEstadoSistema;
        case md::PACOTE_RESPOSTA_ESTADO_SISTEMA:
            return ModuloTiposPacotes::TipoPacote::pacoteRespostaEstadoSistema;
        case md::PACOTE_SOLICITACAO_VERSAO_PACOTE:
            return ModuloTiposPacotes::TipoPacote::pacoteSolicitacaoVersaoPacote;
        case md::PACOTE_PROCESSAMENTO_RESULTADO_URNA_CADASTRO:
            return ModuloTiposPacotes::TipoPacote::pacoteProcessamentoResultadoUrnaCadastro;
        case md::PACOTE_NOTIFICACAO_DISPONIBILIDADE_SISTEMA:
            return ModuloTiposPacotes::TipoPacote::pacoteNotificacaoDisponibilidadeSistema;
        case md::PACOTE_CANDIDATOS_TSE:
            return ModuloTiposPacotes::TipoPacote::pacoteCandidatosTSE;
        case md::PACOTE_FOTOS_CANDIDATOS_TSE:
            return ModuloTiposPacotes::TipoPacote::pacoteFotosCandidatosTSE;
        case md::PACOTE_ALTERACAO_CANDIDATURA_TSE:
            return ModuloTiposPacotes::TipoPacote::pacoteAlteracaoCandidaturaTSE;
        case md::PACOTE_SOLICITACAO_DADOS_CADASTRO:
            return ModuloTiposPacotes::TipoPacote::pacoteSolicitacaoDadosCadastro;
        case md::PACOTE_DADOS_ELEITOR:
            return ModuloTiposPacotes::TipoPacote::pacoteDadosEleitor;
        case md::PACOTE_DADOS_DOCUMENTACAO_CANDIDATURA:
            return ModuloTiposPacotes::TipoPacote::pacoteDadosDocumentacaoCandidatura;
        case md::PACOTE_COMPLEMENTOS_MUNICIPIOS:
            return ModuloTiposPacotes::TipoPacote::pacoteComplementosMunicipios;
        case md::PACOTE_ELEICAO:
            return ModuloTiposPacotes::TipoPacote::pacoteEleicao;
        case md::PACOTE_SITUACOES_ELEICOES:
            return ModuloTiposPacotes::TipoPacote::pacoteSituacoesEleicoes;
        case md::PACOTE_TRANSFERENCIA_TEMPORARIA_ELEITORES:
            return ModuloTiposPacotes::TipoPacote::pacoteTransferenciaTemporariaEleitores;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_TIPO_PACOTE_INVALIDO_CONVERTE, std::format("Tipo de pacote inválido: {}", tipo));
}

// (original lines 234-256: content not recovered)
#line 257
md::ETipoPacote Utils::DesconverteTipoPacote(const ModuloTiposPacotes::TipoPacote& tipo)
{
    switch (tipo) {
        case ModuloTiposPacotes::TipoPacote::pacoteEleitores:
            return md::PACOTE_ELEITORES;
        case ModuloTiposPacotes::TipoPacote::pacoteMunicipiosZonas:
            return md::PACOTE_MUNICIPIOS_ZONAS;
        case ModuloTiposPacotes::TipoPacote::pacoteImpedidos:
            return md::PACOTE_IMPEDIDOS;
        case ModuloTiposPacotes::TipoPacote::pacoteCandidatosTRE:
            return md::PACOTE_CANDIDATOS_TRE;
        case ModuloTiposPacotes::TipoPacote::pacoteFotosCandidatosTRE:
            return md::PACOTE_FOTOS_CANDIDATOS_TRE;
        case ModuloTiposPacotes::TipoPacote::pacoteCorrespondencia:
            return md::PACOTE_CORRESPONDENCIA;
        case ModuloTiposPacotes::TipoPacote::pacoteSecoes:
            return md::PACOTE_SECOES;
        case ModuloTiposPacotes::TipoPacote::pacoteNotificacaoPacote:
            return md::PACOTE_NOTIFICACAO_PACOTE;
        case ModuloTiposPacotes::TipoPacote::pacoteConfiguracaoProcessoEleitoral:
            return md::PACOTE_CONFIGURACAO_PROCESSO_ELEITORAL;
        case ModuloTiposPacotes::TipoPacote::pacoteValidacaoCandidatos:
            return md::PACOTE_VALIDACAO_CANDIDATOS;
        case ModuloTiposPacotes::TipoPacote::pacoteAlteracaoCandidaturaTRE:
            return md::PACOTE_ALTERACAO_CANDIDATURA_TRE;
        case ModuloTiposPacotes::TipoPacote::pacoteResultadoTotalizacao:
            return md::PACOTE_RESULTADO_TOTALIZACAO;
        case ModuloTiposPacotes::TipoPacote::pacoteRespostaVersaoPacote:
            return md::PACOTE_RESPOSTA_VERSAO_PACOTE;
        case ModuloTiposPacotes::TipoPacote::pacoteJuntas:
            return md::PACOTE_JUNTAS;
        case ModuloTiposPacotes::TipoPacote::pacoteEleicoesSegundoTurno:
            return md::PACOTE_ELEICOES_SEGUNDO_TURNO;
        case ModuloTiposPacotes::TipoPacote::pacoteParametrosUrna:
            return md::PACOTE_PARAMETROS_URNA;
        case ModuloTiposPacotes::TipoPacote::pacoteNotificacaoImportacao:
            return md::PACOTE_NOTIFICACAO_IMPORTACAO;
        case ModuloTiposPacotes::TipoPacote::pacotePrestacaoContas:
            return md::PACOTE_PRESTACAO_CONTAS;
        case ModuloTiposPacotes::TipoPacote::pacoteSolicitacaoEstadoSistema:
            return md::PACOTE_SOLICITACAO_ESTADO_SISTEMA;
        case ModuloTiposPacotes::TipoPacote::pacoteRespostaEstadoSistema:
            return md::PACOTE_RESPOSTA_ESTADO_SISTEMA;
        case ModuloTiposPacotes::TipoPacote::pacoteSolicitacaoVersaoPacote:
            return md::PACOTE_SOLICITACAO_VERSAO_PACOTE;
        case ModuloTiposPacotes::TipoPacote::pacoteProcessamentoResultadoUrnaCadastro:
            return md::PACOTE_PROCESSAMENTO_RESULTADO_URNA_CADASTRO;
        case ModuloTiposPacotes::TipoPacote::pacoteNotificacaoDisponibilidadeSistema:
            return md::PACOTE_NOTIFICACAO_DISPONIBILIDADE_SISTEMA;
        case ModuloTiposPacotes::TipoPacote::pacoteCandidatosTSE:
            return md::PACOTE_CANDIDATOS_TSE;
        case ModuloTiposPacotes::TipoPacote::pacoteFotosCandidatosTSE:
            return md::PACOTE_FOTOS_CANDIDATOS_TSE;
        case ModuloTiposPacotes::TipoPacote::pacoteAlteracaoCandidaturaTSE:
            return md::PACOTE_ALTERACAO_CANDIDATURA_TSE;
        case ModuloTiposPacotes::TipoPacote::pacoteSolicitacaoDadosCadastro:
            return md::PACOTE_SOLICITACAO_DADOS_CADASTRO;
        case ModuloTiposPacotes::TipoPacote::pacoteDadosEleitor:
            return md::PACOTE_DADOS_ELEITOR;
        case ModuloTiposPacotes::TipoPacote::pacoteDadosDocumentacaoCandidatura:
            return md::PACOTE_DADOS_DOCUMENTACAO_CANDIDATURA;
        case ModuloTiposPacotes::TipoPacote::pacoteComplementosMunicipios:
            return md::PACOTE_COMPLEMENTOS_MUNICIPIOS;
        case ModuloTiposPacotes::TipoPacote::pacoteEleicao:
            return md::PACOTE_ELEICAO;
        case ModuloTiposPacotes::TipoPacote::pacoteSituacoesEleicoes:
            return md::PACOTE_SITUACOES_ELEICOES;
        case ModuloTiposPacotes::TipoPacote::pacoteTransferenciaTemporariaEleitores:
            return md::PACOTE_TRANSFERENCIA_TEMPORARIA_ELEITORES;
        default:
            break;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_TIPO_PACOTE_INVALIDO_DESCONVERTE, std::format("Tipo de pacote inválido: {}", tipo.asInt()));
}


ModuloTiposEleitorais::IDPacote Utils::ConverteIdPacote(const md::CIDPacote& idPacote)
{
    ModuloTiposEleitorais::IDPacote id;
    const md::CIDEleitoral& idEleitoral = idPacote.GetIdEleitoral();
    if (idEleitoral.GetTipo() == md::CIDEleitoral::TIPO_PROCESSO_ELEITORAL) {
        id.set_idPacoteEleitoral().select_idProcessoEleitoral() = idEleitoral.GetId();
    } else if (idEleitoral.GetTipo() == md::CIDEleitoral::TIPO_PLEITO) {
        id.set_idPacoteEleitoral().select_idPleito() = idEleitoral.GetId();
    } else if (idEleitoral.GetTipo() == md::CIDEleitoral::TIPO_ELEICAO) {
        id.set_idPacoteEleitoral().select_idEleicao() = idEleitoral.GetId();
    } else {
        throw CUeComumAsnError(EUE_COMUM_ASN_TIPO_ID_ELEITORAL_INVALIDO, "Tipo IDEleitoral inválido.");
    }
    id.set_fase(ConverteFase(idPacote.GetFase()));
    if (idPacote.TemUF()) {
        id.set_siglaUF(idPacote.UF());
    } else {
        id.omit_siglaUF();
    }
    if (idPacote.TemMunicipio()) {
        id.set_codigoMunicipio(idPacote.Municipio());
    } else {
        id.omit_codigoMunicipio();
    }
    if (idPacote.TemZona()) {
        id.set_numeroZona(idPacote.Zona());
    } else {
        id.omit_numeroZona();
    }
    return id;
}

md::CIDPacote Utils::DesconverteIdPacote(const ModuloTiposEleitorais::IDPacote& idPacote)
{
    const md::CIDEleitoral idEleitoral = DesconverteIdEleitoral(idPacote.get_idPacoteEleitoral());
    const EUrnaFase fase = DesconverteFase(idPacote.get_fase());
    if (!idPacote.siglaUF_isPresent()) {
        return md::CIDPacote(idEleitoral, fase);
    }
    const std::string uf = idPacote.get_siglaUF();
    if (!idPacote.codigoMunicipio_isPresent()) {
        return md::CIDPacote(idEleitoral, fase, uf);
    }
    const TMunicipioID municipio = idPacote.get_codigoMunicipio().getValue();
    if (!idPacote.numeroZona_isPresent()) {
        return md::CIDPacote(idEleitoral, fase, uf, municipio);
    }
    return md::CIDPacote(idEleitoral, fase, uf, municipio, idPacote.get_numeroZona().getValue());
}

// (original lines 383-390: content not recovered)
#line 391
ModuloTiposEleitorais::Sistema Utils::ConverteIdSistema(const ESistemaJE& sistema)
{
    switch (sistema) {
        case SISTEMA_CONFIGURADOR:
            return ModuloTiposEleitorais::Sistema::configurador;
        case SISTEMA_INTERCAD:
            return ModuloTiposEleitorais::Sistema::intercad;
        case SISTEMA_CANDIDATURAS:
            return ModuloTiposEleitorais::Sistema::candidaturas;
        case SISTEMA_SIMON:
            return ModuloTiposEleitorais::Sistema::simon;
        case SISTEMA_SEWEB:
            return ModuloTiposEleitorais::Sistema::seweb;
        case SISTEMA_GEDAI:
            return ModuloTiposEleitorais::Sistema::gedai;
        case SISTEMA_URNA_ELETRONICA:
            return ModuloTiposEleitorais::Sistema::urnaEletronica;
        case SISTEMA_SIMULADOR:
            return ModuloTiposEleitorais::Sistema::simulador;
        case SISTEMA_PARAMETRIZADOR:
            return ModuloTiposEleitorais::Sistema::parametrizador;
        case SISTEMA_GERADOR_DE_BASES:
            return ModuloTiposEleitorais::Sistema::geradorDeBases;
        case SISTEMA_SISTOT:
            return ModuloTiposEleitorais::Sistema::sistot;
        case SISTEMA_PADA_UE:
            return ModuloTiposEleitorais::Sistema::padaUE;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_SISTEMA_INVALIDO_CONVERTE, std::format("Sistema inválido: {}", sistema));
}


ESistemaJE Utils::DesconverteIdSistema(const ModuloTiposEleitorais::Sistema& sistema)
{
    switch (sistema) {
        case ModuloTiposEleitorais::Sistema::configurador:
            return SISTEMA_CONFIGURADOR;
        case ModuloTiposEleitorais::Sistema::intercad:
            return SISTEMA_INTERCAD;
        case ModuloTiposEleitorais::Sistema::candidaturas:
            return SISTEMA_CANDIDATURAS;
        case ModuloTiposEleitorais::Sistema::gedai:
            return SISTEMA_GEDAI;
        case ModuloTiposEleitorais::Sistema::urnaEletronica:
            return SISTEMA_URNA_ELETRONICA;
        case ModuloTiposEleitorais::Sistema::simulador:
            return SISTEMA_SIMULADOR;
        case ModuloTiposEleitorais::Sistema::parametrizador:
            return SISTEMA_PARAMETRIZADOR;
        case ModuloTiposEleitorais::Sistema::geradorDeBases:
            return SISTEMA_GERADOR_DE_BASES;
        case ModuloTiposEleitorais::Sistema::sistot:
            return SISTEMA_SISTOT;
        case ModuloTiposEleitorais::Sistema::seweb:
            return SISTEMA_SEWEB;
        case ModuloTiposEleitorais::Sistema::simon:
            return SISTEMA_SIMON;
        case ModuloTiposEleitorais::Sistema::padaUE:
            return SISTEMA_PADA_UE;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_SISTEMA_INVALIDO_DESCONVERTE, std::format("Sistema inválido: {}", sistema.asInt()));
}

// (original lines 454-470: content not recovered)
#line 471
md::CSexo::ESexo Utils::DesconverteSexo(ModuloTiposEleitorais::CodigoSexo::NamedNumber sexo)
{
    switch (sexo) {
        case ModuloTiposEleitorais::CodigoSexo::sexoMasculino:
            return md::CSexo::SEXO_MASCULINO;
        case ModuloTiposEleitorais::CodigoSexo::sexoFeminino:
            return md::CSexo::SEXO_FEMININO;
        case ModuloTiposEleitorais::CodigoSexo::sexoNaoInformado:
            return md::CSexo::SEXO_NAO_INFORMADO;
        default:
            break;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_SEXO_INVALIDO, std::format("Sexo inválido: {}", sexo));
}

md::ETipoAbrangencia Utils::DesconverteAbrangencia(ModuloTiposEleitorais::TipoAbrangencia::NamedNumber abrangencia)
{
    switch (abrangencia) {
        case ModuloTiposEleitorais::TipoAbrangencia::municipal:
            return md::ABRANGENCIA_MUNICIPAL;
        case ModuloTiposEleitorais::TipoAbrangencia::estadual:
            return md::ABRANGENCIA_ESTADUAL;
        case ModuloTiposEleitorais::TipoAbrangencia::federal:
            return md::ABRANGENCIA_FEDERAL;
        default:
            break;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_ABRANGENCIA_INVALIDA, std::format("Abrangência inválida: {}", abrangencia));
}

// (original lines 501-502: content not recovered)
#line 503
ModuloTiposEleitorais::TipoAbrangencia::NamedNumber Utils::ConverteAbrangencia(md::ETipoAbrangencia abrangencia)
{
    switch (abrangencia) {
        case md::ABRANGENCIA_MUNICIPAL:
            return ModuloTiposEleitorais::TipoAbrangencia::municipal;
        case md::ABRANGENCIA_ESTADUAL:
            return ModuloTiposEleitorais::TipoAbrangencia::estadual;
        case md::ABRANGENCIA_FEDERAL:
            return ModuloTiposEleitorais::TipoAbrangencia::federal;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_ABRANGENCIA_INVALIDA_CONVERTE, std::format("Abrangência inválida: {}", static_cast<int>(abrangencia)));
}

ModuloTiposCadastro::TipoLocalVotacao Utils::ConverteTipoLocalVotacao(ETipoLocalVotacao tipo)
{
    switch (tipo) {
        case LOCAL_VOTACAO_NORMAL:
            return ModuloTiposCadastro::TipoLocalVotacao::normal;
        case LOCAL_VOTACAO_EM_TRANSITO:
            return ModuloTiposCadastro::TipoLocalVotacao::emTransito;
        case LOCAL_VOTACAO_PRESO_PROVISORIO:
            return ModuloTiposCadastro::TipoLocalVotacao::presoProvisorio;
        case LOCAL_VOTACAO_TEMPORARIO:
            return ModuloTiposCadastro::TipoLocalVotacao::temporario;
        default:
            break;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_TIPO_LOCAL_INVALIDO_CONVERTE, std::format("Tipo de local de votação inválido: {}", tipo));
}

// (original lines 533-534: content not recovered)
#line 535
ETipoLocalVotacao Utils::DesconverteTipoLocalVotacao(ModuloTiposCadastro::TipoLocalVotacao tipo)
{
    switch (tipo) {
        case ModuloTiposCadastro::TipoLocalVotacao::normal:
            return LOCAL_VOTACAO_NORMAL;
        case ModuloTiposCadastro::TipoLocalVotacao::emTransito:
            return LOCAL_VOTACAO_EM_TRANSITO;
        case ModuloTiposCadastro::TipoLocalVotacao::presoProvisorio:
            return LOCAL_VOTACAO_PRESO_PROVISORIO;
        case ModuloTiposCadastro::TipoLocalVotacao::temporario:
            return LOCAL_VOTACAO_TEMPORARIO;
        default:
            break;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_TIPO_LOCAL_INVALIDO_DESCONVERTE, std::format("Tipo de local de votação inválido: {}", tipo.asInt()));
}

// (original lines 552-555: content not recovered)
#line 556
ModuloTiposEleitorais::Turno Utils::ConverteTurno(EUrnaTurno turno)
{
    switch (turno) {
        case SEM_TURNO:
            return ModuloTiposEleitorais::Turno::semTurno;
        case TURNO_1:
            return ModuloTiposEleitorais::Turno::turno1;
        case TURNO_2:
            return ModuloTiposEleitorais::Turno::turno2;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_TURNO_INVALIDO_CONVERTE, std::format("Turno inválido: {}", turno));
}

// (original lines 569-570: content not recovered)
#line 571
EUrnaTurno Utils::DesconverteTurno(ModuloTiposEleitorais::Turno turno)
{
    switch (turno) {
        case ModuloTiposEleitorais::Turno::semTurno:
            return SEM_TURNO;
        case ModuloTiposEleitorais::Turno::turno1:
            return TURNO_1;
        case ModuloTiposEleitorais::Turno::turno2:
            return TURNO_2;
    }
    throw CUeComumAsnError(EUE_COMUM_ASN_TURNO_INVALIDO_DESCONVERTE, std::format("Turno inválido: {}", turno.asInt()));
}



} // namespace comum::asn
