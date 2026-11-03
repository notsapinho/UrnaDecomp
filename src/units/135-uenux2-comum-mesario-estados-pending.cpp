// Pending members of comum's mesario states (src/units/135-uenux2-comum-mesario-estados.mk): the vtable slots that are
// not reconstructed, one trap each, so that the classes link and the members written can be measured. The object
// compiles with the unit's flags. A member's stub goes with its vtable in the link, so the note over each says what it
// waits for and the records it holds in the file of its class, whose lines stay blank there.
//
// comum::CPedeDigitalMesario's key function is its destructor, in cpededigitalmesario.cpp, which emits its vtable; one of
// its slots is trapped here.

#include "app/comum/comparecimentomesario/estados/cpededigitalmesario.h"

namespace comum {

// CPedeDigitalMesario::ProcessTick: fn 10316 (3808 B), records cpededigitalmesario.cpp:141, 142, 143, 182, 262
// (ExecutaBatimentoDigitalMesario, inlined) and 304 (GetControlador, inlined), callees with no name: 781, 1903,
// 1937, 2223, 2224, 2742, 3615, 3719, 5382, 6269 (395 has one since unit 31, 816 and 1686 since this unit's roots,
// 1149 since unit 214). It
// holds CDigitalMesarioNaoReconhecida's GetInst inlined, whose form takes cdigitalmesarionaoreconhecida.cpp's
// CNomeMesariosUrnaDS::Text (10323), the other half of fn 6008.
void CPedeDigitalMesario::ProcessTick(uebyte)
{
    __builtin_trap();
}

} // namespace comum
