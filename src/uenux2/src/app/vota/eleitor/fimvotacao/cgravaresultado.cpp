#include "app/vota/eleitor/fimvotacao/cgravaresultado.h"

namespace vota {

CGravaResultado::CGravaResultado()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CGravaResultado& CGravaResultado::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CGravaResultado());
    }
    return *s_inst;
}

std::unique_ptr<CGravaResultado> CGravaResultado::s_inst;
std::mutex CGravaResultado::s_mutex;

} // namespace vota
