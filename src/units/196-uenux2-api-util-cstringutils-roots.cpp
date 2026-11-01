// Roots: api::CStringUtils::GetVersionNumber (target fn 1539) has six direct callers in the target, fns 5579, 5596,
// 5604, 11908, 12105 and 12110, none of them in our link. binaryen inlines a function with one call site, so these two
// stand for them, with bodies that differ from each other's and from every target function. Declared through an asm
// label with the object's signature, so this TU needs no header and instantiates nothing.
extern "C" void w1539_root(void*, int) __asm__(
    "_ZN3api12CStringUtils16GetVersionNumberERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");

namespace {

__attribute__((noinline)) int VersaoDe(int versao)
{
    int numero[3];
    w1539_root(numero, versao);
    return numero[1];
}

__attribute__((noinline)) int VersoesDe(int primeira, int segunda)
{
    int numeros[6];
    w1539_root(numeros, primeira);
    w1539_root(numeros + 3, segunda + 12);
    return numeros[2] - numeros[5];
}

const void* volatile cstringutils_sink;

struct SCStringUtilsRoots {
    SCStringUtilsRoots()
    {
        cstringutils_sink = reinterpret_cast<const void*>(&VersaoDe);
        cstringutils_sink = reinterpret_cast<const void*>(&VersoesDe);
    }
} cstringutils_roots;

} // namespace
