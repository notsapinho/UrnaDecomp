#pragma once

#include <memory>
#include <mutex>
#include <string>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CTituloEncerramentoInvalido (RTTI: si_class of comum::CAppState; vtable @1587412 [244, 387, 1718, 7480, 1661,
// 218, 425, 10727, 425]): the title typed to close the voting is not valid. It overrides the destructors, StartState
// (slot 2, fn 1718, the body it shares with vota::CUrnaInspecionada's and other states' StartState: the form's slot 2,
// then the next state is the state itself) and ProcessInput (slot 7, fn 10727, which goes back to
// vota::CPedeTituloEncerramento on api::INPUT_CORRIGE). Slots 0 and 1 are fns 244 and 387, the out-of-line destructors
// 49 final states share: a std::shared_ptr at +12, the form, is all they release. A singleton: GetInst creates the
// 20-byte object under a static std::mutex (@1905088) and keeps it in a static std::unique_ptr (@1905112); binaryen
// inlines it into its one caller, vota::CPedeTituloEncerramento::ProcessInput (fn 10721), with the constructor, which
// passes EVENTO_ENTRADA (2) to the base's and initializes the form from a helper that builds it. The member names are
// chosen. src/units/277-uenux2-app-vota-operador-outrasopcoes.mk says which of this is evidence and which is chosen.
class CTituloEncerramentoInvalido final : public comum::CAppState {
public:
    virtual ~CTituloEncerramentoInvalido() override;

    static CTituloEncerramentoInvalido& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CTituloEncerramentoInvalido();

    static std::unique_ptr<CTituloEncerramentoInvalido> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

// fn 10728: the text of the form's second field, passed by its table slot (3781) to api::CMTFormBuilder::AddTextField
// (fn 619): the title the operator typed, vota::CThreadOperador's string at +120, formatted "{:<12s}". Its name and its
// being a free function declared here are chosen: no record, slot or RTTI names it.
std::string TituloEncerramentoDigitado();

} // namespace vota
