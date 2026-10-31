#include "ecourna/app/dados/asn/cconversorconfiguracaomunicipios.hpp"

#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

#include "ecourna/app/dados/asn/cconversorcabecalhoentidade.hpp"
#include "ecourna/app/dados/asn/cconversorconfiguracaomunicipio.hpp"
#include "ecourna/app/dados/asn/sequenciaasn.hpp"

namespace ecourna::app::dados::asn {

CConversorConfiguracaoMunicipios::TEntidade CConversorConfiguracaoMunicipios::DoConverte(const TDado& dado) const
{
    CConversorCabecalhoEntidade conversorCabecalho;
    CConversorConfiguracaoMunicipio conversorConfiguracao;
    TEntidade entidade;
    entidade.set_cabecalho() = conversorCabecalho.Converte(dado.GetCabecalho());
    const std::vector<CConfiguracaoMunicipio> configuracoes = ParaVetor(dado.GetConfiguracoes());
    entidade.set_configuracoes() = ConverteSequencia(configuracoes, conversorConfiguracao);
    return entidade;
}

CConversorConfiguracaoMunicipios::TDado CConversorConfiguracaoMunicipios::DoDeconverte(const TEntidade& entidade) const
{
    CConversorCabecalhoEntidade conversorCabecalho;
    CConversorConfiguracaoMunicipio conversorConfiguracao;
    const CCabecalhoEntidade cabecalho = conversorCabecalho.Deconverte(entidade.get_cabecalho());
    return TDado(cabecalho, ParaMapa(DeconverteSequencia(entidade.get_configuracoes(), conversorConfiguracao)));
}

std::vector<CConfiguracaoMunicipio> CConversorConfiguracaoMunicipios::ParaVetor(const TMapConfiguracaoMunicipio& mapa)
{
    std::vector<CConfiguracaoMunicipio> configuracoes;
    std::transform(mapa.begin(), mapa.end(), std::back_inserter(configuracoes), [](const auto& item) { return item.second; });
    return configuracoes;
}

TMapConfiguracaoMunicipio CConversorConfiguracaoMunicipios::ParaMapa(const std::vector<CConfiguracaoMunicipio>& configuracoes)
{
    TMapConfiguracaoMunicipio mapa;
    std::transform(configuracoes.begin(), configuracoes.end(), std::inserter(mapa, mapa.end()),
                   [](const CConfiguracaoMunicipio& configuracao) {
                       return std::make_pair(configuracao.GetCodigoMunicipio(), configuracao);
                   });
    return mapa;
}

} // namespace ecourna::app::dados::asn
