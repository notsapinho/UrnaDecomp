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
// 3825 and 3826, and 2281, std::set<std::string>'s hinted insert from the tree root roots_set.cpp, among them).
// It waits above all for the code it holds: besides its own 384-byte frame, 31 stack prologues of functions binaryen
// inlined (read from pnpm wasm fn's readout, a reading of each by its strings, records, calls and vptr stores):
// comum::CGeracaoVersoesContratos::GetInst with the md classes' constructors, CPolySingleton<T>::set and instance,
// CPolySingletonList::push<T> and instance<T> (GetInst and its constructor written in unit 268, compared with nothing;
// the templates unit 100's header code; the md constructors, records cdependenciascontratos.cpp:27 and
// cversoescontratos.cpp:29, are not written); the constructors of comum::CGravadorBU, CGravadorVersoesArquivos and
// CGravadorLog (their vptrs stored behind prologues; not written), CGravadorRCSecao's (frameless) with
// comum::CGravadorUtil::ConverteFaseEcourna (record cgravadorutil.cpp:113) behind a 480-byte prologue and a second one
// of 480 bytes with no code left (a reading: ConverteSituacaoArquivoEcourna, record 129, which no function loads),
// seven comum::CLogComum members (records clogcomum.cpp:44, 50, 56, 62, 166, 172, 178),
// CAssinador::AssinaArquivosResultado (cassinador.cpp:141, 146, 149), comum::AssinarEcourna (iinterfacesavd.cpp:1022),
// a progress screen over ctelasvota.cpp's fonts (its AddProgressBar call is fn 5545's second target caller) and the
// CGeradorResultados steps: none written.
void CGravaResultado::StartState()
{
    __builtin_trap();
}

} // namespace vota
