// Pending members of unit 138: the slots the unit's vtables need and no reconstructed source holds yet. Their bodies are
// NOT the target's, they trap. All are reached only through the vtables. What each waits for (a callee "with no name"
// has no line in splat/matched.txt or splat/symbol_addrs.txt):
//
// vota::testeteclado::CPreZeresima, in src/uenux2/src/app/vota/eleitor/iniciovotacao/testeteclado/cprezeresima.cpp:
// - GetTela 11862 (slot 10): fns 6580 and 6581, with no name (3648, CDate::operator-, matches), and api::CDateTime's
//   ConvertFromLocalTime (fn 5476),
//   private in api/util/cdatetime.h.
// vota::testeteclado::CRetomada, in cretomada.cpp:
// - GetTela 11831 (slot 10): fns 6580 and 6581.
// - GetEstadoPassouNoTeste 11830 (slot 11): fn 491, with no name.
// vota::CVerificaHorarioZeresima, in src/uenux2/src/app/vota/eleitor/iniciovotacao/cverificahorariozeresima.cpp:
// - ProcessInput 11869 (slot 7), 861 B: fns 455, 491, 5586, 5591 and 6595, with no name, and 5880 (IEventosLog's).
//
// Move each into its class's .cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/eleitor/iniciovotacao/cverificahorariozeresima.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cesperaretestar.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cprezeresima.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cretomada.h"

namespace vota {

void CVerificaHorarioZeresima::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota

namespace vota::testeteclado {

CFormInterativoTelaVota CPreZeresima::GetTela()
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
