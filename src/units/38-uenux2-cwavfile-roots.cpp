// Roots: keep api::CWavFile's destructors (target fns 5345 and 10238, slots 0 and 1 of the CWavFile vtable @1600476)
// in the skeleton link the way the target keeps them. In the target the vtable is referenced only by the constructor,
// which binaryen inlined into its one caller (fn 10841, slot 11 of api::CRHVoiceTextToSpeech), not reconstructed yet;
// the vtable's two slots put both destructors in the table, and the deleting destructor calls the other one. Rooting
// the vtable keeps the same set. Declared through an asm label, so this TU needs no uenux2 header and instantiates
// nothing.
extern "C" {
extern const char cwavfile_vt[] __asm__("_ZTVN3api8CWavFileE");
}

namespace {

const void* volatile cwavfile_sink;

struct SCWavFileRoots {
    SCWavFileRoots() { cwavfile_sink = cwavfile_vt; }
} cwavfile_roots;

} // namespace
