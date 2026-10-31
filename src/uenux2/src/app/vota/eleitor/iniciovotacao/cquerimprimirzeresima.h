#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IInputKbd;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CQuerImprimirZeresima (RTTI: si_class of comum::CAppState; vtable @1544840 [244, 387, 11921, 7480, 1661, 218,
// 425, 11920, 425]): it overrides the destructors, StartState (slot 2, fn 11921) and ProcessInput (slot 7, fn 11920).
// The 20-byte object is what GetInst (fn 5957) stores: the base's constructor gets 2 and +12 a std::shared_ptr copied
// from vota::CTelasVota::GetInst()'s +228 (fn 407), whose slot 2 StartState calls. The pointee is the records' form:
// ProcessInput holds api::CInteractiveForm<api::IScreen, api::IInputKbd>::Read() (record cinteractiveform.h:57) on +12.
// The destructor is out of line: slots 0 and 1 hold the D2 and D0 that 49 final states share (fns 244 and 387; fn 387
// is `f244(p0); f136(p0)`, the 13-B shape of docs/reference/facts/reading.md R5), and fn 244 releases +12 and stores no
// vptr, as a final class's (R4). A singleton: GetInst keeps the object in a static std::unique_ptr (@1834324, destroyed
// at exit by fn 11923) under a static std::mutex (@1834300, by fn 11922); the constructor, inlined there, stores the
// vptr on the base constructor's result. Not recovered: StartState (it calls fn 5882, a vota::CLogVota member with no
// body here) and ProcessInput (src/units/169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp).
// src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk says which of this is evidence and which is chosen.
class CQuerImprimirZeresima final : public comum::CAppState {
public:
    virtual ~CQuerImprimirZeresima() override;

    static CQuerImprimirZeresima& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CQuerImprimirZeresima();

    static std::mutex s_mutex;
    static std::unique_ptr<CQuerImprimirZeresima> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
