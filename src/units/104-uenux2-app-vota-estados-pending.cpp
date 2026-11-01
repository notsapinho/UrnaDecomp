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
// with no name: 378, 491, 502, 620, 886, 1164, 1269, 1933, 1935, 2281, 2543, 2763, 2821, 2822, 2824, 2860, 3782,
// 3825, 3826, 5462, 5480, 5545, 5866, 5869, 5870 and 6174; its other callees have names (units 193's 675 and 676,
// 195's 5824 and 95's 3829, 5889, 5891 and 5905 among them).
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
// 407, 455, 491, 903, 1127, 2890, 4556, 4557, 4563, 4582, 5987 (2888 and 3701 are named: units 37 and 93).
void CEmitirMaisBU::ProcessInput()
{
    __builtin_trap();
}

// CImprimindoBim::StartState: fn 12071 (1074 B), records cimprimindobim.cpp:50, cimprimindobim.cpp:51,
// cimprimindobim.cpp:66, callees with no name: 185, 187, 261, 401, 463, 1127, 1487, 1488, 2291.
void CImprimindoBim::StartState()
{
    __builtin_trap();
}

// CImprimirBUOutrasObrigatorias::StartState: fn 12065 (1790 B), records cimprimirbuoutrasobrigatorias.cpp:50,
// cimprimirbuoutrasobrigatorias.cpp:53, cimprimirbuoutrasobrigatorias.cpp:57, callees with no name: 185, 187, 202,
// 203, 261, 407, 463, 491, 502, 886, 1127, 1191, 1880, 2244, 2291, 2890, 5918 (3701 is named: unit 93).
void CImprimirBUOutrasObrigatorias::StartState()
{
    __builtin_trap();
}

// CImprimindoZeresima::StartState: fn 11991 (2577 B), records cimprimindozeresima.cpp:104, cimprimindozeresima.cpp:77,
// callees with no name: 185, 187, 261, 491, 1127, 1487, 1488, 2882, 6587.
void CImprimindoZeresima::StartState()
{
    __builtin_trap();
}

// CInicioZeresima::StartState: fn 11924 (41 B), callees with no name: 185, 261, 491, 697 (unit 169's: 5957, 5959).
void CInicioZeresima::StartState()
{
    __builtin_trap();
}

// CReinicioComparecimentoMesario::StartState: fn 11917 (9 B), callees with no name: 6058.
void CReinicioComparecimentoMesario::StartState()
{
    __builtin_trap();
}

// CMaisInformacoes::StartState: fn 11897 (182 B), callee with no name: 6599.
void CMaisInformacoes::StartState()
{
    __builtin_trap();
}

// CMenuFiltrarCandidatosPorNumero::StartState: fn 11892 (1721 B), callees with no name: 187, 202, 203, 242, 267, 365,
// 374, 502, 653, 861, 2383, 5951 (and unit 150's 1279; 576 has one since unit 165).
void CMenuFiltrarCandidatosPorNumero::StartState()
{
    __builtin_trap();
}

// CMenuFiltrarCandidatosPorNumero::ProcessInput: fn 11891 (999 B), callees with no name: 202, 203, 455, 521, 1401,
// 2245, 5446, 5550, 5951 (and units 89's 1273 and 150's 1279).
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
// no name: 185, 187, 261, 491, 1127, 1487, 1488, 6587.
void CReimprimindoResumoZeresima::StartState()
{
    __builtin_trap();
}

// CReimprimindoZeresima::StartState: fn 11852 (1153 B), records creimprimindozeresima.cpp:51, callees with no name:
// 187, 1127, 1487, 1488.
void CReimprimindoZeresima::StartState()
{
    __builtin_trap();
}

// CQuerReimprimirZeresima::StartState: fn 11849 (250 B), records cquerreimprimirzeresima.cpp:45, callees 555 and 1269
// with no name, 2282 and 5882 (comum::IEventosLog::logaErro and LogaMesarioIndagadoImprimirZeresima, unit 111).
void CQuerReimprimirZeresima::StartState()
{
    __builtin_trap();
}

// CQuerReimprimirZeresima::ProcessInput: fn 11848 (349 B), callees with no name: 2520, 2882.
void CQuerReimprimirZeresima::ProcessInput()
{
    __builtin_trap();
}

// CFimAquisicaoVotos::StartState: fn 10737 (79 B), callees with no name: 316, 2520, 3610 (501 is named: unit 174).
void CFimAquisicaoVotos::StartState()
{
    __builtin_trap();
}

// CCancelaHabilitacaoEleitor::StartState: fn 10646 (40 B), callee with no name: 652 (599 and 1687 are unit 50's).
void CCancelaHabilitacaoEleitor::StartState()
{
    __builtin_trap();
}

// CProcuraEleitor::StartState: fn 10631 (657 B), callees with no name: 654, 3625, 4578, 5424 (named: unit 152's 3624,
// unit 174's 1688, unit 178's 2798, unit 110's 326 and 2264, unit 50's 1535).
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

// CSincronismoOperador::StartState: fn 10210 (334 B), callees with no name: 185, 261, 291, 316, 326, 656, 1271 (501 is
// named: unit 174).
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
