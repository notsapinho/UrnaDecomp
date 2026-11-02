// Roots of src/units/152-uenux2-app-vota-operador-estados.mk: keep its functions in the skeleton link the way the target
// keeps them.
//
// - The vtables of the seven states, and with them every slot: each is referenced in the target only by its class's
//   constructor, inlined into the function that creates the singleton (not reconstructed: the fragment names them).
//   Taking the vtables' addresses keeps every slot, as unit 142's roots do.
// - vota::IIniciaJustificativa's constructor (target fn 3624) has two direct callers in the target, fns 10631 and 10635,
//   which build the derived states and use the `this` it returns. Two noinline callers stand in for them and use that
//   result; their bodies differ from each other and from every target function, one adding to the result and one to
//   the address (unit 71's shape). Its vptr store keeps the class's vtable.
// - vota::CLogVota::LogaAudioDesativadoFimVotacao (fn 4529, callers 10435 and 10646) and LogaSuspensaoAbortada (fn
//   4535, callers 10407 and 10420): two call sites each, so that binaryen keeps both out of line as the target does.
//   Two noinline stand-ins call 4529 for its two callers, one of them with an offset address; the first also calls
//   4535 for 10420, the caller that waits: 10407 (CSuspensaoAutomaticaEleitor::ProcessInput) is in the link.
//
// Declared through asm labels with the object's signatures (a constructor returns `this`), so this TU needs no uenux2
// header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char csuspensaoautomaticaeleitor_vt[] __asm__("_ZTVN4vota27CSuspensaoAutomaticaEleitorE");
extern const char cperguntaeleitorvotando_vt[] __asm__("_ZTVN4vota23CPerguntaEleitorVotandoE");
extern const char cdesabilitaaudioeleitor_vt[] __asm__("_ZTVN4vota23CDesabilitaAudioEleitorE");
extern const char cperguntafilaeleitorvazia_vt[] __asm__("_ZTVN4vota25CPerguntaFilaEleitorVaziaE");
extern const char chorariovotacaoterminou_vt[] __asm__("_ZTVN4vota23CHorarioVotacaoTerminouE");
extern const char cinspecionaurna_vt[] __asm__("_ZTVN4vota15CInspecionaUrnaE");
extern const char chabilitaaudioeleitor_vt[] __asm__("_ZTVN4vota21CHabilitaAudioEleitorE");
int w3624_root_0(int, const void*) __asm__("_ZN4vota20IIniciaJustificativaC2EPNS_22IConfirmaJustificativaE");
void w4529_root_0(void*) __asm__("_ZN4vota8CLogVota29LogaAudioDesativadoFimVotacaoEv");
void w4535_root_0(void*) __asm__("_ZN4vota8CLogVota21LogaSuspensaoAbortadaEv");
}

namespace {

__attribute__((noinline)) int ConstroiIniciaJustificativa(int estado, const void* confirma)
{
    return w3624_root_0(estado, confirma) + 4;
}

__attribute__((noinline)) int ConstroiIniciaJustificativaMembro(int bloco, const void* confirma)
{
    return w3624_root_0(bloco + 16, confirma);
}

__attribute__((noinline)) void LogaFimEAbortada(char* log)
{
    w4529_root_0(log);
    w4535_root_0(log);
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
        estados152_sink = cdesabilitaaudioeleitor_vt;
        estados152_sink = cperguntafilaeleitorvazia_vt;
        estados152_sink = chorariovotacaoterminou_vt;
        estados152_sink = cinspecionaurna_vt;
        estados152_sink = chabilitaaudioeleitor_vt;
        estados152_sink = reinterpret_cast<const void*>(&ConstroiIniciaJustificativa);
        estados152_sink = reinterpret_cast<const void*>(&ConstroiIniciaJustificativaMembro);
        estados152_sink = reinterpret_cast<const void*>(&LogaFimEAbortada);
        estados152_sink = reinterpret_cast<const void*>(&LogaFimDeslocado);
    }
} estados152_roots;

} // namespace
