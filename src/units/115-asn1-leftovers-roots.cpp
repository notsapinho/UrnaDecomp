// Roots of the ASN.1 runtime's leftovers. Declared through asm labels with the wasm-level signatures.
extern "C" {
int leftovers_string_literal(int, int, int) __asm__("_ZN4ASN114AbstractStringC1EPKvPKc");
int leftovers_string_copy(int, int, int) __asm__("_ZN4ASN114AbstractStringC1EPKvRKNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEE");
int leftovers_first_not_of(int, int, int) __asm__("_ZNKSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE17find_first_not_ofB8ne210108EPKcm");
}

namespace {

// std::string::find_first_not_of(const char*, size_t) (1843): 11546, 11571 and 14477 are not written, and they pass
// other sets and positions than 1519 and 2185 do; without a caller that varies them binaryen folds both arguments.
__attribute__((noinline)) int FirstNotOfStandIn(int texto, int posicao)
{
    return leftovers_first_not_of(texto, reinterpret_cast<int>(" \t"), posicao + 1);
}

const void* volatile leftovers_sink;

struct SLeftoversRoots {
    SLeftoversRoots()
    {
        leftovers_sink = reinterpret_cast<const void*>(&leftovers_string_literal);
        leftovers_sink = reinterpret_cast<const void*>(&leftovers_string_copy);
        leftovers_sink = reinterpret_cast<const void*>(&FirstNotOfStandIn);
    }
} leftovers_roots;

} // namespace
