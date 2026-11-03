// Roots: give the members fragment 234 adds to units 35, 119 and 04 the call sites the target gives them, while their
// callers are not written. comum::FormataTamanho (fn 1947) takes nothing here: its three direct callers in the target,
// vota::CThreadMonitor::Run (fn 10226, unit 116's), comum::IInterfaceInit::MontarMRSemHabilitar (fn 5896, unit 35's)
// and vota::CLogVota::LogaQuantidade (fn 3268), are in the link.
//
// ecourna::app::dados::asn::FormataHora (fn 2686) has one direct caller in the target, vota::CImpressaoPU::StartState
// (fn 11902, a trap in unit 176), which calls it four times: Horas stands for it with two calls.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
// The strings FormataHora returns through a pointer are left as they are, as nothing calls these.
extern "C" {
void w234_hora(void* resultado, const void* dataHora) __asm__(
    "_ZN7ecourna3app5dados3asn11FormataHoraERKN5boost10posix_time5ptimeE");
}

namespace {

const void* volatile app_monitor_callers_sink;

// stands for fn 11902
__attribute__((noinline)) int Horas(const void* inicio, const void* fim)
{
    char texto[12];
    char outro[12];
    w234_hora(texto, inicio);
    w234_hora(outro, fim);
    return texto[11] - outro[11] * 5;
}

struct SAppMonitorCallersRoots {
    SAppMonitorCallersRoots()
    {
        app_monitor_callers_sink = reinterpret_cast<const void*>(&Horas);
    }
} app_monitor_callers_roots;

} // namespace
