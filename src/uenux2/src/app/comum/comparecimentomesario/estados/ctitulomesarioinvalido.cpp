#include "app/comum/comparecimentomesario/estados/ctitulomesarioinvalido.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/iform.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace comum {

// (original lines 11-39: content not recovered)
#line 40
CTituloMesarioInvalido::~CTituloMesarioInvalido() = default;

std::unique_ptr<CTituloMesarioInvalido> CTituloMesarioInvalido::s_inst;
std::mutex CTituloMesarioInvalido::s_mutex;

void CTituloMesarioInvalido::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    m_formEleitor->Slot2();
    GetControlador().LogaTituloInvalidoRegistroMesario();
}

void CTituloMesarioInvalido::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeTituloMesario::GetInst();
    }
}

// (original lines 60-72: content not recovered)
#line 73
const IControladorRegistraMesarios& CTituloMesarioInvalido::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

} // namespace comum
