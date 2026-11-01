// Pending members of unit 116's vota threads, each a slot of a vtable the unit emits (src/units/116-uenux2-cthreads.mk).
// What each waits for:
// - vota::CThreadVota::TrataErro(const CError&) 7710 (slot 3), 2317 B, and TrataErro(const std::exception&) 7709 (slot 4),
//   2883 B: the unnamed callees 1695, 1696, 3336, 4633, 5566, 5568 and 5569. The first is the class's key function, so
//   CThreadVota's vtable, typeinfo and D2 are emitted in this object, and move to cthreadvota.cpp when it lands.
// - vota::CThreadEleitor::Run 7061 (slot 2), 4119 B: fns 2450, 3844 and ProcessarEntrada 4349 (record
//   cthreadeleitor.cpp:134). 7061's records all belong to code inlined from cajusteinicial.cpp, so its stub sat there, and
//   that file's stub-only state is unchanged by this trap's taking the stub.
// - vota::CThreadEleitor::ParaOutrasThreads 7030 (slot 5), 18 B: `IExecucaoVota::GetInst().Slot6();`, which needs fn 3594,
//   record iexecucaovota.cpp:74, 1923 B, not written. Slot 6 of vota::IExecucaoVota is the call at vtable + 24.
// - vota::CThreadOperador::Run 10204 (slot 2), 1873 B, record cthreadoperador.cpp:87: fns 3593, 3966, 5343, 5450 and
//   5908 to 5911, comum::CAppStateContext's members among them (fragment 168 matches its 3842, 3843 and 3844); its
//   other callees, 180, 203, 1694 and 3842, match.
// - vota::CThreadMonitor::Run 10226 (slot 2), 7171 B: its records name VotacaoSuspensa, MonitorFoneOuvido,
//   VerificaErroCriticoFlash, VerificaErroCriticoKbdTE, LogaEspaco, LogaStatusRedeAcBateria and
//   CMonitoraAlimentacao::GetInst and VerificaAlimentacao, all inlined there.
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/monitor/cthreadmonitor.h"
#include "app/vota/operador/cthreadoperador.h"

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

void CThreadOperador::Run()
{
    __builtin_trap();
}

void CThreadMonitor::Run()
{
    __builtin_trap();
}

} // namespace vota
