#include "app/comum/comparecimentomesario/estados/cconfirmafimregistromesarios.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/iform.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cencerraregistromesarios.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace comum {

CConfirmaFimRegistroMesarios::~CConfirmaFimRegistroMesarios() = default;

std::unique_ptr<CConfirmaFimRegistroMesarios> CConfirmaFimRegistroMesarios::s_inst;
std::mutex CConfirmaFimRegistroMesarios::s_mutex;

// (original lines 17-57: content not recovered)
#line 58
const IControladorRegistraMesarios& CConfirmaFimRegistroMesarios::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

void CConfirmaFimRegistroMesarios::StartState()
{
    m_pNextState = this;
    GetControlador().LogaIndagaFinalizaRegistro();
    m_formEleitor->Slot2();
    m_form->Slot2();
}

void CConfirmaFimRegistroMesarios::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        m_pNextState = &CEncerraRegistroMesarios::GetInst();
        break;
    case api::INPUT_CORRIGE:
        GetControlador().LogaConfirmouRegistroMesarios();
        m_pNextState = &CPedeTituloMesario::GetInst();
        break;
    }
}

} // namespace comum

// <stubs>
// f5389 · 983 B · unmatched · placement: link order · name unknown
// ? f5389() { ... }
// </stubs>
