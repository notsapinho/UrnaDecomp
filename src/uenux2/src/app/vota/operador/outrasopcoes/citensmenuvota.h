#pragma once

#include "app/comum/informacao/citemmenu.h"
#include "app/comum/informacao/cmenubase.h"

namespace vota {

// The items of vota's "Mais informacoes" menu (RTTI; fn 6599 builds them, each as a
// std::shared_ptr<comum::CItemMenu>(new X)). Recovered: the heads and slot 3. Each class is final: the control block's
// __on_zero_shared (fn 2932, one body for the four below) holds the destructor inlined instead of the call through the
// vtable (fn 172) a class open to derivation gives (docs/reference/facts/reading.md R4). Their vtables are [2937, 2939,
// <the comum class's slot 2>, <own>]: each inherits slot 2 and fills the pure slot 3 (fns 12267, 12266, 12259, 12255),
// defined in citensmenuvota.cpp, the item's count of copies printed (CEstadoGeralVota's CNumViasImpressasRelatorios,
// through the const CAppInfo::GetVota, fn 903). Its result is 32 bits and unsigned: comum's four Slot2 compare it with
// lt_u, and with it comum::CItemImprimeListaEleitores::Slot2 (fn 11668) gives the target's rows (local count, lt_u);
// with uebyte and the count unsigned int it keeps the count on the stack and compares gt_u (score 7 over 55 rows, 2
// deleted; the other three Slot2 still match), and with uebyte and an int count gt_s. unsigned int is chosen. Fn 2939,
// the four classes' D0, is the implicit destructor's (CItemMenu's inline D2 and a free), a thunk into binaryen's fn
// 1969 in both links. Each constructor passes the count of copies its caller reads to the comum class's constructor of
// one argument, and is defined in the class: vota::CMenuMaisInformacoesVota's constructor
// (cmenumaisinformacoesvota.cpp) holds it, with this class's vptr stored after the comum constructor's frame
// (app/comum/informacao/citemmenu.h has the evidence); the parameter's type and name are chosen. The path is chosen: no
// record names it. The target's use band 1 runs these classes' slot 3, the fifth item's D0 and slot 2 (12267 to 12244)
// between the members of CriaTelaVisualizacaoCandidato's lambda and the control blocks fn 6599 builds, and the data
// hold their vtables in the same run (@1539636 to @1539780, after that lambda's @1539548, before the menu's and the
// blocks'). This file's object links in unit 102's list all the same: compiled after ctelasvota.cpp.o, it inverted 34
// pairs of objects and gained nothing (src/units/102-uenux2-control-blocks.mk has the measurement); the menu
// constructor's file links there. Its path, unit 102's choice, stays.
class CItemImprimeEstadoUrnaVota final : public comum::CItemImprimeEstadoUrna {
public:
    explicit CItemImprimeEstadoUrnaVota(uebyte numViasImpressas)
        : comum::CItemImprimeEstadoUrna(numViasImpressas)
    {
    }

    unsigned int Slot3() override;
};

class CItemImprimeListaEleitoresVota final : public comum::CItemImprimeListaEleitores {
public:
    explicit CItemImprimeListaEleitoresVota(uebyte numViasImpressas)
        : comum::CItemImprimeListaEleitores(numViasImpressas)
    {
    }

    unsigned int Slot3() override;
};

class CItemVersoesPacotesVota final : public comum::CItemVersoesPacotes {
public:
    explicit CItemVersoesPacotesVota(uebyte numViasImpressas)
        : comum::CItemVersoesPacotes(numViasImpressas)
    {
    }

    unsigned int Slot3() override;
};

class CItemParametrosUrnaVota final : public comum::CItemParametrosUrna {
public:
    explicit CItemParametrosUrnaVota(uebyte numViasImpressas)
        : comum::CItemParametrosUrna(numViasImpressas)
    {
    }

    unsigned int Slot3() override;
};

// The fifth item derives from CItemMenu directly. Its D0 (fn 12251) calls the D2 and then frees `this` with a drop
// between them, which an out-of-line destructor gives, and slot 0 holds the base's D2 (fn 2937), since a D2 that adds
// nothing is that body (docs/reference/facts/reading.md R5, 3609 over 1378). The block's __on_zero_shared (fn 12172)
// calls that D2 and frees what it returns, no call through the vtable, so the class is final here too. Its constructor
// is the key 5, "Visualizar candidatos" and the point (100, 255), CItemMenu's inline constructor with no frame of its
// own in 6599 (no call of the class's own either). Slot 2 (fn 12244), in citensmenuvota.cpp, says whether the menu
// offers the item: whether a candidacy of comum::CCandidaturas (fn 521's map) has a post in CCargos::GetMapaCargos'
// copy (fn 2834) whose candidate detail is engaged (the byte at +84 of the md::CCargo, HasDetalheCandidato). The
// target's loop is the find over a range-for (measured: std::any_of with a lambda gives one row more, 5 over 132
// against 4 over 131, pnpm wasm score in the whole link); the name stays the slot's (no record or caller names it).
class CItemVisualizarCandidatosVota final : public comum::CItemMenu {
public:
    CItemVisualizarCandidatosVota()
        : comum::CItemMenu(5, "Visualizar candidatos", api::SPoint(100, 255))
    {
    }

    ~CItemVisualizarCandidatosVota() override;

    bool Slot2() override;
};

// vota::CMenuMaisInformacoesVota (RTTI; vtable @1539812 [12235, 6188, 5913]): it overrides nothing, so its slots are
// comum::CMenuBase's D2 and MontaMenu and a D0 byte-identical to the base's (6188, matched under this class's symbol,
// the twin that links first). Its constructor builds the five items, each as std::shared_ptr<comum::CItemMenu>(new X)
// (the five __shared_ptr_pointer blocks' RTTI), with the counts of copies the vota state holds (fn 261's result, +73 to
// +76), and adds each through AdicionaItem (fn 2285); fn 6599 holds it behind an 80-byte frame of its own, so it is out
// of line, in app/vota/eleitor/comum/cmenumaisinformacoesvota.cpp (whose note says why that TU), and binaryen inlined
// it. The class's header (this one), the constructor's parameter and the item temporaries' form are chosen.
class CMenuMaisInformacoesVota : public comum::CMenuBase {
public:
    explicit CMenuMaisInformacoesVota(api::CFormBuilder& form);
};

} // namespace vota
