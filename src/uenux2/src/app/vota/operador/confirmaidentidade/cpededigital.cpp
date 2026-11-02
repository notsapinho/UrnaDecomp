// vota::CPedeDigital (/home/rubio/tse/uenux2/src/app/vota/operador/confirmaidentidade/cpededigital.cpp). The reconstruction's
// note, not TSE's text. The file's records are StartState's (lines 115, 120, 125), FinishState's (131, 132), ProcessTick's
// (162 to 164) and three private members' (234, 262, 279), none written: their lines stay blank. The destructor and
// ProcessInput have no record; their lines are a choice, in the order of their use band (src/units/192-uenux2-app-vota-estados-sincronismo.mk).
#include "app/vota/operador/confirmaidentidade/cpededigital.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

// (original lines 13-104: content not recovered)
#line 105
CPedeDigital::~CPedeDigital() = default;

// (original lines 107-136: content not recovered)
#line 137
void CPedeDigital::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        CLogVota::GetInst().LogaHabilitacaoCanceladaReconhecimentoBiometrico();
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
    }
}

} // namespace vota

// <stubs>
// f5397 · 2997 B · unmatched · name unknown
// void f5397(i32, i32) { ... }

// f2740 · 1815 B · unmatched · placement: link order · name unknown
// ? f2740() { ... }
// </stubs>
