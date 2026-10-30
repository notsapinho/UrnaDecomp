#include "app/comum/dados/asn/processoeleitoral/cconversornomescargo.h"

namespace comum::asn {

CConversorNomesCargo::TDado CConversorNomesCargo::DoDesconverte(const TEntidade& entidade) const
{
    const std::string nomeNeutro = entidade.get_nomeNeutro();
    const std::string nomeMasculino = entidade.get_nomeMasculino();
    const std::string nomeFeminino = entidade.get_nomeFeminino();
    const std::string nomeAbreviado = entidade.get_nomeAbreviado();
    return md::CNomesCargo(nomeNeutro, nomeMasculino, nomeFeminino, nomeAbreviado);
}

} // namespace comum::asn
