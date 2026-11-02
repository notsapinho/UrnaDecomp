// Roots of unit 230: callers that stand for target functions not reconstructed, so that binaryen keeps the unit's
// out-of-line functions and unit 123's new CRelUtil members out of line, as the target does (each has more than one
// direct caller there: awk -F'\t' '$2==<index>' ledger/callgraph.tsv). They declare what they call through __asm__
// labels with the object's signatures, so the rule needs no header.
// - w230_titulos stands for fns 1543 and 5579, which call CRelUtil::ImprimeTitulos with the UF (fn 3689); its third
//   caller, fn 5584, is written (crelutil.cpp).
// - w230_titulos_local stands for fns 5591 and 12110, which call the overload without the UF (fn 5584).
// - w230_abertura stands for fns 12105 and 12110, which call CRelUtil::ImprimeAberturaFechamento (fn 3688).
// Each calls twice, with arguments the target's callers do not fold.
extern "C" {
void crelutil_imprime_titulos(int builder, int titulos, int uf) __asm__(
    "_ZN5comum8CRelUtil14ImprimeTitulosERN3api17CPaperFormBuilderERKNSt3__26vectorIN7ecourna3app5dados16CTituloRelatorioENS4_"
    "9allocatorIS9_EEEERKNS4_12basic_stringIcNS4_11char_traitsIcEENSA_IcEEEE");
void crelutil_imprime_titulos_local(int builder, int titulos) __asm__(
    "_ZN5comum8CRelUtil14ImprimeTitulosERN3api17CPaperFormBuilderERKNSt3__26vectorIN7ecourna3app5dados16CTituloRelatorioENS4_"
    "9allocatorIS9_EEEE");
void crelutil_imprime_abertura(int builder, int abertura, int fechamento) __asm__(
    "_ZN5comum8CRelUtil25ImprimeAberturaFechamentoERN3api17CPaperFormBuilderERKNS1_9CDateTimeES6_");
}

namespace {

__attribute__((noinline)) void w230_titulos(int builder, int titulos, int uf, int outra)
{
    crelutil_imprime_titulos(builder, titulos, uf);
    crelutil_imprime_titulos(builder, titulos, outra);
}

__attribute__((noinline)) void w230_titulos_local(int builder, int titulos, int outros)
{
    crelutil_imprime_titulos_local(builder, titulos);
    crelutil_imprime_titulos_local(builder, outros);
}

__attribute__((noinline)) void w230_abertura(int builder, int abertura, int fechamento)
{
    crelutil_imprime_abertura(builder, abertura, fechamento);
    crelutil_imprime_abertura(builder, fechamento, abertura);
}

void (*volatile w230_sink4)(int, int, int, int);
void (*volatile w230_sink3)(int, int, int);

struct SW230Roots {
    SW230Roots()
    {
        w230_sink4 = w230_titulos;
        w230_sink3 = w230_titulos_local;
        w230_sink3 = w230_abertura;
    }
} w230_roots;

} // namespace
