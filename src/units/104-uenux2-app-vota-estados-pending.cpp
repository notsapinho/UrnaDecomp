// Pending members of the state singletons (src/units/104-uenux2-app-vota-estados.mk): the vtable slots of those states
// that are not reconstructed, one trap each, so that the classes link and GetInst can be measured. The object compiles
// with the unit's flags. StartState is the key function of the classes that do not write it or an out-of-line
// destructor, so for them this object emits the vtable, the typeinfo and the deleting destructor, with no change when
// the member lands (src/units/README.md "Pending members"). A member's stub goes with its vtable in the link, so the note
// over each says what it waits for and the records it holds in the file of its class, whose lines stay blank there.

#include "app/vota/eleitor/fimvotacao/cgravaresultado.h"
#include "app/vota/eleitor/fimvotacao/cimprimindobim.h"
#include "app/vota/eleitor/fimvotacao/cimprimirbuoutrasobrigatorias.h"
#include "app/vota/eleitor/fimvotacao/ciniciobu.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatosporcargo.h"
#include "app/vota/eleitor/iniciovotacao/creimprimindozeresima.h"
#include "app/vota/operador/cfinalizaoperador.h"

namespace vota {

// CGravaResultado::StartState: fn 12098 (26731 B), records cgravaresultado.cpp:63, cgravaresultado.cpp:79, no callee
// unnamed of 133, imports aside (491, 1935, 2821, 2543, 5545, 2860, 5866, 5869, 5870 and 5480, unit 379's, named); its
// other callees have names (502, 886 and 6174, units 31's, 165's and 220's, units 193's 675 and 676, 195's 5824, 95's
// 1164, 3829, 5889, 5891 and 5905, 32's 378, 2763 and 5462, 154's 620, 13's 1269, 110's 2822 and 2824, 88's 3782, 227's
// 3825 and 3826, and 2281, std::set<std::string>'s hinted insert from the tree root roots_set.cpp, among them). Besides
// its own 384-byte frame it holds 31 stack prologues of functions binaryen inlined (pnpm wasm fn's readout, a reading of
// each by its strings, records, calls and vptr stores). Written since, unrooted, with no index of their own: the
// gravadores' constructors and converters and the md classes' constructors (units 122, 136, 200, 227, 268, 305;
// md::CVersoesContratos' through its GetTag, unit 227), comum::GetPathLogArquivados (the 32-byte "arquivados/" path,
// cgravadorlog.cpp, unit 136), CLogComum's seven members, CAssinador::AssinaArquivosResultado, comum::AssinarEcourna,
// IInterfaceSavd::EnviarLocal, CAssinador's and vota::CAssinadorVota's second constructors (units 34, 95, 111, 165),
// vota::CProgressoEncerramento's constructor over vota::TelaProgressoEncerramento and the base's out-of-line
// constructor (unit 48). Its own code is not written. It waits for that, and for fn 5545's font: the target's
// AddProgressBar has that parameter folded (both target callers pass one constant), and with the progress screen in
// our link next to unit 31's roots, which pass another object for 7787, ours keeps it (unit 48's fragment has the
// measurement).
void CGravaResultado::StartState()
{
    __builtin_trap();
}

} // namespace vota
