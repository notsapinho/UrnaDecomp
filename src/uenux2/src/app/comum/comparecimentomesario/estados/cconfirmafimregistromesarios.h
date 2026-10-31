#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IScreenMT;
class IInputMT;
template <typename MEDIA>
class IForm;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace comum {

class IControladorRegistraMesarios;

// comum::CConfirmaFimRegistroMesarios (RTTI: si_class of comum::CAppState; vtable @1593792 [448, 765, 10385, 7480,
// 1661, 218, 425, 10383, 425]): it overrides StartState (slot 2, fn 10385), which asks whether to end the registration
// of mesarios, and ProcessInput (slot 7, fn 10383), which goes on with the next mesario on CORRIGE and ends on
// CONFIRMA. GetInst (fn 5389) and the constructor inlined there, which builds both forms, are not reconstructed: they
// call fns 395 and 1255, which have no body here. A singleton: GetInst keeps the object in a static std::unique_ptr
// (@1909484, destroyed at exit by fn 10387) under a static std::mutex (@1909460, by fn 10386). The 28-byte object and
// its two forms are those of the 19 states over the destructors 448 and 765:
// src/units/135-uenux2-comum-mesario-estados.mk says which of this is evidence and which is chosen.
class CConfirmaFimRegistroMesarios final : public CAppState {
public:
    virtual ~CConfirmaFimRegistroMesarios() override;

    static CConfirmaFimRegistroMesarios& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CConfirmaFimRegistroMesarios();

    const IControladorRegistraMesarios& GetControlador();

    static std::mutex s_mutex;
    static std::unique_ptr<CConfirmaFimRegistroMesarios> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::IForm<api::IScreen>> m_formEleitor;
};

} // namespace comum
