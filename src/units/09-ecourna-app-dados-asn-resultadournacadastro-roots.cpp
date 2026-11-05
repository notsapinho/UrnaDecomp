// Roots: keep what the app/dados/asn/resultadournacadastro converters call in the skeleton link the way the target keeps
// it. Declared through asm labels, so this TU needs no ecourna or ASN.1 header and instantiates nothing.
extern "C" {
int rrucconv_apresentacao_ctor(int, int, int) __asm__("_ZN7ecourna3app5dados24CApresentacaoFotoEleitorC1ENS2_7EEstadoENS2_10EResultadoE");
}

namespace {

const void* volatile rrucconv_sink;

// CApresentacaoFotoEleitor's constructor: binaryen folds it into fn 1081 with other two-word constructors (8 callers);
// alone it has one caller (9087) and would be inlined.
__attribute__((noinline)) int UsaApresentacao(int obj, int estado) { return rrucconv_apresentacao_ctor(obj, estado, estado + 2) + 7; }
// CBaseType<unsigned short, 0, 999, 38>'s constructor (TScoreHabilitacao, fn 2850) needs no stand-in: its two target
// callers, 9066 and comum's 11616 (unit 122's), are in the link.

struct SRucConvRoots {
    SRucConvRoots()
    {
        rrucconv_sink = reinterpret_cast<const void*>(&UsaApresentacao);
    }
} rrucconv_roots;

} // namespace
