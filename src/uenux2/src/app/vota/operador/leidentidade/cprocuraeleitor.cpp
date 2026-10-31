#include "app/vota/operador/leidentidade/cprocuraeleitor.h"

namespace vota {

CProcuraEleitor::CProcuraEleitor()
    : comum::CAppState(EVENTO_ENTRADA | EVENTO_TICK)
{
}

CProcuraEleitor& CProcuraEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CProcuraEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CProcuraEleitor> CProcuraEleitor::s_inst;
std::mutex CProcuraEleitor::s_mutex;

} // namespace vota
