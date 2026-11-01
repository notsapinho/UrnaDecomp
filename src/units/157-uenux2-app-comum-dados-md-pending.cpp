// Pending members: the member CConversorLocal's vtable needs that no source of ours defines yet.
// comum::asn::CConversorLocal::DoDesconverte, slot 3, target fn 11452 (record cconversorlocal.cpp:70, which stays blank
// in cconversorlocal.cpp until it lands). md/clocal.h reads 11452 as holding md::CLocal's two constructors, each calling
// CLocal::ValidaCriacao (fn 5673) once, and those constructors are not written: they belong in md/clocal.cpp, a source
// of 89-uenux2-clocal.mk.
#include "app/comum/dados/asn/cconversorlocal.h"

namespace comum::asn {

md::CLocal CConversorLocal::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
