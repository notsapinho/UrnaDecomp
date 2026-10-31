// Roots of unit 137: keep the new api/security classes in the skeleton link the way the target reaches them.
// - CPrng's constructor (target fn 9503) is table slot 114, which the executable TU's main (10307) passes to
//   invoke_iii with a seed of 0: its address is taken, and the vptr store it holds keeps CPrng's vtable and slots.
// - CSymmetricCipherFactory and cepesc::CCepescCipher have no constructor out of line: uenux2's 2725, 11419, 11616 and
//   11629 store both vptrs (1113840, 1115004) themselves, and 12110 and main the factory's only, none of them written.
//   The vtables' addresses stand for those stores, which keeps every slot (src/units/README.md "Companion files"). The
//   factory's slot 3 (fn 9489) stores CBlockCipher<CAesCipher, CTrng>'s vptr, whose Encrypt builds the CTrng, so those
//   two classes need no root of their own.
// Declared through asm labels, so no header is needed; compiled with APP_CXXFLAGS like the other stand-ins.
extern "C" {
int w137_prng(int, int) __asm__("_ZN7ecourna3api8security5CPrngC1Ei");
extern const char w137_factory_vt[] __asm__("_ZTVN7ecourna3api8security23CSymmetricCipherFactoryE");
extern const char w137_cepesc_vt[] __asm__("_ZTVN7ecourna3api6cepesc13CCepescCipherE");
}

namespace {

const void* volatile w137_sink;

struct SW137Roots {
    SW137Roots()
    {
        w137_sink = reinterpret_cast<const void*>(&w137_prng);
        w137_sink = w137_factory_vt;
        w137_sink = w137_cepesc_vt;
    }
} w137_roots;

} // namespace
