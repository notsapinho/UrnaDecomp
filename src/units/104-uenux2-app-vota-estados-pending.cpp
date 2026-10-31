// Pending members of the state singletons (src/units/104-uenux2-app-vota-estados.mk): the vtable slots of those states
// that are not reconstructed, one trap each, so that the classes link and GetInst can be measured. The object compiles
// with the unit's flags. StartState is the key function of the classes that do not write it or an out-of-line
// destructor, so for them this object emits the vtable, the typeinfo and the deleting destructor, with no change when
// the member lands (src/units/README.md "Pending members"). A member's stub goes with its vtable in the link, so the note
// over each says what it waits for and the records it holds in the file of its class, whose lines stay blank there.
// vota::CQuerReimprimirZeresima is the exception: nothing in our link stores its vptr, so wasm-ld drops the vtable and
// its two traps, and its StartState keeps its stub until its GetInst is written.

#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/eleitor/ciniciodeciclo.h"
#include "app/vota/eleitor/fimvotacao/cgravaresultado.h"
#include "app/vota/eleitor/fimvotacao/cemitirmaisbu.h"
#include "app/vota/eleitor/fimvotacao/cimprimindobim.h"
#include "app/vota/eleitor/fimvotacao/cimprimirbuoutrasobrigatorias.h"
#include "app/vota/eleitor/fimvotacao/ciniciobu.h"
#include "app/vota/eleitor/iniciovotacao/cimprimindozeresima.h"
#include "app/vota/eleitor/iniciovotacao/ciniciozeresima.h"
#include "app/vota/eleitor/iniciovotacao/creiniciocomparecimentomesario.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenuvisualizarcandidatos.h"
#include "app/vota/eleitor/cdefinerotaposreinicio.h"
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

// CAguardaMensagem::ProcessKey: fn 7481 (742 B), callees with no name: 185, 261, 407, 491, 2376, 3229, 6129, 6557.
void CAguardaMensagem::ProcessKey(uebyte)
{
    __builtin_trap();
}

// CIniciodeCiclo::StartState: fn 7306 (251 B), records ciniciodeciclo.cpp:48, ciniciodeciclo.cpp:61, callees with no
// name: 185, 187, 261, 291, 491, 1823, 2880, 3333, 3705.
void CIniciodeCiclo::StartState()
{
    __builtin_trap();
}

// CGravaResultado::StartState: fn 12098 (26731 B), records cgravaresultado.cpp:63, cgravaresultado.cpp:79, callees
// with no name: 183, 185, 187, 202, 203, 261, 273, 291, 326, 332, 378, 401, 436, 457, 463, 491, 502,
// 509, 555, 600, 602, 620, 624, 631, 640, 675, 676, 886, 1164, 1249, 1269, 1274, 1405, 1485, 1822,
// 1933, 1935, 1960, 2281, 2543, 2763, 2821, 2822, 2824, 2860, 3782, 3784, 3788, 3825, 3826, 3829,
// 3834, 5462, 5480, 5545, 5824, 5856, 5866, 5869, 5870, 5876, 5887, 5888, 5889, 5891, 5899, 5905,
// 6174.
void CGravaResultado::StartState()
{
    __builtin_trap();
}

// CEmitirMaisBU::StartState: fn 12082 (250 B), records cemitirmaisbu.cpp:46, cemitirmaisbu.cpp:47, callees with no
// name: 185, 407, 463, 903, 4563.
void CEmitirMaisBU::StartState()
{
    __builtin_trap();
}

// CEmitirMaisBU::ProcessInput: fn 12081 (1543 B), records cemitirmaisbu.cpp:64, callees with no name: 185, 261,
// 407, 455, 491, 903, 1127, 2888, 2890, 3701, 4556, 4557, 4563, 4582, 5987.
void CEmitirMaisBU::ProcessInput()
{
    __builtin_trap();
}

// CImprimindoBim::StartState: fn 12071 (1074 B), records cimprimindobim.cpp:50, cimprimindobim.cpp:51,
// cimprimindobim.cpp:66, callees with no name: 183, 185, 187, 261, 401, 436, 463, 1127, 1487, 1488, 2291.
void CImprimindoBim::StartState()
{
    __builtin_trap();
}

// CImprimirBUOutrasObrigatorias::StartState: fn 12065 (1790 B), records cimprimirbuoutrasobrigatorias.cpp:50,
// cimprimirbuoutrasobrigatorias.cpp:53, cimprimirbuoutrasobrigatorias.cpp:57, callees with no name: 185, 187, 202,
// 203, 261, 407, 463, 491, 502, 886, 1127, 1191, 1880, 2244, 2291, 2890, 3701, 5918.
void CImprimirBUOutrasObrigatorias::StartState()
{
    __builtin_trap();
}

// CInicioBU::StartState: fn 12062 (189 B): it holds vota::CQuerImprimirBU's GetInst inlined, whose constructor copies a
// member of CTelasVota (+236) that app/vota/eleitor/comum/ctelasvota.h has no accessor for.
void CInicioBU::StartState()
{
    __builtin_trap();
}

// CImprimindoZeresima::StartState: fn 11991 (2577 B), records cimprimindozeresima.cpp:104, cimprimindozeresima.cpp:77,
// callees with no name: 183, 185, 187, 261, 436, 491, 1127, 1487, 1488, 2882, 6587.
void CImprimindoZeresima::StartState()
{
    __builtin_trap();
}

// CInicioZeresima::StartState: fn 11924 (41 B), callees with no name: 185, 261, 491, 697, 5957, 5959.
void CInicioZeresima::StartState()
{
    __builtin_trap();
}

// CReinicioComparecimentoMesario::StartState: fn 11917 (9 B), callees with no name: 6058.
void CReinicioComparecimentoMesario::StartState()
{
    __builtin_trap();
}

// CMaisInformacoes::StartState: fn 11897 (182 B), callees with no name: 407, 6599.
void CMaisInformacoes::StartState()
{
    __builtin_trap();
}

// CMaisInformacoes::ProcessInput: fn 11896 (717 B), callees with no name: 455.
void CMaisInformacoes::ProcessInput()
{
    __builtin_trap();
}

// CMenuFiltrarCandidatosPorNumero::StartState: fn 11892 (1721 B), callees with no name: 187, 202, 203, 242, 267, 365,
// 374, 502, 576, 653, 861, 1279, 2383, 5951.
void CMenuFiltrarCandidatosPorNumero::StartState()
{
    __builtin_trap();
}

// CMenuFiltrarCandidatosPorNumero::ProcessInput: fn 11891 (999 B), callees with no name: 202, 203, 455, 521, 1273,
// 1279, 1401, 2245, 5446, 5550, 5951.
void CMenuFiltrarCandidatosPorNumero::ProcessInput()
{
    __builtin_trap();
}

// CMenuVisualizarCandidatos::StartState: fn 11881 (2561 B), records cmenuvisualizarcandidatos.cpp:55, callees with no
// name: 202, 203, 455, 502, 576, 653, 1279, 1693, 1763, 3675, 3861.
void CMenuVisualizarCandidatos::StartState()
{
    __builtin_trap();
}

// CDefineRotaPosReinicio::NeedChangeState: fn 11858 (562 B), records cdefinerotaposreinicio.cpp:81, callees with no
// name: 185, 261, 2520, 2880, 3279.
bool CDefineRotaPosReinicio::NeedChangeState()
{
    __builtin_trap();
}

// CReimprimindoResumoZeresima::StartState: fn 11855 (1305 B), records creimprimindoresumozeresima.cpp:60, callees with
// no name: 183, 185, 187, 261, 436, 491, 1127, 1487, 1488, 6587.
void CReimprimindoResumoZeresima::StartState()
{
    __builtin_trap();
}

// CReimprimindoZeresima::StartState: fn 11852 (1153 B), records creimprimindozeresima.cpp:51, callees with no name:
// 183, 187, 436, 1127, 1487, 1488.
void CReimprimindoZeresima::StartState()
{
    __builtin_trap();
}

// CQuerReimprimirZeresima::StartState: fn 11849 (250 B), records cquerreimprimirzeresima.cpp:45, callees with no name:
// 555, 1269, 2282, 5882.
void CQuerReimprimirZeresima::StartState()
{
    __builtin_trap();
}

// CQuerReimprimirZeresima::ProcessInput: fn 11848 (349 B), callees with no name: 455, 2520, 2880, 2882.
void CQuerReimprimirZeresima::ProcessInput()
{
    __builtin_trap();
}

// CFimAquisicaoVotos::StartState: fn 10737 (79 B), callees with no name: 316, 501, 2520, 3610.
void CFimAquisicaoVotos::StartState()
{
    __builtin_trap();
}

// CCancelaHabilitacaoEleitor::StartState: fn 10646 (40 B), callees with no name: 599, 652, 1687, 4529.
void CCancelaHabilitacaoEleitor::StartState()
{
    __builtin_trap();
}

// CProcuraEleitor::StartState: fn 10631 (657 B), callees with no name: 326, 654, 1535, 1688, 2264, 2798, 3624, 3625,
// 4578, 5424.
void CProcuraEleitor::StartState()
{
    __builtin_trap();
}

} // namespace vota

namespace comum {

// CPedeTituloMesario::StartState: fn 10388 (4789 B), records cpedetitulomesario.cpp:33,
// cpedetitulomesariofinal.cpp:45, cpedetitulomesarioinicial.cpp:44, cpedetitulomesariovotacao.cpp:44, callees with no
// name: 180, 203, 301, 728, 1151, 1255.
void CPedeTituloMesario::StartState()
{
    __builtin_trap();
}

} // namespace comum

namespace vota {

// CFinalizaOperador::StartState: fn 10214 (685 B), callees with no name: 180, 435, 1694.
void CFinalizaOperador::StartState()
{
    __builtin_trap();
}

// CSincronismoOperador::StartState: fn 10210 (334 B), callees with no name: 185, 261, 291, 316, 326, 501, 656, 1271.
void CSincronismoOperador::StartState()
{
    __builtin_trap();
}

// CSincronismoOperador::ProcessKey: fn 10209 (120 B), callees with no name: 509, 652, 697, 1901, 5341, 5393.
void CSincronismoOperador::ProcessKey(uebyte)
{
    __builtin_trap();
}

} // namespace vota
