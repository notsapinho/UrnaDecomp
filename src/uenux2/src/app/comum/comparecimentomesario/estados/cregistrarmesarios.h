#pragma once

#include <memory>
#include <mutex>

#include "api/gui/primitives.h"
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

// comum::CRegistrarMesarios (RTTI: si_class of comum::CAppState; vtable @1593584 [448, 765, 10392, 7480, 1661, 218,
// 425, 10391, 425]): it overrides StartState (slot 2, fn 10392), which calls the controller's slots 23
// (LogaIndagaRegistroMesarios), 5 and 7 and goes to CLimiteMesariosRegistradosAtingido when slot 7 returns true, else
// shows both forms; and ProcessInput (slot 7, fn 10391), a thunk into binaryen's fn 6011, the body it shares with
// comum::CMesarioRegistrado::ProcessInput (fn 10338; src/units/247-uenux2-cregistrarmesarios.mk has its evidence).
// A singleton: GetInst (fn 3610) keeps the object in a static std::unique_ptr (@1909428, destroyed at exit by fn
// 10394) under a static std::mutex (@1909404, by fn 10393); the constructor, out of line and inlined there by
// binaryen, passes EVENTO_ENTRADA to the base's and assigns both forms, the voter's from TelaRegistroMesarios and the
// operator's from TelaIndagaRegistroMesarios. The 28-byte object and its two forms are those of the 19 states over the
// destructors 448 and 765 (src/units/135-uenux2-comum-mesario-estados.mk); src/units/247-uenux2-cregistrarmesarios.mk
// says which of this is evidence and which is chosen.
class CRegistrarMesarios final : public CAppState {
public:
    virtual ~CRegistrarMesarios() override;

    static CRegistrarMesarios& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CRegistrarMesarios();

    const IControladorRegistraMesarios& GetControlador();

    static std::mutex s_mutex;
    static std::unique_ptr<CRegistrarMesarios> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::IForm<api::IScreen>> m_formEleitor;
};

// The voter's screen while the poll workers register: the status header (date and time, mode, battery icon), "REGISTRO
// DE MESÁRIOS" at (320, 150) in a 35-point font and "Siga as instruções no terminal do mesário." at (320, 250) in a
// 25-point one, centred, colours 2 over 1, as an unnamed api::IForm<api::IScreen> over a clear screen. Target fn 1255
// is its body, which binaryen keeps once for this function and for comum::IPedeTituloMesario::GetTelaEleitor
// (ipedetitulomesario.h says why there are two). Its name, its being a free function of comum, and this header's path,
// beside cregistrarmesarios.cpp, are chosen.
std::shared_ptr<api::IForm<api::IScreen>> TelaRegistroMesarios();

// The operator's form of CRegistrarMesarios: a buzz (51, 10), "Registrar mesário?" at {1, 1}, "CORRIGE: Cancelar
// CONFIRMA: Prosseguir" at {1, 4}, the input control, and the interactive form with an empty name that clears the
// keyboard. fn 3610 holds it behind a stack frame of its own inside the constructor's, the sign of binaryen's inlining
// of an out-of-line function (docs/reference/facts/reading.md R10); with internal linkage clang inlines it into the
// constructor (a scratch compile: one frame), so its linkage is external. Its name, its being a free function of comum
// and its declaration here are chosen.
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaIndagaRegistroMesarios();

// The two fonts of that screen, SFont {35, 0} and {25, 0}: the target holds them once (@540572 and @540580, between
// the typeinfo names of comum::CRegistrarMesarios and comum::CPedeTituloMesario), and 1255 alone reads them; that both
// functions here read them is part of the reading of two copies. Their names, their being constants of
// cregistrarmesarios.cpp declared here, and that file are chosen.
extern const api::SFont FONTE_TITULO_REGISTRO_MESARIOS;
extern const api::SFont FONTE_TEXTO_REGISTRO_MESARIOS;

} // namespace comum
