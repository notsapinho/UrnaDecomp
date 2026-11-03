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

// comum::CTituloMesarioJaRegistrado (RTTI: si_class of comum::CAppState; vtable @1594752 [448, 765, 10343, 7480, 1661,
// 218, 425, 10342, 425]): it overrides StartState (slot 2, fn 10343), which logs the titulo the controller holds, and
// ProcessInput (slot 7, fn 10342, a thunk into fn 2895, shared with three other states), which goes back to asking for
// the titulo on CORRIGE. GetInst, with the constructor and its form's builder, has no target function of its own:
// comum::IPedeTituloMesario::ProcessInput (fn 10313) holds them inlined by binaryen. The form shows the titulo through
// the file's anonymous CTituloMesarioJaRegistradoDS::Text (fn 10344, record ctitulomesariojaregistrado.cpp:29), a thunk
// into binaryen's fn 6009, which CTituloMesarioInvalidoDS::Text shares. A singleton: GetInst keeps the object in a static
// std::unique_ptr (@1909708, destroyed at exit by fn 10346) under a static std::mutex (@1909684, by fn 10345). The
// 28-byte object and its two forms are those of the 19 states over the destructors 448 and 765:
// src/units/135-uenux2-comum-mesario-estados.mk says which of this is evidence and which is chosen.
class CTituloMesarioJaRegistrado final : public CAppState {
public:
    virtual ~CTituloMesarioJaRegistrado() override;

    static CTituloMesarioJaRegistrado& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CTituloMesarioJaRegistrado();

    const IControladorRegistraMesarios& GetControlador();

    static std::mutex s_mutex;
    static std::unique_ptr<CTituloMesarioJaRegistrado> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::IForm<api::IScreen>> m_formEleitor;
};

// The operator's form of this state, which the constructor assigns to m_form. Fn 10313 holds it inlined by binaryen
// behind a 64-byte frame: "Título:", the titulo the controller holds and "Já registrado".
// Its name and its being a free function of comum with external linkage are chosen; in the anonymous namespace
// clang inlines it into the constructor, one frame where the target has two (src/units/135-uenux2-comum-mesario-estados.mk).
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaTituloMesarioJaRegistrado();

} // namespace comum
