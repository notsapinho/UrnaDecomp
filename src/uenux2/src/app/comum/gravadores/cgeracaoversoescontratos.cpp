// Reconstruction's note: comum::CGeracaoVersoesContratos (cgeracaoversoescontratos.cpp, the file the record of its
// GetInst names): ObtemDependencias (target fn 5869) and the destructor (fn 5866), which have no record. Line 38 is
// GetInst's record (fn 12098 holds it inlined, not written) and stays blank; their lines, after it, are a choice.
#include "app/comum/gravadores/cgeracaoversoescontratos.h"

#include "ecourna/api/util/cstringutils.hpp"

namespace comum {































std::set<std::string> CGeracaoVersoesContratos::ObtemDependencias(const std::string& contrato,
    std::set<std::string>& dependencias)
{
    const std::string valor = m_dependencias.GetValor(contrato);
    for (const std::string& dependencia : ecourna::api::util::CStringUtils::Split(valor, ',')) {
        if (dependencia.empty()) {
            continue;
        }
        if (dependencias.insert(dependencia).second) {
            dependencias.insert(dependencia);
            ObtemDependencias(dependencia, dependencias);
        }
    }
    return dependencias;
}

CGeracaoVersoesContratos::~CGeracaoVersoesContratos() = default;

} // namespace comum
