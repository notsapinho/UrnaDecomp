// Pending members: the api::CLineField members src/uenux2/src/api/gui/clinefield.cpp does not hold yet. The class's
// vtable (emitted with GetTypeName in that TU) needs them defined; their bodies are NOT the target's, they trap.
// Target functions:
//   11068 Draw(IScreen&) const: one call through IScreen slot 8 (vtable offset 32) with (m_inicio, m_fim, m_cor, 1);
//         api/gui/iscreen.h does not declare that slot yet, and nothing names it
//   5527  Move(const SPoint&): binaryen's one body for this class and CTextFieldDoubleLine (whose Move is pending in
//         28-uenux2-ctextfielddoubleline-pending.cpp); it moves m_fim by the offset of the new m_inicio, then marks the
//         field changed through IForm<IScreen> (its +28 mutex, +4 flag and slot 4), which api/gui/iform.h declares
//         as IsVisible and Refresh
// Move each into clinefield.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/clinefield.h"

namespace api {

void CLineField::Draw(IScreen&) const
{
    __builtin_trap();
}

void CLineField::Move(const SPoint&)
{
    __builtin_trap();
}

} // namespace api
