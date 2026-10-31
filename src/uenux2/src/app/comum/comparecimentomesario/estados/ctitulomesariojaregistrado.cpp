#include "app/comum/comparecimentomesario/estados/ctitulomesariojaregistrado.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/iform.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace comum {

// (original lines 11-39: content not recovered)
#line 40
CTituloMesarioJaRegistrado::~CTituloMesarioJaRegistrado() = default;

std::unique_ptr<CTituloMesarioJaRegistrado> CTituloMesarioJaRegistrado::s_inst;
std::mutex CTituloMesarioJaRegistrado::s_mutex;

// (original lines 45-49: content not recovered)
#line 50
void CTituloMesarioJaRegistrado::StartState()
{
    m_pNextState = this;
    auto& controladorMesario = api::CPolySingleton<IControladorRegistraMesarios>::instance();
    m_form->Slot2();
    m_formEleitor->Slot2();
    GetControlador().LogaMesarioJaRegistrado(controladorMesario.GetTituloMesario());
}

void CTituloMesarioJaRegistrado::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeTituloMesario::GetInst();
    }
}

// (original lines 66-73: content not recovered)
#line 74
const IControladorRegistraMesarios& CTituloMesarioJaRegistrado::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

} // namespace comum
