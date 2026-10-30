// Roots: keep the comum::CSigVerifier constructor (target fn 1540) in the skeleton link the way the target reaches it.
// Seven functions call it directly in the target (2890 11852 11855 11991 12068 12071 12074, ledger/callgraph.tsv), none
// reconstructed yet and none through the table. Each passes the same ESavdAplic, 1, so binaryen's dead-argument
// elimination folds it into the constructor, and each uses the `this` it returns. These two noinline callers do the
// same; they are address-taken from a static constructor. The constructor brings in the vtable its vptr store names,
// and with it the implicit destructors (fns 11178, 11176) and the pending Verify. Declared through an asm label with
// the wasm-level signature (`this`, the ESavdAplic, the three std::string arguments by address); compiled as uenux2
// code.
extern "C" {
int w1540_root_0(int, int, int, int, int) __asm__(
    "_ZN5comum12CSigVerifierC1ENS_10ESavdAplicENSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEES8_S8_");
}

namespace {

__attribute__((noinline)) int VerificadorA(int verificador, int diretorio, int arquivo, int pacote)
{
    return w1540_root_0(verificador, 1, diretorio, arquivo, pacote);
}

// the strings in another order, so binaryen does not merge the two callers into one (with one caller it would inline
// the constructor)
__attribute__((noinline)) int VerificadorB(int verificador, int diretorio, int arquivo, int pacote)
{
    return w1540_root_0(verificador, 1, pacote, arquivo, diretorio);
}

void* volatile w1540_sink;

struct SW1540Roots {
    SW1540Roots()
    {
        w1540_sink = reinterpret_cast<void*>(&VerificadorA);
        w1540_sink = reinterpret_cast<void*>(&VerificadorB);
    }
} w1540_roots;

} // namespace
