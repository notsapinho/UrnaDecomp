// vota::testeteclado::CTesteFalhou: no record names this file or any of its members; the reconstruction's notes are in
// ctestefalhou.h and src/units/217-uenux2-ctesteteclado.mk.
#include "app/vota/eleitor/iniciovotacao/testeteclado/ctestefalhou.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cenviarmanutencao.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cesperaretestar.h"

namespace vota::testeteclado {

CTesteFalhou::~CTesteFalhou() = default;

CTesteFalhou& CTesteFalhou::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CTesteFalhou());
    }
    return *s_inst;
}

CTesteFalhou::CTesteFalhou()
    : CEstadoComDesligamentoAutomatico(EVENTO_ENTRADA)
    , m_form(TelaTeclaErradaTesteTeclado())
{
}

std::unique_ptr<CTesteFalhou> CTesteFalhou::s_inst;
std::mutex CTesteFalhou::s_mutex;

void CTesteFalhou::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CTesteFalhou::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        m_pNextState = &CEsperaRetestar::GetInst();
        break;
    case api::INPUT_CORRIGE:
        m_pNextState = &CEnviarManutencao::GetInst();
        break;
    default:
        break;
    }
}

} // namespace vota::testeteclado
