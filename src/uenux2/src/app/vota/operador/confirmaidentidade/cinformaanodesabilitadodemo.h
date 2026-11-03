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

// vota::CInformaAnoDesabilitadoDemo (RTTI: si_class of comum::CAppState; vtable @1591176 [244, 387, 1718, 7480,
// 1661, 218, 425, 10504, 425]): the operator is told that the year-of-birth check is off in a demonstration.
// Slots 0 and 1 are fns 244 and 387, the out-of-line destructors the final states share: a std::shared_ptr at +12
// is all they release. +12 is the form. StartState (slot 2) is fn 1718, one body with vota::CUrnaInspecionada's.
// ProcessInput (slot 7) is fn 10504, a thunk into fn 3883 (below). A singleton: GetInst, with the constructor and
// the form, has no target function of its own: fn 10500 (vota::CNomeEleitor::ProcessInput, its one caller) holds
// them inlined, with the static std::mutex (@1908788, destroyed at exit by fn 10505) and std::unique_ptr
// (@1908812, by fn 10506).
// ProcessInput reads the form through api::CInteractiveForm<api::IScreenMT, api::IInputMT>::Read() and on CONFIRMA
// goes to vota::CHabilitaAudioEleitor::GetInst() (fn 2743) when vota::IsAudioAtivado() (fn 2746) says so, else posts 1
// to CThreadEleitor's queue and goes to vota::CMostraEleitorVotando::GetInst() (fn 1150). The slot-7 bodies of
// vota::CInformaBioDesabilitadaDemo, CInformaAnoDesabilitadoDemo and CInformaEleitorPodeVotar differ only in the record
// of Read() that each TU holds, so binaryen keeps one, fn 3883, and each slot 7 is a thunk that passes its record
// (src/units/282-uenux2-confirmaidentidade-estados.mk).
// The member names, the file names (the class name in lower case) and the directory are chosen: the fragment says
// why.
class CInformaAnoDesabilitadoDemo final : public comum::CAppState {
public:
    virtual ~CInformaAnoDesabilitadoDemo() override;

    static CInformaAnoDesabilitadoDemo& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CInformaAnoDesabilitadoDemo();

    static std::unique_ptr<CInformaAnoDesabilitadoDemo> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
