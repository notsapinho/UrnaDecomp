// Reconstruction: comum::asn::CConversorDadoCarga (target fns 11401, 11402, 5693, 5694). The records place the throws.


#include "app/comum/dados/asn/estadoaplicacao/cconversordadocarga.h"

#include <format>
#include "app/comum/asn/util.h"
#include "app/comum/dados/asn/estadoaplicacao/enumeradoasn.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 13-17: content not recovered)
#line 18
CConversorDadoCarga::TDado CConversorDadoCarga::DoDesconverte(const TEntidade& entidade) const
{
    const EUrnaTurno turno = Utils::DesconverteTurno(entidade.get_turno());
    const EUrnaTipo tipoUrnaT1 = DesconverteTipoUrna(entidade.get_tipoUrnaT1());
    const EUrnaTipo tipoUrnaT2 = DesconverteTipoUrna(entidade.get_tipoUrnaT2());
    const EUrnaFase fase = Utils::DesconverteFase(entidade.get_fase());
    return TDado(turno, tipoUrnaT1, tipoUrnaT2, DesconverteModelo(entidade.get_modelo()), fase);
}

CConversorDadoCarga::TEntidade CConversorDadoCarga::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_turno() = Utils::ConverteTurno(dado.GetTurno());
    entidade.set_tipoUrnaT1(ConverteTipoUrna(dado.GetTipoUrnaT1()));
    entidade.set_tipoUrnaT2(ConverteTipoUrna(dado.GetTipoUrnaT2()));
    entidade.set_fase() = Utils::ConverteFase(dado.GetFase());
    entidade.set_modelo() = ConverteModelo(dado.GetModelo());
    return entidade;
}

// (original lines 38-46: content not recovered)
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


ModuloTiposEcoUrna::ModeloEquipamento CConversorDadoCarga::ConverteModelo(const EUrnaModelo modelo) const
{
    switch (modelo) {
        case eModeloUE2013:
            return ModuloTiposEcoUrna::ModeloEquipamento::ue2013;
        case eModeloUE2015:
            return ModuloTiposEcoUrna::ModeloEquipamento::ue2015;
        case eModeloUE2020:
            return ModuloTiposEcoUrna::ModeloEquipamento::ue2020;
        case eModeloUE2022:
            return ModuloTiposEcoUrna::ModeloEquipamento::ue2022;
        default:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7913,
                                     std::format("Valor não suportado para EUrnaModelo: {}", modelo));
    }
}

// (original lines 110-113: content not recovered)
#line 114
EUrnaModelo CConversorDadoCarga::DesconverteModelo(const ModuloTiposEcoUrna::ModeloEquipamento& modelo) const
{
    switch (modelo) {
        case ModuloTiposEcoUrna::ModeloEquipamento::ue2022:
            return eModeloUE2022;
        case ModuloTiposEcoUrna::ModeloEquipamento::ue2020:
            return eModeloUE2020;
        case ModuloTiposEcoUrna::ModeloEquipamento::ue2015:
            return eModeloUE2015;
        case ModuloTiposEcoUrna::ModeloEquipamento::ue2013:
            return eModeloUE2013;
        case ModuloTiposEcoUrna::ModeloEquipamento::tpm20:
        case ModuloTiposEcoUrna::ModeloEquipamento::unknownEnumeration_:
            throw CUeComumDadosError(EUE_COMUM_DADOS_7915,
                                     std::format("Valor não suportado para ModeloUrna: {}", modelo));
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7916,
                             std::format("Valor inválido para ModeloUrna: {}", modelo));
}







} // namespace comum::asn
