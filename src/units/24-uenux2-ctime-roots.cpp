// Roots: keep the api::CTime constructor from hours, minutes and seconds (target fn 3642) and CTime::operator-(int)
// (target fn 3641) in the skeleton link. The target calls each directly from three functions (3642 from 2233 2725
// 5476, 3641 from 7160 7306 10710, ledger/callgraph.tsv), none reconstructed yet and neither through the table; two
// noinline callers of each give it more than one call site, so binaryen keeps its body out of line as the target
// does. Every caller reads the result, as the target's do (5476 and 2233 load the member through the returned
// `this`), so binaryen's dead-argument elimination drops no return value, and each passes its arguments through, so
// it folds no parameter in. operator+= and operator-= are deliberately not rooted: the target has no body of either,
// operator- holds both (-= inlined by the compiler, += by binaryen into its only caller). The callers are
// address-taken from a static constructor. Declared through asm labels with the wasm-level signatures; compiled as
// uenux2 code.
extern "C" {
int* w3642_root_0(int*, int, int, int) __asm__("_ZN3api5CTimeC1Ehhh");
int w3641_root_0(const int*, int) __asm__("_ZNK3api5CTimemiEi");
}

namespace {

__attribute__((noinline)) int SegundosDaHora(int hora, int minuto, int segundo)
{
    int tempo;
    return *w3642_root_0(&tempo, hora, minuto, segundo);
}

__attribute__((noinline)) int SegundosDoMinuto(int hora, int minuto)
{
    int tempo;
    return *w3642_root_0(&tempo, hora, minuto, 0);
}

__attribute__((noinline)) int HoraAntes(const int* hora, int segundos)
{
    return w3641_root_0(hora, segundos);
}

__attribute__((noinline)) int MinutosAntes(const int* hora, int minutos)
{
    return w3641_root_0(hora, minutos * 60);
}

void* volatile w3642_sink;

struct SW3642Roots {
    SW3642Roots()
    {
        w3642_sink = reinterpret_cast<void*>(&SegundosDaHora);
        w3642_sink = reinterpret_cast<void*>(&SegundosDoMinuto);
        w3642_sink = reinterpret_cast<void*>(&HoraAntes);
        w3642_sink = reinterpret_cast<void*>(&MinutosAntes);
    }
} w3642_roots;

} // namespace
