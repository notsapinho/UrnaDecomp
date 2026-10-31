#pragma once

#include <optional>
#include <string>
#include <vector>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/cnumviasimpressasrelatorios.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"

namespace comum::md::estadoaplicacao {

// The state of the gap between applications: the fields of ModuloEstadoGeralGap::EstadoGeralGap. The offsets come from the
// constructor (target fn 5626). Only the layout is recovered, and the member names follow the ASN.1 fields. Which field each
// of the last four is reads from the order: the entity has ten fields and fn 5626 ten parameters, the same order and widths
// (fn 11395 passes the two counts through the converter of CNumViasImpressasRelatorios). The bodies do not say more.
class CEstadoGeralGap {
public:
    std::vector<std::string> GetCodigosCarga() const;

private:
    std::vector<CDadoCorrespondencia> m_correspondencias;
    EUrnaAplicativo m_appId;
    EUrnaAplicativo m_appAnteriorId;
    bool m_executadoRED;
    bool m_identificadoATUE;
    bool m_audio;
    bool m_data2T;
    CNumViasImpressasRelatorios m_numViasImpressasRelatorios1T;
    CNumViasImpressasRelatorios m_numViasImpressasRelatorios2T;
    std::optional<api::CDate> m_dataSegundoTurno;
};

} // namespace comum::md::estadoaplicacao
