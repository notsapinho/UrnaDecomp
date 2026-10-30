#pragma once

#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CConfirmaVotoEmCargo (RTTI: si_class of vota::CVotacaoStateAudio; vtable @1548232 [1035, 325, 7028, 7480, 1661,
// 7022, 425, 7029, 7010, 11754, 11755, 218, 425, 3139, 6999, 12143, 12143, 425]): the states that confirm a vote. Slots
// 9 and 10 are pending; slot 12 is empty (fn 425), slot 15 stays pure and slots 16 and 17 are this class's: fn 11754
// stores slot 16's result as the next state and calls slot 17 with the form's result. Their names and types are chosen.
// The class's data members (+28 and +32, which fn 5929 stores) and its constructor are not reconstructed: nothing
// constructs it yet, so its sizeof is wrong. This header's path is chosen, beside cconfirmavotoemcargo.cpp, a file the
// record of GetTelaCargoAtual (:71) names; slot 9, declared first here, is the key function by choice.
class CConfirmaVotoEmCargo : public CVotacaoStateAudio {
public:
    virtual void ProcessInputAudio() override;

    virtual void StartStateAudio() override;

    virtual void ProcessTickAudio(uebyte) override {}

    virtual comum::CAppState* GetProximoEstado() const = 0;

    virtual void AoConcluirEntrada(api::EInputResult) {}
};

} // namespace vota
