#include "app/comum/dados/asn/municipiozona/cconversorcomplementosmunicipios.h"

#include <format>
#include <string>

#include "app/comum/dados/asn/municipiozona/cconversorcomplementomunicipio.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 11-24: content not recovered)
#line 25
md::CComplementosMunicipiosUF CConversorComplementosMunicipios::DoDesconverte(const TEntidade& entidade) const
{
    const TEntidade::municipiosUf::value_type& municipiosUf = entidade.get_municipiosUf();
    if (municipiosUf.size() != 1) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7944, std::format("Quantidade inválida de UFs [{}]", municipiosUf.size()));
    }

    const auto& complementosMunicipios = municipiosUf.at(0).get_complementosMunicipios();
    CConversorComplementoMunicipio conversor;
    md::CComplementosMunicipiosUF::TVetorCM complementos;
    for (const auto& complemento : complementosMunicipios) {
        complementos.emplace_back(conversor.Desconverte(complemento));
    }
    const std::string uf(municipiosUf.at(0).get_uf());
    return md::CComplementosMunicipiosUF(uf, complementos);
}

} // namespace comum::asn
