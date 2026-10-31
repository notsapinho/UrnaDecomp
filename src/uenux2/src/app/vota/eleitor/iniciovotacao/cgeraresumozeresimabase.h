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

// vota::CGeraResumoZeresimaBase (RTTI: si_class of comum::CAppState; vtable @1544448 [1952, 325, 11943, 7480, 1661,
// 218, 425, 218, 425, 12143, 12143]): an abstract state, the base of vota::CGeraResumoZeresima and
// vota::CRegeraResumoZeresima. Slot 1 is the trap an abstract class's deleting destructor is (fn 325), and slots 9 and
// 10 are pure (fn 12143). StartState (slot 2, fn 11943) ends by calling slot 9 and storing what slot 10 returns as the
// next state, so slot 10 returns the state that follows; its overriders return vota::CImprimindoZeresima::GetInst() (fn
// 11939) and vota::CReimprimindoZeresima::GetInst() (fn 11845). The layout is the constructor's (fn 11945): the base's
// constructor gets 0, and +12 a std::shared_ptr copied from vota::CTelasVota::GetInst()'s +220 (fn 407), whose slot 2
// StartState calls first; the pointee's type is chosen, the type of vota::CTelasVota's members. The destructor is out
// of line, in another object than the derived classes': their destructors (fns 5964 and 5963) call fn 1952, which
// stores this class's vptr and releases +12 (through binaryen's fn 2902). Not recovered: the constructor (it reads a
// private member of vota::CTelasVota, whose head has no accessor for it) and StartState (it calls fns 183, 436 and 491,
// which have no name; src/units/169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp).
// src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk says which of this is evidence and which is chosen.
class CGeraResumoZeresimaBase : public comum::CAppState {
public:
    virtual ~CGeraResumoZeresimaBase() override;

    virtual void StartState() override;

protected:
    CGeraResumoZeresimaBase();

    virtual void AposGeracao() = 0;

    virtual comum::CAppState* GetProximoEstado() = 0;

private:
    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
