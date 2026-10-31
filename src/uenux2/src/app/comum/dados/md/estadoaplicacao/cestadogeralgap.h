#pragma once

#include <optional>
#include <string>
#include <vector>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"

namespace comum::md::estadoaplicacao {

// The state of the gap between applications: the fields of ModuloEstadoGeralGap::EstadoGeralGap. The offsets come from the
// constructor (target fn 5626). Only the layout is recovered. The names of the members the ASN.1 fields name follow those
// fields; the last three are named from their widths and are chosen.
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
    bool m_flag;
    int m_valor1;
    int m_valor2;
    std::optional<api::CDate> m_data;
};

} // namespace comum::md::estadoaplicacao
