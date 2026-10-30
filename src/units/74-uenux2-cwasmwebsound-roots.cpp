// Roots: keep unit 74's simulador::CWasmWebSound in the skeleton link the way the target keeps it. The target reaches
// every member through the vtable only (none has a direct caller): the one reference is the vptr store of the
// constructor, which binaryen inlined into the lambda of main that registers the sound (fn 10384, not reconstructed).
// Rooting the vtable keeps the same set: its ten members and the destructors in the table. Declared through an asm
// label, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char cwasmwebsound_vt[] __asm__("_ZTVN9simulador13CWasmWebSoundE");
}

namespace {

const void* volatile cwasmwebsound_sink;

struct SCWasmWebSoundRoots {
    SCWasmWebSoundRoots() { cwasmwebsound_sink = cwasmwebsound_vt; }
} cwasmwebsound_roots;

} // namespace
