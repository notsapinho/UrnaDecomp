// Roots of the ASN.1 runtime's AVNEncoder, AVNDecoder and InvalidTracer. Declared through asm labels with the wasm-level
// signatures, so this TU instantiates nothing and each template below keeps the copy of the first object that defines it.
//
// - std::string::append<const char*> (178): 76 direct callers in the target, 70 of them in the link with their calls at
//   e7d03612 (cpath.cpp's 6047, unit 381's 6035 and 6036, and the written 5360 among them); AppendStandIn, which stood
//   in for them when std::getline's was the one call in our link and binaryen inlined it there, stands for the other
//   six. The first object to define it is mock/app/comum/cappinfobuilder.cpp's (unit 253).
extern "C" {
int avn_append(int, int, int) __asm__("_ZNSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6appendB8ne210108IPKcTnNS_9enable_ifIXsr31__has_forward_iterator_categoryIT_EE5valueEiE4typeELi0EEERS5_SA_SA_");
}

namespace {

__attribute__((noinline)) int AppendStandIn(int texto, int primeiro, int ultimo)
{
    return avn_append(texto, primeiro, ultimo + 1);
}

const void* volatile avn_sink;

struct SAvnRoots {
    SAvnRoots()
    {
        avn_sink = reinterpret_cast<const void*>(&AppendStandIn);
    }
} avn_roots;

} // namespace
