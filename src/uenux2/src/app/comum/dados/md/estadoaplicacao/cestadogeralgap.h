#pragma once

#include <optional>
#include <string>
#include <vector>

#include "api/util/cdate.h"
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
    // Target fn 5626, out of line: comum::asn::CConversorEstadoGeralGap::DoDesconverte (fn 11395) calls it, and table
    // slot 453 holds it. Its last statement sets m_data2T again, from m_dataSegundoTurno against today's date. The
    // by-value parameters are the copies fn 11395 makes; no record names the constructor.
    CEstadoGeralGap(std::vector<CDadoCorrespondencia> correspondencias, EUrnaAplicativo appId,
                    EUrnaAplicativo appAnteriorId, bool executadoRED, bool identificadoATUE, bool audio, bool data2T,
                    CNumViasImpressasRelatorios numViasImpressasRelatorios1T,
                    CNumViasImpressasRelatorios numViasImpressasRelatorios2T, std::optional<api::CDate> dataSegundoTurno);

    std::vector<std::string> GetCodigosCarga() const;

    // What comum::asn::CConversorEstadoGeralGap::DoConverte (target fn 11394) reads: the vector, the enums, the flags and
    // the optional in place (it loads them from the object, or passes their address), and each
    // CNumViasImpressasRelatorios through a 4-byte copy it makes before the converter's call, so those two return by
    // value. No record names any of them: the names follow the members', chosen, and defining them in the class is a
    // choice.
    const std::vector<CDadoCorrespondencia>& GetCorrespondencias() const { return m_correspondencias; }
    EUrnaAplicativo GetAppId() const { return m_appId; }
    EUrnaAplicativo GetAppAnteriorId() const { return m_appAnteriorId; }
    bool GetExecutadoRED() const { return m_executadoRED; }
    bool GetIdentificadoATUE() const { return m_identificadoATUE; }
    bool GetAudio() const { return m_audio; }
    bool GetData2T() const { return m_data2T; }
    CNumViasImpressasRelatorios GetNumViasImpressasRelatorios1T() const { return m_numViasImpressasRelatorios1T; }
    CNumViasImpressasRelatorios GetNumViasImpressasRelatorios2T() const { return m_numViasImpressasRelatorios2T; }
    const std::optional<api::CDate>& GetDataSegundoTurno() const { return m_dataSegundoTurno; }

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
