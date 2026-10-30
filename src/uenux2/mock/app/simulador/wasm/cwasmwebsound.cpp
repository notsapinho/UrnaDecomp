#include "cwasmwebsound.h"

#include <map>
#include <utility>

#include "api/audio/alsa/cwavfile.h"
#include "api/audio/cesperaaudio.h"

// the JavaScript side (EM_JS, src/web/wasm_shim.cpp, whose generated declarations take an int for every pointer: the
// same wasm type)
extern "C" {
void js_wasm_web_sound_play_wav(const void* header, int headerSize, const void* data, int dataSize, int volume,
                                int modo);
void js_wasm_web_sound_pause();
void js_wasm_web_sound_stop();
void js_wasm_web_sound_mute(int mute);
int js_wasm_web_sound_get_status();
void js_wasm_web_sound_wait_async(int id);
void js_wasm_web_sound_cancel_wait(int id);
}

namespace simulador {

namespace {

// a wait the browser holds: the two functions WaitAsync was given
struct SEspera {
    std::function<bool()> cancelado;
    std::function<void(bool)> fim;
};

std::map<int, SEspera> s_esperas;
int s_proximaEspera = 1;

class CEsperaAudioWasm final : public api::IEsperaAudio {
public:
    explicit CEsperaAudioWasm(int id) : m_id(id) {}
    virtual ~CEsperaAudioWasm() override { Cancela(); }

    virtual void Cancela() override
    {
        if (!m_cancelada) {
            m_cancelada = true;
            s_esperas.erase(m_id);
            js_wasm_web_sound_cancel_wait(m_id);
        }
    }
    virtual bool Cancelada() override { return m_cancelada; }

private:
    int m_id;
    bool m_cancelada = false;
};

} // namespace

extern "C" int uenux_wasm_web_sound_wait_cancel_requested(int id)
{
    const auto espera = s_esperas.find(id);
    if (espera == s_esperas.end() || !espera->second.cancelado) {
        return 0;
    }
    return espera->second.cancelado();
}

extern "C" void uenux_wasm_web_sound_wait_finished(int id, int terminou)
{
    const auto espera = s_esperas.find(id);
    if (espera == s_esperas.end()) {
        return;
    }
    std::function<void(bool)> fim = std::move(espera->second.fim);
    s_esperas.erase(espera);
    if (fim) {
        fim(terminou != 0);
    }
}

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

std::shared_ptr<api::IEsperaAudio> CWasmWebSound::WaitAsync(std::function<bool()> cancelado,
                                                            std::function<void(bool)> fim)
{
    if (cancelado && cancelado()) {
        auto espera = std::make_shared<api::CEsperaAudio>();
        espera->Cancela();
        return espera;
    }
    if (GetStatus() != TOCANDO) {
        auto espera = std::make_shared<api::CEsperaAudio>();
        if (fim)
            fim(true);
        return espera;
    }
    const int id = s_proximaEspera++;
    s_esperas[id] = SEspera{std::move(cancelado), std::move(fim)};
    js_wasm_web_sound_wait_async(id);
    return std::make_shared<CEsperaAudioWasm>(id);
}

} // namespace simulador
