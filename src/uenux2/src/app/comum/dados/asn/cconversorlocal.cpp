// Reconstruction: comum::asn::CConversorLocal's DoDesconverte (target fn 11452) and DoConverte (fn 11451); their
// records (line 70, and lines 120, 124 and 128, column 15) place their throws. Where DoDesconverte begins is chosen;
// src/units/296-uenux2-relatorios-impressao.mk says what its bytes decide.
#include "app/comum/dados/asn/cconversorlocal.h"

#include "app/comum/dados/asn/cconversorsecaoeleitoral.h"
#include "app/comum/dados/asn/municipiozona/cconversorcomplementomunicipio.h"
#include "app/comum/dados/asn/municipiozona/cconversormunicipio.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 13-33: content not recovered)
#line 34
md::CLocal CConversorLocal::DoDesconverte(const TEntidade& entidade) const
{
    const uedword idPE = entidade.get_idPE().getValue();
    const std::string pais = entidade.get_pais();
    const std::string siglaUF = entidade.get_uf().get_sigla();
    const std::string nomeUF = entidade.get_uf().get_nome();

    CConversorMunicipio conversorMunicipio;
    const md::CMunicipio municipio = conversorMunicipio.Desconverte(entidade.get_municipio());
    CConversorComplementoMunicipio conversorComplemento;
    const md::CComplementoMunicipio complemento =
        conversorComplemento.Desconverte(entidade.get_complementoMunicipio());
    const bool comBiometria =
        entidade.get_municipio().comBiometria_isPresent() && entidade.get_municipio().get_comBiometria();
    md::CInfoMunicipio infoMunicipio(municipio.GetCodigo(), municipio.GetNome(), complemento.GetFusoHorario(),
                                     comBiometria);
    if (complemento.TemHorarioVerao()) {
        infoMunicipio = md::CInfoMunicipio(municipio.GetCodigo(), municipio.GetNome(), complemento.GetFusoHorario(),
                                           comBiometria, complemento.GetHorarioVerao());
    }

    switch (entidade.get_id().currentSelection()) {
    case ModuloLocal::Local::id::value_type::secao0: {
        CConversorSecaoEleitoral conversorSecao;
        return md::CLocal(idPE, pais, siglaUF, nomeUF, infoMunicipio,
                          conversorSecao.Desconverte(entidade.get_id().get_secao()));
    }
    case ModuloLocal::Local::id::value_type::contingencia1: {
        const ModuloLocal::IdentificacaoUrnaContingencia& contingencia = entidade.get_id().get_contingencia();
        const ModuloLocal::IdentificacaoUrnaContingencia::municipioZona::value_type& municipioZona =
            contingencia.get_municipioZona();
        return md::CLocal(idPE, pais, siglaUF, nomeUF, infoMunicipio,
                          md::CIdentificacaoUrnaContingencia(eUrnaContingencia, municipioZona.get_municipio().getValue(),
                                                             municipioZona.get_zona().getValue()));
    }
    default:
        throw CUeComumDadosError(EUE_COMUM_DADOS_7887, "CHOICE de id inválida.");
    }
}

// (original lines 74-83: content not recovered)
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
