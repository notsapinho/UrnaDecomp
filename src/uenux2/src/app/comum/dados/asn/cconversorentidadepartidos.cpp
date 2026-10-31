#include "app/comum/dados/asn/cconversorentidadepartidos.h"

#include "app/comum/asn/cconversorabrangencia.h"
#include "app/comum/asn/cconversorcabecalhoentidade.h"
#include "app/comum/dados/asn/cconversorpartido.h"

namespace comum::asn {

CConversorEntidadePartidos::TEntidade CConversorEntidadePartidos::DoConverte(const TDado& dado) const
{
    TEntidade entidade;

    CConversorCabecalhoEntidade conversorCabecalho;
    const TEntidade::cabecalho::value_type cabecalho = conversorCabecalho.Converte(dado.GetCabecalho());
    entidade.set_cabecalho() = cabecalho;

    CConversorAbrangencia conversorAbrangencia;
    const TEntidade::abrangencia::value_type abrangencia = conversorAbrangencia.Converte(dado.GetAbrangencia());
    entidade.set_abrangencia() = abrangencia;

    TEntidade::partidos::value_type partidos;
    for (std::size_t i = 0; i < dado.GetPartidos().size(); ++i) {
        CConversorPartido conversorPartido;
        partidos.push_back(conversorPartido.Converte(dado.GetPartidos()[i]));
    }
    entidade.set_partidos() = partidos;

    return entidade;
}

CConversorEntidadePartidos::TDado CConversorEntidadePartidos::DoDesconverte(const TEntidade& entidade) const
{
    CConversorCabecalhoEntidade conversorCabecalho;
    const md::CCabecalhoEntidade cabecalho = conversorCabecalho.Desconverte(entidade.get_cabecalho());

    CConversorAbrangencia conversorAbrangencia;
    const md::CAbrangencia abrangencia = conversorAbrangencia.Desconverte(entidade.get_abrangencia());

    std::vector<md::CPartido> partidos;
    for (std::size_t i = 0; i < entidade.get_partidos().size(); ++i) {
        CConversorPartido conversorPartido;
        const md::CPartido partido = conversorPartido.Desconverte(entidade.get_partidos()[i]);
        partidos.push_back(partido);
    }

    return TDado(cabecalho, abrangencia, partidos);
}

} // namespace comum::asn
