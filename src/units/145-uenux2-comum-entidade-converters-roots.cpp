// Roots: keep unit 145's comum::asn::CConversorEntidadePartidos in the skeleton link the way the target keeps it. In
// the target the converter's vtable is data whose DoConverte/DoDesconverte slots put the bodies in the table, and no
// function calls either directly. The function that stores the vptr (@1561344), fn 7787, is not reconstructed, so
// rooting the vtable keeps the same set. comum::asn::CConversorVersoesArquivos's vptr (@1599296) is stored by its
// GravaArquivo, which fn 11582 holds inlined (unit 122), in the link.
// comum::asn::CConversorCabecalhoEntidade needs no root: fn 11458 stores its vptr.
// Declared through asm labels, so this TU needs no uenux2 or ASN.1 header and instantiates nothing.
extern "C" {
extern const char w145_partidos_vt[] __asm__("_ZTVN5comum3asn26CConversorEntidadePartidosE");
}

namespace {

const void* volatile w145_sink;

struct SEntidadeConvertersRoots {
    SEntidadeConvertersRoots()
    {
        w145_sink = w145_partidos_vt;
    }
} w145_roots;

} // namespace
