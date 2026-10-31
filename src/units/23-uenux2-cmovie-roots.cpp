// Roots: keep the api::CMovie constructor (target fn 5526) in the skeleton link. The target calls it directly from two
// functions (1593, which inlines api::getResourceMovie and builds the CMovie inside a std::make_shared block, 12 bytes
// past the control block's start; and 8605, simulador::CWasmResource slot 4, written in unit 127) and neither through
// the table (ledger/callgraph.tsv; no elem entry is fn 5526). 8605 is in the link; 1593 is not reconstructed yet, and
// the noinline caller below stands for it, so the constructor keeps two call sites and binaryen keeps its body out of
// line; both drop the constructor's `this` return, so binaryen's dead-argument
// elimination removes it, as the target's wasm type (i32 i32 i32)->() shows. The caller is address-taken from a static
// constructor. Declared through an asm label with the
// wasm-level signature (the constructor returns `this` before binaryen runs); compiled with APP_CXXFLAGS.
extern "C" {
int w5526_root_0(int, int, int) __asm__("_ZN3api6CMovieC1ENSt3__26vectorINS_11CMovieFrameENS1_9allocatorIS3_EEEERKNS_6SPointE");
}

namespace {

__attribute__((noinline)) void CriaFilmeCompartilhado(int bloco, int quadros, int tamanho)
{
    w5526_root_0(bloco + 12, quadros, tamanho);
}

void* volatile w5526_sink;

struct SW5526Roots {
    SW5526Roots()
    {
        w5526_sink = reinterpret_cast<void*>(&CriaFilmeCompartilhado);
    }
} w5526_roots;

} // namespace
