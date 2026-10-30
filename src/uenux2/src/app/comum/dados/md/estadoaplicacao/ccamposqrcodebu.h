#pragma once

#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace comum::md::estadoaplicacao {

// The target's fns 5622 and 5623 write the IDCA, HIQT and HICA fields of the boletim de urna's QR code into std::strings
// at +168 and +156 of a 396-byte object that fns 1956 and 12110 zero with fn 5624. No record, slot or RTTI names the
// class, this file or its members: all of those are chosen from those field names, and the layout is all that is
// recovered of the rest of the object, so nothing may construct this one.
class CCamposQRCodeBU {
public:
    void DefineIdentificadorCarga(const std::string& identificadorCarga);
    void DefineHistoricoCargas(const std::vector<std::string>& cargas);

private:
    uebyte m_inicio[156];
    std::string m_identificadorCarga;
    std::string m_historicoCargas;
};

} // namespace comum::md::estadoaplicacao
