// Pending members of unit 138: the slots the unit's vtables need and no reconstructed source holds yet. Their bodies are
// NOT the target's, they trap. All are reached only through the vtables. What each waits for (a callee "with no name"
// has no line in splat/matched.txt or splat/symbol_addrs.txt):
//
// vota::testeteclado::CBase, in src/uenux2/src/app/vota/eleitor/iniciovotacao/testeteclado/cbase.cpp:
// - ProcessInput 11874 (slot 7), 352 B: fn 455 (CPolySingleton<api::IInputKbd>::instance, with no name) and
//   api::CInteractiveForm's Read() (record cinteractiveform.h:57), which this tree's head of that class lacks; and
//   CTesteTeclado::GetInst (fn 3855), which calls the base's constructor (fn 1285, unit 97's) and is not written.
// vota::testeteclado::CPreZeresima, in cprezeresima.cpp:
// - GetTela 11862 (slot 10): fns 3648, 6580 and 6581, with no name, and api::CDateTime's ConvertFromLocalTime (fn 5476),
//   private in api/util/cdatetime.h.
// - GetEstadoPassouNoTeste 5945 (slot 11, record :56): fn 5881 (comum::IEventosLog::LogaErroEstadoAplicativo, unit 111)
//   and CVerificaHorarioZeresima::GetInst (fn 5947), which calls the base's constructor.
// - GetEstadoSemTeste 11861 (slot 12): fn 3648 and slot 11's body (fn 5945, called directly).
// vota::testeteclado::CRetomada, in cretomada.cpp:
// - GetTela 11831 (slot 10): fns 6580 and 6581.
// - GetEstadoPassouNoTeste 11830 (slot 11): fn 491, with no name.
// vota::CVerificaHorarioZeresima, in src/uenux2/src/app/vota/eleitor/iniciovotacao/cverificahorariozeresima.cpp:
// - StartState 11871 (slot 2, record :64): it throws api::EUeAssertError 3481 through fn 463 with the uenux2 assert
//   macro's text, "Assert (appinfo.GetVota().GetEstadoVota() == EAVAGUARDAHORAZERESIMA)", and logs through a
//   vota::CLogVota member binaryen inlines; the assert macro, the EEstadoVota enumerator and CEstadoGeralVota's
//   GetEstadoVota are in this tree now, the codes 3481 and 3482 not (fragment 138 says what else it waits for).
// - ProcessInput 11869 (slot 7), 861 B: fns 455, 491, 5586, 5591 and 6595, with no name, and 5880 (IEventosLog's).
// vota::CReinicioVotacao, in src/uenux2/src/app/vota/eleitor/iniciovotacao/creiniciovotacao.cpp:
// - StartState 11835 (slot 2), 712 B: fns 183, 436, 1269, 1391 and 5940, with no name; 5957 and 412 have names since.
//
// Move each into its class's .cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/iniciovotacao/cverificahorariozeresima.h"
#include "app/vota/eleitor/iniciovotacao/creiniciovotacao.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cesperaretestar.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cprezeresima.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cretomada.h"

namespace vota {

void CVerificaHorarioZeresima::StartState()
{
    __builtin_trap();
}

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

comum::CAppState* CPreZeresima::GetEstadoPassouNoTeste()
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
