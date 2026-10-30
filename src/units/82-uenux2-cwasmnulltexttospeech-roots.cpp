// Roots: keep unit 82's simulador::CWasmNullTextToSpeech in the skeleton link the way the target keeps it. The target
// reaches every member through the vtable only (`awk -F'\t' '$2==11518' ledger/callgraph.tsv` and the same for the other
// slots print nothing; each fills one table slot, shared by the three vtables): the references are the vptr stores of
// the implicit constructor, fn 13877 and the copy inlined into fn 8302, neither reconstructed. Rooting the vtable keeps
// the same set: the class's own members and, through its slots, ITextToSpeech's. Declared through an asm label, so this
// TU needs no uenux2 header and instantiates nothing.
extern const char cwasmnulltexttospeech_vt[] __asm__("_ZTVN9simulador21CWasmNullTextToSpeechE");

namespace {

const void* volatile cwasmnulltexttospeech_sink;

struct SCWasmNullTextToSpeechRoots {
    SCWasmNullTextToSpeechRoots() { cwasmnulltexttospeech_sink = cwasmnulltexttospeech_vt; }
} cwasmnulltexttospeech_roots;

} // namespace
