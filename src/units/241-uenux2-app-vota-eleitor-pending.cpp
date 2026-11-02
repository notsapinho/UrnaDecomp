// Pending member of fragment 241's class vota::impl::CSincronismoVotoEleitor
// (src/units/241-uenux2-app-vota-eleitor.mk), its class's key function, so this object emits its vtable; trapped so
// that the class links. Its body is NOT the target's. What it waits for:
// - vota::impl::CSincronismoVotoEleitor::Sincroniza 7174 (slot 2), 3288 B: it holds the records of
//   csincronizavota.cpp's vota::(anonymous namespace)::SincronizaRDVInternoSeguro and SincronizaRDVExternoSeguro (lines
//   290 and 303), so it calls into that file, and of the 48 functions it calls (imports aside) fns 1551, 1692, 1701,
//   2369, 2543, 2826, 3789 and 3790 have no name and no match. Its stub, which sat at csincronizavota.cpp:287, goes
//   with this trap.
#include "app/vota/eleitor/csincronismovotoeleitor.h"

namespace vota {

namespace impl {

bool CSincronismoVotoEleitor::Sincroniza()
{
    __builtin_trap();
}

} // namespace impl

} // namespace vota
