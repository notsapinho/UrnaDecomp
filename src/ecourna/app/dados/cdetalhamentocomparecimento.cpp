#include "ecourna/app/dados/cdetalhamentocomparecimento.hpp"

namespace ecourna::app::dados {

CDetalhamentoComparecimento::CDetalhamentoComparecimento(TQtdEleitor qtdEleitoresCompareceramSemBiometria,
                                                         TQtdEleitor qtdEleitoresHabilitadosPorBiometria,
                                                         TQtdEleitor qtdEleitoresHabilitadosPorBiografia)
    : m_qtdEleitoresCompareceramSemBiometria(qtdEleitoresCompareceramSemBiometria),
      m_qtdEleitoresHabilitadosPorBiometria(qtdEleitoresHabilitadosPorBiometria),
      m_qtdEleitoresHabilitadosPorBiografia(qtdEleitoresHabilitadosPorBiografia)
{
}

} // namespace ecourna::app::dados
