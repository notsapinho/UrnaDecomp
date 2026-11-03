// vota::CContadoresBiometria (app/vota/operador/outrasopcoes/ccontadoresbiometria.cpp, the class name in lower case).
// This comment is the reconstruction's: no record names this file or its functions, so every line is a choice;
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk has the evidence.
#include "app/vota/operador/outrasopcoes/ccontadoresbiometria.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

CContadoresBiometria::~CContadoresBiometria() = default;

void CContadoresBiometria::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CContadoresBiometria::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CEscolheOpcao::GetInst();
    }
}

} // namespace vota
