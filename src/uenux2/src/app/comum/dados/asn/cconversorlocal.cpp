// Reconstruction: comum::asn::CConversorLocal::DoConverte (target fn 11451); its records (lines 120, 124 and 128, column
// 15) place its throws. DoDesconverte (fn 11452, record line 70) is pending: 157-uenux2-app-comum-dados-md-pending.cpp
// says what it waits for.
#include "app/comum/dados/asn/cconversorlocal.h"

#include "app/comum/dados/asn/cconversorsecaoeleitoral.h"
#include "app/comum/dados/asn/municipiozona/cconversorcomplementomunicipio.h"
#include "app/comum/dados/asn/municipiozona/cconversormunicipio.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 13-83: content not recovered)
#line 84
ModuloLocal::Local CConversorLocal::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_idPE(dado.GetIdPE());
    entidade.set_pais(dado.GetNomePais());

    ModuloTiposEleitorais::UF uf;
    uf.set_sigla(dado.GetSiglaUF());
    uf.set_nome(dado.GetNomeUF());
    entidade.set_uf() = uf;

    CConversorMunicipio conversorMunicipio;
    const md::CMunicipio municipio(
        dado.GetMunicipio().GetCodigo(), dado.GetMunicipio().GetNome(), dado.GetMunicipio().EhUrnaBiometrica());
    const ModuloTiposCadastro::Municipio entidadeMunicipio = conversorMunicipio.Converte(municipio);
    entidade.set_municipio() = entidadeMunicipio;

    CConversorComplementoMunicipio conversorComplemento;
    if (dado.GetMunicipio().TemHorarioVerao()) {
        const md::CComplementoMunicipio complemento(
            dado.GetMunicipio().GetCodigo(), dado.GetMunicipio().GetFusoHorario(), dado.GetMunicipio().GetHorarioVerao());
        entidade.set_complementoMunicipio() = conversorComplemento.Converte(complemento);
    } else {
        const md::CComplementoMunicipio complemento(dado.GetMunicipio().GetCodigo(), dado.GetMunicipio().GetFusoHorario());
        entidade.set_complementoMunicipio() = conversorComplemento.Converte(complemento);
    }

    if (dado.TemContingencia()) {
        ModuloLocal::IdentificacaoUrnaContingencia contingencia;
        contingencia.set_municipioZona().set_municipio(dado.GetContingencia().GetMunicipio());
        contingencia.set_municipioZona().set_zona(dado.GetContingencia().GetZona());
        entidade.set_id().select_contingencia() = contingencia;
    } else if (dado.TemSecao()) {
        CConversorSecaoEleitoral conversorSecao;
        entidade.set_id().select_secao() = conversorSecao.Converte(dado.GetSecao());
    } else {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7888, "Tipo de local indefinido.");
    }

    if (!entidade.isValid()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7889, "A entidade não está válida.");
    }

    if (!entidade.isStrictlyValid()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7890, "A entidade não está estritamente válida.");
    }
    return entidade;
}

} // namespace comum::asn
