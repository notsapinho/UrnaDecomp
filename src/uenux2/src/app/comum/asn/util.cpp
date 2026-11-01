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

// (original lines 67-91: content not recovered)
#line 92
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

// (original lines 120-227: content not recovered)
#line 228
// <stubs>
// f11438 · 2119 B · unmatched · name unknown
// void f11438(i32, i32, i32) { ... }
// </stubs>

// (original lines 233-325: content not recovered)
#line 326
// <stubs>
// f11437 · 2893 B · unmatched · name unknown
// void f11437(i32, i32, i32) { ... }
// </stubs>

// (original lines 331-470: content not recovered)
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
