#pragma once

#include <cstddef>
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

// comum::CLimiteMesariosRegistradosAtingido (RTTI: si_class of comum::CAppState; vtable @1594408 [448, 765, 10358,
// 7480, 1661, 218, 425, 10357, 425]): it overrides StartState (slot 2, fn 10358), which shows both forms and logs that
// the limit of mesarios is reached, and ProcessInput (slot 7, fn 10357), which ends the registration on CONFIRMA.
// A singleton: GetInst (fn 5386) keeps the object in a static std::unique_ptr (@1909624, destroyed at exit by fn 10360)
// under a static std::mutex (@1909600, by fn 10359); the constructor, out of line and inlined there by binaryen, passes
// EVENTO_ENTRADA to the base's and assigns both forms, the voter's from TelaRegistroMesarios (cregistrarmesarios.h) and
// the operator's from TelaLimiteMesariosRegistrados below. The 28-byte object and its two forms are those of the 19
// states over the destructors 448 and 765: src/units/135-uenux2-comum-mesario-estados.mk says which of this is evidence
// and which is chosen.
class CLimiteMesariosRegistradosAtingido final : public CAppState {
public:
    virtual ~CLimiteMesariosRegistradosAtingido() override;

    static CLimiteMesariosRegistradosAtingido& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CLimiteMesariosRegistradosAtingido();

    const IControladorRegistraMesarios& GetControlador();

    static std::mutex s_mutex;
    static std::unique_ptr<CLimiteMesariosRegistradosAtingido> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::IForm<api::IScreen>> m_formEleitor;
};

// The operator's form of CLimiteMesariosRegistradosAtingido: "Limite de mesários registrados atingido" at {1, 1},
// "Quantidade máxima permitida: {}" formatted with the limit at {1, 2}, "CONFIRMA: Finalizar" at {40, 4} on the
// right, the input control, and the interactive form with an empty name that clears the keyboard. fn 5386 holds it
// behind a stack frame of its own inside the constructor's, the sign of binaryen's inlining of an out-of-line function
// (docs/reference/facts/reading.md R10); with internal linkage clang inlines it into the constructor (a scratch compile:
// one frame), so its linkage is external. Its name, its being a free function of comum, its parameter and its
// declaration here are chosen.
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaLimiteMesariosRegistrados(
    std::size_t quantidadeMaxima);

} // namespace comum
