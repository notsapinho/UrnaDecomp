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

// comum::CMesarioRegistrado (RTTI: si_class of comum::CAppState; vtable @1594872 [448, 765, 10339, 7480, 1661, 218,
// 425, 10338, 425]): the state after a poll worker is registered, which asks whether to register another. It overrides
// StartState (slot 2, fn 10339), which logs the registered titulo through the controller's slots 19 and 17, goes to
// CLimiteMesariosRegistradosAtingido when slot 7 returns true, else logs through slot 35 and shows both forms; and
// ProcessInput (slot 7, fn 10338), a thunk into binaryen's fn 6011, the body it shares with
// CRegistrarMesarios::ProcessInput (fn 10391), each passing its own GetControlador record and its copy of
// api::CInteractiveForm<IScreenMT, IInputMT>::Read()'s. The record of cmesarioregistrado.cpp (line 72) names
// GetControlador, a non-static, non-const member returning `const IControladorRegistraMesarios &`. A singleton: the
// class's GetInst, its constructor and its operator's form are held inlined by IGestorDadoMesario::StartState (fn 10337,
// not written): the object in a static std::unique_ptr (@1909736) under a static std::mutex (@1909712), the constructor
// passing EVENTO_ENTRADA to the base's and assigning the voter's form from TelaRegistroMesarios and the operator's from
// TelaMesarioRegistrado, behind a frame of its own (binaryen's inlining). The 28-byte object and its two forms are those
// of the 19 states over the destructors 448 and 765 (src/units/135-uenux2-comum-mesario-estados.mk). Chosen: the
// members' names and this header's path, beside its .cpp.
class CMesarioRegistrado final : public CAppState {
public:
    virtual ~CMesarioRegistrado() override;

    static CMesarioRegistrado& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CMesarioRegistrado();

    const IControladorRegistraMesarios& GetControlador();

    static std::mutex s_mutex;
    static std::unique_ptr<CMesarioRegistrado> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::IForm<api::IScreen>> m_formEleitor;
};

// The operator's form of CMesarioRegistrado: a buzz (51, 10), "Mesario registrado com sucesso." at {1, 1}, "Continuar
// registrando mesarios?" at {1, 2}, "CORRIGE: Encerrar  CONFIRMA: Prosseguir" at {1, 4}, the input control, and the
// interactive form with an empty name that clears the keyboard (fn 10337 holds it behind a frame of its own inside the
// constructor's). Its name, its being a free function of comum with external linkage, as TelaIndagaRegistroMesarios's,
// and its declaration here are chosen.
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaMesarioRegistrado();

} // namespace comum
