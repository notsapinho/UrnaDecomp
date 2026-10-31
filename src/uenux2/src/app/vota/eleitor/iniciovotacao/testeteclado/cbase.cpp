#include "app/vota/eleitor/iniciovotacao/testeteclado/cbase.h"

#include "api/gui/cinteractiveform.h"

namespace vota::testeteclado {

void CBase::StartState()
{
    m_pNextState = this;
    m_form = GetTela();
    m_form->Slot2();
}

} // namespace vota::testeteclado

// <stubs>
// f5948 · 28 B · unmatched · placement: link order · name unknown
// ? f5948(i32) { ... }
// </stubs>
