#include "app/vota/operador/outrasopcoes/cperguntafilaeleitorvazia.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CPerguntaFilaEleitorVazia::~CPerguntaFilaEleitorVazia() = default;

void CPerguntaFilaEleitorVazia::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    CLogVota::GetInst().loga("Operador indagado se todas as pessoas presentes votaram");
}

} // namespace vota

// <stubs>
// f5426 · 851 B · unmatched · placement: link order · name unknown
// ? f5426() { ... }
// </stubs>
