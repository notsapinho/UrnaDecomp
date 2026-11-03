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

// vota::CInformaEleitorPodeVotar (RTTI: si_class of comum::CAppState; vtable @1591352 [244, 387, 1070, 7480,
// 1661, 218, 425, 10496, 425]): the operator is told that the voter may vote. Slots 0 and 1 are fns 244 and 387,
// the out-of-line destructors the final states share: a std::shared_ptr at +12 is all they release. +12 is the
// form, from vota::MontaTelaEleitorPodeVotar (fn 5410, ccontrolareconhecimento.h), which
// vota::CControlaReconhecimento's GetInst (fn 1256) builds its +12 with too. StartState (slot 2) is fn 1070, one body
// with comum::CDigitalMesarioNaoReconhecida's: `this` as the next state, then the form's slot 2. ProcessInput (slot 7)
// is fn 10496, a thunk into fn 3883 (below). A singleton: GetInst (fn 5399) creates the 20-byte object under a static
// std::mutex (@1908844, destroyed at exit by fn 10497) and keeps it in a static std::unique_ptr (@1908868, by fn
// 10499); the constructor is inlined into it.
// ProcessInput reads the form through api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() and on CONFIRMA
// goes to vota::CHabilitaAudioEleitor::GetInst() (fn 2743) when vota::IsAudioAtivado() (fn 2746) says so, else posts 1
// to CThreadEleitor's queue and goes to vota::CMostraEleitorVotando::GetInst() (fn 1150). The slot-7 bodies of
// vota::CInformaBioDesabilitadaDemo, CInformaAnoDesabilitadoDemo and CInformaEleitorPodeVotar differ only in the record
// of Read() that each TU holds, so binaryen keeps one, fn 3883, and each slot 7 is a thunk that passes its record
// (src/units/282-uenux2-confirmaidentidade-estados.mk).
// The member names, the file names (the class name in lower case) and the directory are chosen: the fragment says
// why.
class CInformaEleitorPodeVotar final : public comum::CAppState {
public:
    virtual ~CInformaEleitorPodeVotar() override;

    static CInformaEleitorPodeVotar& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CInformaEleitorPodeVotar();

    static std::unique_ptr<CInformaEleitorPodeVotar> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
