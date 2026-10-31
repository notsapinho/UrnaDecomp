#include "app/comum/dados/asn/municipiozona/cconversorcomplementomunicipio.h"

#include "app/comum/dados/asn/cconversorhorarioverao.h"

namespace comum::asn {

CConversorComplementoMunicipio::TEntidade CConversorComplementoMunicipio::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_codigoMunicipio(dado.GetCodigo());
    entidade.set_fuso(dado.GetFusoHorario());
    if (dado.TemHorarioVerao()) {
        CConversorHorarioVerao conversor;
        entidade.set_horarioVerao() = conversor.Converte(dado.GetHorarioVerao());
    }
    else {
        entidade.omit_horarioVerao();
    }
    return entidade;
}

CConversorComplementoMunicipio::TDado CConversorComplementoMunicipio::DoDesconverte(const TEntidade& entidade) const
{
    const uedword codigo = entidade.get_codigoMunicipio().getValue();
    const int fuso = entidade.get_fuso().getValue();
    if (entidade.horarioVerao_isPresent()) {
        CConversorHorarioVerao conversor;
        return TDado(codigo, fuso, conversor.Desconverte(entidade.get_horarioVerao()));
    }
    return TDado(codigo, fuso);
}

} // namespace comum::asn
