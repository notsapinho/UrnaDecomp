#include "app/vota/operador/aguardaeleitor/celeitorvotounaovotou.h"

#include "api/gui/cinteractiveform.h"

namespace vota {

CEleitorVotouNaoVotou::~CEleitorVotouNaoVotou() = default;

void CEleitorVotouNaoVotou::StartState()
{
    *m_situacao = m_bVotou ? "VOTOU. Pode entregar o comprovante" : "NÃO VOTOU. Não entregar o comprovante";
    *m_complemento = " ";
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota

// <stubs>
// f1901 · 1197 B · unmatched · placement: link order · name unknown
// ? f1901() { ... }
// </stubs>
