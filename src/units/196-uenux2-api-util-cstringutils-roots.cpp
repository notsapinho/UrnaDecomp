// Roots: api::CStringUtils::GetVersionNumber (target fn 1539) has six direct callers in the target, fns 5579, 5596,
// 5604, 11908, 12105 and 12110; 5596 (unit 296) and 5604 (unit 155's written Gera) are in our link. binaryen inlines a
// function with one call site, so these two stand for the other four, with bodies that differ from each other's and
// from every target function. Declared through an asm
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

} // namespace

// api::CStringUtils::JuntaTags (target fn 3646) has three direct callers in the target: fn 5782 (comum::CQRCodeDS's
// call operator, fragment 299, in our link) and fns 12039 and 12110 (vota::CGeraBU's slot 2), not in our link. This
// stands for those two.
extern "C" void w3646_junta(void*, const void*) __asm__(
    "_ZN3api12CStringUtils9JuntaTagsERKNSt3__26vectorINS1_4pairINS1_12basic_stringIcNS1_11char_traitsIcEENS1_"
    "9allocatorIcEEEES9_EENS7_ISA_EEEE");

namespace {

__attribute__((noinline)) int TextoDosPares(char* texto, const char* pares)
{
    w3646_junta(texto, pares + 12);
    return texto[11] - texto[0];
}

const void* volatile cstringutils_sink;

struct SCStringUtilsRoots {
    SCStringUtilsRoots()
    {
        cstringutils_sink = reinterpret_cast<const void*>(&VersaoDe);
        cstringutils_sink = reinterpret_cast<const void*>(&VersoesDe);
        cstringutils_sink = reinterpret_cast<const void*>(&TextoDosPares);
    }
} cstringutils_roots;

} // namespace
