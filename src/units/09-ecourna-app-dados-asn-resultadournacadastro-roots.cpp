// Roots: keep what the app/dados/asn/resultadournacadastro converters call in the skeleton link the way the target keeps
// it. Declared through asm labels, so this TU needs no ecourna or ASN.1 header and instantiates nothing.
extern "C" {
int rrucconv_apresentacao_ctor(int, int, int) __asm__("_ZN7ecourna3app5dados24CApresentacaoFotoEleitorC1ENS2_7EEstadoENS2_10EResultadoE");
int rrucconv_score_ctor(int, int) __asm__("_ZN9CBaseTypeItLt0ELt999ELi38EEC2Et");
}

namespace {

const void* volatile rrucconv_sink;

// CApresentacaoFotoEleitor's constructor: binaryen folds it into fn 1081 with other two-word constructors (8 callers);
// alone it has one caller (9087) and would be inlined.
__attribute__((noinline)) int UsaApresentacao(int obj, int estado) { return rrucconv_apresentacao_ctor(obj, estado, estado + 2) + 7; }
// CBaseType<unsigned short, 0, 999, 38>'s constructor (TScoreHabilitacao, fn 2850) has two callers in the target
// (9066 and comum's 11616): a second noinline caller keeps binaryen from inlining it into 9066.
__attribute__((noinline)) int UsaScore(int obj, int valor) { return rrucconv_score_ctor(obj, valor + 3) * 5; }

struct SRucConvRoots {
    SRucConvRoots()
    {
        rrucconv_sink = reinterpret_cast<const void*>(&UsaScore);
        rrucconv_sink = reinterpret_cast<const void*>(&UsaApresentacao);
    }
} rrucconv_roots;

} // namespace
