// Roots: reach unit 200's functions the way the target does, until their callers land. It compiles with the tree's
// flags.
// - comum::CGravadorBU's vtable (@1554132), whose slots (the destructors, fns 5857 and 11628, and GravaResultado, fn
//   11629) the target reaches only through it: the constructor that stores it (inlined into
//   vota::CGravaResultado::StartState, fn 12098) is not written, so its address goes into a sink.

extern "C" {
extern const char w200_vt_bu[] __asm__("_ZTVN5comum11CGravadorBUE");
}

namespace {

const void* volatile w200_sink_vt;

struct SW200Roots {
    SW200Roots() { w200_sink_vt = w200_vt_bu; }
} w200_roots;

} // namespace
