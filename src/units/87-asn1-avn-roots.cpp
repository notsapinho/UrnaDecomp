// Roots of the ASN.1 runtime's AVNEncoder, AVNDecoder and InvalidTracer. Declared through asm labels with the wasm-level
// signatures, so this TU instantiates nothing and each template below keeps the copy of the first object that defines it.
//
// - AVNEncoder's vtable: only 3559, 8903 and 9770 hold its vptr in the target, and 9770 is not written yet. Taking the
//   vtable's address keeps its slots, as that store does.
// - std::string::append<const char*> (178): 76 direct callers in the target, one in our link, std::getline's, so binaryen
//   inlines it there. AppendStandIn stands in for the others. ecourna's icompressor object is the first to define it.
// - std::string's substring constructor (1497): four direct callers in the target, 1519, 2184, 2185 and 13229, and one in
//   our link, 2184, so binaryen inlines it there. SubstringStandIn stands in for the others.
extern "C" {
extern const char avn_vt_encoder[] __asm__("_ZTVN4ASN110AVNEncoderE");
int avn_append(int, int, int) __asm__("_ZNSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6appendB8ne210108IPKcTnNS_9enable_ifIXsr31__has_forward_iterator_categoryIT_EE5valueEiE4typeELi0EEERS5_SA_SA_");
int avn_substring(int, int, int, int, int) __asm__("_ZNSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2ERKS5_mmRKS4_");
}

namespace {

__attribute__((noinline)) int AppendStandIn(int texto, int primeiro, int ultimo)
{
    return avn_append(texto, primeiro, ultimo + 1);
}

__attribute__((noinline)) int SubstringStandIn(int destino, int origem, int inicio, int tamanho, int alocador)
{
    return avn_substring(destino, origem, inicio + 1, tamanho + 2, alocador);
}

const void* volatile avn_sink;

struct SAvnRoots {
    SAvnRoots()
    {
        avn_sink = avn_vt_encoder;
        avn_sink = reinterpret_cast<const void*>(&AppendStandIn);
        avn_sink = reinterpret_cast<const void*>(&SubstringStandIn);
    }
} avn_roots;

} // namespace
