#include "ecourna/app/dados/asn/federacoes/cconversorfederacao.hpp"

#include <algorithm>
#include <iterator>

namespace ecourna::app::dados::asn {

CConversorFederacao::TEntidade CConversorFederacao::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_identificador() = TEntidade::identificador::value_type(dado.GetId());
    entidade.set_sigla(dado.GetSigla());
    entidade.set_nome(dado.GetNome());
    const TVectorNumeroPartido partidos = dado.GetPartidos();
    std::transform(partidos.begin(), partidos.end(), std::back_inserter(entidade.ref_partidos()),
                   [](TPartidoID partido) { return TEntidade::partidos::value_type::value_type(partido); });
    return entidade;
}

CConversorFederacao::TDado CConversorFederacao::DoDeconverte(const TEntidade& entidade) const
{
    const TFederacaoID id(entidade.get_identificador().getValue());
    const TEntidade::sigla::value_type sigla = entidade.get_sigla();
    const TEntidade::nome::value_type nome = entidade.get_nome();
    const TEntidade::partidos::value_type partidos = entidade.get_partidos();
    TVectorNumeroPartido numeros;
    std::transform(partidos.begin(), partidos.end(), std::back_inserter(numeros),
                   [](TEntidade::partidos::value_type::value_type partido) { return TPartidoID(partido.getValue()); });
    return TDado(id, sigla, nome, numeros);
}

} // namespace ecourna::app::dados::asn
