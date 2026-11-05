// Roots: keep api::CBmpConversor::VerticalFlip and InvertColors (target fns 3664 and 3663) in the skeleton link. The
// target calls both directly from the same three functions (10316 10451 10465, ledger/callgraph.tsv), none through the
// table; 10316 (unit 135's) and 10465 (unit 282's) are in the link, and the noinline ConverteImagem stands for 10451
// with one call of each (a second stand-in, ConverteLinha, stood for 10316 and went with it). ConverteImagem passes
// every argument through, so binaryen's dead-argument elimination folds none of them in. Its address is taken from a
// static constructor.
// Declared through asm labels with the wasm-level signatures; compiled as uenux2 code.
extern "C" {
void w3664_root_0(int, int, int) __asm__("_ZN3api13CBmpConversor12VerticalFlipEPhii");
void w3663_root_0(int, int, int) __asm__("_ZN3api13CBmpConversor12InvertColorsEPhii");
}

namespace {

__attribute__((noinline)) void ConverteImagem(int dados, int largura, int altura)
{
    w3664_root_0(dados, largura, altura);
    w3663_root_0(dados, largura, altura);
}

void* volatile w3663_sink;

struct SW3663Roots {
    SW3663Roots()
    {
        w3663_sink = reinterpret_cast<void*>(&ConverteImagem);
    }
} w3663_roots;

} // namespace
