#include "cwasmwebsound.h"

#include "api/audio/alsa/cwavfile.h"

// the JavaScript side (EM_JS, src/web/wasm_shim.cpp, whose generated declarations take an int for every pointer: the
// same wasm type)
extern "C" {
void js_wasm_web_sound_play_wav(const void* header, int headerSize, const void* data, int dataSize, int volume,
                                int modo);
void js_wasm_web_sound_pause();
void js_wasm_web_sound_stop();
void js_wasm_web_sound_mute(int mute);
int js_wasm_web_sound_get_status();
}

namespace simulador {

void CWasmWebSound::Pause()
{
    m_status = PAUSADO;
    js_wasm_web_sound_pause();
}

void CWasmWebSound::Play(const std::string& arquivo)
{
    if (!m_mute)
        m_status = PARADO;
}

void CWasmWebSound::Play(const std::string& arquivo, EModo modo)
{
    if (!m_mute)
        m_status = PARADO;
}

void CWasmWebSound::Play(std::shared_ptr<api::CWavFile> wav)
{
    Play(wav, INTERROMPE);
}

void CWasmWebSound::Play(std::shared_ptr<api::CWavFile> wav, EModo modo)
{
    if (m_mute) {
        m_status = PARADO;
        return;
    }
    const uebyte* dados = wav ? wav->GetDados() : nullptr;
    const uedword tamanho = wav ? wav->GetTamanhoDados() : 0;
    if (dados == nullptr || tamanho == 0) {
        m_status = PARADO;
        return;
    }
    m_status = TOCANDO;
    js_wasm_web_sound_play_wav(&wav->GetAudio(), sizeof(api::CWavAudio), dados, tamanho, m_volume * 5 + 50,
                               modo != INTERROMPE);
}

void CWasmWebSound::Stop()
{
    m_status = PARADO;
    js_wasm_web_sound_stop();
}

void CWasmWebSound::Mute(bool mute)
{
    m_mute = mute;
    js_wasm_web_sound_mute(mute);
}

api::ISound::EStatus CWasmWebSound::GetStatus()
{
    return static_cast<EStatus>(js_wasm_web_sound_get_status());
}

bool CWasmWebSound::Wait(std::function<bool()> cancelado)
{
    if (cancelado && cancelado())
        return false;
    return GetStatus() != TOCANDO;
}

} // namespace simulador
