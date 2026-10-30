// Roots: keep comum::asn::CConversorHashArquivo in the skeleton link the way the target keeps it. Its users are not
// reconstructed yet; in the target the converter's vtable (@1598992) is data whose DoConverte/DoDesconverte slots put
// the bodies in the table (fns 10267, 10269; table slots 4507, 4508) and no function calls either directly, so rooting
// the vtable keeps the same set.
// Declared through an asm label, so this TU needs no uenux2 or ASN.1 header and instantiates nothing.
extern "C" {
extern const char hasharquivo_vt[] __asm__("_ZTVN5comum3asn21CConversorHashArquivoE");
}

namespace {

const void* volatile hasharquivo_sink;

struct SHashArquivoRoots {
    SHashArquivoRoots() { hasharquivo_sink = hasharquivo_vt; }
} hasharquivo_roots;

} // namespace
