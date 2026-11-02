// Pending members: the comum::CGravadorWSQ and comum::IGravador members no source of ours holds yet. Their bodies are
// NOT the target's, they trap.
// - CGravadorWSQ's vtable (@1557292) is emitted with its key function Slot2, and needs Slot2, Slot3 and Slot6 defined:
//   Slot2 is fn 11579 (slot 2, 319 B: it builds a path from the directory fn 1274 gives for 0 and m_nomeArquivo, with
//   fns 178 and 183, and passes it to fn 5821 with 0), Slot3 fn 11577 and Slot6 fn 11578 (slots 3 and 6, 9 B each: fn
//   6041 with 0 and with 1, which does the same with fn 1274's directory for 1, passing its argument on to fn 5821,
//   when m_gravaMidiaExterna is set). 5821 (8686 B) holds the records of GetCaminhoCorretoInternal and
//   GetCaminhoCorretoExternal (cgravadorwsq.cpp:175 and :192); 6041 is not named, and 1274 is
//   comum::CPath::GetPathResult (unit 190). They go in src/uenux2/src/app/comum/gravadores/cgravadorwsq.cpp when they
//   are reconstructed; with Slot2 the vtable and the implicit destructors move there too, under the same symbols.
// - comum::IGravador's Slot4 and Slot5, fns 11634 and 11633 (slots 4 and 5 of IGravador's vtable @1553648, 438 B each,
//   no record). IGravador's key function, Slot2, and Slot3 and Slot6 are unit 122's, in iresultado.cpp, which emits the
//   vtable, and these two go there when they are written. Each builds the path of the file in the work directory of
//   one flash (comum::CPath::GetPathTrab with 0 and with 1, fn 436, then path::operator/= with the file name at +20),
//   opens it with ecourna::api::io::CFile's constructor (fn 517, the mode "wb" and FileMode 0), passes the file to
//   GravaResultado (slot 7), then calls Close (fn 336), and the CFile's inline destructor follows. They wait for the
//   type of GravaResultado's parameter: its records (cgravadorbu.cpp:484, cgravadorhashes.cpp:112,
//   cgravadorrcsecao.cpp:110) spell it api::CFile, and app/comum/gravadores/igravador.h only forward-declares an
//   api::CFile, no header of this tree declaring that name as the ecourna::api::io::CFile these bodies pass.
//   Measured in a whole-link variant (docs/reference/facts/workflow.md W13: iresultado.cpp's object and this one's
//   replaced), with igravador.h under -iquote declaring `namespace api { using ecourna::api::io::CFile; }` and each
//   slot written in iresultado.cpp before Slot2 as a named const path (GetPathTrab with FLASH_INTERNA or FLASH_EXTERNA,
//   then / m_nomeArquivo), `api::CFile arquivo(caminho.string(), "wb");`, `GravaResultado(arquivo);` and
//   `arquivo.Close();`: fns 11634 and 11633 each scored 15 over 210 rows (pnpm wasm score against the target),
//   operand-only, every operand a call's or a data address.
// Delete this file with the last of them.
#include "app/comum/gravadores/cgravadorwsq.h"

namespace comum {

void IGravador::Slot4()
{
    __builtin_trap();
}

void IGravador::Slot5()
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
