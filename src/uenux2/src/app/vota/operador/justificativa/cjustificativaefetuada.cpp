#include "app/vota/operador/justificativa/cjustificativaefetuada.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CJustificativaEfetuada::~CJustificativaEfetuada() = default;

void CJustificativaEfetuada::StartState()
{
    if (m_bRecebida) {
        *m_titulo = "AUSÊNCIA JUSTIFICADA";
        CLogVota::GetInst().LogaJustificativaRecebida();
    } else {
        *m_titulo = "JÁ JUSTIFICOU";
        CLogVota::GetInst().LogaEleitorJaJustificou();
    }
    m_form->Slot2();
    m_pNextState = this;
}

void CJustificativaEfetuada::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
    }
}

} // namespace vota

// <stubs>
// f2747 · 908 B · unmatched · placement: link order · name unknown
// ? f2747() { ... }
// </stubs>
