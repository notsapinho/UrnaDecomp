#include "app/comum/comparecimentomesario/estados/cgestordadomesario.h"

namespace comum {

CGestorDadoMesario::CGestorDadoMesario()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CGestorDadoMesario& CGestorDadoMesario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CGestorDadoMesario());
    }
    return *s_inst;
}

std::unique_ptr<CGestorDadoMesario> CGestorDadoMesario::s_inst;
std::mutex CGestorDadoMesario::s_mutex;

} // namespace comum
