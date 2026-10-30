// Roots: keep unit 49's simulador::CWasmTimer in the skeleton link, reached the way the target reaches it.
// The target builds its timers in one place, slot 0 of simulador::CWasmTimerScheduler (fn 7871, not reconstructed):
// a std::make_shared<CWasmTimer> into which binaryen inlined the constructor (its own frame sits inside 7871). That
// make_shared brings std::__shared_ptr_emplace<CWasmTimer>, whose __on_zero_shared (fn 7839) calls the destructor
// (fn 3347) directly, its second caller beside the deleting destructor (fn 7926), and the vtable the constructor
// stores, through which the target reaches every other member.
// This one stand-in does the same make_shared, so the constructor has one caller here too; it takes the interval and
// the callback by value and moves the callback, so its body is not 7871's (which copies a callback it gets by
// reference). It includes the class header and instantiates make_shared, as the roots of units 14, 27 and 28 do: the
// control block's members come from this object until the scheduler is reconstructed. Address-taken from a static
// constructor; compiled with APP_CXXFLAGS.
#include <chrono>
#include <functional>
#include <memory>
#include <utility>

#include "uenux2/mock/app/simulador/wasm/cwasmtimer.h"

namespace {

__attribute__((noinline)) std::shared_ptr<api::ITimer> CriaTimer(long long intervalo, std::function<void()> callback)
{
    return std::make_shared<simulador::CWasmTimer>(std::chrono::milliseconds(intervalo), std::move(callback));
}

void* volatile w3347_sink;

struct SW3347Roots {
    SW3347Roots()
    {
        w3347_sink = reinterpret_cast<void*>(&CriaTimer);
    }
} w3347_roots;

} // namespace
