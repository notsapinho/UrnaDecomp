#pragma once

#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::CConfirmaVotoEmCargo (RTTI: si_class of vota::CVotacaoStateAudio; vtable @1548232 [1035, 325, 7028, 7480, 1661,
// 7022, 425, 7029, 7010, 11754, 11755, 218, 425, 3139, 6999, 12143, 12143, 425]): the states that confirm a vote. Slots
// 9 and 10 are pending; slot 12 is empty (fn 425), slot 15 stays pure and slots 16 and 17 are this class's: fn 11754
// stores slot 16's result as the next state and calls slot 17 with the form's result. Their names and types are chosen.
// The constructor (fn 5929, out of line: it has two callers, the constructors of CConfirmaProporcional and
// CConfirmaMajoritario, fns 11752 and 11700) passes its first argument to CVotacaoStateAudio's and stores the other two
// at +28 (a byte) and +32 (a word). The widths are evidence; the types, the names and what the two hold are chosen, as
// no function written here reads them: the singletons' builders pass for +28 one less than the second template argument
// of the CConfereVotoEmCargo class whose slot 16 builds them (13 for CCandidatoInapto's, whose class has
// (ETelaVotacao)14), and for +32 a small number that branco states pass as 3 and nulo states as 4 (fns 11670 to 11673,
// 11707, 11715 to 11717, 11738, 11739). This header's path is chosen, beside cconfirmavotoemcargo.cpp, a file the
// record of GetTelaCargoAtual (:71) names; slot 9, declared first here, is the key function by choice.
class CConfirmaVotoEmCargo : public CVotacaoStateAudio {
public:
    virtual void ProcessInputAudio() override;

    virtual void StartStateAudio() override;

    virtual void ProcessTickAudio(uebyte) override {}

    virtual comum::CAppState* GetProximoEstado() const = 0;

    virtual void AoConcluirEntrada(api::EInputResult) {}

protected:
    CConfirmaVotoEmCargo(int eventos, uebyte tela, int tipoVoto);

private:
    uebyte m_tela;
    int m_tipoVoto;
};

} // namespace vota
