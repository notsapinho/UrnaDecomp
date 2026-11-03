// vota::CDigitalNaoCapturada (no record names its file). The reconstruction's notes are in cdigitalnaocapturada.h and
// src/units/278-uenux2-cvalidaidentidade.mk.
#include "app/vota/operador/confirmaidentidade/cdigitalnaocapturada.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/operador/confirmaidentidade/cregistradigitaloperador.h"

namespace vota {

CDigitalNaoCapturada::~CDigitalNaoCapturada() = default;

void CDigitalNaoCapturada::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CDigitalNaoCapturada::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CRegistraDigitalOperador::GetInst();
    }
}

} // namespace vota
