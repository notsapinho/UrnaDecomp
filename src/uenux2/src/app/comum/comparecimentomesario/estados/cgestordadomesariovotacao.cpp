#include "app/comum/comparecimentomesario/estados/cgestordadomesariovotacao.h"

namespace comum {

CGestorDadoMesarioVotacao::CGestorDadoMesarioVotacao()
    : IGestorDadoMesario()
{
}

CGestorDadoMesarioVotacao& CGestorDadoMesarioVotacao::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CGestorDadoMesarioVotacao());
    }
    return *s_inst;
}

std::unique_ptr<CGestorDadoMesarioVotacao> CGestorDadoMesarioVotacao::s_inst;
std::mutex CGestorDadoMesarioVotacao::s_mutex;

int CGestorDadoMesarioVotacao::Slot9() const
{
    return 1;
}

} // namespace comum
