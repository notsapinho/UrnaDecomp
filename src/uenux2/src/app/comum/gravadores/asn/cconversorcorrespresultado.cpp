// Reconstruction: comum::asn::CConversorCorrespResultado's DoConverte and DoDesconverte (target fns 10289 and 10288).
// Their throws are records of the target (lines 53 and 85, columns 23 and 15); the lines of the code around them are a
// choice.

#include "app/comum/gravadores/asn/cconversorcorrespresultado.h"

#include <format>

#include "app/comum/gravadores/asn/cconversorcarga.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::asn {

// (original lines 14-23: content not recovered)
#line 24
CConversorCorrespResultado::TEntidade CConversorCorrespResultado::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    if (dado.GetSecao() == 0) {
        ModuloTiposEleitorais::IdentificacaoContingencia contingencia;
        contingencia.set_municipioZona().set_municipio(dado.GetMunicipio());
        contingencia.set_municipioZona().set_zona(dado.GetZona());
        entidade.set_identificacao().select_identificacaoContingencia() = contingencia;
    } else {
        switch (dado.GetTipoUrna()) {
            case eUrnaVota:
            case eUrnaContingenciaVota:
            case eUrnaContingenciaVotaRecupera: {
                ModuloTiposEleitorais::IdentificacaoSecaoEleitoral secao;
                secao.set_municipioZona().set_municipio(dado.GetMunicipio());
                secao.set_municipioZona().set_zona(dado.GetZona());
                secao.set_secao(dado.GetSecao());
                secao.set_local(1);
                entidade.set_identificacao().select_identificacaoSecaoEleitoral() = secao;
                break;
            }
            case eUrnaContingencia: {
                ModuloTiposEleitorais::IdentificacaoContingencia contingencia;
                contingencia.set_municipioZona().set_municipio(dado.GetMunicipio());
                contingencia.set_municipioZona().set_zona(dado.GetZona());
                entidade.set_identificacao().select_identificacaoContingencia() = contingencia;
                break;
            }
            case eUrnaSemTipo:
                throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8601, std::format("Tipo inválido de urna: {}", static_cast<int>(dado.GetTipoUrna())));
        }
    }
    const CConversorCarga conversorCarga;
    entidade.set_carga() = conversorCarga.Converte(dado.GetCarga());
    return entidade;
}

// (original lines 61-63: content not recovered)
#line 64
md::CCorrespondenciaResultado CConversorCorrespResultado::DoDesconverte(const TEntidade& entidade) const
{
    const ModuloTiposResultadosEcoUrna::Identificacao& identificacao = entidade.get_identificacao();
    uedword municipio;
    ueword zona;
    EUrnaTipo tipoUrna;
    ueword secao = 0;
    if (identificacao.identificacaoSecaoEleitoral_isSelected()) {
        const ModuloTiposEleitorais::IdentificacaoSecaoEleitoral& secaoEleitoral =
            identificacao.get_identificacaoSecaoEleitoral();
        municipio = secaoEleitoral.get_municipioZona().get_municipio().getValue();
        zona = secaoEleitoral.get_municipioZona().get_zona().getValue();
        secao = secaoEleitoral.get_secao().getValue();
        tipoUrna = eUrnaVota;
    } else if (identificacao.identificacaoContingencia_isSelected()) {
        const ModuloTiposEleitorais::IdentificacaoContingencia& contingencia =
            identificacao.get_identificacaoContingencia();
        municipio = contingencia.get_municipioZona().get_municipio().getValue();
        zona = contingencia.get_municipioZona().get_zona().getValue();
        tipoUrna = eUrnaContingencia;
    } else {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8602, "Entidade em formato incorreto");
    }
    const CConversorCarga conversorCarga;
    return TDado(municipio, zona, secao, conversorCarga.Desconverte(entidade.get_carga()), tipoUrna);
}

} // namespace comum::asn
