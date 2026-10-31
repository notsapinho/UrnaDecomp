#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CCancelaHabilitacaoEleitor::CCancelaHabilitacaoEleitor()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CCancelaHabilitacaoEleitor& CCancelaHabilitacaoEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CCancelaHabilitacaoEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CCancelaHabilitacaoEleitor> CCancelaHabilitacaoEleitor::s_inst;
std::mutex CCancelaHabilitacaoEleitor::s_mutex;

} // namespace vota
