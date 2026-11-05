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
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatosporcargo.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatosporpartido.h"
#include "app/vota/eleitor/iniciovotacao/creimprimindozeresima.h"
#include "app/vota/operador/cfinalizaoperador.h"

namespace vota {

// CGravaResultado::StartState: fn 12098 (26731 B), records cgravaresultado.cpp:63, cgravaresultado.cpp:79, callees
// with no name (491, 1935 and 2821 are named now (units 205 and 110)): 2543, 2860, 5480, 5545, 5866, 5869 and 5870; its other callees have names
// (502, 886 and 6174, units 31's, 165's and 220's, units 193's 675 and 676, 195's 5824, 95's 1164, 3829, 5889, 5891
// and 5905, 32's 378, 2763 and 5462, 154's 620, 13's 1269, 110's 2822 and 2824, 88's 3782, fragment 227's 3825 and 3826, and
// 2281, std::set<std::string>'s hinted insert, from the tree root src/app/roots_set.cpp, among them).
void CGravaResultado::StartState()
{
    __builtin_trap();
}

// CMenuFiltrarCandidatosPorNumero::StartState: fn 11892 (1721 B), callees with no name: 2383; the others have names
// (365 since fragment 191, 374 since unit 88's GetCargos, 502 unit 31's, 1279 unit 150's, 576 unit 165's, 653 unit
// 120's).
void CMenuFiltrarCandidatosPorNumero::StartState()
{
    __builtin_trap();
}

// CMenuFiltrarCandidatosPorNumero::ProcessInput: fn 11891 (999 B), every callee has a name (5446 unit 01's,
// 1273 unit 89's, 1279 unit 150's). It holds two functions binaryen inlined, each behind a stack prologue of its own:
// a message screen ("Candidato não encontrado!" over an api::CWait of 2000 ms the caller builds in its own frame) and,
// inside it, a GetForm over std::shared_ptr<IPreShow<IScreen>>(new CPreShowNothing<IScreen>). Written in a scratch
// link with the two out of line in other TUs than their callers' (vota::MostraMensagemTemporaria beside ProcessInput,
// vota::MontaForm in comum/ctelasvota.cpp, names chosen), it scored 33 over 447 rows, all operand-only: calls and data
// but for one frame slot, the message's second api::SPoint temporary at +12 where the target has +20. Step 8's
// vptr-anchor then read that 12 and 20 as table slots and took the name of fn 608 (ours 678, at slot 12), and ten
// matches left (599, 2509, 2924, 3387, 3622, 3928, 4867, 4873, 6131, 11004). It waits for a form of the message whose
// temporaries take the target's slots.
void CMenuFiltrarCandidatosPorNumero::ProcessInput()
{
    __builtin_trap();
}

// CMenuFiltrarCandidatosPorPartido::StartState: fn 11884 (3643 B), record cmenufiltrarcandidatosporpartido.cpp:39 (its
// line stays blank there), not written: its menu holds api::CMenuItem::SetFormatString and
// api::CInputMenuField::SetFormatString inlined (records cinputmenufield.cpp:156 and 468), which are not written, and
// it calls fn 5953 (CVisualizarCandidatos::CarregaCandidaturas, written in cvisualizarcandidatos.cpp) before it collects
// the candidatures' parties into a set in its frame.
void CMenuFiltrarCandidatosPorPartido::StartState()
{
    __builtin_trap();
}

} // namespace vota
