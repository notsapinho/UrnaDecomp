#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota {

// vota::CMaisInformacoes (RTTI: si_class of comum::CAppState; vtable @1545304 [244, 387, 11897, 7480, 1661, 218, 425,
// 11896, 425]): it overrides StartState (slot 2) and ProcessInput (slot 7). The 24-byte object adds a std::shared_ptr
// at +12, to the form StartState builds (fn 11897 replaces it and calls its slot 2; the pointee's type is chosen, the
// one vota::CExibeAlertaDesligamento's form has), and at +20 the state to go back to, which GetInst stores when its
// argument is not null and ProcessInput (fn 11896) moves to the next state. The destructor is out of line: the
// deleting one (fn 387) calls it and frees `this`, and it stores no vptr, as a final class's. 49 states share those
// two bodies, fns 244 and 387. A singleton: GetInst (fn 1280) keeps the object in a static std::unique_ptr (@1834520,
// destroyed at exit by fn 11899) under a static std::mutex (@1834496, by fn 11898). The constructor passes 2 to the
// base's. src/units/104-uenux2-app-vota-estados.mk says which of this is evidence and which is chosen.
class CMaisInformacoes final : public comum::CAppState {
public:
    virtual ~CMaisInformacoes() override;

    static CMaisInformacoes& GetInst(comum::CAppState* pRetorno = nullptr);

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CMaisInformacoes();

    static std::mutex s_mutex;
    static std::unique_ptr<CMaisInformacoes> s_inst;

    std::shared_ptr<api::IForm<api::IScreen>> m_form;
    comum::CAppState* m_pRetorno;
};

} // namespace vota
