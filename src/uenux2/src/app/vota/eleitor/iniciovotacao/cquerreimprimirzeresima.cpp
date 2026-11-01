#include "app/vota/eleitor/iniciovotacao/cquerreimprimirzeresima.h"

#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CQuerReimprimirZeresima::~CQuerReimprimirZeresima() = default;

CQuerReimprimirZeresima::CQuerReimprimirZeresima()
    : comum::CAppState(EVENTO_ENTRADA), m_form(CTelasVota::GetInst().GetTelaQuerReimprimirZeresima())
{
}

CQuerReimprimirZeresima& CQuerReimprimirZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CQuerReimprimirZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CQuerReimprimirZeresima> CQuerReimprimirZeresima::s_inst;
std::mutex CQuerReimprimirZeresima::s_mutex;

} // namespace vota
