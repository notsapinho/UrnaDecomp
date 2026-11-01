#pragma once

#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CCompletaProporcional (RTTI: si_class of vota::CVotacaoStateAudio; vtable @1548096 [1035, 325, 7028, 7480,
// 1661, 7022, 425, 7029, 7010, 11756, 11757, 218, 425, 5930, 6999, 12143, 12143]): the states that complete a
// proportional vote. Abstract (slots 15 and 16 pure), with an implicit destructor: slot 0 holds CVotacaoStateAudio's
// D2. Slots 9 and 13 are pending (fns 11756 and 5930, record ccompletaproporcional.cpp:60, which names slot 13 an override
// of EmiteEcoComInputField); slot 10 (fn 11757) shows the form GetTelaCargoAtual (record :83) returns for the screen
// at +28; slot 16 is the one vota::CPedeNulo's record names (cpedenulo.cpp:44,
// GetProximoEstado(const std::string &) const). The constructor (fn 5932) passes 6 to the base's and stores its
// argument at +28 (a byte): the width is evidence, its type and name are chosen, as nothing written reads it. The
// parameter's name is chosen too, and so is ProcessInputAudio as the key function (its record is not in this file).
// GetTelaCargoAtual's being private and its parameter's name are chosen. This header's path is chosen, beside
// ccompletaproporcional.cpp.
class CCompletaProporcional : public CVotacaoStateAudio {
public:
    virtual void ProcessInputAudio() override;

    virtual void StartStateAudio() override;

    virtual void ProcessTickAudio(uebyte) override {}

    virtual std::pair<api::EInputResult, std::string> EmiteEcoComInputField(
        const CFormInterativoTelaVota& form) const override;

    virtual comum::CAppState* GetProximoEstado(const std::string& numero) const = 0;

protected:
    explicit CCompletaProporcional(uebyte tela);

private:
    CFormInterativoTelaVota GetTelaCargoAtual(const std::string& chamador);

    uebyte m_tela;
};

} // namespace vota
