#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/iniciovotacao/cgerazeresimabase.h"

namespace vota {

// vota::CGeraZeresima (RTTI: si_class of vota::CGeraZeresimaBase; vtable @1544576 [5961, 5960, 11946, 7480, 1661, 218,
// 425, 218, 425, 218, 11935]): it overrides slots 9 and 10 and adds no data member (GetInst, fn 5962, allocates the
// base's 20 bytes). Slot 9 is empty (fn 218, the empty body 126 slots share); slot 10 (fn 11935) returns
// vota::CGeraResumoZeresima::GetInst(), which it holds inlined (a thunk into binaryen's fn 6056, which merges it with
// vota::CRegerarZeresima's slot 10). The destructor is out of line: slot 0 (fn 5961) is one call of the base's
// destructor (fn 1720), a body of another object, and the deleting one (fn 5960) is `f1720(p0); drop; f136(p0)`, the
// 13-B shape of docs/reference/facts/reading.md R5, read as its call of slot 0 with that one-call body inlined. final:
// GetInst calls fn 1720 for the object it replaces, with no call through the vtable (unit 104's fragment measures that
// a state that is not final deletes through it). A singleton: GetInst (fn 5962) keeps the object in a static
// std::unique_ptr (@1834212, destroyed at exit by fn 11938) under a static std::mutex (@1834188, by fn 11937); the
// constructor is out of line: GetInst stores what operator new returned and stores the vptr on the base constructor's
// result (fn 5965), the shape unit 104's fragment measures for an out-of-line constructor that binaryen inlined.
// src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk says which of this is evidence and which is chosen.
class CGeraZeresima final : public CGeraZeresimaBase {
public:
    virtual ~CGeraZeresima() override;

    static CGeraZeresima& GetInst();

private:
    CGeraZeresima();

    static std::mutex s_mutex;
    static std::unique_ptr<CGeraZeresima> s_inst;

    virtual comum::CAppState* GetProximoEstado() override;

    virtual void AposGeracao() override {}
};

} // namespace vota
