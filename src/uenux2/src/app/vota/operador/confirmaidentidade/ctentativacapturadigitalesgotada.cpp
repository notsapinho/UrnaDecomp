// vota::CTentativaCapturaDigitalEsgotada (no record names its file). The reconstruction's notes are in
// ctentativacapturadigitalesgotada.h and src/units/278-uenux2-cvalidaidentidade.mk.
#include "app/vota/operador/confirmaidentidade/ctentativacapturadigitalesgotada.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CTentativaCapturaDigitalEsgotada::~CTentativaCapturaDigitalEsgotada() = default;

void CTentativaCapturaDigitalEsgotada::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CTentativaCapturaDigitalEsgotada::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CPedeIdentidade::GetInst();
    }
}

} // namespace vota
