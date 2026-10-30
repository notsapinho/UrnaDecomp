// Roots: keep api::CFileSeeder's vtable (api/io/asn/cpartialfileasn.h) in the skeleton link the way the target keeps it.
// Every member is in the class and the class has no key function, so only a TU that uses the vtable emits it. The target's
// are the two ReadFromFile instances (fns 11523, 7787), which are not reconstructed: each does
// `std::shared_ptr<ASN1::ISeeder>(new CFileSeeder(file))`, with the constructor inlined. The optnone function below does
// the same, so clang emits the constructor here and with it the vtable, its members, the typeinfos and the
// __shared_ptr_pointer control block (as COMDATs). It is not rooted, so wasm-ld drops it and the constructor, which the
// target has no function of its own for either. The target reaches every member of the unit only through the two
// vtables (ledger/callgraph.tsv has no direct caller of them), so the static constructor takes their addresses: the
// reference the target's constructor stores, which keeps every slot.
#include <memory>

#include "api/io/asn/cpartialfileasn.h"

extern "C" {
extern const char w83_vtable[] __asm__("_ZTVN3api11CFileSeederE");
extern const char w83_vtable_controle[] __asm__(
    "_ZTVNSt3__220__shared_ptr_pointerIPN3api11CFileSeederENS_10shared_ptrIN4ASN17ISeederEE27__shared_ptr_default_deleteIS6_S2_EENS_9allocatorIS2_EEEE");
}

__attribute__((optnone, noinline)) std::shared_ptr<ASN1::ISeeder> w83_emite(const ecourna::api::io::CFile& arquivo)
{
    return std::shared_ptr<ASN1::ISeeder>(new api::CFileSeeder(arquivo));
}

namespace {

const void* volatile w83_sink;

struct SW83Roots {
    SW83Roots()
    {
        w83_sink = w83_vtable;
        w83_sink = w83_vtable_controle;
    }
} w83_roots;

} // namespace
