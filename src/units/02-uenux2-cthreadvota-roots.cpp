// Roots: vota::CThreadVota::StartTick (target fn 700) is called on the CThreadEleitor and CThreadOperador
// singletons by 16 target functions; two are reconstructed (fn 10798, unit 119's slot 4, and fn 7028, unit 97's
// CVotacaoStateAudio::StartState), the others not. Address-taken from a static constructor (as in
// 06-ecourna-api-compression-roots.cpp) so the link keeps it out of line.
// CThreadVota::StopTick (fn 422) has 23 callers in the target; two are reconstructed (fn 10799, unit 119's slot 3, and
// fn 7022, unit 97's CVotacaoStateAudio::FinishState): ParaDoisTicks stands for the others (4454, 7010, 10451, ...).
// CThreadVota::AddTick(const std::chrono::milliseconds&) (fn 4640) has two callers in the target, fns 1285 and 5979;
// unit 97 reconstructs 1285, and TickDeTempo stands for 5979. CThreadVota::AddStoppedTick (fn 807) has 11, of which unit
// 97's fn 1785 calls it twice: DoisTicksParados stands for the other ten (652, 1165, 2740, 2880, ...), which still wait.
// CTickManager::AddStoppedTick (fn 5452) has fn 807 and fn 5947, not reconstructed: TickParado stands for 5947.
// CTickManager::AddTick (fn 3644) and StopTick (fn 5451)
// have all their target callers in the link (4640, 5452 and unit 119's slot 2, which holds CThreadVota::AddTick inlined;
// 422 and 5452). Each stand-in adds a constant to an argument, so no two are alike, and the census pairs none with a
// target function.
// The target's callers of api::CWait's ctor (fn 5447) use the object after constructing it, so the ctor keeps its
// `this` result (binaryen's dead-argument pass drops it when no caller reads it): EsperaUsando stands for them.
// Compiled as uenux2 code.
#include <cstddef>

#include "api/util/cwait.h"

extern "C" {
void five700_root_0(int, int) __asm__("_ZN4vota11CThreadVota9StartTickEh");
void w02_para_thread(void*, int) __asm__("_ZN4vota11CThreadVota8StopTickEh");
int w02_adiciona_tempo(void*, const long long*) __asm__(
    "_ZN4vota11CThreadVota7AddTickERKNSt3__26chrono8durationIxNS1_5ratioILx1ELx1000EEEEE");
int w02_adiciona_parado_thread(void*, int) __asm__("_ZN4vota11CThreadVota14AddStoppedTickEm");
int w02_adiciona_parado(void*, int) __asm__("_ZN3api12CTickManager14AddStoppedTickEm");
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

// stands for fn 5979
__attribute__((noinline)) int TickDeTempo(void* thread, long long milissegundos)
{
    const long long tempo = milissegundos + 2;
    return w02_adiciona_tempo(thread, &tempo);
}

// stands for fn 807's callers
__attribute__((noinline)) int DoisTicksParados(void* thread, int milissegundos)
{
    return w02_adiciona_parado_thread(thread, milissegundos) + w02_adiciona_parado_thread(thread, milissegundos + 3);
}

// stands for fn 5947
__attribute__((noinline)) int TickParado(void* ticks, int milissegundos)
{
    return w02_adiciona_parado(ticks, milissegundos + 4);
}

struct SFive700Roots {
    SFive700Roots()
    {
        five700_sink = reinterpret_cast<void*>(&five700_root_0);
        five700_sink = reinterpret_cast<void*>(&EsperaUsando);
        five700_sink = reinterpret_cast<void*>(&ParaDoisTicks);
        five700_sink = reinterpret_cast<void*>(&TickDeTempo);
        five700_sink = reinterpret_cast<void*>(&DoisTicksParados);
        five700_sink = reinterpret_cast<void*>(&TickParado);
    }
} five700_roots;

} // namespace
