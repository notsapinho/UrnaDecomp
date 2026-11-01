#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/iniciovotacao/cgeraresumozeresimabase.h"

namespace vota {

// vota::CRegeraResumoZeresima (RTTI: si_class of vota::CGeraResumoZeresimaBase; vtable @1546428 [5964, 5963, 11943,
// 7480, 1661, 218, 425, 218, 425, 218, 11845]): it overrides slots 9 and 10 and adds no data member (the object fn 6056
// builds is the base's 20 bytes). Slot 10 (fn 11845) returns vota::CReimprimindoZeresima::GetInst() (fn 5941); slot 9
// is empty (fn 218, the empty body 126 slots share). The destructors are vota::CGeraResumoZeresima's bodies (fns 5964
// and 5963): out of line, as that class's are. final, as that class is: fn 6056 is their two GetInst, merged. A
// singleton: GetInst, held inlined by vota::CRegerarZeresima's slot 10 (fn 11841, a thunk into fn 6056), keeps the
// object in a static std::unique_ptr (@1834884, destroyed at exit by fn 11847) under a static std::mutex (@1834860, by
// fn 11846). The constructor is out of line, as vota::CGeraResumoZeresima's is.
// src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk says which of this is evidence and which is chosen.
class CRegeraResumoZeresima final : public CGeraResumoZeresimaBase {
public:
    virtual ~CRegeraResumoZeresima() override;

    static CRegeraResumoZeresima& GetInst();

private:
    CRegeraResumoZeresima();

    static std::mutex s_mutex;
    static std::unique_ptr<CRegeraResumoZeresima> s_inst;

    virtual comum::CAppState* GetProximoEstado() override;

    virtual void AposGeracao() override {}
};

} // namespace vota
