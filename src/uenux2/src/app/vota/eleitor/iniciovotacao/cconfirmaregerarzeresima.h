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

// vota::CConfirmaRegerarZeresima (RTTI: si_class of comum::CAppState; vtable @1546556 [244, 387, 5958, 7480, 1661,
// 218, 425, 11838, 425]): it overrides the destructors, StartState (slot 2, fn 5958, one body with
// vota::CConfirmaImpressaoZeresima's) and ProcessInput (slot 7, fn 11838), which reads the form (Read(), record
// cinteractiveform.h:57 @1546612, right after this class's typeinfo) and goes to vota::CRegerarZeresima on CONFIRMA and
// to vota::CMaisInformacoes, with this state to come back to, on BRANCO. The destructors are the bodies 49 final states
// share (fns 244 and 387): final, and out of line (docs/reference/facts/reading.md R4, R5). +12 is the form StartState
// shows. A singleton: GetInst, held inlined by vota::CReinicioVotacao::StartState (fn 11835), keeps the object in a
// static std::unique_ptr (@1834940, destroyed at exit by fn 11840) under a static std::mutex (@1834916, by fn 11839);
// its constructor passes 2 to the base's and copies vota::CTelasVota::GetInst()'s +84 and +88, which
// app/vota/eleitor/comum/ctelasvota.h has no accessor for: the constructor, GetInst and the statics are not
// reconstructed. src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk says which of this is evidence and
// which is chosen.
class CConfirmaRegerarZeresima final : public comum::CAppState {
public:
    virtual ~CConfirmaRegerarZeresima() override;

    static CConfirmaRegerarZeresima& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CConfirmaRegerarZeresima();

    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
