#pragma once

#include <memory>
#include <mutex>

#include "api/util/cdatetime.h"
#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IInputKbd;
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CInicioVotacao (RTTI: si_class of comum::CAppState; vtable @1543592 [448, 765, 11988, 7480, 1661, 218, 425,
// 218, 11987]): the wait for the time the voting starts. It overrides StartState (slot 2, fn 11988) and ProcessTick
// (slot 8, fn 11987), both pending. The destructors are the bodies 19 states over two std::shared_ptr at +12 and +20
// share (fns 448 and 765): final, and out of line (docs/reference/facts/reading.md R4, R5). A singleton: GetInst (fn
// 2880) builds the 44-byte object and keeps it in a static std::unique_ptr (@1834128, destroyed at exit by fn 11990)
// under a static std::mutex (@1834104, by fn 11989). The layout is what the constructor, inlined there, stores: the
// base's constructor with 4; +12 a copy of vota::CTelasVota::GetInst()'s +116, the voter's form; +20 the operator's
// form, built in the body with api::CMTFormBuilder (GetInteractiveForm, fn 301, moved in); +28 a copy of
// comum::CConfiguracaoEleicao's CDateTime at +556, the start of the voting, whose time it formats; +40 the id of a
// 1000-ms tick added stopped (fn 807). Every member name, GetInst's and the statics', the destructor declared first as
// the key function and this header's path, beside the .cpp, are chosen.
class CInicioVotacao final : public comum::CAppState {
public:
    virtual ~CInicioVotacao() override;

    static CInicioVotacao& GetInst();

    virtual void StartState() override;

    virtual void ProcessTick(uebyte tick) override;

private:
    CInicioVotacao();

    static std::mutex s_mutex;
    static std::unique_ptr<CInicioVotacao> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_formOperador;
    api::CDateTime m_inicio;
    uebyte m_tick;
};

} // namespace vota
