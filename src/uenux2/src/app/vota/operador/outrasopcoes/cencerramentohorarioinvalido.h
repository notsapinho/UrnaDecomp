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

// vota::CEncerramentoHorarioInvalido (RTTI: si_class of comum::CAppState; vtable @1587764 [244, 387, 10710, 7480, 1661,
// 218, 425, 10709, 425]): the operator asked to close the voting before its time. It overrides the destructors,
// StartState (slot 2, fn 10710, records cencerramentohorarioinvalido.cpp:60 and :73) and ProcessInput (slot 7, fn
// 10709). Slots 0 and 1 are fns 244 and 387, the out-of-line destructors 49 final states share: a std::shared_ptr at
// +12, the form, is all they release. A singleton: GetInst creates the 20-byte object under a static std::mutex
// (@1905200, destroyed at exit by fn 10711) and keeps it in a static std::unique_ptr (@1905224, by fn 10712); binaryen
// inlines it into its one caller, vota::CIniciaFinalizacao::StartState (fn 10706), with the constructor, which passes
// EVENTO_ENTRADA (2) to the base's and initializes the form from a helper that builds it. The member names are chosen.
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk says which of this is evidence and which is chosen.
class CEncerramentoHorarioInvalido final : public comum::CAppState {
public:
    virtual ~CEncerramentoHorarioInvalido() override;

    static CEncerramentoHorarioInvalido& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CEncerramentoHorarioInvalido();

    static std::unique_ptr<CEncerramentoHorarioInvalido> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
