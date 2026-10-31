// Roots: vota::CThreadVota::StartTick (target fn 700) is called on the CThreadEleitor and CThreadOperador
// singletons from 16 sites in vota TUs not reconstructed yet. Address-taken from a static constructor (as in
// 06-ecourna-api-compression-roots.cpp) so the link keeps it out of line.
// CThreadVota::StopTick (fn 422) has 23 callers in the target, one of them reconstructed (fn 10799, unit 119's slot 3):
// ParaDoisTicks stands for the others (4454, 7010, 7022, 10451, ...), so it stays out of line. Fn 5452, not written,
// calls CTickManager::AddTick (fn 3644) and StopTick (fn 5451), and fn 4640 AddTick: TickParado stands for them, so each
// keeps a second caller beside unit 119's slot 2 (CThreadVota::AddTick, inlined) and fn 422. Each stand-in adds 1 to an
// argument, and the census pairs neither with a target function.
// The target's callers of api::CWait's ctor (fn 5447) use the object after constructing it, so the ctor keeps its
// `this` result (binaryen's dead-argument pass drops it when no caller reads it): EsperaUsando stands for them.
// Compiled as uenux2 code.
#include <cstddef>

#include "api/util/cwait.h"

extern "C" {
void five700_root_0(int, int) __asm__("_ZN4vota11CThreadVota9StartTickEh");
void w02_para_thread(void*, int) __asm__("_ZN4vota11CThreadVota8StopTickEh");
int w02_adiciona(void*, int) __asm__("_ZN3api12CTickManager7AddTickEm");
void w02_para(void*, int) __asm__("_ZN3api12CTickManager8StopTickEh");
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

// stands for fns 5452 and 4640
__attribute__((noinline)) int TickParado(void* ticks, int milissegundos)
{
    const int id = w02_adiciona(ticks, milissegundos);
    w02_para(ticks, id + 1);
    return id;
}

struct SFive700Roots {
    SFive700Roots()
    {
        five700_sink = reinterpret_cast<void*>(&five700_root_0);
        five700_sink = reinterpret_cast<void*>(&EsperaUsando);
        five700_sink = reinterpret_cast<void*>(&ParaDoisTicks);
        five700_sink = reinterpret_cast<void*>(&TickParado);
    }
} five700_roots;

} // namespace
