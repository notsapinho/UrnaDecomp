#pragma once

#include "app/comum/validamidia/ivalidamidia.h"

// comum::impl::CValidaMidia (RTTI: si_class of comum::impl::IValidaMidia; vtable @1577024 [174, 144, 11173, 11172, 11171,
// 11170, 11169, 11168, 11167, 11166], ledger/vtables.json), the implementation IValidaMidia::GetInst (fn 5575, record
// cvalidamidia.cpp:182) builds: it allocates 4 bytes and stores this vptr, so the class has no data member. Slots 0 and 1
// are binaryen's shared bodies 174 and 144, a destructor that destroys nothing: left implicit. No record names this
// header; its path is chosen, beside cvalidamidia.cpp, and so is declaring the class in a header rather than in that
// .cpp (the units' pending object needs it). Slot 2 calls slot 3 through the vtable, which reads as a class that is not
// final (clang calls a final class's own member directly).
// Out of line in cvalidamidia.cpp: EhValida (fn 11173), the key function, with which the vtable and the typeinfos
// (@1577072, then IValidaMidia's @1577084) are emitted; the other slots are not written
// (src/units/179-uenux2-cvalidamidia-pending.cpp holds them).

namespace comum::impl {

class CValidaMidia : public IValidaMidia {
public:
    bool EhValida(EAplicativosDeUrna aplicativo, EUrnaTurno turno) override;
    SResultadoValidacao Valida(EAplicativosDeUrna aplicativo, EUrnaTurno turno) override;
    int Slot4() override;
    int Slot5(int, int, int, int, int, int) override;
    int Slot6() override;
    int Slot7(int) override;
    int Slot8() override;
    void Slot9() override;
};

} // namespace comum::impl
