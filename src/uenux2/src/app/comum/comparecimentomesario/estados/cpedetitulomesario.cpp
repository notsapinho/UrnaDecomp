#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"

namespace comum {

CPedeTituloMesario::CPedeTituloMesario()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CPedeTituloMesario& CPedeTituloMesario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeTituloMesario());
    }
    return *s_inst;
}

std::unique_ptr<CPedeTituloMesario> CPedeTituloMesario::s_inst;
std::mutex CPedeTituloMesario::s_mutex;

} // namespace comum
