#pragma once

#include <memory>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IInputKbd;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CGeraZeresimaBase (RTTI: si_class of comum::CAppState; vtable @1544384 [1720, 325, 11946, 7480, 1661, 218, 425,
// 218, 425, 12143, 12143]): an abstract state, the base of vota::CGeraZeresima and vota::CRegerarZeresima. Slot 1 is
// the trap an abstract class's deleting destructor is (fn 325), and slots 9 and 10 are pure (fn 12143). StartState
// (slot 2, fn 11946) ends by calling slot 9 and storing what slot 10 returns as the next state, as
// vota::CGeraResumoZeresimaBase's does. The layout is the constructor's (fn 5965): the base's constructor gets 0, and
// +12 a std::shared_ptr copied from vota::CTelasVota::GetInst()'s +212 (fn 407), whose slot 2 StartState calls; the
// pointee's type is chosen, the type of vota::CTelasVota's members. The destructor is out of line, in another object
// than the derived classes': their destructors (fns 5961 and 5960) call fn 1720, which stores this class's vptr and
// releases +12 (through binaryen's fn 2902). The constructor reads the member through a getter chosen for it
// (ctelasvota.h). Not recovered: StartState (6878 B; it calls fns 183, 436 and 491, which have no name;
// src/units/169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp).
// src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk says which of this is evidence and which is chosen.
class CGeraZeresimaBase : public comum::CAppState {
public:
    virtual ~CGeraZeresimaBase() override;

    virtual void StartState() override;

protected:
    CGeraZeresimaBase();

    virtual void AposGeracao() = 0;

    virtual comum::CAppState* GetProximoEstado() = 0;

private:
    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
