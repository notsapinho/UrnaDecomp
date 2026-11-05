// Pending members: the key function of comum's hashes recorder, which no source of ours holds yet. Its body is NOT the
// target's, it traps. It is its class's first out-of-line virtual member, so the class's vtable is emitted here, and
// with it the implicit destructors its slots 0 and 1 name, the compiler's code for the class definition in the header
// (src/units/README.md "Pending members", "The key function pending"):
// - comum::CGravadorHashes::GravaResultado, fn 11620 (slot 7, 4622 B, record cgravadorhashes.cpp:112): it builds the
//   hashes entity, with two md::CEntidadeHashes (fn 5855 twice), and writes it.
// It goes in cgravadorhashes.cpp (the record's file) when it is reconstructed; the vtable and the implicit destructors
// move with it, under the same symbols. cgravadorhashes.cpp was a stub-only file, and it went with its stubs (fns
// 11620, 11619, 5853): its one record is GravaResultado's, line 112, column 15, so writing that member writes the file
// again. Delete this file with it. (comum::CGravadorLog::GravaResultado, fn 11584, trapped here before, is written in
// app/comum/gravadores/cgravadorlog.cpp.)
#include "app/comum/gravadores/cgravadorhashes.h"

namespace comum {

void CGravadorHashes::GravaResultado(api::CFile&) const
{
    __builtin_trap();
}

} // namespace comum
