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

// vota::CNomeEleitor (RTTI: si_class of comum::CAppState; vtable @1591248 [244, 387, 10501, 7480, 1661, 218, 425,
// 10500, 425]): the operator's screen with the voter's name, number, section and title. It overrides the destructors,
// StartState (slot 2, fn 10501: HabilitaEleitor in the voters' training, else vota::ApresentaFotoEleitor, the form and
// `this` as the next state) and ProcessInput (slot 7, fn 10500, records cnomeeleitor.cpp:145 and :156). Slots 0 and 1
// are fns 244 and 387, the out-of-line destructors the final states share: a std::shared_ptr at +12 is all they
// release. +12 is the form: StartState shows it. A singleton: GetInst (fn 5401) creates the 20-byte object under a
// static std::mutex (@1908816, destroyed at exit by fn 10502) and keeps it in a static std::unique_ptr (@1908840, by fn
// 10503); the constructor, inlined into it, initializes the form from a helper that builds it. The member names and the
// header's path (the class name in lower case, beside the records' cnomeeleitor.cpp) are chosen;
// src/units/239-uenux2-cnomeeleitor.mk says which of this is evidence.
class CNomeEleitor final : public comum::CAppState {
public:
    virtual ~CNomeEleitor() override;

    static CNomeEleitor& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CNomeEleitor();

    // fn 5400, out of line (its two target callers, StartState and ProcessInput, keep the call): the voter goes on to
    // vote without biometrics, after vota::LimpaBiometria, through CHabilitaAudioEleitor when the audio is on, else
    // through a message to CThreadEleitor and CMostraEleitorVotando. It writes m_pNextState, so it is a member. No
    // record, slot or string names it: its name is chosen.
    void HabilitaEleitor();
    // ProcessInput's CONFIRMA, by GetPedeAnoNascimentoEleitor: each has a frame of its own in fn 10500, so each is out
    // of line, inlined by binaryen into its one caller (a reading, how-to step 3). No record names them: their names
    // are chosen.
    void ConfirmaComAnoNascimento();
    void ConfirmaSemAnoNascimento();
    // Records cnomeeleitor.cpp:145 and :156 (fn 10500) give their names and signatures; clang inlines each into its
    // callers above (no frame of their own).
    void NavegaBiometrica();
    void NavegaAnoNascimento();

    static std::unique_ptr<CNomeEleitor> s_inst;
    static std::mutex s_mutex;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

// Whether the current voter's sequence number falls in the last sixth of the voters, above five sixths of
// comum::CEleitores' count and not past it: CNomeEleitor::ProcessInput (fn 10500) tests it in the mesarios' training
// and asks for the year of birth instead of the fingerprint then. Out of line in cnomeeleitorauxiliares.cpp, inlined by
// binaryen into its one caller (no target index). It reads no CNomeEleitor state, so it is a free function of vota's;
// its name, its file and its declaration here are chosen.
bool EleitorNaFaixaSemBiometria();

} // namespace vota
