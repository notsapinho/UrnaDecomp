// Reconstruction's note: comum::CGeracaoVersoesContratos (cgeracaoversoescontratos.cpp, the file the record of its
// GetInst names): GetInst on its record's line (38, column 12, the start of CPolySingleton<T>::instance()'s call, whose
// std::source_location default argument the record is), the constructor, ObtemDependencias (target fn 5869) and the
// destructor (fn 5866), which have no record; their lines are a choice. Unit 268's fragment says what GetInst is read
// from and what is chosen.
#include "app/comum/gravadores/cgeracaoversoescontratos.h"

#include <memory>

#include "api/pattern/cpolysingleton.h"
#include "app/comum/cpath.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

// (original lines 16-25: content not recovered)
#line 26
CGeracaoVersoesContratos::CGeracaoVersoesContratos(const std::string& dependencias, const std::string& versoes)
    : m_dependencias(dependencias), m_versoes(versoes)
{
}

CGeracaoVersoesContratos& CGeracaoVersoesContratos::GetInst()
{
    if (!api::CPolySingletonList::has<CGeracaoVersoesContratos>()) {
        api::CPolySingleton<CGeracaoVersoesContratos>::set(std::make_unique<CGeracaoVersoesContratos>(
            (CPath::GetPathRoot() / "etc/dependencias.properties").string(),
            (CPath::GetPathRoot() / "etc/versoes.properties").string()));
    }
    return api::CPolySingleton<CGeracaoVersoesContratos>::instance();
}

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
