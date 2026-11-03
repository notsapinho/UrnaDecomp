// Pending member of comum::CRegistrarMesarios (src/units/247-uenux2-cregistrarmesarios.mk): its ProcessInput, one trap,
// so that the class links and GetInst and StartState can be measured. The object compiles with the unit's flags. The
// class's key function is its destructor, in cregistrarmesarios.cpp, which emits the vtable; the trap moves there when
// the member is written.
//
// CRegistrarMesarios::ProcessInput: fn 10391 (17 B), `f6011(p0, 1593628, 1593656)`, a thunk into binaryen's fn 6011,
// whose other caller is fn 10338 (comum::CMesarioRegistrado::ProcessInput, `f6011` with that class's two records): the
// constants are the records the merged body loads, cregistrarmesarios.cpp:68 (GetControlador, inlined) and this file's
// copy of cinteractiveform.h:57 (CInteractiveForm<IScreenMT, IInputMT>::Read()). Its source, read from 6011's br_table
// on Read() - 5 (a reading; not compiled):
//
//     switch (m_form->Read()) {
//     case api::INPUT_CONFIRMA:
//         GetControlador().LogaConfirmouRegistroMesarios();
//         m_pNextState = &CPedeTituloMesario::GetInst();
//         break;
//     case api::INPUT_CORRIGE:
//         GetControlador().LogaCancelouRegistroMesarios();
//         m_pNextState = &CConfirmaFimRegistroMesarios::GetInst();
//         break;
//     }
//
// (slots 24 and 25 of IControladorRegistraMesarios, then fns 2729 and 5389; the target stores the next state once,
// after the cases). The target's 10391 is a 17-byte thunk, which our link forms only when binaryen merges two bodies of
// that shape: it waits for 10338 to be written, and for 6011's callee 5389 (CConfirmaFimRegistroMesarios::GetInst),
// which has no body in this tree yet. Until then it stays a trap (src/units/README.md "Pending members", a member whose
// target body is a merge thunk).
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"

namespace comum {

void CRegistrarMesarios::ProcessInput()
{
    __builtin_trap();
}

} // namespace comum
