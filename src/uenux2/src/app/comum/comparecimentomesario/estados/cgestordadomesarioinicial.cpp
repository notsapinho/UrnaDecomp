#include "app/comum/comparecimentomesario/estados/cgestordadomesarioinicial.h"

namespace comum {

CGestorDadoMesarioInicial::CGestorDadoMesarioInicial()
    : IGestorDadoMesario()
{
}

CGestorDadoMesarioInicial& CGestorDadoMesarioInicial::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CGestorDadoMesarioInicial());
    }
    return *s_inst;
}

std::unique_ptr<CGestorDadoMesarioInicial> CGestorDadoMesarioInicial::s_inst;
std::mutex CGestorDadoMesarioInicial::s_mutex;

int CGestorDadoMesarioInicial::Slot9() const
{
    return 1;
}

} // namespace comum
