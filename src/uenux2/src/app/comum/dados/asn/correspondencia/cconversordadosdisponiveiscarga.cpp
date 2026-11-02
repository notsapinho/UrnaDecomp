// Reconstruction: comum::asn::CConversorDadosDisponiveisCarga::DoConverte and DoDesconverte (target fns 11424 and 11423).
// No record names this file or a line in it: the records the two load are inlined callees' (IConversorASN::Converte's,
// iconversorasn.h:56, and CDadosDisponiveisCarga's constructor's, cdadosdisponiveiscarga.cpp). DoConverte comes first, as
// the use band orders the two (11424 links ahead of 11423). The forms the bodies decide are in fragment 245.
#include "app/comum/dados/asn/correspondencia/cconversordadosdisponiveiscarga.h"

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "app/comum/asn/util.h"
#include "app/comum/dados/asn/cconversorsecaoeleitoral.h"
#include "app/comum/dados/asn/correspondencia/cconversorcabecalhopacote.h"
#include "app/comum/dados/asn/municipiozona/cconversorcomplementomunicipio.h"
#include "app/comum/dados/asn/municipiozona/cconversormunicipio.h"

namespace comum::asn {

ModuloDadosDisponiveisCarga::DadosDisponiveisCarga CConversorDadosDisponiveisCarga::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_fase() = Utils::ConverteFase(dado.GetFase());
    entidade.set_idPE(dado.GetIdPE());
    entidade.set_idPleito(dado.GetIdPleito());
    entidade.set_serialFlashCarga(dado.GetSerialFlashCarga());
    entidade.set_pais(dado.GetPais());

    ModuloTiposEleitorais::UF uf;
    uf.set_sigla(dado.GetSiglaUF());
    uf.set_nome(dado.GetNomeUF());
    entidade.set_uf() = uf;
    entidade.set_zona(dado.GetZona());

    CConversorComplementoMunicipio conversorComplemento;
    CConversorMunicipio conversorMunicipio;
    CConversorSecaoEleitoral conversorSecao;
    ASN1::SEQUENCE_OF<ModuloDadosDisponiveisCarga::MunicipioDisponivel> municipios;
    for (const md::CMunicipioDisponivel& municipioDisponivel : dado.GetMunicipios()) {
        const md::CInfoMunicipio& info = municipioDisponivel.GetMunicipio();
        const md::CMunicipio municipio(info.GetCodigo(), info.GetNome(), info.EhUrnaBiometrica());
        ModuloDadosDisponiveisCarga::MunicipioDisponivel entidadeMunicipio;
        entidadeMunicipio.set_municipio() = conversorMunicipio.Converte(municipio);
        entidadeMunicipio.set_municipio().set_comBiometria(info.EhUrnaBiometrica());

        md::CComplementoMunicipio complemento(info.GetCodigo(), info.GetFusoHorario());
        if (info.TemHorarioVerao()) {
            complemento = md::CComplementoMunicipio(info.GetCodigo(), info.GetFusoHorario(), info.GetHorarioVerao());
        }
        entidadeMunicipio.set_complementoMunicipio() = conversorComplemento.Converte(complemento);

        ASN1::SEQUENCE_OF<ModuloLocal::SecaoEleitoral> secoes;
        std::transform(municipioDisponivel.GetSecoes().begin(), municipioDisponivel.GetSecoes().end(),
                       std::back_inserter(secoes),
                       [&conversorSecao](const md::CSecaoEleitoral& secao) { return conversorSecao.Converte(secao); });
        static_cast<ASN1::SEQUENCE_OF<ModuloLocal::SecaoEleitoral>&>(entidadeMunicipio.set_secoes()) = secoes;
        municipios.push_back(entidadeMunicipio);
    }
    static_cast<ASN1::SEQUENCE_OF<ModuloDadosDisponiveisCarga::MunicipioDisponivel>&>(entidade.set_municipios()) =
        municipios;
    static_cast<ASN1::SEQUENCE_OF<ModuloTiposEleitorais::CabecalhoPacote>&>(entidade.set_pacotesImportados()) =
        ConvertePacotes(dado.GetPacotes());
    return entidade;
}

md::CDadosDisponiveisCarga CConversorDadosDisponiveisCarga::DoDesconverte(const TEntidade& entidade) const
{
    const EUrnaFase fase = Utils::DesconverteFase(entidade.get_fase());
    const TProcessoEleitoralID idPE = entidade.get_idPE().getValue();
    const TPleitoID idPleito = entidade.get_idPleito().getValue();
    const std::string pais = entidade.get_pais();
    const std::string serialFlashCarga = entidade.get_serialFlashCarga();
    const std::string siglaUF = entidade.get_uf().get_sigla();
    const std::string nomeUF = entidade.get_uf().get_nome();
    const TZonaID zona = entidade.get_zona().getValue();

    CConversorMunicipio conversorMunicipio;
    CConversorComplementoMunicipio conversorComplemento;
    CConversorSecaoEleitoral conversorSecao;
    std::vector<md::CMunicipioDisponivel> municipios;
    for (const auto& municipioDisponivel : entidade.get_municipios()) {
        const md::CMunicipio municipio = conversorMunicipio.Desconverte(municipioDisponivel.get_municipio());
        const md::CComplementoMunicipio complemento =
            conversorComplemento.Desconverte(municipioDisponivel.get_complementoMunicipio());
        const bool urnaBiometrica = municipioDisponivel.get_municipio().comBiometria_isPresent() &&
            municipioDisponivel.get_municipio().get_comBiometria();
        md::CInfoMunicipio info(municipio.GetCodigo(), municipio.GetNome(), complemento.GetFusoHorario(), urnaBiometrica);
        if (complemento.TemHorarioVerao()) {
            info = md::CInfoMunicipio(municipio.GetCodigo(), municipio.GetNome(), complemento.GetFusoHorario(),
                                      urnaBiometrica, complemento.GetHorarioVerao());
        }
        const auto& secoesEntidade = municipioDisponivel.get_secoes();
        std::vector<md::CSecaoEleitoral> secoes;
        std::transform(secoesEntidade.begin(), secoesEntidade.end(), std::back_inserter(secoes),
                       [&conversorSecao](const ModuloLocal::SecaoEleitoral& secao) { return conversorSecao.Desconverte(secao); });
        const md::CMunicipioDisponivel disponivel(info, secoes);
        municipios.push_back(disponivel);
    }

    const std::vector<md::CCabecalhoPacote> pacotes = DesconvertePacotes(entidade.get_pacotesImportados());
    return md::CDadosDisponiveisCarga(fase, idPE, idPleito, serialFlashCarga, pais, siglaUF, nomeUF, zona, municipios,
                                      pacotes);
}

} // namespace comum::asn
