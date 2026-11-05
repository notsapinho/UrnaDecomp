// Roots of unit 354: vota::CTelasVota::CriaTelaMaisInformacoes (target fn 6599) has two direct callers in the target,
// 7787 and 11897 (ledger/callgraph.tsv). 11897, vota::CMaisInformacoes::StartState, is in the link (unit 104's
// cmaisinformacoes.cpp); 7787 is not written. A function with one call site in the link is inlined by binaryen into it,
// so w354_tela stands for 7787's call and gives the function its second call site. It returns a value no target
// function computes. Declared through its __asm__ label with the object's signature: the static member returns a
// std::shared_ptr by value, so it takes the result's address and returns nothing (src/units/README.md "Companion files").
extern "C" void w354_cria_tela_mais_informacoes(void* resultado) __asm__(
    "_ZN4vota10CTelasVota23CriaTelaMaisInformacoesEv");

namespace {

// stands for fn 7787
__attribute__((noinline)) int w354_tela(int n)
{
    alignas(8) char resultado[8];
    w354_cria_tela_mais_informacoes(resultado);
    return n + 354;
}

int (*volatile w354_sink_tela)(int);

struct S354Roots {
    S354Roots() { w354_sink_tela = w354_tela; }
} w354_roots;

} // namespace
