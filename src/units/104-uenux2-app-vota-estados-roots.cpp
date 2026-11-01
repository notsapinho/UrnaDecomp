// Roots: keep GetInst of the states of unit 104 (src/units/104-uenux2-app-vota-estados.mk) in the skeleton link the way
// the target keeps them.
//
// Each is called directly in the target, from two to ten callers (ledger/callgraph.tsv), none of which is reconstructed
// but 10791 (5342's, slot 12 of unit 119's controller), 11794 (1337's, unit 142's) and 2895, 10317 and 10383 (2729's,
// unit 135's), and binaryen inlines a function with one call site. So one noinline stand-in calls each twice, which is
// one caller that calls it twice (src/units/README.md "Companion files"). It adds the results, so binaryen keeps every
// result (the target's wasm type is ()->(i32), and (i32)->(i32) for fn 1280), and its body is no target function's. A
// line goes when every target caller it stands for is in the link, and stays while some still wait, the callers already
// in the link in parentheses (src/units/README.md "Companion files"). The target callers each pair stands for:
//
// 1337: 4449, 6058, 7198, 7221, 11987, 11988, 11994 (11794 is in the link); 4433: 7481, 11994; 6037: 7160, 12077; 3879:
// 12023, 12030, 12077; 5985: 12065, 12068; 5984: 7160, 12134; 5983: 7160, 12105; 5973: 7160 (11939 is in the link);
// 3865: 7160, 11870, 11871; 3864: 7160, 11848, 11858; 1280: 11834, 11838, 11848, 11869, 11881, 11902, 11905, 11908,
// 11911, 11927; 5954: 11881, 11888; 2288: 11876, 11884, 11888, 11891, 11896; 5943: 11834, 11855; 5942: 11848, 11852;
// 5941: 11848 (11845 is in the link); 5428: 10217, 10734; 1536: 6015, 10466, 10473, 10477, 10485, 10489, 10500, 10593;
// 5421: 10626, 10627; 2729: 6011, which still waits (2895, 10317 and 10383 are in the link); 5383: 10313, 10316; 5342:
// 10737 (10791 is in the link); 1897: 10404, 10419, 10425.
//
// vota::CMaisInformacoes::GetInst (fn 1280) takes the state to go back to: its target callers pass 0 and their own
// `this`, so one call passes 0 and the other the stand-in's argument, and binaryen folds no constant into the body.
// vota::CAguardaMensagem::GetInst (fn 1337) is also in the target's table (slot 125), so its address is taken as well.
//
// Declared through asm labels with the wasm-level signatures, so this TU needs no uenux2 header and instantiates
// nothing; compiled with APP_CXXFLAGS.
extern "C" {
int w1337_getinst(void) __asm__("_ZN4vota16CAguardaMensagem7GetInstEv");
int w4433_getinst(void) __asm__("_ZN4vota14CIniciodeCiclo7GetInstEv");
int w6037_getinst(void) __asm__("_ZN4vota15CGravaResultado7GetInstEv");
int w3879_getinst(void) __asm__("_ZN4vota13CEmitirMaisBU7GetInstEv");
int w5985_getinst(void) __asm__("_ZN4vota14CImprimindoBim7GetInstEv");
int w5984_getinst(void) __asm__("_ZN4vota29CImprimirBUOutrasObrigatorias7GetInstEv");
int w5983_getinst(void) __asm__("_ZN4vota9CInicioBU7GetInstEv");
int w5973_getinst(void) __asm__("_ZN4vota19CImprimindoZeresima7GetInstEv");
int w3865_getinst(void) __asm__("_ZN4vota15CInicioZeresima7GetInstEv");
int w3864_getinst(void) __asm__("_ZN4vota30CReinicioComparecimentoMesario7GetInstEv");
int w1280_getinst(int) __asm__("_ZN4vota16CMaisInformacoes7GetInstEPN5comum9CAppStateE");
int w5954_getinst(void) __asm__("_ZN4vota31CMenuFiltrarCandidatosPorNumero7GetInstEv");
int w2288_getinst(void) __asm__("_ZN4vota25CMenuVisualizarCandidatos7GetInstEv");
int w5943_getinst(void) __asm__("_ZN4vota22CDefineRotaPosReinicio7GetInstEv");
int w5942_getinst(void) __asm__("_ZN4vota27CReimprimindoResumoZeresima7GetInstEv");
int w5941_getinst(void) __asm__("_ZN4vota21CReimprimindoZeresima7GetInstEv");
int w5428_getinst(void) __asm__("_ZN4vota18CFimAquisicaoVotos7GetInstEv");
int w1536_getinst(void) __asm__("_ZN4vota26CCancelaHabilitacaoEleitor7GetInstEv");
int w5421_getinst(void) __asm__("_ZN4vota15CProcuraEleitor7GetInstEv");
int w2729_getinst(void) __asm__("_ZN5comum18CPedeTituloMesario7GetInstEv");
int w5383_getinst(void) __asm__("_ZN5comum18CGestorDadoMesario7GetInstEv");
int w5342_getinst(void) __asm__("_ZN4vota17CFinalizaOperador7GetInstEv");
int w1897_getinst(void) __asm__("_ZN4vota20CSincronismoOperador7GetInstEv");
}

namespace {

__attribute__((noinline)) int ChamaGetInstDosEstados(int n)
{
    int total = 0;
    total += w1337_getinst() + w1337_getinst();
    total += w4433_getinst() + w4433_getinst();
    total += w6037_getinst() + w6037_getinst();
    total += w3879_getinst() + w3879_getinst();
    total += w5985_getinst() + w5985_getinst();
    total += w5984_getinst() + w5984_getinst();
    total += w5983_getinst() + w5983_getinst();
    total += w5973_getinst() + w5973_getinst();
    total += w3865_getinst() + w3865_getinst();
    total += w3864_getinst() + w3864_getinst();
    total += w1280_getinst(0) + w1280_getinst(n);
    total += w5954_getinst() + w5954_getinst();
    total += w2288_getinst() + w2288_getinst();
    total += w5943_getinst() + w5943_getinst();
    total += w5942_getinst() + w5942_getinst();
    total += w5941_getinst() + w5941_getinst();
    total += w5428_getinst() + w5428_getinst();
    total += w1536_getinst() + w1536_getinst();
    total += w5421_getinst() + w5421_getinst();
    total += w2729_getinst() + w2729_getinst();
    total += w5383_getinst() + w5383_getinst();
    total += w5342_getinst() + w5342_getinst();
    total += w1897_getinst() + w1897_getinst();
    return total;
}

const void* volatile estados_sink;

struct SEstadosRoots {
    SEstadosRoots()
    {
        estados_sink = reinterpret_cast<const void*>(&ChamaGetInstDosEstados);
        estados_sink = reinterpret_cast<const void*>(&w1337_getinst);
    }
} estados_roots;

} // namespace
