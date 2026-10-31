// Reconstruction: comum::asn::CConversorDadoCarga::ConverteTipoUrna and DesconverteTipoUrna (target fns 5693, 5694, the
// records at lines 61, 84 and 88). ConverteModelo and DesconverteModelo, the records at lines 105, 127 and 131, and the
// DoConverte and DoDesconverte they are inlined into, are not reconstructed; those lines stay blank.
#include "app/comum/dados/asn/estadoaplicacao/cconversordadocarga.h"

#include <format>

#include "app/comum/dados/asn/estadoaplicacao/enumeradoasn.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 13-46: content not recovered)
#line 47
ModuloEstadoGeralUrna::TipoUrnaOperacao CConversorDadoCarga::ConverteTipoUrna(const EUrnaTipo tipo) const
{
    switch (tipo) {
        case eUrnaSemTipo:
            return ModuloEstadoGeralUrna::TipoUrnaOperacao::semtipo;
        case eUrnaVota:
            return ModuloEstadoGeralUrna::TipoUrnaOperacao::vota;
        case eUrnaContingencia:
            return ModuloEstadoGeralUrna::TipoUrnaOperacao::contingencia;
        case eUrnaContingenciaVota:
            return ModuloEstadoGeralUrna::TipoUrnaOperacao::contingenciavota;
        case eUrnaContingenciaVotaRecupera:
            return ModuloEstadoGeralUrna::TipoUrnaOperacao::contingenciavotarecupera;
        default:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7909,
                                     std::format("Valor inválido para EUrnaTipo: {}", static_cast<int>(tipo)));
    }
}

// (original lines 66-69: content not recovered)
#line 70
EUrnaTipo CConversorDadoCarga::DesconverteTipoUrna(const ModuloEstadoGeralUrna::TipoUrnaOperacao& tipo) const
{
    switch (tipo) {
        case ModuloEstadoGeralUrna::TipoUrnaOperacao::semtipo:
            return eUrnaSemTipo;
        case ModuloEstadoGeralUrna::TipoUrnaOperacao::vota:
            return eUrnaVota;
        case ModuloEstadoGeralUrna::TipoUrnaOperacao::contingencia:
            return eUrnaContingencia;
        case ModuloEstadoGeralUrna::TipoUrnaOperacao::contingenciavota:
            return eUrnaContingenciaVota;
        case ModuloEstadoGeralUrna::TipoUrnaOperacao::contingenciavotarecupera:
            return eUrnaContingenciaVotaRecupera;
        case ModuloEstadoGeralUrna::TipoUrnaOperacao::unknownEnumeration_:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7911,
                                     std::format("Valor inválido para TipoUrnaOperacao: {}", tipo));
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7912,
                             std::format("Valor inválido para TipoUrnaOperacao: {}", tipo));
}

} // namespace comum::asn

// <stubs>
// f11402 · 1603 B · unmatched · name unknown
// void f11402(i32, i32, i32) { ... }
// </stubs>
