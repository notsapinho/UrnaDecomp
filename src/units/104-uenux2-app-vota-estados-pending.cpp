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
// its own 384-byte frame it holds 31 stack prologues of functions binaryen inlined (pnpm wasm fn's readout, a reading
// of each by its strings, records, calls and vptr stores). Written since, unrooted, with no index of their own: the
// gravadores' constructors and converters and the md classes' constructors (units 122, 136, 200, 227, 268, 305;
// md::CVersoesContratos' through its GetTag, unit 227), comum::GetPathLogArquivados (the 32-byte "arquivados/" path,
// cgravadorlog.cpp, unit 136), CLogComum's seven members, CAssinador::AssinaArquivosResultado, comum::AssinarEcourna,
// IInterfaceSavd::EnviarLocal, CAssinador's and vota::CAssinadorVota's second constructors (units 34, 95, 111, 165),
// vota::CProgressoEncerramento's constructor over vota::TelaProgressoEncerramento and the base's out-of-line
// constructor (unit 48). Its own code is not written, and it waits for that: the body around the 384-byte frame, and
// five functions it holds behind frames of their own that no unit writes yet (lines of pnpm wasm fn's folded readout,
// from the line after `;; --- folded readout`): comum::CGeracaoVersoesContratos' versions builder (80 bytes, line 1938)
// and its dependencies loop (16 bytes, line 1942), a comum::CGeradorResultados constructor that passes fn 5824 an empty
// second vector (48 bytes, line 2801; 5824's two calls there read as one call split on whether the std::shared_ptr
// argument has a control block), a member that runs the recorders inside api::CApplication contexts and logs and signs
// them (352 bytes, line 2824), and a loop that copies the result files (32 bytes, line 3447). Read from that code: what
// 5824 copies to +76 is the progress screen, the shared_ptr of the vota::CProgressoEncerramento 12098 builds, whose
// slots 2 and 4 (comum::CAbstractTelaProgresso's Inicia and Incrementa) the member calls, where cgeradorresultados.h
// declares an IGravador; and record 79's text, "Assert (eleitores.GetNumComparecimentos() == rdv.Comparecimento())",
// spells the accessor of comum::CEleitores' word at +104 that celeitores.h calls GetComparecimento, a chosen name. Fn
// 5545's folded font is the screen's vota::FONTE_BARRA_PROGRESSO, which unit 31's roots pass.
void CGravaResultado::StartState()
{
    __builtin_trap();
}

} // namespace vota
