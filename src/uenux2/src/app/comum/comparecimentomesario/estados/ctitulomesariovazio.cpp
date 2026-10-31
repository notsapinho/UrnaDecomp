#include "app/comum/comparecimentomesario/estados/ctitulomesariovazio.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/iform.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace comum {

CTituloMesarioVazio::~CTituloMesarioVazio() = default;

std::unique_ptr<CTituloMesarioVazio> CTituloMesarioVazio::s_inst;
std::mutex CTituloMesarioVazio::s_mutex;

void CTituloMesarioVazio::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    m_formEleitor->Slot2();
    GetControlador().LogaTituloInvalidoRegistroMesario();
}

void CTituloMesarioVazio::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeTituloMesario::GetInst();
    }
}

// (original lines 31-54: content not recovered)
#line 55
const IControladorRegistraMesarios& CTituloMesarioVazio::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

} // namespace comum
