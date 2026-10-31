#pragma once

#include <memory>

#include "app/vota/eleitor/cvotacaostateaudio.h"

namespace vota {

// vota::IConfereVotoEmCargo (RTTI: si_class of vota::CVotacaoStateAudio; vtable @1547576 [1717, 325, 7028, 7480, 1661,
// 7022, 425, 7029, 7010, 11791, 11793, 11792, 11790, 3139, 6999, 11789, 12143]): the base of the CConfereVotoEmCargo<T,
// ETelaVotacao> states (RTTI), abstract (slot 1 is the trap 325, slot 16 pure). Records of cconferevotoemcargo.cpp name
// slot 9 (ProcessInputAudio, :80) and a member slot 12 calls, ExecutarAposAudioAtual (:95, fn 3851); slot 10 holds the
// record :41 of an anonymous-namespace GetCargoID. Slots 9, 10 and 12 are pending
// (src/units/97-uenux2-cvotacaostateaudio-pending.cpp); slot 11 (fn 11792) cancels the wait at +32, slot 15 (fn 11789)
// returns its message. The destructor is in the class: fn 1278, the D0 of every instance, frees what fn 1717, this
// class's D2 in slot 0 of each, returns (docs/reference/facts/reading.md R5), and fn 1717 cancels the +32 wait as slot
// 11 does, then releases it and calls CVotacaoStateAudio's D2. The layout is what the constructor (fn 1165, not
// reconstructed: it reads an int at +176 of comum::CConfiguracaoEleicao::GetInst(), which no accessor of that class's
// header gives) stores: +28 a tick id it creates stopped, +29 a byte, 1 when it created one, +30 its argument's byte,
// +32 a std::shared_ptr. The widths are evidence; the +32 pointee is chosen as CVotacaoStateAudio's wait type, whose
// member takes the same call of slot 2 and reset; the member names, the helper's and the slot-16 name are chosen.
// ProcessInputAudio, declared first among the out-of-line members, is the key function, a choice. This header's path is
// chosen, beside cconferevotoemcargo.cpp.
class IConfereVotoEmCargo : public CVotacaoStateAudio {
public:
    virtual ~IConfereVotoEmCargo() override { CancelaEsperaConfere(); }

    virtual void ProcessInputAudio() override;

    virtual void StartStateAudio() override;

    virtual void FinishStateAudio() override;

    virtual void ProcessTickAudio(uebyte tick) override;

    virtual std::string GetMensagem() const override;

    virtual comum::CAppState* GetProximoEstado() const = 0;

private:
    void CancelaEsperaConfere()
    {
        if (m_esperaConfere) {
            m_esperaConfere->Cancela();
            m_esperaConfere.reset();
        }
    }

    uebyte m_tickConfere;
    bool m_bTickConfere;
    uebyte m_tela;
    std::shared_ptr<api::IEsperaAudio> m_esperaConfere;
};

} // namespace vota
