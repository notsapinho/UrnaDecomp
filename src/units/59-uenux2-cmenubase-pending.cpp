// Pending members: the comum::CMenuBase member no source holds yet. The class's vtable is emitted with MontaMenu, its
// key function (the destructor is defined inline in the header), and needs it defined; its body is NOT the target's,
// it traps.
// With the vtable this object also emits the destructors (target fns 12235 and 6188, slots 0 and 1), the compiler's
// code for the class definition in src/uenux2/src/app/comum/informacao/cmenubase.h; they move with the vtable to the
// class's source when MontaMenu does.
// Target function: MontaMenu 5913 (vtable slot 2, 1334 B; its name is chosen, cmenubase.h says why). It formats a line
// "[{}] - {}" per item and adds it to the form builder through fn 202, then the prompt, then builds an
// api::CInputField<api::CFramedText> (fn 2024; fn 1385 is the CFramedText constructor its record names) over an
// api::COptionValidation of the options' keys and hands it to the form builder (fn 426). The symbol file names all
// four now.
// Move it into the class's source (app/comum/informacao/cmenubase.cpp, a chosen path) when it is reconstructed; delete
// this file with it.
#include "app/comum/informacao/cmenubase.h"

namespace comum {

void CMenuBase::MontaMenu()
{
    __builtin_trap();
}

} // namespace comum
