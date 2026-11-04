// Roots of unit 220: the call sites the target gives the functions below, whose target callers are not in the link.
// binaryen inlines a function with one call site (docs/reference/facts/tool-traps.md X1), and each of these has two
// or more direct callers in the target (ledger/callgraph.tsv), so the stand-ins give them two call sites each. Each
// stand-in names the target callers it stands for, and goes when they are in splat/matched.txt or written in the link.
// Declared through asm labels, so this TU needs no uenux2 header; compiled as app code.
extern "C" {
int w220_gerabu_getinst(void) __asm__("_ZN4vota7CGeraBU7GetInstEv");
int w220_gerarelatorios_getinst(void) __asm__("_ZN4vota15CGeraRelatorios7GetInstEv");
int w220_copiaresultado_getinst(void) __asm__("_ZN4vota21CCopiaResultadoParaMR7GetInstEv");
void w220_cabecalho_teste(int) __asm__("_ZN4vota29AdicionaCabecalhoTesteTecladoERN3api12CFormBuilderE");
int w220_esperaretestar_getinst(void) __asm__("_ZN4vota12testeteclado15CEsperaRetestar7GetInstEv");
long long w220_diferenca(int, int) __asm__("_ZNK3api9CDateTimemiERKS0_");
}

namespace {

volatile int w220_n;

// Stands for the other caller of the GetInst of vota::CGeraBU (fn 6129), vota::CCopiaResultadoParaMR (fn 6174) and
// vota::CGeraRelatorios (fn 6084), whose first, vota::CAjusteInicial::StartState (fn 7160, unit 329), is in the link:
// fn 7481 (CGeraBU's), CGravaResultado::StartState (fn 12098, CCopiaResultadoParaMR's) and CGeraBU::StartState (fn
// 12110, pending here, CGeraRelatorios's).
__attribute__((noinline)) int ChamaEstadosEncerramentoOutros(int n)
{
    return w220_gerarelatorios_getinst() * 7 + w220_copiaresultado_getinst() + w220_gerabu_getinst() * 11 + n;
}

// Stands for two of the four callers of vota::AdicionaCabecalhoTesteTeclado (fn 3054,
// app/vota/eleitor/comum/ctelasvota.cpp): CTesteTeclado's ProcessInput (fn 11804, pending in unit 217) and
// CTesteFalhou's ProcessInput (fn 11809, not written). The other two are in the link: CEsperaRetestar::GetInst (fn 5936)
// and CTesteTeclado::StartState (fn 11805, written in unit 217, not matched).
__attribute__((noinline)) int CabecalhosTesteTeclado(int construtor)
{
    w220_cabecalho_teste(construtor + 12);
    return construtor * 13 + 17;
}

// Stands for the two callers of vota::testeteclado::CEsperaRetestar::GetInst (fn 5936): CTesteFalhou's and
// CEnviarManutencao's ProcessInput (fns 11809 and 11812), whose classes are not written.
__attribute__((noinline)) int ChamaEsperaRetestar(int n)
{
    return w220_esperaretestar_getinst() * 29 + w220_esperaretestar_getinst() + n;
}

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
        w220_n = CabecalhosTesteTeclado(w220_n);
        w220_n = ChamaEsperaRetestar(w220_n);
        w220_n = DiferencaDatas(w220_n, w220_n + 12);
    }
} w220_roots;

} // namespace
