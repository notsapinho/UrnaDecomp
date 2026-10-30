// comum::asn::Utils (/home/rubio/tse/uenux2/src/app/comum/asn/util.cpp). Every throw is a record of the target, so each
// sits on its record's line and column; the lines between them are blank where the original is not recovered. The
// switches' forms and the enumerators are chosen, and 96-uenux2-app-comum-asn.mk lists what the bytes do and do not
// decide, with the members of this file that are not written.
#include "app/comum/asn/util.h"

#include <format>

#include "app/comum/asn/euecomumasnerror.h"

namespace comum::asn {

// (original lines 13-37: content not recovered)
#line 38
// <stubs>
// f1713 · 556 B · unmatched · name unknown
// void f1713(i32, i32) { ... }
// </stubs>

// (original lines 43-91: content not recovered)
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

// (original lines 331-485: content not recovered)
#line 486
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

// (original lines 501-515: content not recovered)
#line 516
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

} // namespace comum::asn

// <stubs>
// f11401 · 1227 B · unmatched · name unknown
// void f11401(i32, i32, i32) { ... }
// </stubs>
