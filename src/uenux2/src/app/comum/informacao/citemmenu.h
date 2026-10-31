#pragma once

#include <string>

namespace comum {

// comum::CItemMenu, an item of a comum::CMenuBase, and the four items comum defines over it (RTTI). Recovered: the
// head, as far as the destructor. The vtable (@1539884) is [2937, 325, 12143]: an abstract class with one pure slot
// (slot 2, not recovered, named after its slot). Its D2 (fn 2937, a merge thunk over fn 1727) stores the vptr and frees
// a std::string at +8, so the destructor is inline here; the +4 word is not read by any body read, and its type and
// every name are chosen. fn 6599 builds the items and stores more at +20 and +24 of the one it builds in place. The
// path is chosen beside cmenubase.h: no record names it.
class CItemMenu {
public:
    virtual ~CItemMenu() = default;

    virtual void Slot2() = 0;

private:
    int m_slot4;
    std::string m_texto;
};

class CItemImprimeEstadoUrna : public CItemMenu {};

class CItemImprimeListaEleitores : public CItemMenu {};

class CItemParametrosUrna : public CItemMenu {};

class CItemVersoesPacotes : public CItemMenu {};

} // namespace comum
