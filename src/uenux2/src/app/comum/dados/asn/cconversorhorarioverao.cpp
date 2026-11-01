// Reconstruction: comum::asn::CConversorHorarioVerao's two slots, DoConverte and DoDesconverte (target fns 11385 and
// 11384). No record names this file or a line in it: the path is the header's (cconversorhorarioverao.h), and the
// functions' order is chosen. DoDesconverte holds md::CHorarioVerao's constructor, inlined by binaryen.
#include "app/comum/dados/asn/cconversorhorarioverao.h"

#include "app/comum/asn/util.h"

namespace comum::asn {

CConversorHorarioVerao::TEntidade CConversorHorarioVerao::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_inicioHV() = Utils::ConverteDataJE(dado.GetInicio());
    entidade.set_fimHV() = Utils::ConverteDataJE(dado.GetFim());
    entidade.set_diferencaHV(dado.GetDiferenca());
    return entidade;
}

CConversorHorarioVerao::TDado CConversorHorarioVerao::DoDesconverte(const TEntidade& entidade) const
{
    return TDado(Utils::DesconverteDataJE(entidade.get_inicioHV()), Utils::DesconverteDataJE(entidade.get_fimHV()),
                 entidade.get_diferencaHV().getValue());
}

} // namespace comum::asn
