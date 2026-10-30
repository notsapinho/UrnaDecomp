#pragma once

#include <functional>
#include <memory>
#include <string>

#include "api/audio/cesperaaudio.h"
#include "api/util/csystem.h"

namespace api {

class CWavFile;

// Recovered: RTTI names api::ISound (typeinfo 1526576), a polymorphic class with no base, and its two implementers
// simulador::CWasmWebSound and simulador::CWasmNullSound (vtables @1528468 and @1530360, 12 slots each). The class has
// no key function, so every virtual member is inline or pure: its typeinfo lies inside vota_web_wasm.cpp's data, a
// copy in a TU that only uses the class, just before the record of api::CPolySingleton<api::ISound>::instance at
// 1526584 and with that file's records on both sides (1526324, 1526664), where a key function would have put it in
// that function's own TU. Its destructor is in slots 10 and 11 (both implementers' 174/144, and fn 10384 deletes a
// std::unique_ptr<api::ISound> through slot 11), so it is declared after the ten members. The int at +4 is the volume,
// a level that CWasmWebSound hands to the browser as volume * 5 + 50 percent (fns 9559, 9565), and both implementers'
// constructors store 9 there (fn 10384, which news a 16-byte CWasmWebSound, and fn 8302, which news an 8-byte
// CWasmNullSound): this class's member and default.
// The slots, from both implementers' bodies and from the callers that reach them through
// api::CPolySingleton<api::ISound>::instance (fn 1091):
// - slot 1 takes a const std::string &: vota::CVotacaoStateAudio::PlayFile(const std::string &), inlined into fn
//   1455, passes its string to it; slot 2 the same and a mode, slots 3 and 4 a std::shared_ptr<CWavFile> by value
//   (the callee releases it) and the same mode. CWasmWebSound's slot 4 hands the browser `modo != 0`, and its slot 3
//   is slot 4 with mode 0.
// - slot 6 takes a bool: (anonymous namespace)::CVotaWebEngine::SetAudioEnabled(bool) (fn 10240) passes it !enabled.
// - slot 7 returns the browser's status (0 stopped, 1 playing, 2 paused: CWasmWebSound stores the same codes at its
//   +8 in slots 0, 3 and 5), which CWasmNullSound's slot 8 polls while it is 1.
// - slot 8 takes a std::function<bool ()> that cancels the wait; ISound::Wait() (whose lambda, returning false, the
//   typeinfo `api::ISound::Wait()::{lambda()#1}` names) calls it. slot 9 is ISound::WaitAsync(std::function<bool ()>,
//   std::function<void (bool)>), which its lambda's typeinfo names; it returns a std::shared_ptr to the
//   std::make_shared<api::CEsperaAudio> it builds (CEsperaAudio is an si_class of api::IEsperaAudio) through a hidden
//   result (fns 8450 and 3851).
// Four slots have ISound's own bodies in the target, which only CWasmNullSound's vtable shows, and all four are written
// below and emitted by the class that inherits them: fns 8479 and 8472 build ISound::Wait()'s lambda, and fn 8450 builds
// ISound::WaitAsync's, whose captures are the CEsperaAudio and the cancelling function, in that order (the lambda's
// __func holds the shared_ptr at +8 and the std::function at +16). Fn 8461 builds no lambda: its being ISound's is
// inferred from its calls of slot 7 through the vtable, in a class whose slot 7 returns 0. Its sleep is CSystem::Dorme,
// which api/util/csystem.h says what is chosen about. No evidence gives ISound a body in the six other slots.
// No record, symbol or string names this file or the member names but Wait and WaitAsync, so all of those are chosen.
// So are the two enumerations and the type of the mode of slots 2 and 4 (an enumeration: it is compared with 1, where a
// bool is passed on as it is). The target's own glue backs EModo's two values: its js_wasm_web_sound_play_wav takes
// that argument as `modo` and runs `if(modo===0){stopCurrent(state,true)}`, so 0 interrupts and clears the queue, and
// any other value queues.
class ISound {
public:
    enum EModo { INTERROMPE, ENFILEIRA };
    enum EStatus { PARADO, TOCANDO, PAUSADO };

    virtual void Pause() = 0;
    virtual void Play(const std::string& arquivo) = 0;
    virtual void Play(const std::string& arquivo, EModo modo)
    {
        if (modo == ENFILEIRA)
            Wait();
        Play(arquivo);
    }
    virtual void Play(std::shared_ptr<CWavFile> wav) = 0;
    virtual void Play(std::shared_ptr<CWavFile> wav, EModo modo)
    {
        if (modo == ENFILEIRA)
            Wait();
        Play(wav);
    }
    virtual void Stop() = 0;
    virtual void Mute(bool mute) = 0;
    virtual EStatus GetStatus() = 0;
    virtual bool Wait(std::function<bool()> cancelado)
    {
        while (GetStatus() == TOCANDO) {
            if (cancelado && cancelado())
                return false;
            CSystem::Dorme(20);
        }
        return true;
    }
    virtual std::shared_ptr<IEsperaAudio> WaitAsync(std::function<bool()> cancelado, std::function<void(bool)> fim)
    {
        auto espera = std::make_shared<CEsperaAudio>();
        const bool terminou = Wait([espera, cancelado] { return espera->Cancelada() || (cancelado && cancelado()); });
        if (!espera->Cancelada() && fim)
            fim(terminou);
        return espera;
    }
    virtual ~ISound() = default;

    void Wait()
    {
        Wait([] { return false; });
    }

protected:
    int m_volume = 9;
};

} // namespace api
