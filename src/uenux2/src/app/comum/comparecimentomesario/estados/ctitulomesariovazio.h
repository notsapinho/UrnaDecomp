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

// comum::CTituloMesarioVazio (RTTI: si_class of comum::CAppState; vtable @1594560 [448, 765, 10353, 7480, 1661, 218,
// 425, 10352, 425]): it overrides StartState (slot 2, fn 10353, a thunk into binaryen's fn 6010, which
// CTituloMesarioInvalido's StartState shares) and ProcessInput (slot 7, fn 10352, a thunk into fn 2895, shared with
// three other states), which goes back to asking for the titulo on CORRIGE. GetInst and its constructor are not
// reconstructed: no target function of their own holds them. A singleton: GetInst keeps the object in a static
// std::unique_ptr (@1909652, destroyed at exit by fn 10355) under a static std::mutex (@1909628, by fn 10354). The
// 28-byte object and its two forms are those of the 19 states over the destructors 448 and 765:
// src/units/135-uenux2-comum-mesario-estados.mk says which of this is evidence and which is chosen.
class CTituloMesarioVazio final : public CAppState {
public:
    virtual ~CTituloMesarioVazio() override;

    static CTituloMesarioVazio& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CTituloMesarioVazio();

    const IControladorRegistraMesarios& GetControlador();

    static std::mutex s_mutex;
    static std::unique_ptr<CTituloMesarioVazio> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::IForm<api::IScreen>> m_formEleitor;
};

} // namespace comum
