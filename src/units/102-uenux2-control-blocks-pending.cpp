// Pending of unit 102: vota::CItemVisualizarCandidatosVota's slot 2 (target fn 12244, (i32) -> (i32)). The class's
// vtable, emitted with its out-of-line destructor, needs it. No evidence names the slot, and what the body does is not
// read yet; bool is the base's, which citemmenu.h reads from the other items' slot 2.
#include "app/vota/operador/outrasopcoes/citensmenuvota.h"

namespace vota {

bool CItemVisualizarCandidatosVota::Slot2()
{
    __builtin_trap();
}

} // namespace vota
