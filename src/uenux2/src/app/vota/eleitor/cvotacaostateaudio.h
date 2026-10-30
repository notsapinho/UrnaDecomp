#pragma once

#include <memory>
#include <string>
#include <utility>

#include "api/audio/cesperaaudio.h"
#include "app/comum/cappstate.h"

namespace api {
class IScreen;
class IInputKbd;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
// The record of fn 3139 qualifies it (std::pair<api::EInputResult, std::string>). Its enumerators are not recovered
// and no header of this tree defines it yet: declared opaque, 4 bytes by fn 3139, signedness chosen.
enum EInputResult : int;
} // namespace api

namespace vota {

// The form a voting state shows. The records spell the name; that it is a typedef, and of a std::shared_ptr, is read from
// fn 11755, which takes one by value from GetTelaCargoAtual (fn 5928), calls its slot 2 and releases its count. The form's
// instance is the records' Read().
using CFormInterativoTelaVota = std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>>;

// The +16 member's type: the destructor is the only code that touches the member, through slot 1, so the class and its
// name are chosen.
class IRecursoAudio {
public:
    virtual ~IRecursoAudio() = default;
};

// vota::CVotacaoStateAudio (RTTI: si_class of comum::CAppState; vtable @1534928 [1035, 325, 7028, 7480, 1661, 7022, 425,
// 7029, 7010, 12143, 12143, 218, 12143, 3139, 6999, 12143]): the base of the voting states that speak. It is abstract
// (slot 1 is the trap 325). Records of cvotacaostateaudio.cpp name ProcessInput (:69), ProcessTick (:120) and
// EmiteEcoComInputField (:188); the overriders' records name slots 9 and 10 (ProcessInputAudio and StartStateAudio,
// cinstrucaovotacaoacessibilidade.cpp:54 and :129). StartState and FinishState are comum::CAppState's names. Chosen:
// the names of slots 11 (FinishState calls it last), 12 (ProcessTick calls it with any other tick's id), 14 and 15, and
// slots 14 and 15's const. ProcessTick (fn 7010) calls slot 15 and hands the result to slot 14: slot 15 is the message, with
// {cargo-atual}-style tags, and slot 14 fills them in (fn 6999 holds those tags and returns a string).
// Slots 2, 5, 7, 8, 13 and 14 are pending (src/units/97-uenux2-cvotacaostateaudio-pending.cpp).
//
// The layout is what the constructor (fn 1785, not reconstructed: it calls fns 316 and 807, with no name yet) stores:
// +11 a flag read before every use of audio (fn 7028 stores a comparison's result there, and the readers compare it with
// 1: the width is evidence, the bool is chosen), +12 and +13 two tick ids, +16 a std::unique_ptr (the destructor deletes
// it through slot 1), +20 the wait for the end of the audio. The wait's type follows
// api::ISound::WaitAsync, which IniciarEsperaFimAudio (record :388, inlined into fn 7010) calls and whose result it
// stores there. All member names, and the name of the private member the destructor calls, are chosen. That member's
// code sits in fns 1035, 7010, 7022 and 7029 with no frame of its own, so clang inlines it: written in the class, a
// choice among the forms the fragment lists. The destructor is declared first, as the key function, a choice: the
// vtable's place shows that a member is out of line in cvotacaostateaudio.cpp, not which, and the destructor's own form
// is in the fragment. This header's path is chosen, beside that file.
class CVotacaoStateAudio : public comum::CAppState {
public:
    virtual ~CVotacaoStateAudio() override;

    virtual void StartState() override;

    virtual void FinishState() override;

    virtual void ProcessInput() override;

    virtual void ProcessTick(uebyte tick) override;

    virtual void ProcessInputAudio() = 0;

    virtual void StartStateAudio() = 0;

    virtual void FinishStateAudio() {}

    virtual void ProcessTickAudio(uebyte tick) = 0;

    virtual std::pair<api::EInputResult, std::string> EmiteEcoComInputField(const CFormInterativoTelaVota& form) const;

    virtual std::string FormataMensagem(const std::string& mensagem) const;

    virtual std::string GetMensagem() const = 0;

private:
    void CancelaEsperaFimAudio()
    {
        if (m_esperaFimAudio) {
            m_esperaFimAudio->Cancela();
            m_esperaFimAudio.reset();
        }
    }

    bool m_bAudioHabilitado;
    uebyte m_tickEco;
    uebyte m_tickMensagem;
    std::unique_ptr<IRecursoAudio> m_recurso;
    std::shared_ptr<api::IEsperaAudio> m_esperaFimAudio;
};

} // namespace vota
