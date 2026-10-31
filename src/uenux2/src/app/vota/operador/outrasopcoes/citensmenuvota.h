#pragma once

#include "app/comum/informacao/citemmenu.h"

namespace vota {

// The items of vota's "Mais informacoes" menu (RTTI; fn 6599 builds them, each as a
// std::shared_ptr<comum::CItemMenu>(new X)). Recovered: the heads only. Each class is final: the control block's
// __on_zero_shared (fn 2932, one body for the four below) holds the destructor inlined instead of the call through the
// vtable (fn 172) a class open to derivation gives (docs/reference/facts/reading.md R4). Slot 2 is declared so that the
// class is concrete; slot 3 and the constructors are not reconstructed. The path is chosen: no record names it.
class CItemImprimeEstadoUrnaVota final : public comum::CItemImprimeEstadoUrna {
public:
    void Slot2() override;
};

class CItemImprimeListaEleitoresVota final : public comum::CItemImprimeListaEleitores {
public:
    void Slot2() override;
};

class CItemVersoesPacotesVota final : public comum::CItemVersoesPacotes {
public:
    void Slot2() override;
};

class CItemParametrosUrnaVota final : public comum::CItemParametrosUrna {
public:
    void Slot2() override;
};

// The fifth item derives from CItemMenu directly. Its D0 (fn 12251) calls the D2 and then frees `this` with a drop
// between them, which an out-of-line destructor gives, and slot 0 holds the base's D2 (fn 2937), since a D2 that adds
// nothing is that body (docs/reference/facts/reading.md R5, 3609 over 1378). The block's __on_zero_shared (fn 12172)
// calls that D2 and frees what it returns, no call through the vtable, so the class is final here too. Slot 2 (fn 12244)
// is pending. fn 6599 stores more at +20 and +24 of this object, nothing the destructor reads, so those members are not
// declared.
class CItemVisualizarCandidatosVota final : public comum::CItemMenu {
public:
    ~CItemVisualizarCandidatosVota() override;

    void Slot2() override;
};

} // namespace vota
