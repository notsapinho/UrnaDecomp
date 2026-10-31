#pragma once

#include "app/comum/informacao/citemmenu.h"

namespace vota {

// The items of vota's "Mais informacoes" menu (RTTI; fn 6599 builds them, each as a
// std::shared_ptr<comum::CItemMenu>(new X)). Recovered: the heads and slot 3. Each class is final: the control block's
// __on_zero_shared (fn 2932, one body for the four below) holds the destructor inlined instead of the call through the
// vtable (fn 172) a class open to derivation gives (docs/reference/facts/reading.md R4). Their vtables are [2937, 2939,
// <the comum class's slot 2>, <own>]: each inherits slot 2 and fills the pure slot 3 (fns 12267, 12266, 12259, 12255),
// defined in citensmenuvota.cpp, the item's count of copies printed (CEstadoGeralVota's CNumViasImpressasRelatorios,
// through the const CAppInfo::GetVota, fn 903). Its result is unsigned int: comum's four Slot2 compare it with lt_u,
// and with that type comum::CItemImprimeListaEleitores::Slot2 (fn 11668) gives the target's rows (the count in a local,
// lt_u); with uebyte, the count held as unsigned int so that the compare stays unsigned, it keeps the count on the
// stack and compares gt_u (score 7 over 55 rows, 2 deleted), while the other three Slot2 give the target's rows. Fn
// 2939, the four classes' D0, is the implicit destructor's (CItemMenu's inline D2 and a free), a thunk into binaryen's
// fn 1969 in both links. The constructors are not reconstructed. The path is chosen: no record names it.
class CItemImprimeEstadoUrnaVota final : public comum::CItemImprimeEstadoUrna {
public:
    unsigned int Slot3() override;
};

class CItemImprimeListaEleitoresVota final : public comum::CItemImprimeListaEleitores {
public:
    unsigned int Slot3() override;
};

class CItemVersoesPacotesVota final : public comum::CItemVersoesPacotes {
public:
    unsigned int Slot3() override;
};

class CItemParametrosUrnaVota final : public comum::CItemParametrosUrna {
public:
    unsigned int Slot3() override;
};

// The fifth item derives from CItemMenu directly. Its D0 (fn 12251) calls the D2 and then frees `this` with a drop
// between them, which an out-of-line destructor gives, and slot 0 holds the base's D2 (fn 2937), since a D2 that adds
// nothing is that body (docs/reference/facts/reading.md R5, 3609 over 1378). The block's __on_zero_shared (fn 12172)
// calls that D2 and frees what it returns, no call through the vtable, so the class is final here too. Slot 2 (fn
// 12244) is pending. fn 6599 stores more at +20 and +24 of this object, nothing the destructor reads, so those members
// are not declared.
class CItemVisualizarCandidatosVota final : public comum::CItemMenu {
public:
    ~CItemVisualizarCandidatosVota() override;

    bool Slot2() override;
};

} // namespace vota
