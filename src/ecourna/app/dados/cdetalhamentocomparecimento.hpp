#pragma once
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace ecourna::app::dados {

// How many voters attended, by how they were enabled: 6 bytes, three counts in the ASN.1
// ModuloBoletimUrna::DetalhamentoComparecimento field order, whose names these follow. The constructor is out of line
// (fn 5094, callers 9221 and 12098).
class CDetalhamentoComparecimento {
public:
    CDetalhamentoComparecimento(TQtdEleitor qtdEleitoresCompareceramSemBiometria,
                                TQtdEleitor qtdEleitoresHabilitadosPorBiometria,
                                TQtdEleitor qtdEleitoresHabilitadosPorBiografia);

    TQtdEleitor GetQtdEleitoresCompareceramSemBiometria() const { return m_qtdEleitoresCompareceramSemBiometria; }
    TQtdEleitor GetQtdEleitoresHabilitadosPorBiometria() const { return m_qtdEleitoresHabilitadosPorBiometria; }
    TQtdEleitor GetQtdEleitoresHabilitadosPorBiografia() const { return m_qtdEleitoresHabilitadosPorBiografia; }

private:
    TQtdEleitor m_qtdEleitoresCompareceramSemBiometria;
    TQtdEleitor m_qtdEleitoresHabilitadosPorBiometria;
    TQtdEleitor m_qtdEleitoresHabilitadosPorBiografia;
};

} // namespace ecourna::app::dados
