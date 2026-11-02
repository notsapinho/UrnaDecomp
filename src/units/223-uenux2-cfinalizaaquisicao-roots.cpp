// Roots: keep fragment 223's class in the skeleton link the way the target reaches it.
// - vota::CFinalizaAquisicao is reached only through its vtable (@1540308), whose address point one function stores in
//   the target, fn 7160 (vota::CAjusteInicial, not written), which holds the class's GetInst inlined. The static
//   constructor takes the vtable's address, which keeps every slot. It goes when fn 7160 is in the link.
// Declared through an asm label; no header.
extern const char w223_vt_finalizaaquisicao[] __asm__("_ZTVN4vota18CFinalizaAquisicaoE");

namespace {

const void* volatile w223_sink;

struct SW223Roots {
    SW223Roots()
    {
        w223_sink = w223_vt_finalizaaquisicao;
    }
} w223_roots;

} // namespace
