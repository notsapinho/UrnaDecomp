// Pending members: the api::CInputMenuField member src/uenux2/src/api/gui/cinputmenufield.cpp does not hold yet. The
// class's vtable is emitted there with the destructor, its key function, and needs it defined; its body is NOT the
// target's, it traps. Target function, reached only through the vtable:
// - Draw 10897 (slot 2, 607 B, which holds CMenuItem::Draw inlined, record cinputmenufield.cpp 74:21): it calls fn 5492,
//   which CMenuItem::UpdateRect (fn 3657) calls too, and which is not written and has no name. 5492 calls fn 160,
//   std::string's append, three times (ledger/callgraph.tsv), a call uenux2's -O2 inlines at the sites
//   docs/reference/facts/levels.md V3 measures; so Draw waits for 5492, and 5492 for that level or a name its two callers
//   vote for.
// Move it into cinputmenufield.cpp when it is reconstructed; delete this file with it.
#include "api/gui/cinputmenufield.h"

namespace api {

void CInputMenuField::Draw(IScreen&) const
{
    __builtin_trap();
}

} // namespace api
