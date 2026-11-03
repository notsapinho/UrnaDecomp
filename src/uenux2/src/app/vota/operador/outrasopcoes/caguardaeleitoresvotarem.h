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

// vota::CAguardaEleitoresVotarem (RTTI: si_class of comum::CAppState; vtable @1587620 [244, 387, 10718, 7480, 1661,
// 218, 425, 218, 425]): the operator waits until everyone present has voted. It overrides the destructors and
// StartState (slot 2, fn 10718, record caguardaeleitoresvotarem.cpp:47), which shows the form, sleeps 3000 ms through
// api::CSystem::Dorme, clears the MT keyboard and goes to vota::CPedeIdentidade. Slots 0 and 1 are fns 244 and 387,
// the out-of-line destructors 49 final states share: a std::shared_ptr at +12, the form, is all they release. A
// singleton: GetInst creates the 20-byte object under a static std::mutex (@1905144) and keeps it in a static
// std::unique_ptr (@1905168); binaryen inlines it into its one caller, vota::CPerguntaFilaEleitorVazia::ProcessInput
// (fn 10713), with the constructor, which passes EVENTO_NENHUM (0) to the base's, clears the form's two words and
// builds the form in its body. The member names are chosen. src/units/277-uenux2-app-vota-operador-outrasopcoes.mk says
// which of this is evidence and which is chosen.
class CAguardaEleitoresVotarem final : public comum::CAppState {
public:
    virtual ~CAguardaEleitoresVotarem() override;

    static CAguardaEleitoresVotarem& GetInst();

    virtual void StartState() override;

private:
    CAguardaEleitoresVotarem();

    static std::unique_ptr<CAguardaEleitoresVotarem> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
