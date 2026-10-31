#pragma once

#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/eurnaturno.h"

namespace comum::md::estadoaplicacao {

// The load the urna runs: the fields of ModuloEstadoGeralUrna::DadoCarga, in order, at +0 to +16 (target fn 5633). The
// two urna types' member names and all the types but the records' are chosen: comum::asn::Utils::DesconverteTurno's record
// names the turn's type EUrnaTurno.
class CDadoCarga {
public:
    CDadoCarga(EUrnaTurno turno, EUrnaTipo tipoUrnaT1, EUrnaTipo tipoUrnaT2, EUrnaModelo modelo, EUrnaFase fase);

    EUrnaTurno GetTurno() const { return m_turno; }
    EUrnaTipo GetTipoUrnaT1() const { return m_tipoUrnaT1; }
    EUrnaTipo GetTipoUrnaT2() const { return m_tipoUrnaT2; }
    EUrnaModelo GetModelo() const { return m_modelo; }
    EUrnaFase GetFase() const { return m_fase; }
    char GetFaseChar() const;
    // The name is chosen: the urna's type in the load's turn. comum::CRelatorioTesteImpressora's slot 17 (fn 11190)
    // and its constructor (fn 5586) hold it inlined.
    EUrnaTipo GetTipoUrna() const { return m_turno == TURNO_1 ? m_tipoUrnaT1 : m_tipoUrnaT2; }

private:
    void ValidaModelo(const EUrnaModelo modelo);

    EUrnaTurno m_turno;
    EUrnaTipo m_tipoUrnaT1;
    EUrnaTipo m_tipoUrnaT2;
    EUrnaModelo m_modelo;
    EUrnaFase m_fase;
};

} // namespace comum::md::estadoaplicacao
