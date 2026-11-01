#include "app/vota/eleitor/fimvotacao/cretirarmr.h"

#include "api/gui/cinteractiveform.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/iinterfaceinit.h"
#include "app/vota/eleitor/fimvotacao/cemitirmaisbu.h"

namespace vota {

CRetirarMR::~CRetirarMR() = default;

// (original lines 12-75: content not recovered)
#line 76
void CRetirarMR::ProcessInput()
{
    bool ehDemo = api::CPolySingleton<comum::IInterfaceInit>::instance().GetDemoMode();
    api::EInputResult resultado = ehDemo ? m_formDemo->Read() : m_form->Read();
    if (resultado == api::INPUT_CONFIRMA) {
        m_pNextState = &CEmitirMaisBU::GetInst();
    }
}

} // namespace vota

// <stubs>
// f2291 · 3426 B · unmatched · placement: link order · name unknown
// ? f2291() { ... }
// </stubs>
