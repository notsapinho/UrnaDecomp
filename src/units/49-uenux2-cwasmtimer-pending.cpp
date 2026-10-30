// Pending members: the simulador::CWasmTimer member src/uenux2/mock/app/simulador/wasm/cwasmtimer.cpp does not hold
// yet. The vtable, which the destructor's TU emits (the destructor is the key function), needs it defined; its body
// is NOT the target's, it traps. Target function: Start 7918 (vtable slot 2), with the callback it hands to
// emscripten_async_call, 7909 (table slot 838: `wasm-objdump -x -j Elem target/vota_web_wasm.wasm` prints
// `elem[838] = ref.func:7909`; no stub, its group is libc++), which re-arms itself the same way, so the two land
// together. Written as below in cwasmtimer.cpp, with Call, Schedule and Fire declared private in the class, both are
// the target's once re-pointed, but nothing names 7909: it has no record, RTTI or vtable slot, its only referrer is
// 7918, which splat/symbol_addrs.txt names by `vtable` evidence (that kind casts no `table` vote), and neither pairs in
// the census (their callee 137, `_Znwm`, is not the target's body in our link, so their depth-2 fingerprints differ).
// So 7918 stays `unresolved` on its slot constant and 7909 `no-candidate`. With a scratch symbol file that names 7909,
// `pnpm wasm splat-remap` prints IDENTICAL for both against unit 49's link. The source (names chosen, as in
// cwasmtimer.h):
//
//     // what a pending emscripten_async_call carries: the state, and the generation it was scheduled for
//     struct Call {
//         std::shared_ptr<State> state;
//         std::uint64_t generation;
//     };
//
//     static void Schedule(const std::shared_ptr<State>& state, std::uint64_t generation);
//     static void Fire(void* arg);
//
//     void CWasmTimer::Start()
//     {
//         Stop();
//         m_state->running = true;
//         Schedule(m_state, ++m_state->generation);
//     }
//
//     void CWasmTimer::Schedule(const std::shared_ptr<State>& state, std::uint64_t generation)
//     {
//         emscripten_async_call(&CWasmTimer::Fire, new Call{state, generation}, state->interval);
//     }
//
//     void CWasmTimer::Fire(void* arg)
//     {
//         const std::unique_ptr<Call> call(static_cast<Call*>(arg));
//         const std::shared_ptr<State>& state = call->state;
//         if (state->running && state->generation == call->generation) {
//             state->callback();
//             if (state->running && state->generation == call->generation)
//                 Schedule(state, call->generation);
//         }
//     }
//
// (cwasmtimer.cpp then includes <emscripten.h>; Schedule is inlined into both and has no function of its own.) Move
// Start into cwasmtimer.cpp with them when 7909 can be named; delete this file with it.
#include "uenux2/mock/app/simulador/wasm/cwasmtimer.h"

namespace simulador {

void CWasmTimer::Start()
{
    __builtin_trap();
}

} // namespace simulador
