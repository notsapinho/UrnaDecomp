#pragma once

#include <memory>
#include <mutex>

#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CPedeMajoritario (RTTI: si_class of vota::CVotacaoStateAudio; vtable @1550280 [884, 883, 7028, 7480, 1661,
// 7022, 425, 7029, 7010, 11683, 11684, 218, 425, 3139, 6999, 11682]): the state that asks for a majority vote. It
// overrides slots 9 and 10 (fns 11683, records cpedemajoritario.cpp:64 and :125, and 11684), 12 (empty, fn 425) and 15
// (fn 11682, which returns one of two messages by comum::CCargos::GetInst().GetCurrent().IsConsulta()), and
// the destructors (fns 884 and 883, as vota::CPedeProporcional's). A singleton like that class: GetInst (fn 5921, a
// thunk into fn 6051) under a static std::mutex (@1838316) and a static std::unique_ptr (@1838340); its constructor
// passes 2 to the base's. GetTelaCargoAtual is the record's (:44), non-static: the record does not say `static`, and
// fn 5920 lost `this` to binaryen's dead-argument elimination, as the body does not read it. Private is chosen.
// vota::CPedeProporcional's header says what that form and final rest on; the names of slot 15
// and the statics, and this header's path, are chosen. Slot 9, past its own test of the current post (code 9381),
// echoes the input; on INPUT_BRANCO it clears the number typed and goes to the CConfereVotoEmCargo state over
// vota::CMajoritarioBranco, on INPUT_CONFIRMA it stores the number and goes to the one over CMajoritarioNulo when no
// valid candidate or answer has it, CMajoritarioRepetido when it repeats an earlier choice of the post, else
// CMajoritarioValido.
class CPedeMajoritario final : public CVotacaoStateAudio {
public:
    virtual ~CPedeMajoritario() override;

    static CPedeMajoritario& GetInst();

    virtual void ProcessInputAudio() override;

    virtual void StartStateAudio() override;

    virtual void ProcessTickAudio(uebyte) override {}

    virtual std::string GetMensagem() const override;

private:
    CPedeMajoritario();

    CFormInterativoTelaVota GetTelaCargoAtual();

    // By its record (:125), const and not static: whether the number typed names a valid answer of a consulta, or a
    // candidacy of the post whose holder's situation is 0 and whose party is known (else it logs and throws, code 9382).
    // ProcessInputAudio (fn 11683), its one caller, holds it in a stack frame of its own, inlined by binaryen. Its access
    // is chosen.
    bool ExisteCandidatoValidoResposta(const std::string& numero) const;

    // Whether the post, when it takes several choices and does not allow a repeat, already holds a nominal vote for
    // the number among the votes of this cycle's earlier choices (vota::g_votosEleitor, the last ones first): fn 11683
    // holds it inlined with no frame of its own. That it is a function, its name, its being a member (as
    // ExisteCandidatoValidoResposta is) and its access are chosen.
    bool ExisteVotoRepetido(const std::string& numero) const;

    static std::mutex s_mutex;
    static std::unique_ptr<CPedeMajoritario> s_inst;
};

} // namespace vota
