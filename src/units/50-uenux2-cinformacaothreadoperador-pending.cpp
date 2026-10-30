// Pending members: the vota::impl::CInformacaoThreadOperador members
// src/uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.cpp does not hold yet. The class's vtable is emitted
// with Slot2, its key function (the destructor is implicit), and needs every member defined; their bodies are NOT the
// target's, they trap. Defined in slot order, as the target's function order has them. With the vtable this object
// also emits the implicit destructors (target fns 10552 and 10551, slots 0 and 1), the compiler's code for the class
// definition in cinformacaothreadoperador.h; they move to cinformacaothreadoperador.o with the vtable, when Slot2 does.
// Target functions, by vtable slot (vtable @1590108; ledger/vtables.json), and what each waits for. No record, symbol
// or string names slots 2 to 22 and 27 to 30: their names are chosen (iinformacaothreadoperador.h), so even the ones
// whose callees are all named wait for evidence of a name.
//   2  10581  clears +88 (8 B), +8 and +4; no callee
//   3  10580  +4, else asks comum::CEleitores::GetInst() (fn 326) and CDataMap<...>::GetCurrent (fn 656), both unnamed
//   4  2683   returns +4; a binaryen twin already matched as rtreeEof
//   5  10579  the same question as slot 3 without +4 (fns 326, 656, unnamed)
//   6  2683   as slot 4
//   7  10578  sets +4; no callee
//   8  10577  returns "\xC1UDIO ATIVADO" or " " by +4; calls operator new (fn 137) only
//   9  10576, 10  10574, 11  10573  test +8 for 2, 1, 0; no callee
//   12 10572, 13  10571  set +8 to 2, 1; no callee
//   14 10570  sets +8 to 0; a twin already matched as CInOutTempBuffer::InitWriting
//   15 2587   returns +8; a twin already matched as HTS_ModelSet_get_fperiod
//   16 10569  formats "Local {:04}"; calls fns 697, 555, 1269, 326 and the std::format machinery, unnamed
//   17 10568  sets +12 from fn 5412, unnamed
//   18 10567  returns +12; no callee
//   19 10566  compares api::CDateTime values; inlines CEstadoGeralVota::GetDtHrUltimoVoto (record
//             cestadogeralvota.h:131, where its stub was) and calls fns 1485, 479, 187, 759, 903, 2233, 170, unnamed
//   20 10565  resets the four optionals; calls free (fn 136) only
//   21 10564, 22  10563  set +24 and +40, then call fn 2225, unnamed
//   23 10562  GetIdentidadeDigitada (record :474:15), 24 10561 GetTipoIdentidadeDigitada (:484:15),
//   25 10560  GetIdentidadeEleitor (:494:15), 26 10559 GetIdentidadePrincipalEleitor (:504:15): each throws through
//             fn 253, the CBaseError constructor thunk, unnamed
//   27 10558, 28  10557, 29  10556  set +88 and +92; no callee
//   30 10554  returns a CApresentacaoFotoEleitor built from +88 and +92 (fn 1081, matched)
// Move each into cinformacaothreadoperador.cpp when it is reconstructed; delete this file with the last one.
#include "app/vota/operador/comum/cinformacaothreadoperador.h"

namespace vota::impl {

void CInformacaoThreadOperador::Slot2()
{
    __builtin_trap();
}

bool CInformacaoThreadOperador::Slot3() const
{
    __builtin_trap();
}

bool CInformacaoThreadOperador::Slot4() const
{
    __builtin_trap();
}

bool CInformacaoThreadOperador::Slot5() const
{
    __builtin_trap();
}

bool CInformacaoThreadOperador::Slot6() const
{
    __builtin_trap();
}

void CInformacaoThreadOperador::Slot7(bool)
{
    __builtin_trap();
}

std::string CInformacaoThreadOperador::Slot8() const
{
    __builtin_trap();
}

bool CInformacaoThreadOperador::Slot9() const
{
    __builtin_trap();
}

bool CInformacaoThreadOperador::Slot10() const
{
    __builtin_trap();
}

bool CInformacaoThreadOperador::Slot11() const
{
    __builtin_trap();
}

void CInformacaoThreadOperador::Slot12()
{
    __builtin_trap();
}

void CInformacaoThreadOperador::Slot13()
{
    __builtin_trap();
}

void CInformacaoThreadOperador::Slot14()
{
    __builtin_trap();
}

IInformacaoThreadOperador::EEstado CInformacaoThreadOperador::Slot15() const
{
    __builtin_trap();
}

std::string CInformacaoThreadOperador::Slot16() const
{
    __builtin_trap();
}

void CInformacaoThreadOperador::Slot17()
{
    __builtin_trap();
}

api::CDateTime CInformacaoThreadOperador::Slot18() const
{
    __builtin_trap();
}

bool CInformacaoThreadOperador::Slot19() const
{
    __builtin_trap();
}

void CInformacaoThreadOperador::Slot20()
{
    __builtin_trap();
}

void CInformacaoThreadOperador::Slot21(const std::string&)
{
    __builtin_trap();
}

void CInformacaoThreadOperador::Slot22(ecourna::app::dados::ETipoIdentificadorEleitor)
{
    __builtin_trap();
}

std::string CInformacaoThreadOperador::GetIdentidadeDigitada() const
{
    __builtin_trap();
}

ecourna::app::dados::ETipoIdentificadorEleitor CInformacaoThreadOperador::GetTipoIdentidadeDigitada() const
{
    __builtin_trap();
}

comum::md::CEleitorIdentidade CInformacaoThreadOperador::GetIdentidadeEleitor() const
{
    __builtin_trap();
}

comum::md::CEleitorIdentidade CInformacaoThreadOperador::GetIdentidadePrincipalEleitor() const
{
    __builtin_trap();
}

void CInformacaoThreadOperador::Slot27()
{
    __builtin_trap();
}

void CInformacaoThreadOperador::Slot28()
{
    __builtin_trap();
}

void CInformacaoThreadOperador::Slot29(ecourna::app::dados::CApresentacaoFotoEleitor::EResultado)
{
    __builtin_trap();
}

ecourna::app::dados::CApresentacaoFotoEleitor CInformacaoThreadOperador::Slot30() const
{
    __builtin_trap();
}

} // namespace vota::impl
