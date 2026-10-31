#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/iniciovotacao/cgerazeresimabase.h"

namespace vota {

// vota::CRegerarZeresima (RTTI: si_class of vota::CGeraZeresimaBase; vtable @1546492 [5961, 5960, 11946, 7480, 1661,
// 218, 425, 11842, 11841]): it overrides slots 9 and 10 and adds no data member (the object fn 11838 builds is the
// base's 20 bytes). Slot 10 (fn 11841) returns vota::CRegeraResumoZeresima::GetInst(), which it holds inlined (a thunk
// into binaryen's fn 6056, with vota::CGeraZeresima's slot 10). Slot 9 (fn 11842) calls fn 2882, which has no name
// (src/units/169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp). The destructors are vota::CGeraZeresima's bodies
// (fns 5961 and 5960): out of line, as that class's are. final, as that class is: fn 11838 calls fn 1720 for the object
// it replaces. A singleton: GetInst, held inlined by vota::CConfirmaRegerarZeresima's slot 7 (fn 11838), keeps the
// object in a static std::unique_ptr (@1834912, destroyed at exit by fn 11844) under a static std::mutex (@1834888, by
// fn 11843); the constructor is out of line, as vota::CGeraZeresima's is: fn 11838 stores what operator new returned
// and stores the vptr on the base constructor's result (fn 5965). Not recovered: slot 9.
// src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk says which of this is evidence and which is chosen.
class CRegerarZeresima final : public CGeraZeresimaBase {
public:
    virtual ~CRegerarZeresima() override;

    static CRegerarZeresima& GetInst();

private:
    CRegerarZeresima();

    static std::mutex s_mutex;
    static std::unique_ptr<CRegerarZeresima> s_inst;

    virtual comum::CAppState* GetProximoEstado() override;

    virtual void AposGeracao() override;
};

} // namespace vota
