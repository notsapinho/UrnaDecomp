// Roots: keep api::CFormBuilder::GetLabeledKeyPos (target fn 5544) in the skeleton link. The target calls it from one
// function, 3678 (not reconstructed yet), at two call sites (ledger/callgraph.tsv lists 3678 twice), and never through
// the table (no elem slot holds it); two call sites keep binaryen from inlining it. PosicoesTecla reproduces 3678's
// two calls: the same area and alignment in both, passed through so that binaryen's dead-argument elimination folds
// neither, and the vertical offsets 0 and 21 that 3678 passes. It is address-taken from a static constructor.
// Declared through an asm label with the wasm-level signature (the SPoint result through its address first);
// compiled as uenux2 code.
extern "C" {
void w5544_root_0(void*, const void*, int, int) __asm__("_ZN3api12CFormBuilder16GetLabeledKeyPosERKNS_5SRectENS_14ETextAlignmentEs");
}

namespace {

struct SPosicao {
    short x;
    short y;
};

__attribute__((noinline)) int PosicoesTecla(const void* area, int alinhamento)
{
    SPosicao rotulo;
    SPosicao legenda;
    w5544_root_0(&rotulo, area, alinhamento, 0);
    w5544_root_0(&legenda, area, alinhamento, 21);
    return rotulo.x + legenda.y;
}

void* volatile w5544_sink;

struct SW5544Roots {
    SW5544Roots()
    {
        w5544_sink = reinterpret_cast<void*>(&PosicoesTecla);
    }
} w5544_roots;

} // namespace
