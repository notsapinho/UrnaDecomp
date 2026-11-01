// Pending members of comum's mesario states (src/units/135-uenux2-comum-mesario-estados.mk): the vtable slots that are
// not reconstructed, one trap each, so that the classes link and the members written can be measured. The object
// compiles with the unit's flags. A member's stub goes with its vtable in the link, so the note over each says what it
// waits for and the records it holds in the file of its class, whose lines stay blank there.
//
// comum::IGestorDadoMesario::StartState is the class's key function, so this object emits its vtable and typeinfo. The
// derived classes' constructors store their own vptr over the base's, so nothing stores this vtable and wasm-ld drops it
// (ledger/vtables.json lists none in the target either); the typeinfo stays, named by the derived classes' typeinfos. igestordadomesario.cpp is not
// written: its one record (line 65, GetControlador) belongs to this member. comum::CPedeDigitalMesario's key function is
// its destructor, in cpededigitalmesario.cpp, which emits its vtable; three of its slots are trapped here.

#include "app/comum/comparecimentomesario/estados/cpededigitalmesario.h"
#include "app/comum/comparecimentomesario/estados/igestordadomesario.h"

namespace comum {

// IGestorDadoMesario::StartState: fn 10337 (1733 B), slot 2 of CGestorDadoMesarioInicial, Votacao and Final, records
// igestordadomesario.cpp:65 (GetControlador, inlined) and cregistradormesario.cpp:85, callees with no name: 1149, 1255,
// 2730, 2731, 395, 448, 815 (3611 has one since unit 91, 566 since unit 178).
void IGestorDadoMesario::StartState()
{
    __builtin_trap();
}

// CPedeDigitalMesario::StartState: fn 10318 (257 B), records cpededigitalmesario.cpp:106, cpededigitalmesario.cpp:109,
// cpededigitalmesario.cpp:304 (GetControlador, inlined), callees with no name: 816
// (api::CPolySingleton<api::IFingerScanner>::instance, by its records; no header of this tree declares the class).
void CPedeDigitalMesario::StartState()
{
    __builtin_trap();
}

// CPedeDigitalMesario::FinishState: fn 10315 (17 B, a thunk into binaryen's fn 6012), records
// cpededigitalmesario.cpp:298, cpededigitalmesario.cpp:299, callees with no name: 816.
void CPedeDigitalMesario::FinishState()
{
    __builtin_trap();
}

// CPedeDigitalMesario::ProcessTick: fn 10316 (3808 B), records cpededigitalmesario.cpp:141, 142, 143, 182, 262
// (ExecutaBatimentoDigitalMesario, inlined) and 304 (GetControlador, inlined), callees with no name: 781, 816, 1149,
// 1686, 1903, 1937, 2223, 2224, 2742, 3615, 3719, 395, 5382, 6269.
void CPedeDigitalMesario::ProcessTick(uebyte)
{
    __builtin_trap();
}

} // namespace comum
