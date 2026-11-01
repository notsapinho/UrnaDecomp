// Roots: keep api::CGenericTags::TagSize (target fn 5468) in the skeleton link. The target calls it directly from two
// functions (3647 and 5466, ledger/callgraph.tsv), neither reconstructed yet and neither through the table; two
// noinline callers with different bodies give it two call sites, so binaryen keeps its body out of line as the target
// does (two identical callers would be merged into one, and TagSize inlined into it), and both pass every argument
// through, so binaryen's dead-argument elimination folds none of them in. They are address-taken from a static
// constructor. CGenericTags::insert (target fn 1071) is called directly by 3831 and 5892, neither reconstructed yet:
// two more stand-ins give it two call sites, one passing a varied length-field size, so dead-argument elimination folds
// no argument in. Declared through asm labels with the wasm-level signatures; compiled as uenux2 code.
extern "C" {
int w5468_root_0(int, int) __asm__("_ZNK3api12CGenericTags7TagSizeERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
void w1071_root_0(int, int, unsigned long) __asm__("_ZN3api12CGenericTags6insertERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm");
}

namespace {

__attribute__((noinline)) int TamanhoDaTag(int tags, int tag)
{
    return w5468_root_0(tags, tag);
}

__attribute__((noinline)) int TagLonga(int tags, int tag)
{
    return w5468_root_0(tags, tag) > 1;
}

__attribute__((noinline)) void MapeiaTag(int tags, int tag, unsigned long tamanho)
{
    w1071_root_0(tags, tag, tamanho + 1);
}

__attribute__((noinline)) void MapeiaDuasTags(int tags, int tagA, int tagB)
{
    w1071_root_0(tags, tagA, 1);
    w1071_root_0(tags, tagB, 2);
}

void* volatile w5468_sink;

struct SW5468Roots {
    SW5468Roots()
    {
        w5468_sink = reinterpret_cast<void*>(&TamanhoDaTag);
        w5468_sink = reinterpret_cast<void*>(&TagLonga);
        w5468_sink = reinterpret_cast<void*>(&MapeiaTag);
        w5468_sink = reinterpret_cast<void*>(&MapeiaDuasTags);
    }
} w5468_roots;

} // namespace
