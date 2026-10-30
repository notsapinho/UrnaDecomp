#pragma once

#include <functional>
#include <memory>
#include <string>

#include "api/audio/isound.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::ISound, vtable @1528468), the wasm build's sound, which plays a
// WAV in the browser through the EM_JS functions js_wasm_web_sound_*. The layout is read from its members and from
// the lambda of main that builds it (fn 10384, into which binaryen inlined the constructor): 16 bytes, ISound's
// volume at +4 (9), the status at +8 and the mute flag at +12 (both zero). The status is ISound::EStatus: slot 0 stores
// 2, slots 3 and 4 store 1 when they hand a WAV to the browser and 0 otherwise, slot 5 stores 0. Slots 3 and 8 hold the
// bodies of slots 4 and 7 inlined, which a call that names the member devirtualizes only in a final class. The
// member names are ISound's (api/audio/isound.h says which are chosen); the members' names are chosen too.
class CWasmWebSound final : public api::ISound {
public:
    virtual void Pause() override;
    virtual void Play(const std::string& arquivo) override;
    virtual void Play(const std::string& arquivo, EModo modo) override;
    virtual void Play(std::shared_ptr<api::CWavFile> wav) override;
    virtual void Play(std::shared_ptr<api::CWavFile> wav, EModo modo) override;
    virtual void Stop() override;
    virtual void Mute(bool mute) override;
    virtual EStatus GetStatus() override;
    virtual bool Wait(std::function<bool()> cancelado) override;
    virtual std::shared_ptr<api::IEsperaAudio> WaitAsync(std::function<bool()> cancelado,
                                                         std::function<void(bool)> fim) override;

private:
    EStatus m_status = PARADO;
    bool m_mute = false;
};

} // namespace simulador
