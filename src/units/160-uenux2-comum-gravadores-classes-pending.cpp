// Pending members of unit 160, which no source of ours holds yet. Their bodies are NOT the target's, they trap. Each
// class's first out-of-line virtual member is here, so its vtable is emitted here, and with it the destructors its
// slots 0 and 1 name, the compiler's code for the class definition (src/units/README.md "Pending members", "The key
// function pending"):
// - comum::CCopiadorMR's slot 2, fn 5874, and slot 3, fn 5873 (606 B each, slots of CCopiadorWSQMR's vtable too): each
//   builds paths from the file name at +4 with fn 183 (a reading: path::operator/=) and calls fns 1274, 949 and
//   378, which no evidence names yet. They are named after their slot. CCopiadorMR's destructors are emitted here and
//   in ccopiadorwsqmr.cpp.o, whose copies our link keeps.
// - comum::asn::CConversorCarga's DoConverte and DoDesconverte, fns 10291 and 10290 (slots 2 and 3): they wait for fns
//   1080 and 3734, and 3733 and 2802, which no evidence names yet.
// They go in app/comum/gravadores/ccopiadormr.cpp and in the converter's own .cpp (cconversorcarga.cpp, a path no
// record names) when they are reconstructed; the vtables and the destructors move with them, under the same symbols.
// Delete this file with the last of them.
#include "app/comum/gravadores/asn/cconversorcarga.h"
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

namespace asn {

CConversorCarga::TEntidade CConversorCarga::DoConverte(const TDado&) const
{
    __builtin_trap();
}

CConversorCarga::TDado CConversorCarga::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace asn

} // namespace comum
