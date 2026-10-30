// Roots: keep comum::asn::CConversorPartido in the skeleton link the way the target keeps it. Its users are not
// reconstructed yet; in the target the converter's vtable (@1561260) is data whose DoConverte/DoDesconverte slots put
// the bodies in the table (fns 11460, 11459) and nothing calls them directly, so rooting the vtable keeps the same set.
// Declared through an asm label, so this TU needs no uenux2 or ASN.1 header and instantiates nothing.
extern "C" {
extern const char partido_vt[] __asm__("_ZTVN5comum3asn17CConversorPartidoE");
}

namespace {

const void* volatile partido_sink;

struct SPartidoRoots {
    SPartidoRoots() { partido_sink = partido_vt; }
} partido_roots;

} // namespace
