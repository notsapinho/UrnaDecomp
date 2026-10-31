// Roots: keep the vtables of vota::CLimiteCopiasBUAtingido (@1542828), vota::CMostraQRCodeCertificado (@1542480),
// vota::CQuerImprimirBU (@1542572), vota::CRetirarMR (@1542676) and comum's four menu items (@1550780 to @1550888) in
// the skeleton link the way the target reaches their slots: only through the vtable, which the classes' constructors
// store. The states' constructors are inlined into their GetInst, and none of those four GetInst has a caller here:
// CMostraQRCodeCertificado's only caller is CMostraQRCodeBU::ProcessInput (fn 12051), pending, and the other three are
// not reconstructed (CLimiteCopiasBUAtingido's is inlined into CVerificaQtdBUsAdicionais::StartState, fn 12023,
// CQuerImprimirBU's into CInicioBU::StartState, fn 12062, and CRetirarMR's is fn 2291). Comum's items are built by fn
// 6599, which stores each comum vptr and then the vota item's (unit 102's roots keep the vota items' vtables). Taking
// each vtable's address from a static constructor puts their slots in the table, as the target has them. Declared
// through asm labels, so this TU needs no uenux2 header; compiled as app code.
extern "C" {
int w156_imprimindobu_getinst(void) __asm__("_ZN4vota13CImprimindoBU7GetInstEv");
extern const char w156_vt_climitecopiasbuatingido[] __asm__("_ZTVN4vota23CLimiteCopiasBUAtingidoE");
extern const char w156_vt_cmostraqrcodecertificado[] __asm__("_ZTVN4vota24CMostraQRCodeCertificadoE");
extern const char w156_vt_cquerimprimirbu[] __asm__("_ZTVN4vota15CQuerImprimirBUE");
extern const char w156_vt_cretirarmr[] __asm__("_ZTVN4vota10CRetirarMRE");
extern const char w156_vt_comum_estadourna[] __asm__("_ZTVN5comum22CItemImprimeEstadoUrnaE");
extern const char w156_vt_comum_listaeleitores[] __asm__("_ZTVN5comum26CItemImprimeListaEleitoresE");
extern const char w156_vt_comum_parametrosurna[] __asm__("_ZTVN5comum19CItemParametrosUrnaE");
extern const char w156_vt_comum_versoespacotes[] __asm__("_ZTVN5comum19CItemVersoesPacotesE");
}

namespace {

const void* volatile w156_sink;
volatile int w156_n;

// Stands for vota::CImprimindoBU::GetInst's (fn 5986) two target callers, CQuerImprimirBU::ProcessInput (fn 12034,
// pending here) and CInicioBU::StartState (fn 12062, pending in unit 104): one caller that calls it twice, and adds the
// results and its argument, so binaryen keeps them and its body is no target function's.
__attribute__((noinline)) int ChamaImprimindoBU(int n)
{
    return w156_imprimindobu_getinst() + w156_imprimindobu_getinst() + n;
}

struct SW156Roots {
    SW156Roots()
    {
        w156_n = ChamaImprimindoBU(w156_n);
        w156_sink = w156_vt_climitecopiasbuatingido;
        w156_sink = w156_vt_cmostraqrcodecertificado;
        w156_sink = w156_vt_cquerimprimirbu;
        w156_sink = w156_vt_cretirarmr;
        w156_sink = w156_vt_comum_estadourna;
        w156_sink = w156_vt_comum_listaeleitores;
        w156_sink = w156_vt_comum_parametrosurna;
        w156_sink = w156_vt_comum_versoespacotes;
    }
} w156_roots;

} // namespace
