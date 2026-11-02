#include "app/vota/eleitor/fimvotacao/ccopiaresultadoparamr.h"

#include "api/gui/iform.h"
#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CCopiaResultadoParaMR::CCopiaResultadoParaMR()
    : comum::CAppState(EVENTO_TICK),
      m_tela(TelaCopiaResultadoParaMR())
{
}

CCopiaResultadoParaMR::~CCopiaResultadoParaMR() = default;

CCopiaResultadoParaMR& CCopiaResultadoParaMR::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CCopiaResultadoParaMR());
    }
    return *s_inst;
}

std::unique_ptr<CCopiaResultadoParaMR> CCopiaResultadoParaMR::s_inst;
std::mutex CCopiaResultadoParaMR::s_mutex;

} // namespace vota
