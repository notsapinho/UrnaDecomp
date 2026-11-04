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

// vota::CDigitalNaoReconhecidaDecBiometria (RTTI: si_class of comum::CAppState; vtable @1591728 [244, 387, 10478, 7480,
// 1661, 218, 425, 10477, 425]): an operator's screen of the voter's fingerprint not recognized. It overrides the
// destructors, StartState (slot 2, fn 10478) and ProcessInput (slot 7, fn 10477). The destructor is out of line, the
// body 49 final states share (fns 244 and 387): a std::shared_ptr at +12 is all it releases. A singleton: fn 10474
// (vota::CDigitalNaoReconhecida::StartState) holds GetInst inlined (the one store of the vptr, 1591736), the
// constructor behind an 80-byte frame of its own (binaryen's inlining) that builds the form too: a 20-byte object kept
// in a static std::unique_ptr (@1909008, destroyed at exit by fn 10480) under a static std::mutex (@1908984, by fn
// 10479), comum::CAppState::EVENTO_ENTRADA (2) passed to the base's constructor, the form at +12, which ProcessInput
// reads through api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() (record cinteractiveform.h:57 @1591784).
// The member's name is chosen.
class CDigitalNaoReconhecidaDecBiometria final : public comum::CAppState {
public:
    virtual ~CDigitalNaoReconhecidaDecBiometria() override;

    static CDigitalNaoReconhecidaDecBiometria& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CDigitalNaoReconhecidaDecBiometria();

    static std::unique_ptr<CDigitalNaoReconhecidaDecBiometria> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

// The test both not-recognized states make of the voter's biometry: not the mesarios' training
// (EhTreinamentoMesario, fn 1823) and the decryption's error code above 0 (comum::md::CBiometriaEleitor's +36, a
// signed compare). StartState above holds it inlined by clang in LogaErroDecifracaoBiometria, the log it guards (fn
// 10478 has the code in its own frame); vota::CDigitalNaoReconhecida::StartState (fn 10474), in another TU, holds it
// behind a 48-byte frame of its own, binaryen's inlining of its one call. Neither has a target index of its own. They
// read no class state: their names, their being free functions of namespace vota and their file are chosen.
bool TemErroDecifracaoBiometria();
void LogaErroDecifracaoBiometria();

} // namespace vota
