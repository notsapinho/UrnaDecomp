// Pending of unit 156: the slots of its states not reconstructed, with trapping bodies so that the vtables link.
// - vota::CImprimindoBU::StartState (slot 2, target fn 12078, records cimprimindobu.cpp:70 and 71): it calls fns 1127
//   and 4551 and CImprimindoBU::ImprimeBU (fn 2890, records cimprimindobu.cpp:111 and 114), which have no body here.
// - vota::CImprimindoBU::ProcessInput (slot 7, fn 12077): it calls fn 491, which has no body here, and 3701 (unit 93).
// - vota::CLimiteCopiasBUAtingido::StartState (slot 2, target fn 12027, record climitecopiasbuatingido.cpp:37): it
//   calls fn 4556 on CLogVota::GetInst()'s result (fn 184), which has no body here.
// - vota::CMostraQRCodeCertificado::StartState (slot 2, fn 12040, 1932 B): it builds the screen through fns 502, 576,
//   653 and 2782, which have no body here.
// - vota::CQuerImprimirBU::ProcessInput (slot 7, fn 12034): it calls fn 491, which has no body here, and
//   CAplicacaoEncerrada's GetInst (fn 3877), which matches (unit 138; its constructor copies CTelasVota's +36 through
//   ctelasvota.h's GetTelaAplicacaoEncerrada).
// - vota::CRetirarMR::StartState (slot 2, fn 12031, records cretirarmr.cpp:54 to 56): it calls fn 491, which has no
//   body here, and holds CRetirarMR::AguardaRetiradaMR (record cretirarmr.cpp:96) inlined.
#include "app/vota/eleitor/fimvotacao/cimprimindobu.h"
#include "app/vota/eleitor/fimvotacao/climitecopiasbuatingido.h"
#include "app/vota/eleitor/fimvotacao/cmostraqrcodecertificado.h"
#include "app/vota/eleitor/fimvotacao/cquerimprimirbu.h"
#include "app/vota/eleitor/fimvotacao/cretirarmr.h"

namespace vota {

void CImprimindoBU::StartState()
{
    __builtin_trap();
}

void CImprimindoBU::ProcessInput()
{
    __builtin_trap();
}

void CLimiteCopiasBUAtingido::StartState()
{
    __builtin_trap();
}

void CMostraQRCodeCertificado::StartState()
{
    __builtin_trap();
}

void CQuerImprimirBU::ProcessInput()
{
    __builtin_trap();
}

void CRetirarMR::StartState()
{
    __builtin_trap();
}

} // namespace vota
