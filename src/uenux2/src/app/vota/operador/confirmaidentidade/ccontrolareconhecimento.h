#pragma once

#include <memory>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// vota::CControlaReconhecimento (RTTI: si_class of comum::CAppState; vtable @1590984 [244, 387, 10512, 7480, 1661, 218,
// 425, 10511, 425]): it overrides StartState (slot 2, fn 10512) and ProcessInput (slot 7, fn 10511), both pending, and
// keeps the counters of the voter's biometric recognition in statics that other states' slots test and advance through
// its static members. The records of ccontrolareconhecimento.cpp name three of those: AvancaTentativa (line 167, fn
// 5406), AvancaVerificacao (line 176, held inlined by fn 10447) and AvancaProximoDedo1x4 (line 187, held inlined by fn
// 10465). The destructor is out of line, the body 49 final states share (fns 244 and 387): a std::shared_ptr at +12 is
// all it releases. GetInst (fn 1256, not reconstructed, with the constructor it holds inlined) allocates the 20-byte
// object when the pointer at @1908756 is null, passes comum::CAppState::EVENTO_ENTRADA (2) to the base's constructor,
// calls fns 5410 and 1903, which have no name, deletes the old object through fn 244 and, before it returns, calls fn
// 150 (one body with std::mutex::unlock) on @1908732.
//
// The statics are what the slots and the static members read and write: in .data, three 32-bit words that hold 1, set
// again by StartState, second first (@1590924, @1590928, @1590932: first to third below); in .bss, a byte (@1908668).
// AvancaTentativa compares the first with the byte CConfiguracaoEleicao holds at +136 (its CParametrosUrna's
// numTentativasHabilitacao), AvancaVerificacao the second with the one at +140 (numTentativasVerificacao); fn 10465
// copies the first into the third, and fn 10425 reads the third's low byte. The .bss byte is the index of the finger
// being captured: StartState and AvancaTentativa set it to 0; AvancaProximoDedo1x4, inlined into fn 10465 under
// record 187, adds 1 to it while it is not 4 and otherwise throws EUeVotaError 9399 ("Fim da verificação 1x4
// atingido."); fn 10465 also tests it against 4 at +0xe62, a `br_if` out of a loop, and fns 10465 and 10425 read the
// word at @1590944 + 4 * byte, a table whose words are 1, 6, 2, 7, 3, 4, 5, 8, 9, 10. So it is an unsigned byte
// counter (each read is i32.load8_u), not a flag; uebyte, the tree's spelling of that type, is a choice. StartState
// also writes other .bss words of the file (@1908672 to @1908728) that are not declared here. The statics' names are
// chosen: s_indiceDedo from the byte's role, s_tentativaRegistrada from 10465's copy.
// src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is evidence and which is chosen.
class CControlaReconhecimento final : public comum::CAppState {
public:
    virtual ~CControlaReconhecimento() override;

    static CControlaReconhecimento& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

    static void AvancaTentativa();
    static bool AtingiuLimiteTentativas();
    static bool AtingiuLimiteVerificacoes();
    static bool PrimeiraTentativa();

private:
    CControlaReconhecimento();

    static int s_tentativa;
    static int s_verificacao;
    static int s_tentativaRegistrada;
    static uebyte s_indiceDedo;

    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
