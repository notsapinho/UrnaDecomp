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

// vota::CMenuFiltrarCandidatosPorNumero (RTTI: si_class of comum::CAppState; vtable @1545376 [244, 387, 11892, 7480,
// 1661, 218, 425, 11891, 425]): it overrides StartState (slot 2) and ProcessInput (slot 7). The 20-byte object adds a
// std::shared_ptr at +12, to the form StartState builds (fn 11892 replaces it and calls its slot 2; the pointee's type
// is chosen, the one vota::CExibeAlertaDesligamento's form has). The destructor is out of line: the deleting one (fn
// 387) calls it and frees `this`, and it stores no vptr, as a final class's. 49 states share those two bodies, fns 244
// and 387. A singleton: GetInst (fn 5954) keeps the object in a static std::unique_ptr (@1834548, destroyed at exit by
// fn 11894) under a static std::mutex (@1834524, by fn 11893). The constructor passes 2 to the base's.
// src/units/104-uenux2-app-vota-estados.mk says which of this is evidence and which is chosen.
class CMenuFiltrarCandidatosPorNumero final : public comum::CAppState {
public:
    virtual ~CMenuFiltrarCandidatosPorNumero() override;

    static CMenuFiltrarCandidatosPorNumero& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CMenuFiltrarCandidatosPorNumero();

    static std::mutex s_mutex;
    static std::unique_ptr<CMenuFiltrarCandidatosPorNumero> s_inst;

    std::shared_ptr<api::IForm<api::IScreen>> m_form;
};

} // namespace vota
