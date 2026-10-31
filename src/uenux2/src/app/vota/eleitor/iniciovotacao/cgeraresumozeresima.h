#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/iniciovotacao/cgeraresumozeresimabase.h"

namespace vota {

// vota::CGeraResumoZeresima (RTTI: si_class of vota::CGeraResumoZeresimaBase; vtable @1544512 [5964, 5963, 11943, 7480,
// 1661, 218, 425, 218, 425, 11940, 11939]): it overrides slots 9 and 10 and adds no data member (the object it is built
// in, by fn 6056, is the base's 20 bytes). Slot 10 (fn 11939) returns vota::CImprimindoZeresima::GetInst() (fn 5973).
// Slot 9 (fn 11940) sets one of comum::CAppInfo's vota values and calls fn 491, which has no name
// (src/units/169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp). The destructor is out of line: slot 0 (fn 5964) is
// one call of the base's destructor (fn 1952), a body of another object, and the deleting one (fn 5963) is `f1952(p0);
// drop; f136(p0)`, the 13-B shape of docs/reference/facts/reading.md R5, read as its call of slot 0 with that one-call
// body inlined. final: fn 6056 calls fn 1952 for the object it replaces, with no call through the vtable (unit 104's
// fragment measures that a state that is not final deletes through it). A singleton: GetInst, held inlined by
// vota::CGeraZeresima's slot 10 (fn 11935, a thunk into binaryen's fn 6056), keeps the object in a static
// std::unique_ptr (@1834184, destroyed at exit by fn 11942) under a static std::mutex (@1834160, by fn 11941). Not
// recovered: the constructor, GetInst and the statics (they wait for the base's constructor).
// src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk says which of this is evidence and which is chosen.
class CGeraResumoZeresima final : public CGeraResumoZeresimaBase {
public:
    virtual ~CGeraResumoZeresima() override;

    static CGeraResumoZeresima& GetInst();

private:
    CGeraResumoZeresima();

    virtual comum::CAppState* GetProximoEstado() override;

    virtual void AposGeracao() override;
};

} // namespace vota
