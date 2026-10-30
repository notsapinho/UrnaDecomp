#pragma once

#include <functional>
#include <memory>
#include <string>

#include "api/audio/isound.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::ISound, vtable @1530360), the sound that plays nothing. Its
// object is 8 bytes, the vptr and ISound's volume: simulador's init (fn 8302) allocates 8 bytes and stores the vptr and
// 9 at +4. Its vtable holds its own members in slots 0, 1, 3, 5, 6 and 7:
// 218, 425, 8487, 218, 425 and 340, shared empty bodies but for fn 8487, the one that has to release its by-value
// std::shared_ptr. Slots 2, 4, 8 and 9 (fns 8479, 8472, 8461, 8450) hold ISound's own bodies and are inherited here. The
// implicit destructors are the shared 174 and 144. The member names are ISound's (api/audio/isound.h says which are
// chosen).
class CWasmNullSound : public api::ISound {
public:
    virtual void Pause() override;
    virtual void Play(const std::string& arquivo) override;
    virtual void Play(std::shared_ptr<api::CWavFile> wav) override;
    virtual void Stop() override;
    virtual void Mute(bool mute) override;
    virtual EStatus GetStatus() override;
};

} // namespace simulador
