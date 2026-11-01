// Roots: keep vota::CEleitorVotando::ChamaEstadoProximoCargo (target fn 4459) in the skeleton link the way the target
// keeps it. Its two direct callers in the target, CEleitorVotando's NeedChangeState (fn 7352, slot 3) and its slot 2 (fn
// 7377, which holds IniciaCiclo's records), are not reconstructed; with no caller wasm-ld drops it, and with one binaryen
// inlines it. Precisa stands for fn 7352 and Inicia for fn 7377, each calling it once, with bodies no target function
// has. Each goes when the caller it stands for is in the link.
//
// CEleitorVotando's vtable is referenced in the target only by its constructor, inlined into GetInst (fn 3229, not
// reconstructed); taking the vtable's address keeps every slot, ProcessInput and ProcessTick (fns 7345 and 7349) among
// them.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char celeitorvotando_vt[] __asm__("_ZTVN4vota15CEleitorVotandoE");
void w197_chama_estado(void* eleitor) __asm__("_ZN4vota15CEleitorVotando23ChamaEstadoProximoCargoEv");
}

namespace {

const void* volatile celeitorvotando_sink;

// stands for fn 7352
__attribute__((noinline)) int Precisa(void* eleitor)
{
    w197_chama_estado(eleitor);
    return 197;
}

// stands for fn 7377
__attribute__((noinline)) void Inicia(void* eleitor, int* contador)
{
    w197_chama_estado(eleitor);
    *contador += 2;
}

struct SCEleitorVotandoRoots {
    SCEleitorVotandoRoots()
    {
        celeitorvotando_sink = celeitorvotando_vt;
        celeitorvotando_sink = reinterpret_cast<const void*>(&Precisa);
        celeitorvotando_sink = reinterpret_cast<const void*>(&Inicia);
    }
} celeitorvotando_roots;

} // namespace
