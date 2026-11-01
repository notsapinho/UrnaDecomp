#pragma once

#include <memory>
#include <mutex>

#include "api/util/cwait.h"
#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IInputKbd;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CInformacaoZeresimaTardia (RTTI: si_class of comum::CAppState; vtable @1543648 [2879, 11984, 11983, 7480, 1661,
// 218, 425, 11982, 425]): it overrides the destructors, StartState (slot 2) and ProcessInput (slot 7, records
// cinformacaozeresimatardia.cpp:48 and :51). The layout is what the constructor stores, inlined with GetInst into fn
// 11931 (vota::CImpressaoZeresimaTardia's slot 7): the object is 48 bytes; the base's constructor gets 2; +16 an
// api::CWait built with 1000 (fn 5447 is CWait's constructor), so +12 is the padding its 8-byte timeval asks for; +40 a
// std::shared_ptr copied from vota::CTelasVota::GetInst()'s +68 (fn 407). The pointee is the records' form:
// ProcessInput holds api::CInteractiveForm<api::IScreen, api::IInputKbd>::Read() (record cinteractiveform.h:57) on +40.
// The destructor is out of line: the deleting one (fn 11984) is `f2879(p0); drop; f136(p0)`, the 13-B shape of
// docs/reference/facts/reading.md R5, and fn 2879 releases +40 and stores no vptr, as a final class's (R4). A
// singleton: fn 11931 keeps the object in a static std::unique_ptr (@1834156, destroyed at exit by fn 11986) under a
// static std::mutex (@1834132, by fn 11985). Not recovered: the constructor and GetInst (fn 11931 holds them inlined;
// the constructor reads a private member of vota::CTelasVota, whose head has no accessor for it), the statics, and
// ProcessInput (src/units/169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp).
// src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk says which of this is evidence and which is chosen.
class CInformacaoZeresimaTardia final : public comum::CAppState {
public:
    virtual ~CInformacaoZeresimaTardia() override;

    static CInformacaoZeresimaTardia& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CInformacaoZeresimaTardia();

    api::CWait m_espera;
    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
