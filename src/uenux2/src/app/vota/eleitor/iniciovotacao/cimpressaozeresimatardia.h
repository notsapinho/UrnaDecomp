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

// vota::CImpressaoZeresimaTardia (RTTI: si_class of comum::CAppState; vtable @1544640 [244, 387, 11932, 7480, 1661,
// 218, 425, 11931, 425]): it overrides the destructors, StartState (slot 2, fn 11932), which logs "Mesário indagado se
// horário da urna está correto" through a vota::CLogVota member binaryen inlines, shows the form and stays in this
// state, and ProcessInput (slot 7, fn 11931, pending: src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.cpp).
// The destructors are the bodies 49 final states share (fns 244 and 387): final, and out of line
// (docs/reference/facts/reading.md R4, R5). +12 is the form: StartState calls its slot 2, and ProcessInput holds
// api::CInteractiveForm<api::IScreen, api::IInputKbd>::Read() (record cinteractiveform.h:57 @1544696, right after this
// class's typeinfo). A singleton: GetInst, held inlined by vota::CConfirmaImpressaoZeresima::ProcessInput (fn 11927),
// keeps the object in a static std::unique_ptr (@1834240, destroyed at exit by fn 11934) under a static std::mutex
// (@1834216, by fn 11933); its constructor passes 2 to the base's and copies vota::CTelasVota::GetInst()'s +60 and +64,
// which app/vota/eleitor/comum/ctelasvota.h has no accessor for: the constructor, GetInst and the statics are not
// reconstructed. src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk says which of this is evidence and
// which is chosen.
class CImpressaoZeresimaTardia final : public comum::CAppState {
public:
    virtual ~CImpressaoZeresimaTardia() override;

    static CImpressaoZeresimaTardia& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CImpressaoZeresimaTardia();

    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
