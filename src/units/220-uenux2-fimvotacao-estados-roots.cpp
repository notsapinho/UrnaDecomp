// Roots of unit 220: the call sites the target gives the functions below, whose target callers are not in the link.
// binaryen inlines a function with one call site (docs/reference/facts/tool-traps.md X1), and each of these has two
// or more direct callers in the target (ledger/callgraph.tsv), so the stand-ins give them two call sites each. Each
// stand-in names the target callers it stands for, and goes when they are in splat/matched.txt or written in the link.
// Declared through asm labels, so this TU needs no uenux2 header; compiled as app code.
extern "C" {
int w220_gerarelatorios_getinst(void) __asm__("_ZN4vota15CGeraRelatorios7GetInstEv");
int w220_copiaresultado_getinst(void) __asm__("_ZN4vota21CCopiaResultadoParaMR7GetInstEv");
long long w220_diferenca(int, int) __asm__("_ZNK3api9CDateTimemiERKS0_");
}

namespace {

volatile int w220_n;

// Stands for the other caller of two GetInst, vota::CCopiaResultadoParaMR's (fn 6174) and vota::CGeraRelatorios's
// (fn 6084), whose first, vota::CAjusteInicial::StartState (fn 7160, unit 329), is in the link:
// CGravaResultado::StartState (fn 12098, CCopiaResultadoParaMR's) and CGeraBU::StartState (fn 12110, pending here,
// CGeraRelatorios's). The calls of vota::CGeraBU's (fn 6129) went: its target callers, 7160 and fn 7481 (unit 104's
// CAguardaMensagem::ProcessKey), are in the link.
__attribute__((noinline)) int ChamaEstadosEncerramentoOutros(int n)
{
    return w220_gerarelatorios_getinst() * 7 + w220_copiaresultado_getinst() + n;
}

// The stand-ins for vota::AdicionaCabecalhoTesteTeclado (fn 3054, app/vota/eleitor/comum/ctelasvota.cpp) and
// vota::testeteclado::CEsperaRetestar::GetInst (fn 5936) went: every target caller of each is in the link (3054's
// 5936, 11804, 11809 and 11805, unit 217's, written; 5936's 11809 and 11812).

// Stands for fn 13012, a text callback not written, the other caller of api::CDateTime::operator- (fn 5471) beside
// CEsperaRetestar's (fn 11826, written).
__attribute__((noinline)) int DiferencaDatas(int a, int b)
{
    return static_cast<int>(w220_diferenca(a, b) >> 3) + 31;
}

struct SW220Roots {
    SW220Roots()
    {
        w220_n = ChamaEstadosEncerramentoOutros(w220_n);
        w220_n = DiferencaDatas(w220_n, w220_n + 12);
    }
} w220_roots;

} // namespace
