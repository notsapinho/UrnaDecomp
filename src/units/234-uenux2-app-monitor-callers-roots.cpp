// Roots: give the members fragment 234 adds to units 35, 119 and 04 the call sites the target gives them, while their
// callers are not written.
//
// comum::FormataTamanho (fn 1947) has three direct callers in the target: vota::CThreadMonitor::Run (fn 10226, slot 2,
// a trap in unit 116), which calls it four times, comum::IInterfaceInit::MontarMRSemHabilitar (fn 5896, not written),
// which calls it once, and vota::CLogVota::LogaQuantidade (fn 3268, written): Tamanhos stands for 10226 and 5896.
//
// vota::CLogVota::LogaQuantidade (fn 3268) has one direct caller in the target, fn 10226, which calls it three times:
// Quantidades stands for it with two calls.
//
// ecourna::app::dados::asn::FormataHora (fn 2686) has one direct caller in the target, vota::CImpressaoPU::StartState
// (fn 11902, a trap in unit 176), which calls it four times: Horas stands for it with two calls.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
// The strings FormataTamanho returns through a pointer are left as they are, as nothing calls these.
extern "C" {
void w234_tamanho(void* resultado, unsigned long tamanho) __asm__("_ZN5comum14FormataTamanhoEm");
void w234_quantidade(void* log, const void* quantidade) __asm__(
    "_ZN4vota8CLogVota14LogaQuantidadeERKNSt3__24pairINS1_12basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEyEE");
void w234_hora(void* resultado, const void* dataHora) __asm__(
    "_ZN7ecourna3app5dados3asn11FormataHoraERKN5boost10posix_time5ptimeE");
}

namespace {

const void* volatile app_monitor_callers_sink;

// stands for fns 10226 and 5896 (3268 is in the link)
__attribute__((noinline)) int Tamanhos(unsigned long livre, unsigned long usado)
{
    char texto[12];
    char outro[12];
    w234_tamanho(texto, livre);
    w234_tamanho(outro, usado - livre);
    return texto[11] + outro[11] * 3;
}

// stands for fn 10226
__attribute__((noinline)) void Quantidades(void* log, const void* total, const void* livre)
{
    w234_quantidade(log, total);
    w234_quantidade(log, livre);
}

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
        app_monitor_callers_sink = reinterpret_cast<const void*>(&Tamanhos);
        app_monitor_callers_sink = reinterpret_cast<const void*>(&Quantidades);
        app_monitor_callers_sink = reinterpret_cast<const void*>(&Horas);
    }
} app_monitor_callers_roots;

} // namespace
