// Roots of src/units/243-uenux2-app-vota-justificativa.mk: the second call sites of four functions whose other target
// caller, fn 10635 (vota::CEleitorEncontrado::StartState, pending in this unit), is not reconstructed. Each has two
// target callers or more (ledger/callgraph.tsv), and binaryen inlines a function with one call site:
// - vota::NaoAceitaJustificativa (fn 4578, unit 168's votadefs.cpp): 10631 (in the link) and 10635;
// - vota::CEleitorNaoEncontrado::GetInst (fn 5424, unit 161): 10631 (in the link) and 10635;
// - vota::IEleitorImpedidoVotar's constructor (fn 1905, unit 161): 5424 (in the link), which passes 0 for the int, and
//   10635, which passes 1 five times; the stand-in passes 1, so binaryen folds no constant into the body;
// - vota::IConfirmaJustificativa's constructor (fn 3625, unit 174): 10631 (in the link) and 10635.
// One noinline stand-in for 10635 calls each once and uses every result, as 10635 does (it stores a vptr through each
// constructor's returned `this`). It goes when 10635 is in the link. Its body is no target function's. Declared through
// asm labels with the object's signatures (a constructor returns `this`), so this TU needs no uenux2 header and
// instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
int w243_4578(void) __asm__("_ZN4vota22NaoAceitaJustificativaEv");
int w243_5424(void) __asm__("_ZN4vota21CEleitorNaoEncontrado7GetInstEv");
int w243_1905(int, const void*, const void*, int) __asm__(
    "_ZN4vota21IEleitorImpedidoVotarC2ENSt3__28functionIFNS1_12basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEvEEESA_i");
int w243_3625(int, const void*) __asm__(
    "_ZN4vota22IConfirmaJustificativaC2ERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

// Stands for fn 10635.
__attribute__((noinline)) int EleitorEncontrado(int estado, const void* linha2, const void* linha3, const void* texto)
{
    int total = w243_4578() ? 3 : 5;
    total += w243_5424();
    total += w243_1905(estado, linha2, linha3, 1);
    total += w243_3625(estado + 24, texto);
    return total;
}

const void* volatile w243_sink;

struct SW243Roots {
    SW243Roots() { w243_sink = reinterpret_cast<const void*>(&EleitorEncontrado); }
} w243_roots;

} // namespace
