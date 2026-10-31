#include "app/comum/comparecimentomesario/estados/cgestordadomesario.h"

#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cgestordadomesariofinal.h"
#include "app/comum/comparecimentomesario/estados/cgestordadomesarioinicial.h"
#include "app/comum/comparecimentomesario/estados/cgestordadomesariovotacao.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

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

// (original lines 28-31: content not recovered)
#line 32
void CGestorDadoMesario::StartState()
{
    m_pNextState = this;
    auto& controladorMesario = api::CPolySingleton<IControladorRegistraMesarios>::instance();
    switch (controladorMesario.Slot6()) {
    case 1:
        m_pNextState = &CGestorDadoMesarioInicial::GetInst();
        break;
    case 2:
        m_pNextState = &CGestorDadoMesarioVotacao::GetInst();
        break;
    case 3:
        m_pNextState = &CGestorDadoMesarioFinal::GetInst();
        break;
    }
}

} // namespace comum
