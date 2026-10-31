#include "app/comum/comparecimentomesario/estados/cgestordadomesariofinal.h"

namespace comum {

CGestorDadoMesarioFinal::CGestorDadoMesarioFinal()
    : IGestorDadoMesario()
{
}

CGestorDadoMesarioFinal& CGestorDadoMesarioFinal::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CGestorDadoMesarioFinal());
    }
    return *s_inst;
}

std::unique_ptr<CGestorDadoMesarioFinal> CGestorDadoMesarioFinal::s_inst;
std::mutex CGestorDadoMesarioFinal::s_mutex;

int CGestorDadoMesarioFinal::Slot9() const
{
    return 2;
}

} // namespace comum
