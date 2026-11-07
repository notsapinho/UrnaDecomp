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
// Read since: the caller builds the CWait before the message's prologue (a by-value argument) and the message calls its
// Wait (fn 5446) last; the message's 35-point font (@520148) lies in api/gui/capplication.cpp's run of the data, after
// InitApplication's local class's typeinfo name (@519992), and CPreShowNothing<IScreen>'s vtable (@1577920) right after
// cformbuilder.cpp's records (@1577840 to @1577872): readings that put the message in capplication.cpp and the GetForm
// in cformbuilder.cpp. On CONFIRMA, when comum::CCandidaturas::Busca (fn 1273, on fn 521's singleton) finds the number
// for CVisualizarCandidatos::GetCargo's post, it stores the number into vota::CVisualizarCandidatos' optional at +28
// (its flag at +32), a private member no member of that class's header sets yet. The slot reads as stack colouring; of
// eight forms compiled at src/api's flags and compared by object, the target's slots (the AddTextField result sharing
// the SPoint (639, 310)'s, the form apart) came only with that result a named local, which then lives to the end where
// the target releases it right after the call; in a block, an if's init-statement or a helper clang inlines, the form
// shares their slot too, and discarded, the SPoint shares the form's.
void CMenuFiltrarCandidatosPorNumero::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
