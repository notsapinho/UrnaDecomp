// Pending members: the comum::CGravadorWSQ and comum::IGravador members no source of ours holds yet. Their bodies are
// NOT the target's, they trap.
// - CGravadorWSQ's vtable (@1557292) is emitted with its key function Slot2, and needs Slot2, Slot3 and Slot6 defined:
//   Slot2 is fn 11579 (slot 2, 319 B: it builds a path from the directory fn 1274 gives for 0 and m_nomeArquivo, with
//   fns 178 and 183, and passes it to fn 5821 with 0), Slot3 fn 11577 and Slot6 fn 11578 (slots 3 and 6, 9 B each: fn
//   6041 with 0 and with 1, which does the same with fn 1274's directory for 1, passing its argument on to fn 5821,
//   when m_gravaMidiaExterna is set). 5821 (8686 B) holds the records of GetCaminhoCorretoInternal and
//   GetCaminhoCorretoExternal (cgravadorwsq.cpp:175 and :192); 1274 and 6041 are not named. They go in
//   src/uenux2/src/app/comum/gravadores/cgravadorwsq.cpp when they are reconstructed; with Slot2 the vtable and the
//   implicit destructors move there too, under the same symbols.
// - CGravadorWSQ's typeinfo names IGravador's, which is emitted only with IGravador's key function (its first
//   out-of-line virtual member): without a definition of it the link stops on an undefined `typeinfo for
//   comum::IGravador`. IGravador's vtable (@1553648) needs its five members defined: Slot2 fn 11632, Slot3 fn 11630,
//   Slot4 fn 11634, Slot5 fn 11633, Slot6 fn 11631 (608, 1207, 438, 438 and 608 B, no record). IGravador's
//   constructor (fn 1396, unit 122's, in iresultado.cpp) stores its vptr, so the link keeps that vtable and these
//   traps, and the five stubs went from src/uenux2/unplaced.cpp; the scan lists the five `no-candidate`. They go in
//   the file of IGravador's key function when they are reconstructed: iresultado.cpp, where unit 122 put the
//   constructor, is a choice the vtable's place in the data allows (that unit's fragment), not evidence.
// Delete this file with the last of them.
#include "app/comum/gravadores/cgravadorwsq.h"

namespace comum {

void IGravador::Slot2()
{
    __builtin_trap();
}

void IGravador::Slot3()
{
    __builtin_trap();
}

void IGravador::Slot4()
{
    __builtin_trap();
}

void IGravador::Slot5()
{
    __builtin_trap();
}

void IGravador::Slot6()
{
    __builtin_trap();
}

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
