#include "app/vota/eleitor/iniciovotacao/cquerimprimirzeresima.h"

#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CQuerImprimirZeresima::CQuerImprimirZeresima()
    : comum::CAppState(EVENTO_ENTRADA), m_form(CTelasVota::GetInst().GetTelaQuerImprimirZeresima())
{
}

CQuerImprimirZeresima& CQuerImprimirZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CQuerImprimirZeresima());
    }
    return *s_inst;
}

CQuerImprimirZeresima::~CQuerImprimirZeresima() = default;

std::unique_ptr<CQuerImprimirZeresima> CQuerImprimirZeresima::s_inst;
std::mutex CQuerImprimirZeresima::s_mutex;

} // namespace vota
