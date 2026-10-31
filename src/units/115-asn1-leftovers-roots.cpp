// Roots of the ASN.1 runtime's leftovers. Declared through asm labels with the wasm-level signatures, but for the one
// template built below, a class with no key function (src/units/README.md "A class with no key function").
#include "asn1/asn1.h"

extern "C" {
int leftovers_string_literal(int, int, int) __asm__("_ZN4ASN114AbstractStringC1EPKvPKc");
int leftovers_string_copy(int, int, int) __asm__("_ZN4ASN114AbstractStringC1EPKvRKNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEE");
int leftovers_first_not_of(int, int, int) __asm__("_ZNKSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE17find_first_not_ofB8ne210108EPKcm");
}

namespace {

// std::string::find_first_not_of(const char*, size_t) (1843): 11546, 11571 and 14477 are not written, and they pass
// other sets and positions than 1519 and 2185 do; without a caller that varies them binaryen folds both arguments.
// ASN1::SEQUENCE_OF<ASN1::GeneralString>'s vtable and operator= (5731): 10273 and 11483, the two converters that call it,
// are not written. This stand-in calls it twice, as those two do, and building the local stores the vtable 5731 stores, so
// its slot 1 (859) comes along. Its body is no target function's, and optnone keeps clang from folding the two calls.
typedef ASN1::SEQUENCE_OF<ASN1::GeneralString> TNomes;

__attribute__((optnone, noinline)) void CopiaNomes(TNomes& destino, const TNomes& origem)
{
    TNomes vazio;
    vazio = origem;
    destino = vazio;
}

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
        leftovers_sink = reinterpret_cast<const void*>(&CopiaNomes);
    }
} leftovers_roots;

} // namespace
