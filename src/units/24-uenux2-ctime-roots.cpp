// Roots: keep the api::CTime constructors from hours, minutes and seconds (target fn 3642) and from a string (target
// fn 3643), CTime::operator-(int) (target fn 3641) and api::IsValidTime (target fn 5449) in the skeleton link. The
// target calls each directly, never through the table (ledger/callgraph.tsv): 3642 from 2233 2725 5476, 3643 from 1713
// 5475 7787, 3641 from 7160 7306 10710, none reconstructed yet; 5449 from 3643, which ctime.cpp reconstructs, and from
// 5475, which is not. Two noinline callers of each of the first three, and one caller that calls 5449 twice beside
// 3643's call, give each more than one call site, so binaryen keeps its body out of line as the target does. Every
// caller reads the result, as the target's do (5476 and 2233 load the member through the returned `this`, 5475 stores
// the word 3643 leaves there and branches on 5449's result), so binaryen's dead-argument elimination drops no return
// value, and each passes its arguments through, so it folds no parameter in. operator+= and operator-= are
// deliberately not rooted: the target has no body of either, operator- holds both (-= inlined by the compiler, += by
// binaryen into its only caller); neither is EncodeTime(const std::string &), which the compiler inlines into 3643. The
// callers are address-taken from a static constructor. Declared through asm labels with the wasm-level signatures (a
// std::string passed by reference as its address); compiled as uenux2 code.
extern "C" {
int* w3642_root_0(int*, int, int, int) __asm__("_ZN3api5CTimeC1Ehhh");
int w3641_root_0(const int*, int) __asm__("_ZNK3api5CTimemiEi");
int* w3643_root_0(int*, const void*) __asm__("_ZN3api5CTimeC1ERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int w5449_root_0(const void*) __asm__("_ZN3api11IsValidTimeERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
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

__attribute__((noinline)) int SegundosDoTexto(const void* hora)
{
    int tempo;
    return *w3643_root_0(&tempo, hora);
}

__attribute__((noinline)) int MinutosDoTexto(const void* hora)
{
    int tempo;
    return *w3643_root_0(&tempo, hora) / 60;
}

__attribute__((noinline)) int HorasValidas(const void* inicio, const void* fim)
{
    return w5449_root_0(inicio) + w5449_root_0(fim);
}

void* volatile w3642_sink;

struct SW3642Roots {
    SW3642Roots()
    {
        w3642_sink = reinterpret_cast<void*>(&SegundosDaHora);
        w3642_sink = reinterpret_cast<void*>(&SegundosDoMinuto);
        w3642_sink = reinterpret_cast<void*>(&HoraAntes);
        w3642_sink = reinterpret_cast<void*>(&MinutosAntes);
        w3642_sink = reinterpret_cast<void*>(&SegundosDoTexto);
        w3642_sink = reinterpret_cast<void*>(&MinutosDoTexto);
        w3642_sink = reinterpret_cast<void*>(&HorasValidas);
    }
} w3642_roots;

} // namespace
