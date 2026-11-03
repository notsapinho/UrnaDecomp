#pragma once

#include <memory>
#include <mutex>
#include <string>

#include "api/util/cdatetime.h"
#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CPedeTituloEncerramento (RTTI: si_class of comum::CAppState; vtable @1587548 [244, 387, 10722, 7480, 1661, 218,
// 425, 10721, 425]): the operator types a title to close the voting. It overrides the destructors, StartState (slot 2,
// fn 10722) and ProcessInput (slot 7, fn 10721). Slots 0 and 1 are fns 244 and 387, the out-of-line destructors 49
// final states share: a std::shared_ptr at +12 is all they release. A singleton: GetInst (fn 3631) creates the 32-byte
// object under a static std::mutex (@1905116) and keeps it in a static std::unique_ptr (@1905140); the constructor,
// inlined there, passes EVENTO_ENTRADA (2) to the base's, initializes the form at +12 from a helper that builds it and
// copies comum::CConfiguracaoEleicao's api::CDateTime at +568 (GetDataHoraEncerramento) into +20.
//
// The layout: +12 the form, which StartState shows (slot 2 of api::IForm) and ProcessInput reads through
// api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record cinteractiveform.h:57 @1587604); +20 a copy of
// that time, 12 bytes (an i64 and an i32 copied, the two words of an api::CDateTime), which StartState compares with
// the current time (fn 759, CDateTime's <=>). The member names are chosen. src/units/277-uenux2-app-vota-operador-
// outrasopcoes.mk says which of this is evidence and which is chosen.
class CPedeTituloEncerramento final : public comum::CAppState {
public:
    virtual ~CPedeTituloEncerramento() override;

    static CPedeTituloEncerramento& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CPedeTituloEncerramento();

    comum::CAppState* ConfirmaTitulo();
    static bool TituloValido(const std::string& titulo);

    static std::unique_ptr<CPedeTituloEncerramento> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    api::CDateTime m_dataHoraEncerramento;
};

} // namespace vota
