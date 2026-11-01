// Reconstruction: comum::asn::CConversorUrna's DoConverte and DoDesconverte (target fns 10287 and 10284), with the four
// static members binaryen inlines into them. Their throws are records of the target (lines 77, 95, 117 and 139, column
// 19); DoConverte and DoDesconverte have none, and the lines of all the code around the throws are a choice.

#include "app/comum/gravadores/asn/cconversorurna.h"

#include <format>
#include <string>
#include <vector>

#include "app/comum/asn/util.h"
#include "app/comum/gravadores/asn/cconversorcorrespresultado.h"
#include "app/comum/gravadores/asn/cconversortipoapuracaosa.h"
#include "app/comum/gravadores/asn/util.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::asn {

CConversorUrna::TEntidade CConversorUrna::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_tipoUrna(ConverteTipoUrna(dado.GetTipoUrna()));
    entidade.set_versaoVotacao(dado.GetVersaoVotacao());
    const CConversorCorrespResultado conversorCorrespondencia;
    const ModuloTiposResultadosEcoUrna::CorrespondenciaResultado correspondencia =
        conversorCorrespondencia.Converte(dado.GetCorrespondencia());
    entidade.set_correspondenciaResultado() = correspondencia;
    entidade.set_tipoArquivo(ConverteTipoArquivo(dado.GetTipoArquivo()));
    const std::vector<char> numeroSerieFV = ConverteSerialFlash(dado.GetNumeroSerieFV());
    entidade.set_numeroSerieFV(numeroSerieFV);
    if (dado.GetTipoApuracao()) {
        const CConversorTipoApuracaoSA conversorTipoApuracao;
        entidade.set_motivoUtilizacaoSA() = conversorTipoApuracao.Converte(*dado.GetTipoApuracao());
    } else {
        entidade.omit_motivoUtilizacaoSA();
    }
    return entidade;
}

md::CUrna CConversorUrna::DoDesconverte(const TEntidade& entidade) const
{
    const CConversorCorrespResultado conversorCorrespondencia;
    const EUrnaTipo tipoUrna = DesconverteTipoUrna(entidade.get_tipoUrna());
    const std::string versaoVotacao = entidade.get_versaoVotacao();
    const md::CCorrespondenciaResultado correspondencia =
        conversorCorrespondencia.Desconverte(entidade.get_correspondenciaResultado());
    const ETipoArquivo tipoArquivo = DesconverteTipoArquivo(entidade.get_tipoArquivo());
    const std::string numeroSerieFV = DesconverteSerialFlash(entidade.get_numeroSerieFV());
    const CConversorTipoApuracaoSA conversorTipoApuracao;
    if (entidade.motivoUtilizacaoSA_isPresent()) {
        return TDado(tipoUrna, versaoVotacao, correspondencia, tipoArquivo, numeroSerieFV,
            conversorTipoApuracao.Desconverte(entidade.get_motivoUtilizacaoSA()));
    }
    return TDado(tipoUrna, versaoVotacao, correspondencia, tipoArquivo, numeroSerieFV);
}

// (original lines 57-64: content not recovered)
#line 65
ModuloTiposResultadosEcoUrna::TipoUrna::NamedNumber CConversorUrna::ConverteTipoUrna(EUrnaTipo tipoUrna)
{
    switch (tipoUrna) {
        case eUrnaVota:
            return ModuloTiposResultadosEcoUrna::TipoUrna::secao;
        case eUrnaContingencia:
            return ModuloTiposResultadosEcoUrna::TipoUrna::contingencia;
        case eUrnaContingenciaVota:
            return ModuloTiposResultadosEcoUrna::TipoUrna::contingenciaSecao;
        case eUrnaContingenciaVotaRecupera:
            return ModuloTiposResultadosEcoUrna::TipoUrna::contingenciaEncerrandoSecao;
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8627, std::format("Tipo de urna inválido: {}", static_cast<int>(tipoUrna)));
    }
}

// (original lines 81-82: content not recovered)
#line 83
EUrnaTipo CConversorUrna::DesconverteTipoUrna(ModuloTiposResultadosEcoUrna::TipoUrna::NamedNumber tipoUrna)
{
    switch (tipoUrna) {
        case ModuloTiposResultadosEcoUrna::TipoUrna::secao:
            return eUrnaVota;
        case ModuloTiposResultadosEcoUrna::TipoUrna::contingencia:
            return eUrnaContingencia;
        case ModuloTiposResultadosEcoUrna::TipoUrna::contingenciaSecao:
            return eUrnaContingenciaVota;
        case ModuloTiposResultadosEcoUrna::TipoUrna::contingenciaEncerrandoSecao:
            return eUrnaContingenciaVotaRecupera;
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8628, std::format("Tipo de urna inválido: {}", tipoUrna));
    }
}

// (original lines 99-100: content not recovered)
#line 101
ModuloTiposResultadosEcoUrna::TipoArquivo::NamedNumber CConversorUrna::ConverteTipoArquivo(ETipoArquivo tipoArquivo)
{
    switch (tipoArquivo) {
        case TIPO_ARQUIVO_VOTACAO_UE:
            return ModuloTiposResultadosEcoUrna::TipoArquivo::votacaoUE;
        case TIPO_ARQUIVO_VOTACAO_RED:
            return ModuloTiposResultadosEcoUrna::TipoArquivo::votacaoRED;
        case TIPO_ARQUIVO_SA_MISTA_MR_PARCIAL_CEDULA:
            return ModuloTiposResultadosEcoUrna::TipoArquivo::saMistaMRParcialCedula;
        case TIPO_ARQUIVO_SA_MISTA_BU_IMPRESSO_CEDULA:
            return ModuloTiposResultadosEcoUrna::TipoArquivo::saMistaBUImpressoCedula;
        case TIPO_ARQUIVO_SA_MANUAL:
            return ModuloTiposResultadosEcoUrna::TipoArquivo::saManual;
        case TIPO_ARQUIVO_SA_ELETRONICA:
            return ModuloTiposResultadosEcoUrna::TipoArquivo::saEletronica;
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8629, std::format("Tipo de arquivo inválido: {}", tipoArquivo));
    }
}

// (original lines 121-122: content not recovered)
#line 123
ETipoArquivo CConversorUrna::DesconverteTipoArquivo(ModuloTiposResultadosEcoUrna::TipoArquivo::NamedNumber tipoArquivo)
{
    switch (tipoArquivo) {
        case ModuloTiposResultadosEcoUrna::TipoArquivo::votacaoUE:
            return TIPO_ARQUIVO_VOTACAO_UE;
        case ModuloTiposResultadosEcoUrna::TipoArquivo::votacaoRED:
            return TIPO_ARQUIVO_VOTACAO_RED;
        case ModuloTiposResultadosEcoUrna::TipoArquivo::saMistaMRParcialCedula:
            return TIPO_ARQUIVO_SA_MISTA_MR_PARCIAL_CEDULA;
        case ModuloTiposResultadosEcoUrna::TipoArquivo::saMistaBUImpressoCedula:
            return TIPO_ARQUIVO_SA_MISTA_BU_IMPRESSO_CEDULA;
        case ModuloTiposResultadosEcoUrna::TipoArquivo::saManual:
            return TIPO_ARQUIVO_SA_MANUAL;
        case ModuloTiposResultadosEcoUrna::TipoArquivo::saEletronica:
            return TIPO_ARQUIVO_SA_ELETRONICA;
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8630, std::format("Tipo de arquivo inválido: {}", tipoArquivo));
    }
}

} // namespace comum::asn
