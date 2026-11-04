// Roots: keep the vtables of comum's four menu items (@1550780 to @1550888) in the skeleton link the way the target
// reaches their slots: only through the vtable, which the classes' constructors store. vota::CRetirarMR's vtable
// (@1542676) needs no line now: its constructor is inlined into its GetInst (fn 2291), which the print states'
// StartState (fns 12065, 12068, 12071 and 12074) call.
// vota::CMostraQRCodeCertificado's vtable (@1542480) needs no line: its GetInst is inlined into
// CMostraQRCodeBU::ProcessInput (fn 12051, unit 37), which stores its vptr. vota::CQuerImprimirBU's vtable needs no
// line: its GetInst is inlined into CInicioBU::StartState (fn 12062, unit 104), which stores its vptr.
// vota::CLimiteCopiasBUAtingido's vtable needs no line: its GetInst is inlined into
// CVerificaQtdBUsAdicionais::StartState (fn 12023, unit 185), which stores its vptr. Comum's items are built by fn
// 6599, which stores each comum vptr and then the vota item's (unit 102's roots keep the vota items' vtables). Taking
// each vtable's address from a static constructor puts their slots in the table, as the target has them. The six
// vota::CLogVota members of this unit (fns 1127, 4551, 4556, 2495, 4563 and 4557, in app/vota/log/clogvota.cpp) have
// direct call sites in the target, two or more each (ledger/callgraph.tsv; 4557's two are both in fn 12081), so
// binaryen keeps them out of line; all six have them in the link from their written callers: 4551, 4556, 4563 and
// 4557 from 12077, 12078, 12081, 12027 and 12082, 2495 from 10466, 10473, 10477 and 10485 (unit 282), and 1127 from
// the printing states 11852, 11855, 11991, 12065, 12068, 12071, 12074, 12077, 12078 and 12081, so no stand-in is
// left. Declared through asm labels, so this TU needs no uenux2 header; compiled as app code.
extern "C" {
extern const char w156_vt_comum_estadourna[] __asm__("_ZTVN5comum22CItemImprimeEstadoUrnaE");
extern const char w156_vt_comum_listaeleitores[] __asm__("_ZTVN5comum26CItemImprimeListaEleitoresE");
extern const char w156_vt_comum_parametrosurna[] __asm__("_ZTVN5comum19CItemParametrosUrnaE");
extern const char w156_vt_comum_versoespacotes[] __asm__("_ZTVN5comum19CItemVersoesPacotesE");
}

namespace {

const void* volatile w156_sink;

struct SW156Roots {
    SW156Roots()
    {
        w156_sink = w156_vt_comum_estadourna;
        w156_sink = w156_vt_comum_listaeleitores;
        w156_sink = w156_vt_comum_parametrosurna;
        w156_sink = w156_vt_comum_versoespacotes;
    }
} w156_roots;

} // namespace
