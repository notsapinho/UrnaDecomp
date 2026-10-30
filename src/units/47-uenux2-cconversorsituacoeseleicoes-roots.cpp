// Roots: keep comum::asn::CConversorSituacoesEleicoes in the skeleton link the way the target keeps it. Its users are
// not reconstructed yet; in the target the converter's vtable (@1570516) is data whose DoConverte/DoDesconverte slots
// put the bodies in the table (fns 11360, 11361, table slots 2765, 2766; neither has a direct caller), so rooting the
// vtable keeps the same set.
// Declared through an asm label, so this TU needs no uenux2 or ASN.1 header and instantiates nothing.
extern "C" {
extern const char situacoeseleicoes_vt[] __asm__("_ZTVN5comum3asn27CConversorSituacoesEleicoesE");
}

namespace {

const void* volatile situacoeseleicoes_sink;

struct SSituacoesEleicoesRoots {
    SSituacoesEleicoesRoots() { situacoeseleicoes_sink = situacoeseleicoes_vt; }
} situacoeseleicoes_roots;

} // namespace
