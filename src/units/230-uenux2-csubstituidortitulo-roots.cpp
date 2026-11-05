// Roots of unit 230: callers that stand for target functions not reconstructed, so that binaryen keeps the unit's
// out-of-line functions and unit 123's new CRelUtil members out of line, as the target does (each has more than one
// direct caller there: awk -F'\t' '$2==<index>' ledger/callgraph.tsv). They declare what they call through __asm__
// labels with the object's signatures, so the rule needs no header.
// - w230_titulos_local stands for fn 12110, which calls the overload without the UF (fn 5584); its other caller,
//   fn 5591, is in the link.
// - w230_abertura stands for fn 12110, which calls CRelUtil::ImprimeAberturaFechamento (fn 3688); its other caller,
//   fn 12105 (fragment 372's, two calls), is in the link, and the call that stood for it went.
// w230_titulos_local calls twice, with arguments the target's callers do not fold.
extern "C" {
void crelutil_imprime_titulos_local(int builder, int titulos) __asm__(
    "_ZN5comum8CRelUtil14ImprimeTitulosERN3api17CPaperFormBuilderERKNSt3__26vectorIN7ecourna3app5dados16CTituloRelatorioENS4_"
    "9allocatorIS9_EEEE");
void crelutil_imprime_abertura(int builder, int abertura, int fechamento) __asm__(
    "_ZN5comum8CRelUtil25ImprimeAberturaFechamentoERN3api17CPaperFormBuilderERKNS1_9CDateTimeES6_");
}

namespace {

__attribute__((noinline)) void w230_titulos_local(int builder, int titulos, int outros)
{
    crelutil_imprime_titulos_local(builder, titulos);
    crelutil_imprime_titulos_local(builder, outros);
}

__attribute__((noinline)) void w230_abertura(int builder, int abertura, int fechamento)
{
    crelutil_imprime_abertura(builder + 4, fechamento, abertura);
}

void (*volatile w230_sink3)(int, int, int);

struct SW230Roots {
    SW230Roots()
    {
        w230_sink3 = w230_titulos_local;
        w230_sink3 = w230_abertura;
    }
} w230_roots;

} // namespace
