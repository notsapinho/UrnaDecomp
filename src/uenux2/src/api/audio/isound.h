#pragma once

#include <functional>
#include <memory>
#include <string>

namespace api {

class CWavFile;
class IEsperaAudio;

// Recovered: RTTI names api::ISound (typeinfo 1526576), a polymorphic class with no base, and its two implementers
// simulador::CWasmWebSound and simulador::CWasmNullSound (vtables @1528468 and @1530360, 12 slots each). The target
// has its typeinfo and no vtable of its own: no key function, every member inline or pure. Its destructor is in slots
// 10 and 11 (both implementers' 174/144, and fn 10384 deletes a std::unique_ptr<api::ISound> through slot 11), so it
// is declared after the ten members. The int at +4 is the volume, a level that CWasmWebSound hands to the browser as
// volume * 5 + 50 percent (fns 9559, 9565), and both implementers' constructors store 9 there (fn 10384, which
// news a 16-byte CWasmWebSound, and fn 8302, which news an 8-byte CWasmNullSound): this class's member and default.
// The slots, from both implementers' bodies and from the callers that reach them through
// api::CPolySingleton<api::ISound>::instance (fn 1091):
// - slot 1 takes a const std::string &: vota::CVotacaoStateAudio::PlayFile(const std::string &), inlined into fn
//   1455, passes its string to it; slot 2 the same and a mode, slots 3 and 4 a std::shared_ptr<CWavFile> by value
//   (the callee releases it) and the same mode. CWasmNullSound's slots 2 and 4 call ISound::Wait() when the mode is
//   1 and then slot 1 or 3; CWasmWebSound's slot 4 hands the browser `modo != 0`, and its slot 3 is slot 4 with mode 0.
// - slot 6 takes a bool: (anonymous namespace)::CVotaWebEngine::SetAudioEnabled(bool) (fn 10240) passes it !enabled.
// - slot 7 returns the browser's status (0 stopped, 1 playing, 2 paused: CWasmWebSound stores the same codes at its
//   +8 in slots 0, 3 and 5), which CWasmNullSound's slot 8 polls while it is 1.
// - slot 8 takes a std::function<bool ()> that cancels the wait; ISound::Wait() (whose lambda, returning false, the
//   typeinfo `api::ISound::Wait()::{lambda()#1}` names) calls it. slot 9 is ISound::WaitAsync(std::function<bool ()>,
//   std::function<void (bool)>), which its lambda's typeinfo names; it returns a std::shared_ptr to the
//   std::make_shared<api::CEsperaAudio> it builds (CEsperaAudio is an si_class of api::IEsperaAudio) through a hidden
//   result (fns 8450 and 3851).
// CWasmNullSound's slots 2, 4, 8 and 9 (fns 8479, 8472, 8461, 8450) are bodies that build ISound::Wait()'s and
// ISound::WaitAsync's lambdas, so the target gives ISound inline defaults there (and maybe in other slots, which
// CWasmNullSound fills with empty bodies). Those bodies are not recovered: every slot is declared pure here, which
// changes nothing for an implementer that overrides all ten, as CWasmWebSound does. No record, symbol or string names
// this file, the member names but Wait and WaitAsync, the enumerations or the parameter types of slots 2 and 4 (an
// enumeration: it is compared with 1, where a bool is passed on as it is), so all of those are chosen.
class ISound {
public:
    enum EModo { INTERROMPE, ENFILEIRA };
    enum EStatus { PARADO, TOCANDO, PAUSADO };

    virtual void Pause() = 0;
    virtual void Play(const std::string& arquivo) = 0;
    virtual void Play(const std::string& arquivo, EModo modo) = 0;
    virtual void Play(std::shared_ptr<CWavFile> wav) = 0;
    virtual void Play(std::shared_ptr<CWavFile> wav, EModo modo) = 0;
    virtual void Stop() = 0;
    virtual void Mute(bool mute) = 0;
    virtual EStatus GetStatus() = 0;
    virtual bool Wait(std::function<bool()> cancelado) = 0;
    virtual std::shared_ptr<IEsperaAudio> WaitAsync(std::function<bool()> cancelado, std::function<void(bool)> fim) = 0;
    virtual ~ISound() = default;

    void Wait()
    {
        Wait([] { return false; });
    }

protected:
    int m_volume = 9;
};

} // namespace api
