// Roots: keep GetInst of the states of unit 104 (src/units/104-uenux2-app-vota-estados.mk) in the skeleton link the way
// the target keeps them.
//
// Each is called directly in the target, from two to ten callers (ledger/callgraph.tsv), few of them in the link
// (in parentheses below; 10791, 11794, 2895, 10317 and 10383 are units 119's, 142's and 135's), and binaryen
// inlines a function with one call site. So one noinline stand-in calls each twice, which is
// one caller that calls it twice (src/units/README.md "Companion files"). It adds the results, so binaryen keeps every
// result (the target's wasm type is ()->(i32), and (i32)->(i32) for fn 1280), and its body is no target function's. A
// line goes when every target caller it stands for is in the link, and stays while some still wait, the callers already
// in the link in parentheses (src/units/README.md "Companion files"). The target callers each pair stands for:
//
// 5984: 12134 (7160 is in the link); 5983: 12105 (7160 is in the link); 1280: 11869 (11834, 11838, 11848, 11881,
// 11902, 11905, 11908, 11911 and 11927 are in the link); 5954: 11888 (11881 is); 2288: 11884, 11888, 11891
// (11896, and 11876, unit 150's, are in the link). 1280 and 5954 are called once each, for the one caller each still
// waits for: the second calls stood for 11881, written since (unit 104's). The
// pairs for 6037, 5973, 3865 and 3864 went: their target callers, 7160 (vota::CAjusteInicial::StartState, unit 329) and
// 12077, 11939, 11870 and 11871, and 11848 and 11858, are in the link. The pairs for 5942 and 5941 went: their target
// callers, 11848 with 11852 and with 11845, are in the link; so did 5943's, whose callers 11834 and 11855 are, 5342's,
// whose callers 10737 and 10791 are, 2729's, whose callers 2895, 10317, 10383 and 6011 (the body of
// comum::CRegistrarMesarios's and CMesarioRegistrado's ProcessInput, units 247 and 279) are, 3879's, whose callers
// 12023, 12030 and 12077 are, 1337's, whose callers 4449, 6058, 7198, 7221, 11794, 11987, 11988 and 11994 are, 5428's,
// whose callers 10217 and 10734 are, 5421's, whose callers 10626 and 10627 (unit 278's) are, 5985's, whose callers
// 12065 and 12068 are, 1536's, whose callers 10500 (unit 239's), 6015, 10466, 10473, 10477, 10485, 10489 and 10593 are,
// 4433's, whose callers 7481 (vota::CAguardaMensagem::ProcessKey) and 11994 are, 5383's, whose callers 10313 and
// 10316 are, and 1897's, whose callers 10404, 10419 and 10425 (units 152 and 142) are.
//
// vota::CMaisInformacoes::GetInst (fn 1280) takes the state to go back to: its target callers pass 0 and their own
// `this`, so one call passes 0 and the other the stand-in's argument, and binaryen folds no constant into the body.
// vota::CAguardaMensagem::GetInst (fn 1337) is in the target's table (slot 125), so its address is taken; its call
// pair went with its callers.
//
// Declared through asm labels with the wasm-level signatures, so this TU needs no uenux2 header and instantiates
// nothing; compiled with APP_CXXFLAGS.
extern "C" {
int w1337_getinst(void) __asm__("_ZN4vota16CAguardaMensagem7GetInstEv");
int w5984_getinst(void) __asm__("_ZN4vota29CImprimirBUOutrasObrigatorias7GetInstEv");
int w5983_getinst(void) __asm__("_ZN4vota9CInicioBU7GetInstEv");
int w1280_getinst(int) __asm__("_ZN4vota16CMaisInformacoes7GetInstEPN5comum9CAppStateE");
int w5954_getinst(void) __asm__("_ZN4vota31CMenuFiltrarCandidatosPorNumero7GetInstEv");
int w2288_getinst(void) __asm__("_ZN4vota25CMenuVisualizarCandidatos7GetInstEv");
}

namespace {

__attribute__((noinline)) int ChamaGetInstDosEstados(int n)
{
    int total = 0;
    total += w5984_getinst() + w5984_getinst();
    total += w5983_getinst() + w5983_getinst();
    total += w1280_getinst(n);
    total += w5954_getinst();
    total += w2288_getinst() + w2288_getinst();
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
