#include "ecourna/app/dados/asn/cconversorhorariosurna.hpp"

#include "ecourna/app/dados/asn/datahoraasn.hpp"

namespace ecourna::app::dados::asn {

CConversorHorariosUrna::TEntidade CConversorHorariosUrna::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_emissaoZeresima() = ConverteDataHora(dado.GetEmissaoZeresima());
    entidade.set_inicioVotacao() = ConverteDataHora(dado.GetInicioVotacao());
    entidade.set_encerramentoVotacao() = ConverteDataHora(dado.GetEncerramentoVotacao());
    entidade.set_terminoVotacao() = ConverteDataHora(dado.GetTerminoVotacao());
    return entidade;
}

CHorariosUrna CConversorHorariosUrna::DoDeconverte(const TEntidade& entidade) const
{
    return CHorariosUrna(DesconverteDataHora(entidade.get_emissaoZeresima()),
                         DesconverteDataHora(entidade.get_inicioVotacao()),
                         DesconverteDataHora(entidade.get_encerramentoVotacao()),
                         DesconverteDataHora(entidade.get_terminoVotacao()));
}

} // namespace ecourna::app::dados::asn
