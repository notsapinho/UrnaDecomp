// Pending members: the key functions of comum's recorders, which no source of ours holds yet. Their bodies are NOT the
// target's, they trap. Each is its class's first out-of-line virtual member, so the class's vtable is emitted here,
// and with it the implicit destructors its slots 0 and 1 name, the compiler's code for the class definitions in the
// headers (src/units/README.md "Pending members", "The key function pending"):
// - comum::CGravadorHashes::GravaResultado, fn 11620 (slot 7, 4622 B, record cgravadorhashes.cpp:112): it builds the
//   hashes entity, with two md::CEntidadeHashes (fn 5855 twice), and writes it;
// - comum::CGravadorLog::GravaResultado, fn 11584 (slot 7).
// They go in cgravadorhashes.cpp (the record's file) and in the recorders' own .cpp files, which no record names,
// when they are reconstructed; the vtables and the implicit destructors move with them, under the same symbols.
// cgravadorhashes.cpp was a stub-only file, and it went with its stubs (fns 11620, 11619, 5853): its one record is
// GravaResultado's, line 112, column 15, so writing that member writes the file again. Delete this file with the last
// of them.
#include "app/comum/gravadores/cgravadorhashes.h"
#include "app/comum/gravadores/cgravadorlog.h"

namespace comum {

void CGravadorHashes::GravaResultado(api::CFile&) const
{
    __builtin_trap();
}

void CGravadorLog::GravaResultado(api::CFile&) const
{
    __builtin_trap();
}

} // namespace comum
