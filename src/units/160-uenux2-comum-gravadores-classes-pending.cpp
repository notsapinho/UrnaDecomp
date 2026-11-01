// Pending members of unit 160, which no source of ours holds yet. Their bodies are NOT the target's, they trap. Each
// class's first out-of-line virtual member is here, so its vtable is emitted here, and with it the destructors its
// slots 0 and 1 name, the compiler's code for the class definition (src/units/README.md "Pending members", "The key
// function pending"):
// - comum::CCopiadorMR's slot 2, fn 5874, and slot 3, fn 5873 (606 B each, slots of CCopiadorWSQMR's vtable too): each
//   builds paths from the file name at +4 with fn 183 (path::operator/=) and calls fns 1274 and 949 (comum::CPath's
//   GetPathResult and GetPathMR, unit 190) and 378, which no evidence names yet. They are named after their slot.
//   CCopiadorMR's destructors are emitted here and in ccopiadorwsqmr.cpp.o, whose copies our link keeps.
// They go in app/comum/gravadores/ccopiadormr.cpp when they are reconstructed; the vtable and the destructors move
// with them, under the same symbols. Delete this file with them. comum::asn::CConversorCarga's two slots (10291, 10290)
// were here too, and are written in gravadores/asn/cconversorcarga.cpp (fragment 172).
#include "app/comum/gravadores/ccopiadormr.h"

namespace comum {

void CCopiadorMR::Slot2()
{
    __builtin_trap();
}

void CCopiadorMR::Slot3()
{
    __builtin_trap();
}

} // namespace comum
