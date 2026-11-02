// Roots: keep the api/security units' functions in the skeleton link the way the target keeps them: every one of
// them is reached through invoke_* (a table slot) or has at most one caller that is not reconstructed yet, so they are
// address-taken from a static constructor like tools/round/gen_try_roots.py does (bodies intact, no export, no inlining).
// Declared through asm labels with the wasm-level signatures; chkdfseed.hpp is included for the class whose destructor
// the function below emits. Compiled as uenux2 code (APP_CXXFLAGS): at UENUX2_CXXFLAGS that class's D2 and D0 compare
// equal, by function with the object-local numbers masked.
// CAesCipher's constructor, SetKey, Encrypt and Decrypt (fns 9495, 9494, 9493, 9491) are not taken here: the target
// reaches each through one table slot, which CBlockCipher<CAesCipher, CTrng>'s Encrypt and Decrypt (9487, 9485) and
// their merged body (6154) hold (/usr/bin/grep -rlE 'i32\.const 628[2-5]($|[^0-9])' build/out/splat/pieces/asm), and
// unit 137's objects hold those in our link.
// CSiphashMac's DoMac and DoVerify (fns 9498, 9497) and IMacAlgorithm::Mac are not taken here: the target reaches the
// first two through the vtable that fn 3700 alone stores (/usr/bin/grep -rlE 'i32\.const 1113604($|[^0-9])'
// build/out/splat/pieces/asm), and holds Mac inlined there by binaryen. 3700, comum::CCalculaCV::CalculaCodigo (unit
// 121), is in the link and stores that vptr, and Mac's one call site is in it.
#include "ecourna/api/security/chkdfseed.hpp"

extern "C" {
void rsec_root_4(int, int) __asm__("_ZN7ecourna3api8security9CHKDFSeed7GetSeedEv");
int rsec_root_5(int, int, int, int, int, int) __asm__("_ZN7ecourna3api8security4CKeyC1ERKNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEEjNS1_7KeyTypeERKNS3_6vectorIhNS7_IhEEEESB_");
int rsec_root_6(int, int) __asm__("_ZN7ecourna3api8security8CKeyDataC1ERKNSt3__26vectorIhNS3_9allocatorIhEEEE");
void rsec_root_7(int) __asm__("_ZN7ecourna3api8security4CSha5ResetEv");
void rsec_root_8(int, int) __asm__("_ZN7ecourna3api8security4CSha6FinishEv");
void rsec_root_9(int, int) __asm__("_ZN7ecourna3api8security4CSha6UpdateERKNSt3__26vectorIhNS3_9allocatorIhEEEE");
int rsec_root_10(int, int, int) __asm__("_ZN7ecourna3api8security4CShaC1ENSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEEm");
void rsec_root_11(int) __asm__("_ZN7ecourna3api8security4CShaD0Ev");
int rsec_root_12(int) __asm__("_ZN7ecourna3api8security4CShaD2Ev");
int rsec_root_13(int) __asm__("_ZN7ecourna3api8security7CSha512C1Ev");
int rsec_root_17(int, int) __asm__("_ZN7ecourna3api8security16ISymmetricCipherC2ERKNS1_7CAesKeyE");
extern const char rsec_hkdf_vt[] __asm__("_ZTVN7ecourna3api8security9CHKDFSeedE");
}

// CHKDFSeed has no key function: its vtable, D2 (fn 11498) and D0 (11497) are emitted by a TU that uses the class, in
// the target uenux2's crdv.cpp (the vtable, 1560088, and typeinfo lie among that file's records), not written. Calling
// the destructor by its qualified name emits all three; the function is not rooted and the link drops it, and the
// vtable's address below stands for the uenux2 code that stores the vptr (7787, which holds GetSeed inlined, and the
// two destructors).
__attribute__((optnone, noinline)) void rsec_destroi_semente(ecourna::api::security::CHKDFSeed* semente)
{
    semente->CHKDFSeed::~CHKDFSeed();
}

namespace {

void* volatile rsec_sink;

struct SRsecRoots {
    SRsecRoots()
    {
        rsec_sink = reinterpret_cast<void*>(&rsec_root_4);
        rsec_sink = reinterpret_cast<void*>(&rsec_root_5);
        rsec_sink = reinterpret_cast<void*>(&rsec_root_6);
        rsec_sink = reinterpret_cast<void*>(&rsec_root_7);
        rsec_sink = reinterpret_cast<void*>(&rsec_root_8);
        rsec_sink = reinterpret_cast<void*>(&rsec_root_9);
        rsec_sink = reinterpret_cast<void*>(&rsec_root_10);
        rsec_sink = reinterpret_cast<void*>(&rsec_root_11);
        rsec_sink = reinterpret_cast<void*>(&rsec_root_12);
        rsec_sink = reinterpret_cast<void*>(&rsec_root_13);
        rsec_sink = reinterpret_cast<void*>(&rsec_root_17);
        rsec_sink = const_cast<char*>(rsec_hkdf_vt);
    }
} rsec_roots;

} // namespace
