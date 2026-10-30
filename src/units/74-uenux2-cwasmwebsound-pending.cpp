// Pending members: the simulador::CWasmWebSound member src/uenux2/mock/app/simulador/wasm/cwasmwebsound.cpp does not
// hold yet. The vtable, which cwasmwebsound.cpp emits (Pause, the first member the class declares, is its key
// function), needs it defined; its body is NOT the target's, it traps. Target function: WaitAsync 9515 (vtable slot 9,
// 995 B). When the first function says the wait is cancelled, or the browser's status is not 1 (then it calls the
// second function with true), it returns a std::make_shared<api::CEsperaAudio>, the class ISound::WaitAsync's default
// builds (fn 8450); otherwise it moves both functions into a std::map under a new id (the int at 1528464, incremented),
// calls js_wasm_web_sound_wait_async and returns a std::make_shared of the file-static
// simulador::(anonymous namespace)::CEsperaAudioWasm (vtable @1528660, whose members 9459, 9448, 2680 and 9445 are not
// reconstructed either). The map is an unnamed .bss object (1832664: zeros, which only a name places), so it waits for
// that name and for the CEsperaAudio and CEsperaAudioWasm classes.
#include "uenux2/mock/app/simulador/wasm/cwasmwebsound.h"

namespace simulador {

std::shared_ptr<api::IEsperaAudio> CWasmWebSound::WaitAsync(std::function<bool()> cancelado,
                                                            std::function<void(bool)> fim)
{
    __builtin_trap();
}

} // namespace simulador
