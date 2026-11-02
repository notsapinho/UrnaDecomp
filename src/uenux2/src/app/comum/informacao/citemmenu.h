#pragma once

#include <string>

#include "api/gui/primitives.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// comum::CItemMenu, an item of a comum::CMenuBase, and the four items comum defines over it (RTTI). Recovered: the
// heads, as far as the destructor and the slots' shapes. The vtable (@1539884) is [2937, 325, 12143]: an abstract class
// with one pure slot, slot 2. Its D2 (fn 2937, a merge thunk over fn 1727) stores the vptr and frees a std::string at
// +8. That the destructor is inline here is what fn 2932 says, which holds that body inlined in the control block of a
// derived class; the D2 alone would say nothing (docs/reference/facts/reading.md R5). The +4 word is the item's key
// (below), and every name is chosen. fn 6599 builds the items and stores more at +20 and +24 of the one
// it builds in place. The path is chosen beside cmenubase.h: no record names it.
//
// The four comum classes' vtables are [2937, 325, <own>, 12143]: each fills slot 2 (fns 11669, 11668, 11667, 11666,
// defined in citemmenu.cpp) and adds one pure slot, which vota's overriders fill and those bodies call through the
// vtable. Both are named after their slot. Slot 2 is (i32) -> (i32), and those four return an unsigned compare of slot
// 3's result, so bool is read from them. Slot 3's fills (fns 12267, 12266, 12255, 12259) return a byte they load, as a
// 32-bit unsigned result: with uebyte, fn 11668 compares otherwise than the target (app/vota/operador/outrasopcoes/
// citensmenuvota.h has the measurement). unsigned int is the plainest such type, and chosen.
// The +4 word is the item's key: comum::CMenuBase::AdicionaItem (fn 2285) formats it into the menu's string of keys as
// an unsigned (argument type 6 of its std::format) when slot 2 is true. Unsigned is that evidence; `unsigned int`, the
// getter and both names are chosen.
// comum::CMenuBase::MontaMenu (fn 5913) reads the rest: it formats the key and the string at +8 into the item's line
// (argument types 6 and 13, a string), and adds the line at the api::SPoint at +20 in the api::SFont at +24, which it
// copies into its frame for the call (the getters return them by value, a reading of those copies); after the last
// item it reads the point's two words and the font's size in place. The types are api::CFormBuilder::AddTextField's,
// whose parameters they fill; the getters' and members' names are chosen.
class CItemMenu {
public:
    virtual ~CItemMenu() = default;

    virtual bool Slot2() = 0;

    unsigned int GetChave() const { return m_chave; }
    const std::string& GetTexto() const { return m_texto; }
    api::SPoint GetPosicao() const { return m_posicao; }
    api::SFont GetFonte() const { return m_fonte; }

private:
    unsigned int m_chave;
    std::string m_texto;
    api::SPoint m_posicao;
    api::SFont m_fonte;
};

class CItemImprimeEstadoUrna : public CItemMenu {
public:
    bool Slot2() override;
    virtual unsigned int Slot3() = 0;
};

class CItemImprimeListaEleitores : public CItemMenu {
public:
    bool Slot2() override;
    virtual unsigned int Slot3() = 0;
};

class CItemParametrosUrna : public CItemMenu {
public:
    bool Slot2() override;
    virtual unsigned int Slot3() = 0;
};

class CItemVersoesPacotes : public CItemMenu {
public:
    bool Slot2() override;
    virtual unsigned int Slot3() = 0;
};

} // namespace comum
