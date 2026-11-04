// Roots: keep the vtables of vota::CRetirarMR (@1542676) and comum's four menu items (@1550780 to @1550888) in the
// skeleton link the way the target reaches their slots: only through the vtable, which the classes' constructors store.
// CRetirarMR's constructor is inlined into its GetInst, whose caller (fn 2291) is not reconstructed.
// vota::CMostraQRCodeCertificado's vtable (@1542480) needs no line: its GetInst is inlined into
// CMostraQRCodeBU::ProcessInput (fn 12051, unit 37), which stores its vptr. vota::CQuerImprimirBU's vtable needs no
// line: its GetInst is inlined into CInicioBU::StartState (fn 12062, unit 104), which stores its vptr.
// vota::CLimiteCopiasBUAtingido's vtable needs no line: its GetInst is inlined into
// CVerificaQtdBUsAdicionais::StartState (fn 12023, unit 185), which stores its vptr. Comum's items are built by fn
// 6599, which stores each comum vptr and then the vota item's (unit 102's roots keep the vota items' vtables). Taking
// each vtable's address from a static constructor puts their slots in the table, as the target has them. The six
// vota::CLogVota members of this unit (fns 1127, 4551, 4556, 2495, 4563 and 4557, in app/vota/log/clogvota.cpp) have
// direct call sites in the target, two or more each (ledger/callgraph.tsv; 4557's two are both in fn 12081), so
// binaryen keeps them out of line; 4551, 4556, 4563 and 4557 have them in the link from their written callers (12077,
// 12078, 12081, 12027, 12082), and so has 2495 (10466, 10473, 10477 and 10485, unit 282), and the stand-ins below give
// the others theirs, each standing for the callers it names, and go when those callers are in splat/matched.txt or
// written in the link. Declared through asm labels, so this TU needs no uenux2 header; compiled as app code.
extern "C" {
int w156_logvota_getinst(void) __asm__("_ZN4vota8CLogVota7GetInstEv");
void w156_loga_imprimindo_relatorio(int, int, unsigned char) __asm__(
    "_ZN4vota8CLogVota23LogaImprimindoRelatorioEN5comum13ERelatoriosUEEh");
void w156_imprime_bu(unsigned char, int) __asm__("_ZN4vota13CImprimindoBU9ImprimeBUEhNS_16PrintMessageModeE");
extern const char w156_vt_cretirarmr[] __asm__("_ZTVN4vota10CRetirarMRE");
extern const char w156_vt_comum_estadourna[] __asm__("_ZTVN5comum22CItemImprimeEstadoUrnaE");
extern const char w156_vt_comum_listaeleitores[] __asm__("_ZTVN5comum26CItemImprimeListaEleitoresE");
extern const char w156_vt_comum_parametrosurna[] __asm__("_ZTVN5comum19CItemParametrosUrnaE");
extern const char w156_vt_comum_versoespacotes[] __asm__("_ZTVN5comum19CItemVersoesPacotesE");
}

namespace {

const void* volatile w156_sink;
volatile int w156_n;

// Stands for the printing states' slots that call CLogVota::LogaImprimindoRelatorio (fn 1127) and still wait: 12065,
// 12068, 12071 and 12074 (11852, 11855 and 11991, unit 104's, and 12077, 12078 and 12081 are in the link), each with a
// report and a copy number of its own.
__attribute__((noinline)) int ImprimeRelatorios(int n)
{
    int log = w156_logvota_getinst();
    w156_loga_imprimindo_relatorio(log, 3, 1);
    w156_loga_imprimindo_relatorio(log, n, n + 2);
    return n + 79;
}

// Stands for CImprimirBUOutrasObrigatorias::StartState (fn 12065, pending in unit 104), the one target caller of
// vota::CImprimindoBU::ImprimeBU (fn 2890) not in the link (CImprimindoBU's StartState and ProcessInput, fns 12078 and
// 12077, and CEmitirMaisBU::ProcessInput, fn 12081, are). The callers pass the copy number 1 or a computed one, and the
// mode 0 (12077, 12078, 12081) or 1 (12065), so the two calls vary both and binaryen folds neither into the body.
__attribute__((noinline)) int ImprimeBUs(int n)
{
    w156_imprime_bu(1, 0);
    w156_imprime_bu(static_cast<unsigned char>(n + 1), 1);
    return n * 7 + 97;
}

struct SW156Roots {
    SW156Roots()
    {
        w156_n = ImprimeRelatorios(w156_n);
        w156_n = ImprimeBUs(w156_n);
        w156_sink = w156_vt_cretirarmr;
        w156_sink = w156_vt_comum_estadourna;
        w156_sink = w156_vt_comum_listaeleitores;
        w156_sink = w156_vt_comum_parametrosurna;
        w156_sink = w156_vt_comum_versoespacotes;
    }
} w156_roots;

} // namespace
