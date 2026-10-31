// Roots: keep api::CTime's constructor from a string (target fn 3643) and CTime::operator-(int) (target fn 3641) in the
// skeleton link. The target calls each directly, never through the table (ledger/callgraph.tsv): 3643 from 1713, 5475 and
// 7787, of which cdatetime.cpp reconstructs 5475 (unit 125); 3641 from 7160, 7306 and 10710, none reconstructed yet. One
// noinline caller of 3643 (for 1713 and 7787) and two of 3641 give each more than one call site, so binaryen keeps its body
// out of line as the target does. The constructor from hours, minutes and seconds (fn 3642) needs no stand-in now:
// cdatetime.cpp's ConvertFromLocalTime (5476) and operator+= (2233) call it, two of its three target callers (the third is
// 2725). Neither does api::IsValidTime (fn 5449): its two target callers are 3643, in ctime.cpp, and the check 5475 inlines,
// which cdatetime.cpp defines. Every caller reads the result, as the target's do (3641's callers use the returned word, 5475
// stores the word 3643 leaves there), so binaryen's dead-argument elimination drops no return value, and each passes its
// arguments through, so it folds no parameter in. operator+= and operator-= are deliberately not rooted: the target has no
// body of either, operator- holds both (-= inlined by the compiler, += by binaryen into its only caller); neither is
// EncodeTime(const std::string &), which the compiler inlines into 3643. The callers are address-taken from a static
// constructor. Declared through asm labels with the wasm-level signatures (a std::string passed by reference as its
// address); compiled as uenux2 code.
extern "C" {
int w3641_root_0(const int*, int) __asm__("_ZNK3api5CTimemiEi");
int* w3643_root_0(int*, const void*) __asm__("_ZN3api5CTimeC1ERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

__attribute__((noinline)) int HoraAntes(const int* hora, int segundos)
{
    return w3641_root_0(hora, segundos);
}

__attribute__((noinline)) int MinutosAntes(const int* hora, int minutos)
{
    return w3641_root_0(hora, minutos * 60);
}

__attribute__((noinline)) int SegundosDoTexto(const void* hora)
{
    int tempo;
    return *w3643_root_0(&tempo, hora);
}

void* volatile w3642_sink;

struct SW3642Roots {
    SW3642Roots()
    {
        w3642_sink = reinterpret_cast<void*>(&HoraAntes);
        w3642_sink = reinterpret_cast<void*>(&MinutosAntes);
        w3642_sink = reinterpret_cast<void*>(&SegundosDoTexto);
    }
} w3642_roots;

} // namespace
