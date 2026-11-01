#pragma once

#include <string>
#include <utility>

#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CInstrucaoVotacaoAcessibilidade (RTTI: si_class of vota::CVotacaoStateAudio; vtable @1533608 [2466, 7255, 7028,
// 7480, 1661, 7022, 425, 7029, 7010, 7248, 7242, 218, 425, 3139, 6999, 4407]): the state that tells the voter how to
// use the keyboard. Records of cinstrucaovotacaoacessibilidade.cpp name slots 9 (ProcessInputAudio, :54 to :60, fn
// 7248) and 10 (StartStateAudio, :129 and :131, fn 7242), both pending (src/units/150-uenux2-eleitor-estados-pending.cpp),
// and two private members held inlined: CacheInstructionAudio (:157 and :161, in fn 7787) and GetKeyboardPosition
// (:175, in fn 4407, slot 15, CVotacaoStateAudio's GetMensagem, a name unit 97 chose). Slot 12 is the empty fn 425.
// The layout is what GetInst (fn 4420, not reconstructed) stores: the constructor passes 2 to CVotacaoStateAudio's and
// copies into +28 the std::shared_ptr at +124 of vota::CTelasVota::GetInst(), a form; the D2 (fn 2466) releases it and
// calls CVotacaoStateAudio's D2 with no vptr store of its own, so the class is final (docs/reference/facts/reading.md
// R4), and the D0 (fn 7255) calls the D2 and frees `this`, so the destructor is out of line, declared first as the key
// function. GetInst and the constructor wait for an accessor of that CTelasVota member, which ctelasvota.h does not
// have. The member's name and type are chosen: a std::shared_ptr is what the copy and the release show, and the form
// type is unit 97's, which ctelasvota.h chooses for CTelasVota's members too. This header's path is chosen, beside
// cinstrucaovotacaoacessibilidade.cpp.
class CInstrucaoVotacaoAcessibilidade final : public CVotacaoStateAudio {
public:
    virtual ~CInstrucaoVotacaoAcessibilidade() override;

    virtual void ProcessInputAudio() override;

    virtual void StartStateAudio() override;

    virtual void ProcessTickAudio(uebyte) override {}

    virtual std::string GetMensagem() const override;

private:
    std::string GetKeyboardPosition() const;

    CFormInterativoTelaVota m_tela;
};

} // namespace vota
