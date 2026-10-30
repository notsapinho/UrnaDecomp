// The reconstruction's note, not TSE's text: the destructors (1704, 3767, one body each with the other two DAOs') and
// Clone (10399, slot 2, a thunk into 3894), the only functions written here. No record gives one a line. The records of
// this file, ConverteEstadoBiometria (line 200) and ConverteDedoHabilitacao (line 232), are fns 5391 and 5390: not
// written. Slots 3, 7 and 8 are in src/units/91-uenux2-app-comum-dados-eleitor-pending.cpp.
#include "app/comum/comparecimentomesario/dao/ccomparecimentomesariodao.h"

namespace comum::dao {

CComparecimentoMesarioDAO::~CComparecimentoMesarioDAO() = default;

api::persistencia::IDAO* CComparecimentoMesarioDAO::Clone() const
{
    return new CComparecimentoMesarioDAO(*this);
}

} // namespace comum::dao

// <stubs>
// f5391 · 475 B · unmatched · name unknown
// ? f5391(i32) { ... }

// f5390 · 472 B · unmatched · name unknown
// ? f5390(i32) { ... }
// </stubs>
