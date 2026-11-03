// Pending members of the classes of src/units/282-uenux2-confirmaidentidade-estados.mk, each reached only through its
// vtable. The classes' vtables are emitted in their own .cpp and need every slot defined; these bodies are NOT the
// target's, they trap. Move each into its class's .cpp when it is reconstructed, and delete this file with the last.
//
// What each waits for is a callee with no name on this tree (ledger/callgraph.tsv against splat/matched.txt and
// splat/symbol_addrs.txt):
// - vota::CDigitalReconhecida::ProcessInput (target fn 10481, slot 7, 926 B): it calls fn 3266 (217 B), which no line
//   of splat/symbol_addrs.txt names, and fn 2499 (a __tree::destroy our link pairs with another map's, differs).
// - vota::CDigitalNaoReconhecida::StartState (target fn 10474, slot 2, record cdigitalnaoreconhecida.cpp:82, whose line
//   stays blank): fns 781, 1256, 1393 and 1823. It holds vota::CDigitalNaoReconhecidaDecBiometria's GetInst and
//   constructor inlined (the one store of that vptr, 1591736).
// - vota::CDigitalNaoReconhecidaDecBiometria::StartState (target fn 10478, slot 2): fns 781, 1393 and 1823.
// - vota::CDigitalNaoReconhecidaPorTempo::StartState (target fn 10486, slot 2): fn 1256
//   (vota::CControlaReconhecimento::GetInst, not written).
// - vota::CPedeDigital::ProcessTick (target fn 10465, slot 8, 4463 B, records cpededigital.cpp:162 to 164, whose lines
//   stay blank; it holds VerificaDigital and VerificaDigitalTreinamento inlined, records 262 and 279): it calls fns 395
//   and 1681 (matched: unit 31, src/app/roots_vector.cpp), 816 and 1686 (matched: unit 135), 5397 (written:
//   cpededigital.cpp) and fns 781, 1393, 1823, 1903, 2223, 2224, 2742, 3615, 3719 and 6269, which have no name on this
//   tree. It holds vota::CDigitalNaoReconhecidaPorTempo's GetInst and constructor inlined (the one store of that vptr,
//   1591576).
#include "app/vota/operador/confirmaidentidade/cdigitalnaoreconhecida.h"
#include "app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidadecbiometria.h"
#include "app/vota/operador/confirmaidentidade/cdigitalnaoreconhecidaportempo.h"
#include "app/vota/operador/confirmaidentidade/cdigitalreconhecida.h"
#include "app/vota/operador/confirmaidentidade/cpededigital.h"

namespace vota {

void CDigitalReconhecida::ProcessInput()
{
    __builtin_trap();
}

void CDigitalNaoReconhecida::StartState()
{
    __builtin_trap();
}

void CDigitalNaoReconhecidaDecBiometria::StartState()
{
    __builtin_trap();
}

void CDigitalNaoReconhecidaPorTempo::StartState()
{
    __builtin_trap();
}

void CPedeDigital::ProcessTick(uebyte)
{
    __builtin_trap();
}

} // namespace vota
