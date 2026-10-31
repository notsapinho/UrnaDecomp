#include "app/comum/comparecimentomesario/estados/climitemesariosregistradosatingido.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/iform.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cencerraregistromesarios.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace comum {

CLimiteMesariosRegistradosAtingido::~CLimiteMesariosRegistradosAtingido() = default;

std::unique_ptr<CLimiteMesariosRegistradosAtingido> CLimiteMesariosRegistradosAtingido::s_inst;
std::mutex CLimiteMesariosRegistradosAtingido::s_mutex;

void CLimiteMesariosRegistradosAtingido::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    m_formEleitor->Slot2();
    GetControlador().LogaLimiteMesariosAtingido();
}

void CLimiteMesariosRegistradosAtingido::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CEncerraRegistroMesarios::GetInst();
    }
}

// (original lines 31-50: content not recovered)
#line 51
const IControladorRegistraMesarios& CLimiteMesariosRegistradosAtingido::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

} // namespace comum
