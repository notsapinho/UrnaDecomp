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

// vota::CDadoEleitorNaoConfere (RTTI: si_class of comum::CAppState; vtable @1592640 [448, 765, 10448, 7480, 1661, 218,
// 425, 10447, 425]): an operator's screen shown when the voter's datum does not match. It overrides StartState (slot
// 2, fn 10448), which shows the form at +20 when vota::CControlaReconhecimento's verifications reached their limit and
// the one at +12 otherwise, and ProcessInput (slot 7, fn 10447), which reads the form at +12 and holds
// CControlaReconhecimento::AvancaVerificacao inlined (record ccontrolareconhecimento.cpp:176). The
// destructor is out of line, the body 19 final states share (fns 448 and 765): two std::shared_ptr, +20's released
// first. A singleton: fn 10443 (vota::CVerificaDadoEleitor::ProcessInput) holds GetInst inlined (the one store of the
// vptr, 1592648), the 28-byte object kept in a static std::unique_ptr (@1909176, destroyed at exit by fn 10450) under a
// static std::mutex (@1909152, by fn 10449), and the constructor behind a 64-byte frame of its own (binaryen's
// inlining), which passes comum::CAppState::EVENTO_ENTRADA (2) to the base's and builds the two forms one after the
// other in one builder slot: +12 with LED_OPERACAO_0, "Ano de nascimento não confere. Por favor", "pergunte novamente
// ao eleitor o ano de" and "nascimento dele" at {1, 1} to {1, 3}, "CONFIRMA: tentar novamente" at {40, 4} on the right;
// +20 with LED_OPERACAO_0, "Por favor oriente o eleitor a procurar o", "cartorio eleitoral para consultar a data" and
// "de nascimento dele no cadastro da urna" at {1, 1} to {1, 3}, "CONFIRMA: cancelar a habilitacao" at {40, 4} on the
// right; each with the input control and GetInteractiveForm("", true). The two form helpers' names and their being in
// an anonymous namespace are chosen. src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is
// evidence and which is chosen.
class CDadoEleitorNaoConfere final : public comum::CAppState {
public:
    virtual ~CDadoEleitorNaoConfere() override;

    static CDadoEleitorNaoConfere& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CDadoEleitorNaoConfere();

    static std::unique_ptr<CDadoEleitorNaoConfere> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_formLimite;
};

} // namespace vota
