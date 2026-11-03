// Pending members of comum's mesario states (src/units/135-uenux2-comum-mesario-estados.mk): the vtable slots that are
// not reconstructed, one trap each, so that the classes link and the members written can be measured. The object
// compiles with the unit's flags. A member's stub goes with its vtable in the link, so the note over each says what it
// waits for and the records it holds in the file of its class, whose lines stay blank there.
//
// comum::IGestorDadoMesario::StartState is the class's key function, so this object emits its vtable and typeinfo. The
// derived classes' constructors store their own vptr over the base's, so nothing stores this vtable and wasm-ld drops it
// (ledger/vtables.json lists none in the target either); the typeinfo stays, named by the derived classes' typeinfos. igestordadomesario.cpp is not
// written: its one record (line 65, GetControlador) belongs to this member. comum::CPedeDigitalMesario's key function is
// its destructor, in cpededigitalmesario.cpp, which emits its vtable; two of its slots are trapped here.

#include "app/comum/comparecimentomesario/estados/cpededigitalmesario.h"
#include "app/comum/comparecimentomesario/estados/igestordadomesario.h"

namespace comum {

// IGestorDadoMesario::StartState: fn 10337 (1733 B), slot 2 of CGestorDadoMesarioInicial, Votacao and Final, records
// igestordadomesario.cpp:65 (GetControlador, inlined) and cregistradormesario.cpp:85, callees with no name: 1149 (395
// has one since unit 31, 3611 since unit 91, 566 since unit 178, 815 since unit 113's GetInst, 2730 and 2731 since unit
// 221, 1255 since unit 247; 448 matches from this unit's cconfirmafimregistromesarios.cpp.o).
void IGestorDadoMesario::StartState()
{
    __builtin_trap();
}

// CPedeDigitalMesario::FinishState: fn 10315 (17 B), `f6012(p0, 1595500, 1595484)`, a thunk into binaryen's fn 6012,
// which it shares with vota::CRegistraDigitalOperador::FinishState (10453, records cregistradigitaloperador.cpp:104 and
// :105), not written: a merge-thunk member, which matches once both are in the link. Its source, read from 6012 and its
// records (cpededigitalmesario.cpp:298 and :299, column 5, lines that stay blank there):
//     api::CPolySingleton<api::IFingerScanner>::instance().Slot7(0);
//     api::CPolySingleton<api::IFingerScanner>::instance().Slot6();
// Its callee 816 matches since this unit's roots put IFingerMatcher's instance beside it.
void CPedeDigitalMesario::FinishState()
{
    __builtin_trap();
}

// CPedeDigitalMesario::ProcessTick: fn 10316 (3808 B), records cpededigitalmesario.cpp:141, 142, 143, 182, 262
// (ExecutaBatimentoDigitalMesario, inlined) and 304 (GetControlador, inlined), callees with no name: 781, 1149, 1903,
// 1937, 2223, 2224, 2742, 3615, 3719, 5382, 6269 (395 has one since unit 31, 816 and 1686 since this unit's roots). It
// holds CDigitalMesarioNaoReconhecida's GetInst inlined, whose form takes cdigitalmesarionaoreconhecida.cpp's
// CNomeMesariosUrnaDS::Text (10323), the other half of fn 6008.
void CPedeDigitalMesario::ProcessTick(uebyte)
{
    __builtin_trap();
}

} // namespace comum
