#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CHabilitacaoAudioNaoPermitida (RTTI: si_class of comum::CAppState; vtable @1586896 [244, 387, 10754, 7480,
// 1661, 218, 425, 218, 425]): the audio may not be turned on. It overrides the destructors and StartState (slot 2, fn
// 10754), which shows the form, sleeps 1000 ms through api::CSystem::Dorme and goes back to vota::CEscolheOpcao. Slots
// 0 and 1 are fns 244 and 387, the out-of-line destructors 49 final states share: a std::shared_ptr at +12, the form,
// is all they release. A singleton: GetInst creates the 20-byte object under a static std::mutex (@1904920) and keeps
// it in a static std::unique_ptr (@1904944); binaryen inlines it into its one caller, vota::CEscolheOpcao::ProcessInput
// (fn 10689, pending), so GetInst, the constructor and the statics are declared and not written here: they wait for
// that caller. The member names are chosen. src/units/277-uenux2-app-vota-operador-outrasopcoes.mk says which of this
// is evidence and which is chosen.
class CHabilitacaoAudioNaoPermitida final : public comum::CAppState {
public:
    virtual ~CHabilitacaoAudioNaoPermitida() override;

    static CHabilitacaoAudioNaoPermitida& GetInst();

    virtual void StartState() override;

private:
    CHabilitacaoAudioNaoPermitida();

    static std::unique_ptr<CHabilitacaoAudioNaoPermitida> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
