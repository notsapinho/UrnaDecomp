// Pending members of unit 138: the slots the unit's vtables need and no reconstructed source holds yet. Their bodies are
// NOT the target's, they trap. All are reached only through the vtables. What each waits for (a callee "with no name"
// has no line in splat/matched.txt or splat/symbol_addrs.txt):
//
// vota::testeteclado::CBase, in src/uenux2/src/app/vota/eleitor/iniciovotacao/testeteclado/cbase.cpp:
// - ProcessInput 11874 (slot 7), 352 B: fn 455 (CPolySingleton<api::IInputKbd>::instance, with no name) and
//   api::CInteractiveForm's Read() (record cinteractiveform.h:57), which this tree's head of that class lacks; and
//   CTesteTeclado::GetInst (fn 3855), which calls the base's constructor (fn 1285, unit 97's) and is not written.
// vota::testeteclado::CPreZeresima, in cprezeresima.cpp:
// - GetTela 11862 (slot 10): fns 6580 and 6581, with no name (3648, CDate::operator-, matches), and api::CDateTime's
//   ConvertFromLocalTime (fn 5476),
//   private in api/util/cdatetime.h.
// - GetEstadoSemTeste 11861 (slot 12): its callees have names (3648, CDate::operator-, unit 125); it calls slot 11's
//   body (fn 5945, written) directly.
// vota::testeteclado::CRetomada, in cretomada.cpp:
// - GetTela 11831 (slot 10): fns 6580 and 6581.
// - GetEstadoPassouNoTeste 11830 (slot 11): fn 491, with no name.
// vota::CVerificaHorarioZeresima, in src/uenux2/src/app/vota/eleitor/iniciovotacao/cverificahorariozeresima.cpp:
// - ProcessInput 11869 (slot 7), 861 B: fns 455, 491, 5586, 5591 and 6595, with no name, and 5880 (IEventosLog's).
// vota::CReinicioVotacao, in src/uenux2/src/app/vota/eleitor/iniciovotacao/creiniciovotacao.cpp:
// - StartState 11835 (slot 2), 712 B: fns 1269 and 1391, with no name; 5957, 412, 183 and 436 have names since, and
//   5940 (vota::CQuerReimprimirZeresima::GetInst) is written in unit 104.
//
// Move each into its class's .cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/iniciovotacao/cverificahorariozeresima.h"
#include "app/vota/eleitor/iniciovotacao/creiniciovotacao.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cesperaretestar.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cprezeresima.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cretomada.h"

namespace vota {

void CVerificaHorarioZeresima::ProcessInput()
{
    __builtin_trap();
}

void CReinicioVotacao::StartState()
{
    __builtin_trap();
}

} // namespace vota

namespace vota::testeteclado {

void CBase::ProcessInput()
{
    __builtin_trap();
}

CFormInterativoTelaVota CPreZeresima::GetTela()
{
    __builtin_trap();
}

comum::CAppState* CPreZeresima::GetEstadoSemTeste()
{
    __builtin_trap();
}

CFormInterativoTelaVota CRetomada::GetTela()
{
    __builtin_trap();
}

comum::CAppState* CRetomada::GetEstadoPassouNoTeste()
{
    __builtin_trap();
}

} // namespace vota::testeteclado
