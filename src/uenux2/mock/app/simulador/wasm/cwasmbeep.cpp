#include "cwasmbeep.h"

#include <utility>
#include <vector>

// the JavaScript side (EM_JS, src/web/wasm_shim.cpp)
extern "C" {
void js_wasm_beep_init();
void js_wasm_beep_set_volume(int volume);
void js_wasm_beep_queue(int frequency, int durationMs);
}

namespace simulador {

CWasmBeep::CWasmBeep()
{
    js_wasm_beep_init();
}

void CWasmBeep::SetVolume(int volume)
{
    js_wasm_beep_set_volume(volume);
}

void CWasmBeep::Beep(int frequency, int duration)
{
    js_wasm_beep_queue(frequency, duration * 10);
}

void CWasmBeep::BeepConfirm(int times)
{
    const std::vector<std::pair<int, int>> tones = api::ConfirmTones();
    if (times <= 0 || tones.empty())
        return;
    for (int i = 0; i < times; ++i) {
        for (const auto& [frequency, duration] : tones)
            Beep(frequency, duration);
    }
}

void CWasmBeep::BeepError()
{
    for (const auto& [frequency, duration] : api::ErrorTones())
        Beep(frequency, duration);
}

void CWasmBeep::BeepAlert()
{
    for (const auto& [frequency, duration] : api::AlertTones())
        Beep(frequency, duration);
}

void CWasmBeep::BeepDiscard()
{
    for (const auto& [frequency, duration] : api::DiscardTones())
        Beep(frequency, duration);
}

void CWasmBeep::BeepKey()
{
    Beep(554, 20);
}

} // namespace simulador
