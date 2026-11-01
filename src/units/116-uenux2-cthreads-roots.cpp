// Roots: reach unit 116's singletons the way the target does.
// - CThreadOperador::GetInst (target fn 270, 54 callers, among them 652, 2740, 3887): its real callers here are 10225,
//   and unit 119's 3887 and slots 10785, 10788, 10798 and 10799; Stop stands for the other callers' flag store.
// - CThreadMonitor::GetInst (fn 1898, callers 10203, 10232, 10234, 10235, 10236): 10203 is its one real caller here.
// - CEstadoAudio::GetInst (fn 509, 17 callers, among them 1455, 4349, 7028): unit 97's 7028 is its one real caller
//   here, and two stand-ins stand for the others.
// binaryen inlines a function with one call site, so each gets a second one. CThreadEleitor::GetInst (316) needs no
// root: 10203 and 10225 call it. Each stand-in's body is its own: no target function holds these calls.
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/operador/cthreadoperador.h"

namespace {

__attribute__((noinline)) int ParaOperadorEMonitor()
{
    vota::CThreadOperador::GetInst().Stop();
    return vota::CEstadoAudio::GetInst().Ativo();
}

__attribute__((noinline)) int ValorDoAudio()
{
    return vota::CEstadoAudio::GetInst().Ativo() ? 3 : 5;
}

const void* volatile w116_sink;

struct SW116Roots {
    SW116Roots()
    {
        w116_sink = reinterpret_cast<const void*>(&ParaOperadorEMonitor);
        w116_sink = reinterpret_cast<const void*>(&ValorDoAudio);
    }
} w116_roots;

} // namespace
