#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"

#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesariofinal.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesarioinicial.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesariovotacao.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

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

// (original lines 28-29: content not recovered)
#line 30
void CPedeTituloMesario::StartState()
{
    m_pNextState = this;
    auto& controladorMesario = api::CPolySingleton<IControladorRegistraMesarios>::instance();
    switch (controladorMesario.Slot6()) {
    case 1:
        m_pNextState = &CPedeTituloMesarioInicial::GetInst();
        break;
    case 2:
        m_pNextState = &CPedeTituloMesarioVotacao::GetInst();
        break;
    case 3:
        m_pNextState = &CPedeTituloMesarioFinal::GetInst();
        break;
    }
}

} // namespace comum
