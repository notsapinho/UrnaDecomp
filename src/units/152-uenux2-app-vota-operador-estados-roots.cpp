// Roots of src/units/152-uenux2-app-vota-operador-estados.mk: keep its functions in the skeleton link the way the target
// keeps them.
//
// - The vtables of five of the seven states, and with them every slot: each is referenced in the target only by its
//   class's constructor, inlined into the function that creates the singleton (not reconstructed: the fragment names
//   them). Taking the vtables' addresses keeps every slot, as unit 142's roots do. vota::CDesabilitaAudioEleitor's and
//   vota::CHorarioVotacaoTerminou's constructors are in the link, inlined into their GetInst (fns 5393 and 5430), which
//   the next item keeps, so no sink keeps those two vtables.
// - The GetInst of those two (fns 5393 and 5430), whose target callers are not in the link: fns 10209 and 10430 call
//   5393, fns 10677 and 10689 call 5430. Each stand-in calls its GetInst twice, so that binaryen keeps it a function of
//   its own; one subtracts the two results and the other adds them, so the two bodies differ.
// - vota::IIniciaJustificativa's constructor (target fn 3624) has two direct callers in the target, fns 10631 and 10635,
//   which build the derived states and use the `this` it returns. 10631 is in the link (unit 104, through
//   vota::CIniciaJustificativa's constructor, unit 243); a noinline caller stands in for 10635 and uses that result,
//   its body no target function's.
// - vota::CLogVota::LogaAudioDesativadoFimVotacao (fn 4529, callers 10435 and 10646): two call sites, so that binaryen
//   keeps it out of line as the target does. Two noinline stand-ins call it for its two callers, one of them with an
//   offset address. LogaSuspensaoAbortada (fn 4535) needs none: both its callers, 10407
//   (CSuspensaoAutomaticaEleitor::ProcessInput) and 10420 (CPerguntaCodigoSuspensao::ProcessInput), are in the link.
//
// Declared through asm labels with the object's signatures (a constructor returns `this`), so this TU needs no uenux2
// header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char csuspensaoautomaticaeleitor_vt[] __asm__("_ZTVN4vota27CSuspensaoAutomaticaEleitorE");
extern const char cperguntaeleitorvotando_vt[] __asm__("_ZTVN4vota23CPerguntaEleitorVotandoE");
extern const char cperguntafilaeleitorvazia_vt[] __asm__("_ZTVN4vota25CPerguntaFilaEleitorVaziaE");
extern const char cinspecionaurna_vt[] __asm__("_ZTVN4vota15CInspecionaUrnaE");
extern const char chabilitaaudioeleitor_vt[] __asm__("_ZTVN4vota21CHabilitaAudioEleitorE");
int w3624_root_0(int, const void*) __asm__("_ZN4vota20IIniciaJustificativaC2EPNS_22IConfirmaJustificativaE");
void w4529_root_0(void*) __asm__("_ZN4vota8CLogVota29LogaAudioDesativadoFimVotacaoEv");
int w5393_root_0() __asm__("_ZN4vota23CDesabilitaAudioEleitor7GetInstEv");
int w5430_root_0() __asm__("_ZN4vota23CHorarioVotacaoTerminou7GetInstEv");
}

namespace {

// Stands for fns 10209 and 10430, the target callers of vota::CDesabilitaAudioEleitor::GetInst (fn 5393).
__attribute__((noinline)) int DesabilitaAudio()
{
    return w5393_root_0() - w5393_root_0();
}

// Stands for fns 10677 and 10689, the target callers of vota::CHorarioVotacaoTerminou::GetInst (fn 5430).
__attribute__((noinline)) int HorarioTerminou()
{
    return w5430_root_0() + w5430_root_0();
}

// Stands for fn 10635.
__attribute__((noinline)) int ConstroiIniciaJustificativa(int estado, const void* confirma)
{
    return w3624_root_0(estado, confirma) + 4;
}

__attribute__((noinline)) void LogaFim(char* log)
{
    w4529_root_0(log);
}

__attribute__((noinline)) void LogaFimDeslocado(char* log)
{
    w4529_root_0(log + 4);
}

const void* volatile estados152_sink;

struct SEstados152Roots {
    SEstados152Roots()
    {
        estados152_sink = csuspensaoautomaticaeleitor_vt;
        estados152_sink = cperguntaeleitorvotando_vt;
        estados152_sink = cperguntafilaeleitorvazia_vt;
        estados152_sink = cinspecionaurna_vt;
        estados152_sink = chabilitaaudioeleitor_vt;
        estados152_sink = reinterpret_cast<const void*>(&ConstroiIniciaJustificativa);
        estados152_sink = reinterpret_cast<const void*>(&LogaFim);
        estados152_sink = reinterpret_cast<const void*>(&LogaFimDeslocado);
        estados152_sink = reinterpret_cast<const void*>(&DesabilitaAudio);
        estados152_sink = reinterpret_cast<const void*>(&HorarioTerminou);
    }
} estados152_roots;

} // namespace
