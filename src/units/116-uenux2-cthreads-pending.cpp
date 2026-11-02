// Pending members of unit 116's vota threads, each a slot of a vtable the unit emits (src/units/116-uenux2-cthreads.mk).
// What each waits for:
// - vota::CThreadVota::TrataErro(const CError&) 7710 (slot 3), 2317 B, and TrataErro(const std::exception&) 7709 (slot
//   4), 2883 B: the unnamed callees 1695, 1696, 3336, 4633, 5568 and 5569 (5566 is
//   api::CApplication::EnterLoopDoingNothing, unit 171). The first is the class's key function, so CThreadVota's
//   vtable, typeinfo and D2 are emitted in this object, and move to cthreadvota.cpp when it lands. Read, not written:
//   4633 shows the "URNA ELETRÔNICA INOPERANTE" screen with a LED, its api::CMTFormBuilder cleared in place (the
//   remainder units 104 and 142 record); 3336 stores 1 in the byte @1832936, which 14 other target functions load
//   (`grep -rlE 'i32\.const 1832936($|[^0-9])' build/out/splat/pieces/asm`), 4662 among them, which tests it before
//   throwing the api::CUeDesligandoError fn 1685 builds (both unit 205's, which names the byte
//   vota::CSincronizaVota::s_urnaDesligando); 5568 builds
//   libc++'s std::async state for a lambda of api::CApplication::ShowExceptionMsg (its vptr) and throws "thread
//   constructor failed".
// - vota::CThreadMonitor::Run 10226 (slot 2), 7171 B: its records name VotacaoSuspensa, MonitorFoneOuvido,
//   VerificaErroCriticoFlash, VerificaErroCriticoKbdTE, LogaEspaco, LogaStatusRedeAcBateria and
//   CMonitoraAlimentacao::GetInst and VerificaAlimentacao, all inlined there, and IInterfaceInit::LogDiskInfo
//   (iinterfaceinit.cpp:285) and CLogComum's LogaSuspensoMonitoramenteRepeticao and LogaTipoBateria (clogcomum.cpp:136
//   to 158). Its callees 5453 and 5454 (unit 32, written) wait for libc++'s __space (4677), and 1947 (a size formatter,
//   "{}.{} GB" to "{} B"), 3268, 3336, 5895 and 10224 are not written.
// - vota::CThreadEleitor::Run 7061 (slot 2), 4119 B: fns 2450 and 3844, and ProcessaEventos 4349 (written in
//   cthreadeleitor.cpp, not matched: the fragment says why). 7061's records all belong to code inlined from
//   cajusteinicial.cpp, so its stub sat there, and that file's stub-only state is unchanged by this trap's taking the stub.
// - vota::CThreadEleitor::ParaOutrasThreads 7030 (slot 5), 18 B: `IExecucaoVota::GetInst().ParaThreadsOperadorMonitor();`
//   (slot 6, the call at vtable + 24; fragment 165 writes CExecucaoVota's, fn 10232), which needs GetInst, fn 3594,
//   record iexecucaovota.cpp:74, 1923 B, not written.
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/monitor/cthreadmonitor.h"

namespace vota {

void CThreadVota::TrataErro(const ecourna::api::exception::CError&)
{
    __builtin_trap();
}

void CThreadVota::TrataErro(const std::exception&)
{
    __builtin_trap();
}

void CThreadEleitor::Run()
{
    __builtin_trap();
}

void CThreadEleitor::ParaOutrasThreads()
{
    __builtin_trap();
}

void CThreadMonitor::Run()
{
    __builtin_trap();
}

} // namespace vota
