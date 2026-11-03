// Pending member: comum::impl::CValidaMidia's slot 8, the one slot no source holds yet. The class's vtable is emitted
// with EhValida, its key function (app/comum/validamidia/cvalidamidia.cpp), and needs every slot defined; this body is
// NOT the target's, it traps. Its name and type are chosen (app/comum/validamidia/ivalidamidia.h).
// Target function: fn 11167 (1260 B, slot 8). Not read further than its callees and literals: it builds the result-file
// pattern "#regex#[ost][0-9]{5}[a-z]{2}[0-9]{13}-[a-z]+\\.[a-z]+" (378414) in a vector, reads comum::CPath::GetPathMR
// (949), walks the directory with api::CDirReader (1914, 1260, 1912, 2231, 2232, 1913) and calls api::CasamTodos (2758)
// twice, api::CSystem::IsEmptyDir (2762) and api::ExistResource (1690), csystem.cpp's file-static function: a call of
// another file's internal function puts that call in csystem.cpp's TU, so 11167 holds a csystem.cpp function binaryen
// inlined (a reading, docs/reference/facts/placing.md P2), not written. Move it into cvalidamidia.cpp when it is
// reconstructed; delete this file then.
#include "app/comum/validamidia/cvalidamidia.h"

namespace comum::impl {

int CValidaMidia::Slot8()
{
    __builtin_trap();
}

} // namespace comum::impl
