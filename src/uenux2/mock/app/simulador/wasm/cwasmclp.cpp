#include "api/hwil/clp.h"
#include "api/gui/isubreport.h"
#include "api/hwil/iimpressorarelatorios.h"
#include "api/pattern/cpolysingleton.h"

namespace api {

CLp::CLp()
{
    m_impRel = CPolySingletonList::has<IImpressoraRelatorios>() ? &CPolySingleton<IImpressoraRelatorios>::instance() : nullptr;
    m_impressora = m_impRel;
}

CLp::~CLp() = default;

CLp& CLp::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CLp());
    }
    return *s_inst;
}

std::unique_ptr<CLp> CLp::s_inst;
std::mutex CLp::s_mutex;

void CLp::Imprime(const ISubReport& subRelatorio, const std::function<void()>& corpo)
{
    if (m_impRel) {
        m_impRel->Slot9();
    }
    if (subRelatorio.TemParte()) {
        subRelatorio.ImprimeParte();
    }
    corpo();
}

} // namespace api
