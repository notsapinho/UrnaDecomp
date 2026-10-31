#include "ecourna/app/dados/asn/cconversordetalhamentocomparecimento.hpp"

namespace ecourna::app::dados::asn {

CConversorDetalhamentoComparecimento::TEntidade CConversorDetalhamentoComparecimento::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    entidade.set_qtdEleitoresCompareceramSemBiometria() =
        TEntidade::qtdEleitoresCompareceramSemBiometria::value_type(dado.GetQtdEleitoresCompareceramSemBiometria());
    entidade.set_qtdEleitoresHabilitadosPorBiometria() =
        TEntidade::qtdEleitoresHabilitadosPorBiometria::value_type(dado.GetQtdEleitoresHabilitadosPorBiometria());
    entidade.set_qtdEleitoresHabilitadosPorBiografia() =
        TEntidade::qtdEleitoresHabilitadosPorBiografia::value_type(dado.GetQtdEleitoresHabilitadosPorBiografia());
    return entidade;
}

CConversorDetalhamentoComparecimento::TDado CConversorDetalhamentoComparecimento::DoDeconverte(const TEntidade& entidade) const
{
    return TDado(entidade.get_qtdEleitoresCompareceramSemBiometria().getValue(),
                 entidade.get_qtdEleitoresHabilitadosPorBiometria().getValue(),
                 entidade.get_qtdEleitoresHabilitadosPorBiografia().getValue());
}

} // namespace ecourna::app::dados::asn
