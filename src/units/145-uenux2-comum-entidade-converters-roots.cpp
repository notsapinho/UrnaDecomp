// Roots: keep unit 145's two converters in the skeleton link the way the target keeps them. In the target each
// converter's vtable is data whose DoConverte/DoDesconverte slots put the bodies in the table, and no function calls
// either directly. The functions that store the vptrs are not reconstructed: fn 11582 stores
// comum::asn::CConversorVersoesArquivos's (@1599296), and fn 7787 comum::asn::CConversorEntidadePartidos's (@1561344).
// So rooting the vtables keeps the same set.
// comum::asn::CConversorCabecalhoEntidade needs no root: fn 11458 stores its vptr.
// Declared through asm labels, so this TU needs no uenux2 or ASN.1 header and instantiates nothing.
extern "C" {
extern const char w145_versoes_vt[] __asm__("_ZTVN5comum3asn25CConversorVersoesArquivosE");
extern const char w145_partidos_vt[] __asm__("_ZTVN5comum3asn26CConversorEntidadePartidosE");
}

namespace {

const void* volatile w145_sink;

struct SEntidadeConvertersRoots {
    SEntidadeConvertersRoots()
    {
        w145_sink = w145_versoes_vt;
        w145_sink = w145_partidos_vt;
    }
} w145_roots;

} // namespace
