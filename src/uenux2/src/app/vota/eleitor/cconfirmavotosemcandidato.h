#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <utility>

#include "app/vota/eleitor/comum/ctelascargo.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CConfirmaVotoSemCandidato (RTTI: si_class of vota::CVotacaoStateAudio; vtable @1533012 [884, 883, 7028, 7480,
// 1661, 7022, 425, 7029, 7010, 7428, 7441, 218, 425, 4477, 6999, 7425]): the state that confirms a vote for a post with
// no candidate. Slot 15 (fn 7425, CVotacaoStateAudio's GetMensagem, a name unit 97 chose) returns its message; slots
// 9 and 13 are pending (src/units/150-uenux2-eleitor-estados-pending.cpp): 13 is EmiteEcoComInputField, record
// cconfirmavotosemcandidato.cpp:77; 9 is CVotacaoStateAudio's ProcessInputAudio. Slot 10, StartStateAudio (fn 7441),
// passes a string of its own signature, "virtual void vota::CConfirmaVotoSemCandidato::StartStateAudio()", to
// GetTelaCargoAtual (fn 4483, record :64): read as __PRETTY_FUNCTION__ (a literal: same bytes); no record, so no
// std::source_location. Slot 12 is the empty fn 425. The destructors are fns 884 and 883, the bodies of unit 97's fifteen states over CVotacaoStateAudio's
// D2: out of line, declared first as the key function. A singleton whose GetInst is inlined into fn 4459
// (vota::CEleitorVotando::ChamaEstadoProximoCargo): a 32-byte object, CVotacaoStateAudio's constructor called with 6,
// the byte 17 stored at +28 and the old object deleted through a direct call of CVotacaoStateAudio's D2, so the class
// is final; a static std::mutex (@1832968) and a static std::unique_ptr (@1832992). GetTelaCargoAtual reads that byte
// as the screen (fn 3921, the body binaryen shares for it and the GetTelaCargoAtual of CConfirmaVotoEmCargo and
// CCompletaProporcional, passes it on as an ETelaVotacao). GetInst and the constructor follow unit 104's singletons;
// both are out of line in cconfirmavotosemcandidato.cpp and have no target function of their own: GetInst has the one
// caller and the constructor the one call site. The data member's name, GetTelaCargoAtual's parameter name and its being
// private, the statics' names, and this header's path beside cconfirmavotosemcandidato.cpp, are chosen.
class CConfirmaVotoSemCandidato final : public CVotacaoStateAudio {
public:
    virtual ~CConfirmaVotoSemCandidato() override;

    static CConfirmaVotoSemCandidato& GetInst();

    virtual void ProcessInputAudio() override;

    virtual void StartStateAudio() override;

    virtual void ProcessTickAudio(uebyte) override {}

    virtual std::pair<api::EInputResult, std::string> EmiteEcoComInputField(
        const CFormInterativoTelaVota& form) const override;

    virtual std::string GetMensagem() const override;

private:
    CConfirmaVotoSemCandidato();

    CFormInterativoTelaVota GetTelaCargoAtual(const std::string& chamador);

    static std::mutex s_mutex;
    static std::unique_ptr<CConfirmaVotoSemCandidato> s_inst;

    ETelaVotacao m_tela;
};

} // namespace vota
