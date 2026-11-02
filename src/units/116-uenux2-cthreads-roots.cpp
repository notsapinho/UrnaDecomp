// Roots: reach unit 116's singletons the way the target does.
// - CThreadOperador::GetInst (target fn 270, 54 callers, among them 652, 2740, 3887): its real callers here are 10225,
//   10219, 10220, 10232 to 10236, unit 119's 3887 and slots 10785, 10788, 10798 and 10799, and unit 165's 5343; Stop
//   stands for the other callers' flag store. CThreadMonitor::GetInst (fn 1898) needs none: its five callers are in
//   the link.
// - CEstadoAudio::GetInst (fn 509, 17 callers, among them 1455, 4349, 7028): unit 97's 7028 and this unit's 4349 are
//   its real callers here, and two stand-ins stand for the others.
// - CThreadEleitor::ProcessaEventos (fn 4349): of its two target callers, vota::CExecucaoVotaCooperativa's slot 7 (fn
//   7823, unit 165) is in the link and CThreadEleitor's Run (fn 7061, this unit's pending file) is a trap, so
//   EventosEleitor stands for 7061 and calls it twice.
// binaryen inlines a function with one call site, so each gets a second one. CThreadEleitor::GetInst (316) needs no
// root: 10203 and 10225 call it. Each stand-in's body is its own: no target function holds these calls.
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/cthreadeleitor.h"
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

__attribute__((noinline)) int EventosEleitor()
{
    vota::CThreadEleitor& eleitor = vota::CThreadEleitor::GetInst();
    return eleitor.ProcessaEventos() + 2 * eleitor.ProcessaEventos();
}

const void* volatile w116_sink;

struct SW116Roots {
    SW116Roots()
    {
        w116_sink = reinterpret_cast<const void*>(&ParaOperadorEMonitor);
        w116_sink = reinterpret_cast<const void*>(&ValorDoAudio);
        w116_sink = reinterpret_cast<const void*>(&EventosEleitor);
    }
} w116_roots;

} // namespace
