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

// vota::CEncerramentoAntecipado (RTTI: si_class of comum::CAppState; vtable @1587340 [244, 387, 1718, 7480, 1661, 218,
// 425, 10731, 425]): the operator is asked to confirm closing the voting before its time. It overrides the destructors,
// StartState (slot 2, fn 1718, the body it shares with vota::CUrnaInspecionada's and other states' StartState) and
// ProcessInput (slot 7, fn 10731: vota::CPedeIdentidade on api::INPUT_CORRIGE, vota::CConfirmaEncerramento on
// api::INPUT_CONFIRMA). Slots 0 and 1 are fns 244 and 387, the out-of-line destructors 49 final states share: a
// std::shared_ptr at +12, the form, is all they release. A singleton: GetInst creates the 20-byte object under a static
// std::mutex (@1905060) and keeps it in a static std::unique_ptr (@1905084); binaryen inlines it into its one caller,
// vota::CPedeTituloEncerramento::StartState (fn 10722), with the constructor, which passes EVENTO_ENTRADA (2) to the
// base's and initializes the form from a helper that builds it. The member names are chosen.
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk says which of this is evidence and which is chosen.
class CEncerramentoAntecipado final : public comum::CAppState {
public:
    virtual ~CEncerramentoAntecipado() override;

    static CEncerramentoAntecipado& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CEncerramentoAntecipado();

    static std::unique_ptr<CEncerramentoAntecipado> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
