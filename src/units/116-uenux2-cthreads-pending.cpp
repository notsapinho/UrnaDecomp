// Pending members of unit 116's vota threads, each a slot of a vtable the unit emits (src/units/116-uenux2-cthreads.mk).
// What each waits for:
// - vota::CThreadVota::TrataErro(const CError&) 7710 (slot 3), 2317 B, and TrataErro(const std::exception&) 7709 (slot
//   4), 2883 B. Read, not written: each does nothing once vota::CSincronizaVota::s_urnaDesligando is set (7710 also
//   when the error is an api::CUeDesligandoError, a __dynamic_cast), then stops the other threads (slot 5), calls 4633
//   and 3336, shows the error through code binaryen inlined (a second stack frame of 112 bytes, over 1695, 5569, 1696
//   and 5568) and calls api::CApplication::EnterLoopDoingNothing (5566, unit 171). Of those callees, 3336
//   (CSincronizaVota::MarcaUrnaDesligando, unit 205) and 1696 (api::Join, unit 171) match; 1695 and 5569 (unit 171)
//   are written and not matched, 1695 by one frame offset, 5569 waiting for 1695's name; 4633 and 5568 are not
//   written. 4633 shows the "URNA ELETRÔNICA INOPERANTE" screen with a LED and differs only where it builds its
//   api::CMTFormBuilder, which the target clears in place, the remainder units 104 and 142 record
//   (src/units/02-uenux2-cthreadvota.mk has the measurement). 5568 is api::CApplication::ShowExceptionMsg, whose code
//   after its std::async is not in the target (src/units/171-uenux2-capplication.mk says why that stops it). 7709's
//   inlined code also holds a message extractor (std::regex ".*?\).*?:\d+:-?\d+ - ((.|\n)*)" matched against what()
//   inside a catch (...), the whole text when it does not match) that calls through invoke_*, so it is an
//   -fexceptions TU's code, which uenux2's src/api and src/app files are not (docs/reference/app-flags.md
//   "Exceptions"); not written. The
//   first is the class's key function, so CThreadVota's vtable, typeinfo and D2 are emitted in this object, and move to
//   cthreadvota.cpp when it lands.
// - vota::CThreadMonitor::Run 10226 (slot 2), 7171 B: its records name VotacaoSuspensa, MonitorFoneOuvido,
//   VerificaErroCriticoFlash, VerificaErroCriticoKbdTE, LogaEspaco, LogaStatusRedeAcBateria and
//   CMonitoraAlimentacao::GetInst and VerificaAlimentacao, all inlined there, and IInterfaceInit::LogDiskInfo
//   (iinterfaceinit.cpp:285) and CLogComum's LogaSuspensoMonitoramenteRepeticao and LogaTipoBateria (clogcomum.cpp:136
//   to 158). Its callees 5453 and 5454 (unit 32, written) wait for libc++'s __space (4677), 1947 and 3268
//   (comum::FormataTamanho and vota::CLogVota::LogaQuantidade, fragment 234's) match, and 3336, 5895 and 10224 are
//   not written.
// - vota::CThreadEleitor::Run 7061 (slot 2), 4119 B: fns 2450 and 3844, and ProcessaEventos 4349 (written in
//   cthreadeleitor.cpp, not matched: the fragment says why). 7061's records all belong to code inlined from
//   cajusteinicial.cpp, so its stub sat there, and that file's stub-only state is unchanged by this trap's taking the stub.
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

void CThreadMonitor::Run()
{
    __builtin_trap();
}

} // namespace vota
