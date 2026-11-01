// Roots: keep comum::servico::CComparecimentoMesarioServico's vtable in the skeleton link the way the target keeps it. The
// target stores its vptr only in the constructor fn 815 inlines (CRegistradorMesario's, not reconstructed), and reaches
// the deleting destructor (fn 10312) only through the vtable. Rooting the vtable keeps it and both destructors in the
// link without a constructor, as unit 66's roots do for the DAO. CJustificadorServico's vtable needs no root: comum::
// CJustificador's constructor (fn 3742) stores its vptr. Declared through an asm label, so this TU needs no uenux2 header
// and instantiates nothing.
extern "C" {
extern const char comparecimentomesarioservico_vt[] __asm__("_ZTVN5comum7servico29CComparecimentoMesarioServicoE");
}

namespace {

const void* volatile r163_sink;

struct SRoots163 {
    SRoots163() { r163_sink = comparecimentomesarioservico_vt; }
} roots163;

} // namespace
