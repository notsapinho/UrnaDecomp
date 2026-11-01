#pragma once

#include <memory>
#include <mutex>

#include "api/util/cdatetime.h"
#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IInputKbd;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CConfirmaImpressaoZeresima (RTTI: si_class of comum::CAppState; vtable @1544712 [244, 387, 5958, 7480, 1661,
// 218, 425, 11927, 425]): it overrides the destructors, StartState (slot 2, fn 5958, one body with
// vota::CConfirmaRegerarZeresima's slot 2) and ProcessInput (slot 7, fn 11927). The 32-byte object is what GetInst (fn
// 5959) stores: the base's constructor gets 2; +12 a std::shared_ptr copied from vota::CTelasVota::GetInst()'s +52 (fn
// 407), whose slot 2 StartState calls; +20 an api::CDateTime copied from comum::CConfiguracaoEleicao::GetInst()'s +544
// (fn 187), to which it adds 10800 seconds (fn 2233, CDateTime::operator+=). The pointee is the records' form:
// ProcessInput holds api::CInteractiveForm<api::IScreen, api::IInputKbd>::Read() (record cinteractiveform.h:57) on +12.
// The destructor is out of line: slots 0 and 1 hold the D2 and D0 that 49 states share (fns 244 and 387), and fn 387 is
// `f244(p0); f136(p0)`, the 13-B shape of docs/reference/facts/reading.md R5; fn 244 releases +12 and stores no vptr,
// as a final class's (R4). A singleton: GetInst keeps the object in a static std::unique_ptr (@1834268, destroyed at
// exit by fn 11930) under a static std::mutex (@1834244, by fn 11929). Not recovered: the constructor, GetInst and the
// statics (the constructor reads a private member of vota::CTelasVota, whose head has no accessor for it, and +544 of
// comum::CConfiguracaoEleicao, which its head leaves unrecovered), and ProcessInput
// (src/units/169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp).
// src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk says which of this is evidence and which is chosen.
class CConfirmaImpressaoZeresima final : public comum::CAppState {
public:
    virtual ~CConfirmaImpressaoZeresima() override;

    static CConfirmaImpressaoZeresima& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CConfirmaImpressaoZeresima();

    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
    api::CDateTime m_limite;
};

} // namespace vota
