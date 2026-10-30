// Roots: keep comum::dao::CJustificadorDAO's vtable in the skeleton link the way the target keeps it. Nothing calls
// slot 3 (target fn 11473) or the deleting destructor (3767) directly: the target reaches them through the vtable
// (@1560760, table entries 2468 to 2476), whose address the constructor inlined into fn 7787 stores. Rooting the
// vtable keeps it, its slots' bodies and the destructors in the link without a constructor. Declared through an asm
// label, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char justificadordao_vt[] __asm__("_ZTVN5comum3dao16CJustificadorDAOE");
}

namespace {

const void* volatile justificadordao_sink;

struct SJustificadorDAORoots {
    SJustificadorDAORoots() { justificadordao_sink = justificadordao_vt; }
} justificadordao_roots;

} // namespace
