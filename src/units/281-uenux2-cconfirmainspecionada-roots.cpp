// Roots: keep vota::CConfirmaInspecionada's vtable, the reference the target has: vota::CAguardaInspecao's slot 6 (fn
// 10530, not written) stores its vptr when it builds the object, through the class's GetInst and constructor, which it
// holds inlined. That keeps every slot, ProcessInput (fn 10527) among them. The sink goes when fn 10530 is in the link.
extern "C" {
extern const char w281_vtable[] __asm__("_ZTVN4vota21CConfirmaInspecionadaE");
}

namespace {

const void* volatile w281_sink;

struct SW281Roots {
    SW281Roots() { w281_sink = w281_vtable; }
} w281_roots;

} // namespace
