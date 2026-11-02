// Pending members: the comum::CGravadorWSQ members no source of ours holds yet. Their bodies are NOT the target's, they
// trap.
// - CGravadorWSQ's vtable (@1557292) is emitted with its key function Slot2, and needs Slot2, Slot3 and Slot6 defined:
//   Slot2 is fn 11579 (slot 2, 319 B: it builds a path from the directory fn 1274 gives for 0 and m_nomeArquivo, with
//   fns 178 and 183, and passes it to fn 5821 with 0), Slot3 fn 11577 and Slot6 fn 11578 (slots 3 and 6, 9 B each: fn
//   6041 with 0 and with 1, which does the same with fn 1274's directory for 1, passing its argument on to fn 5821,
//   when m_gravaMidiaExterna is set). 5821 (8686 B) holds the records of GetCaminhoCorretoInternal and
//   GetCaminhoCorretoExternal (cgravadorwsq.cpp:175 and :192); 6041 is not named, and 1274 is
//   comum::CPath::GetPathResult (unit 190). They go in src/uenux2/src/app/comum/gravadores/cgravadorwsq.cpp when they
//   are reconstructed; with Slot2 the vtable and the implicit destructors move there too, under the same symbols.
// Delete this file with the last of them.
#include "app/comum/gravadores/cgravadorwsq.h"

namespace comum {

void CGravadorWSQ::Slot2()
{
    __builtin_trap();
}

void CGravadorWSQ::Slot3()
{
    __builtin_trap();
}

void CGravadorWSQ::Slot6()
{
    __builtin_trap();
}

} // namespace comum
