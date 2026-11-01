// Roots: keep vota::CVerificaQtdBUsAdicionais's vtable (@1542916) in the skeleton link the way the target reaches its
// slots: only through the vtable, which the class's constructor stores. The constructor is inlined into its GetInst,
// and that GetInst into fn 7160, which is not written. Taking the vtable's address from a static constructor puts its
// slots in the table, as the target has them. Declared through an asm label, so this TU needs no uenux2 header;
// compiled as app code.
extern "C" {
extern const char w185_vt_cverificaqtdbusadicionais[] __asm__("_ZTVN4vota25CVerificaQtdBUsAdicionaisE");
}

namespace {

const void* volatile w185_sink;

struct SW185Roots {
    SW185Roots()
    {
        w185_sink = w185_vt_cverificaqtdbusadicionais;
    }
} w185_roots;

} // namespace
