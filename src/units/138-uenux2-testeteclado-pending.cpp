// Pending members of unit 138: the slots the unit's vtables need and no reconstructed source holds yet. Their bodies are
// NOT the target's, they trap. All are reached only through the vtables. What each waits for (a callee "with no name"
// has no line in splat/matched.txt or splat/symbol_addrs.txt):
//
// vota::testeteclado::CPreZeresima, in src/uenux2/src/app/vota/eleitor/iniciovotacao/testeteclado/cprezeresima.cpp:
// - GetTela 11862 (slot 10): fns 6580 and 6581, with no name (3648, CDate::operator-, matches), and api::CDateTime's
//   ConvertFromLocalTime (fn 5476),
//   private in api/util/cdatetime.h.
// - GetEstadoSemTeste 11861 (slot 12): its callees have names (3648, api::CDate::operator-(int), written in
//   api/util/cdate.cpp, unit 125); it calls slot 11's body (fn 5945, written) directly, with its frame pointer as `this`
//   (the target's rows; that 5945 reads no `this` and so takes any value is a reading), and the source below gives that
//   row. Written at the end of cprezeresima.cpp with app/comum/dados/cconfiguracaoeleicao.h included (and Boost's
//   include path on the object, as cverificahorariozeresima.cpp.o has), it scored 3 over 35 rows, all operand-only, the
//   calls of fns 187, 3648 and 5945 (pnpm wasm score in a whole link where 3648 had no name yet; not measured since):
//     comum::CAppState* CPreZeresima::GetEstadoSemTeste()
//     {
//         const api::CDate dataZeresima = comum::CConfiguracaoEleicao::GetInst().GetDataHoraZeresima().GetData();
//         if (m_dataHora.GetData() < dataZeresima - 1) {
//             return GetEstadoPassouNoTeste();
//         }
//         return this;
//     }
//   The target copies the date's 8 bytes from +544 into its frame before fn 3648, as the local does; a form without the
//   local was not compiled. The local's name is chosen.
// vota::testeteclado::CRetomada, in cretomada.cpp:
// - GetTela 11831 (slot 10): fns 6580 and 6581.
// - GetEstadoPassouNoTeste 11830 (slot 11): fn 491, with no name.
// vota::CVerificaHorarioZeresima, in src/uenux2/src/app/vota/eleitor/iniciovotacao/cverificahorariozeresima.cpp:
// - ProcessInput 11869 (slot 7), 861 B: fns 455, 491, 5586, 5591 and 6595, with no name, and 5880 (IEventosLog's).
// vota::CReinicioVotacao, in src/uenux2/src/app/vota/eleitor/iniciovotacao/creiniciovotacao.cpp:
// - StartState 11835 (slot 2), 712 B: fn 1391, with no name; 1269, 5957, 412, 183 and 436 have names since, and
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
