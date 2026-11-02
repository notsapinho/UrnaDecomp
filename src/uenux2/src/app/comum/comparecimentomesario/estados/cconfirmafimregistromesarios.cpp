#include "app/comum/comparecimentomesario/estados/cconfirmafimregistromesarios.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/iform.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cencerraregistromesarios.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace comum {

CConfirmaFimRegistroMesarios::~CConfirmaFimRegistroMesarios() = default;

std::unique_ptr<CConfirmaFimRegistroMesarios> CConfirmaFimRegistroMesarios::s_inst;
std::mutex CConfirmaFimRegistroMesarios::s_mutex;

CConfirmaFimRegistroMesarios::CConfirmaFimRegistroMesarios()
    : CAppState(EVENTO_ENTRADA)
{
    m_formEleitor = TelaRegistroMesarios();
    m_form = TelaConfirmaFimRegistroMesarios();
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaConfirmaFimRegistroMesarios()
{
    api::CMTFormBuilder builder;
    builder.AddBuzz(51, 10);
    builder.AddTextField("Finalizar registro de mesários?", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: Voltar  CONFIRMA: Finalizar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

CConfirmaFimRegistroMesarios& CConfirmaFimRegistroMesarios::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConfirmaFimRegistroMesarios());
    }
    return *s_inst;
}

// (original lines 45-57: content not recovered)
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
