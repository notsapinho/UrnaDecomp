#pragma once

#include "app/comum/dados/md/estadoaplicacao/eurna.h"

namespace comum::md::estadoaplicacao {

// The load the urna runs: the fields of ModuloEstadoGeralUrna::DadoCarga, in order, at +0 to +16 (target fn 5633). The
// two urna types' member names and all the types but the records' are chosen: comum::asn::Utils::DesconverteTurno's record
// names the turn's type EUrnaTurno, which app/comum/eurnaturno.h defines; this constructor keeps an int for it until the
// converter that passes it is written, and GetTurno's result follows.
class CDadoCarga {
public:
    CDadoCarga(int turno, EUrnaTipo tipoUrnaT1, EUrnaTipo tipoUrnaT2, EUrnaModelo modelo, EUrnaFase fase);

    int GetTurno() const { return m_turno; }
    EUrnaFase GetFase() const { return m_fase; }
    char GetFaseChar() const;

private:
    void ValidaModelo(const EUrnaModelo modelo);

    int m_turno;
    EUrnaTipo m_tipoUrnaT1;
    EUrnaTipo m_tipoUrnaT2;
    EUrnaModelo m_modelo;
    EUrnaFase m_fase;
};

} // namespace comum::md::estadoaplicacao
