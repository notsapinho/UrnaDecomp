// Pending of unit 37: the slots of vota::CMostraQRCodeBU not reconstructed, with trapping bodies so that its vtable
// links. Both call GetQRDSInst (fn 1956, the anonymous-namespace accessor of the vota::IQRCodeBUDS the file builds,
// record cmostraqrcodebu.cpp:31) and CMostraQRCodeBU::AjustaTela (fn 5982, record line 195), which have no body here:
// - StartState (slot 2, target fn 12055, record cmostraqrcodebu.cpp:70), which also calls fns 502, 576, 2243, 3877 and
//   5530;
// - ProcessInput (slot 7, fn 12051, record cmostraqrcodebu.cpp:85), which also calls fn 3877 (CAplicacaoEncerrada's
//   GetInst, whose constructor copies a member of CTelasVota that app/vota/eleitor/comum/ctelasvota.h has no accessor
//   for).
#include "app/vota/eleitor/fimvotacao/cmostraqrcodebu.h"

namespace vota {

void CMostraQRCodeBU::StartState()
{
    __builtin_trap();
}

void CMostraQRCodeBU::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota
