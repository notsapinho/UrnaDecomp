#include "app/vota/eleitor/iniciovotacao/cgeradadosdinamicos.h"

namespace vota {

CGeraDadosDinamicos::CGeraDadosDinamicos()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CGeraDadosDinamicos& CGeraDadosDinamicos::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CGeraDadosDinamicos());
    }
    return *s_inst;
}

std::unique_ptr<CGeraDadosDinamicos> CGeraDadosDinamicos::s_inst;
std::mutex CGeraDadosDinamicos::s_mutex;

} // namespace vota
