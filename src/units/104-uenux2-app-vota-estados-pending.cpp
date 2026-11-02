// Pending members of the state singletons (src/units/104-uenux2-app-vota-estados.mk): the vtable slots of those states
// that are not reconstructed, one trap each, so that the classes link and GetInst can be measured. The object compiles
// with the unit's flags. StartState is the key function of the classes that do not write it or an out-of-line
// destructor, so for them this object emits the vtable, the typeinfo and the deleting destructor, with no change when
// the member lands (src/units/README.md "Pending members"). A member's stub goes with its vtable in the link, so the note
// over each says what it waits for and the records it holds in the file of its class, whose lines stay blank there.

#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/eleitor/ciniciodeciclo.h"
#include "app/vota/eleitor/fimvotacao/cgravaresultado.h"
#include "app/vota/eleitor/fimvotacao/cemitirmaisbu.h"
#include "app/vota/eleitor/fimvotacao/cimprimindobim.h"
#include "app/vota/eleitor/fimvotacao/cimprimirbuoutrasobrigatorias.h"
#include "app/vota/eleitor/fimvotacao/ciniciobu.h"
#include "app/vota/eleitor/iniciovotacao/cimprimindozeresima.h"
#include "app/vota/eleitor/iniciovotacao/ciniciozeresima.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenuvisualizarcandidatos.h"
#include "app/vota/eleitor/iniciovotacao/creimprimindoresumozeresima.h"
#include "app/vota/eleitor/iniciovotacao/creimprimindozeresima.h"
#include "app/vota/eleitor/iniciovotacao/cquerreimprimirzeresima.h"
#include "app/vota/operador/outrasopcoes/cfimaquisicaovotos.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"
#include "app/vota/operador/leidentidade/cprocuraeleitor.h"
#include "app/comum/comparecimentomesario/estados/cpedetitulomesario.h"
#include "app/vota/operador/cfinalizaoperador.h"
#include "app/vota/operador/csincronismooperador.h"

namespace vota {

// CAguardaMensagem::ProcessKey: fn 7481 (742 B), callees with no name: 491, 2376, 6557.
void CAguardaMensagem::ProcessKey(uebyte)
{
    __builtin_trap();
}

// CIniciodeCiclo::StartState: fn 7306 (251 B), records ciniciodeciclo.cpp:48, ciniciodeciclo.cpp:61, callees with no
// name: 491, 1823, 3333.
void CIniciodeCiclo::StartState()
{
    __builtin_trap();
}

// CGravaResultado::StartState: fn 12098 (26731 B), records cgravaresultado.cpp:63, cgravaresultado.cpp:79, callees
// with no name: 491, 1935, 2543, 2821, 2824, 2860, 5480, 5545, 5866, 5869 and 5870; its other callees have names
// (502, 886 and 6174, units 31's, 165's and 220's, units 193's 675 and 676, 195's 5824, 95's 1164, 3829, 5889, 5891
// and 5905, 32's 378, 2763 and 5462, 154's 620, 13's 1269, 110's 2822, 88's 3782, fragment 227's 3825 and 3826, and
// 2281, std::set<std::string>'s hinted insert, from the tree root src/app/roots_set.cpp, among them).
void CGravaResultado::StartState()
{
    __builtin_trap();
}

// CEmitirMaisBU::ProcessInput: fn 12081 (1543 B), records cemitirmaisbu.cpp:64, callees with no name: 491; the others
// have names (185, 261, 407, 455, 903, 1127, 4556, 4557, 4563, 5987, 2888 and 3701, units 37's and 93's, 4582, unit
// 168's, and 2890, unit 156's).
void CEmitirMaisBU::ProcessInput()
{
    __builtin_trap();
}

// CImprimindoBim::StartState: fn 12071 (1074 B), records cimprimindobim.cpp:50, cimprimindobim.cpp:51,
// cimprimindobim.cpp:66, callees with no name: 185, 187, 261, 401, 463, 1127, 2291 (1487 and 1488 are unit 168's).
void CImprimindoBim::StartState()
{
    __builtin_trap();
}

// CImprimirBUOutrasObrigatorias::StartState: fn 12065 (1790 B), records cimprimirbuoutrasobrigatorias.cpp:50,
// cimprimirbuoutrasobrigatorias.cpp:53, cimprimirbuoutrasobrigatorias.cpp:57, callees with no name: 491, 2291; the
// others have names (3701 unit 93's, 1880 unit 00's, 2890 unit 156's, 502 unit 31's, 886 unit 165's).
void CImprimirBUOutrasObrigatorias::StartState()
{
    __builtin_trap();
}

// CImprimindoZeresima::StartState: fn 11991 (2577 B), records cimprimindozeresima.cpp:104, cimprimindozeresima.cpp:77,
// callees with no name: 185, 187, 261, 491, 1127, 2882, 6587 (1487 and 1488 are unit 168's).
void CImprimindoZeresima::StartState()
{
    __builtin_trap();
}

// CInicioZeresima::StartState: fn 11924 (41 B), callees with no name: 185, 261, 491, 697 (unit 169's: 5957, 5959).
void CInicioZeresima::StartState()
{
    __builtin_trap();
}

// CMaisInformacoes::StartState: fn 11897 (182 B), callee with no name: 6599.
void CMaisInformacoes::StartState()
{
    __builtin_trap();
}

// CMenuFiltrarCandidatosPorNumero::StartState: fn 11892 (1721 B), callees with no name: 653, 2383; the others have
// names (365 since fragment 191, 374 since unit 88's GetCargos, 502 unit 31's, 1279 unit 150's, 576 unit 165's).
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

// CMenuVisualizarCandidatos::StartState: fn 11881 (2561 B), records cmenuvisualizarcandidatos.cpp:55, callees with no
// name: 653, 1693, 1763, 3675, 3861 (202, 203, 455, 502, 576 and 1279 have names).
void CMenuVisualizarCandidatos::StartState()
{
    __builtin_trap();
}

// CReimprimindoResumoZeresima::StartState: fn 11855 (1305 B), records creimprimindoresumozeresima.cpp:60, callees with
// no name: 185, 187, 261, 491, 1127, 6587 (1487 and 1488 are unit 168's).
void CReimprimindoResumoZeresima::StartState()
{
    __builtin_trap();
}

// CQuerReimprimirZeresima::ProcessInput: fn 11848 (349 B), callee with no name: 2882 (2520 is vota::RegistraMesarios,
// unit 168).
void CQuerReimprimirZeresima::ProcessInput()
{
    __builtin_trap();
}

// CFimAquisicaoVotos::StartState: fn 10737 (79 B), callees with no name: 316, 3610 (501 is named: unit 174; 2520 is
// vota::RegistraMesarios, unit 168).
void CFimAquisicaoVotos::StartState()
{
    __builtin_trap();
}

// CCancelaHabilitacaoEleitor::StartState: fn 10646 (40 B), callee with no name: 652 (599 and 1687 are unit 50's).
void CCancelaHabilitacaoEleitor::StartState()
{
    __builtin_trap();
}

// CProcuraEleitor::StartState: fn 10631 (657 B), callees with no name: 3625, 4578, 5424 (named: unit 98's 654, unit
// 152's 3624, unit 174's 1688, unit 178's 2798, unit 110's 326 and 2264, unit 50's 1535).
void CProcuraEleitor::StartState()
{
    __builtin_trap();
}

} // namespace vota

namespace comum {

// CPedeTituloMesario::StartState: fn 10388 (4789 B), records cpedetitulomesario.cpp:33,
// cpedetitulomesariofinal.cpp:45, cpedetitulomesarioinicial.cpp:44, cpedetitulomesariovotacao.cpp:44, callees with no
// name: 180, 203, 301, 728, 1151.
void CPedeTituloMesario::StartState()
{
    __builtin_trap();
}

} // namespace comum

namespace vota {

// CSincronismoOperador::ProcessKey: fn 10209 (120 B), callees with no name: 509, 652, 697, 1901, 5341, 5393.
void CSincronismoOperador::ProcessKey(uebyte)
{
    __builtin_trap();
}

} // namespace vota
