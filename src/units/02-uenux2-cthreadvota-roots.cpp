// Roots: vota::CThreadVota::StartTick (target fn 700) is called on the CThreadEleitor and CThreadOperador singletons by
// 16 target functions, all in the link (fn 10798, unit 119's slot 4, fns 7028 and 7029, unit 97's
// CVotacaoStateAudio::StartState and ProcessInput, fn 10220, fns 11825 and 11871, unit 138's, and 10468, unit 282's,
// the last, among them), so it needs no stand-in: the address this file took so that the link kept it out of line
// went.
// CThreadVota::StopTick (fn 422) has 23 callers in the target, all but 10451 and 10465 in the link, which ParaDoisTicks
// stands for (fn 10799, unit 119's slot 3, fn 7022, unit 97's CVotacaoStateAudio::FinishState, unit 197's 7337, 7345,
// 7349, 7352 and 4454, unit 97's 7010 and 7029, unit 221's 10452, unit 152's 10404, 10405, 10407, 10408 and 10409,
// unit 161's 10676 and 10678, and 10219, 11790, 11824 and 11868 are linked).
// CThreadVota::AddStoppedTick (fn 807) needs none: of its 11 callers, unit 97's fn 1785 calls it twice, and 1165 and
// 2880 (unit 199), 3229 (unit 197), 5343 (unit 165), 5936 (unit 138), 10409 and 652 (unit 161), 5396 (unit 221), 2740
// (unit 282) and 10440 (unit 152) are linked.
// CTickManager::AddStoppedTick (fn 5452) has fn 807 and fn 5947, both in the link (unit 138 writes 5947).
// CTickManager::GetExpiredTicks (fn 5450) needs no stand-in: its two callers, 4349 and 10204, are unit 116's.
// CThreadVota::AddTick(const std::chrono::milliseconds&) (fn 4640), CTickManager::AddTick (fn 3644) and StopTick
// (fn 5451) have all their target callers in the link (1285, unit 97's, and 5979, unit 61's; 4640, 5452 and unit
// 119's slot 2, which holds CThreadVota::AddTick inlined; 422 and 5452). Each stand-in adds a constant to an
// argument, so no two are alike, and the census pairs none with a target function.
// The target's callers of api::CWait's ctor (fn 5447) use the object after constructing it, so the ctor keeps its
// `this` result (binaryen's dead-argument pass drops it when no caller reads it): EsperaUsando stands for them.
// Compiled as uenux2 code.
#include <cstddef>

#include "api/util/cwait.h"

extern "C" {
void w02_para_thread(void*, int) __asm__("_ZN4vota11CThreadVota8StopTickEh");
}

namespace {

void* volatile five700_sink;

__attribute__((noinline)) void EsperaUsando(size_t milissegundos, void (*usa)(api::CWait&))
{
    api::CWait espera(milissegundos);
    usa(espera);
}

// stands for fn 422's callers other than fn 10799
__attribute__((noinline)) void ParaDoisTicks(void* thread, int id)
{
    w02_para_thread(thread, id);
    w02_para_thread(thread, id + 1);
}

struct SFive700Roots {
    SFive700Roots()
    {
        five700_sink = reinterpret_cast<void*>(&EsperaUsando);
        five700_sink = reinterpret_cast<void*>(&ParaDoisTicks);
    }
} five700_roots;

} // namespace
