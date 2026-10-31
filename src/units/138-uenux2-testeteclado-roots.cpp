// Roots: keep unit 138's classes in the skeleton link the way the target keeps them.
//
// vota::testeteclado::CPreZeresima, CRetomada and CEsperaRetestar, vota::CAplicacaoEncerrada and
// vota::CVerificaHorarioZeresima are reached only through their vtables: the target's constructors that store them are
// inlined into their GetInst (fns 5947, 3877, 5936) or into the callers 11914 and 7160, none reconstructed. Taking the
// vtables' address keeps every slot, vota::testeteclado::CBase's StartState (fn 11875, slot 2 of the first two) and the
// destructors among them (fns 1559, 5946, 785, 1560).
//
// vota::CReinicioVotacao::GetInst (fn 5938) has two direct callers in the target (ledger/callgraph.tsv): 11829,
// CRetomada's slot 12, in the link, and 11830, its slot 11, pending. The noinline stand-in calls it once for 11830, so it
// has two call sites and binaryen does not inline it; it adds an offset to its argument, so its body is no target
// function's. It goes when 11830 is in the link. GetInst stores its class's vtable.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cprezeresima_vt[] __asm__("_ZTVN4vota12testeteclado12CPreZeresimaE");
extern const char cretomada_vt[] __asm__("_ZTVN4vota12testeteclado9CRetomadaE");
extern const char cesperaretestar_vt[] __asm__("_ZTVN4vota12testeteclado15CEsperaRetestarE");
extern const char caplicacaoencerrada_vt[] __asm__("_ZTVN4vota19CAplicacaoEncerradaE");
extern const char cverificahorariozeresima_vt[] __asm__("_ZTVN4vota24CVerificaHorarioZeresimaE");
int w5938_getinst(void) __asm__("_ZN4vota16CReinicioVotacao7GetInstEv");
}

namespace {

__attribute__((noinline)) int ChamaReinicioVotacao(int n)
{
    return w5938_getinst() + (n + 138);
}

const void* volatile testeteclado_sink;

struct STesteTecladoRoots {
    STesteTecladoRoots()
    {
        testeteclado_sink = cprezeresima_vt;
        testeteclado_sink = cretomada_vt;
        testeteclado_sink = cesperaretestar_vt;
        testeteclado_sink = caplicacaoencerrada_vt;
        testeteclado_sink = cverificahorariozeresima_vt;
        testeteclado_sink = reinterpret_cast<const void*>(&ChamaReinicioVotacao);
    }
} testeteclado_roots;

} // namespace
