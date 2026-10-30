#include "cwasmnullsound.h"

namespace simulador {

void CWasmNullSound::Pause() {}

void CWasmNullSound::Play(const std::string& arquivo) {}

void CWasmNullSound::Play(std::shared_ptr<api::CWavFile> wav) {}

void CWasmNullSound::Stop() {}

void CWasmNullSound::Mute(bool mute) {}

api::ISound::EStatus CWasmNullSound::GetStatus()
{
    return PARADO;
}

} // namespace simulador
