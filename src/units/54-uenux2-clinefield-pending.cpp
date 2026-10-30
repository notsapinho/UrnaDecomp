// Pending members: the api::CLineField members src/uenux2/src/api/gui/clinefield.cpp does not hold yet. The class's
// vtable (emitted with GetTypeName in that TU) needs them defined; their bodies are NOT the target's, they trap.
// Target functions:
//   11068 Draw(IScreen&) const: one call through IScreen slot 8 (vtable offset 32) with (m_inicio, m_fim, m_cor, 1);
//         api/gui/iscreen.h declares that slot as DrawLine, a name no evidence gives
// Move each into clinefield.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/clinefield.h"

namespace api {

void CLineField::Draw(IScreen&) const
{
    __builtin_trap();
}

} // namespace api
