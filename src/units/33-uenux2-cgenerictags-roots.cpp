// Roots: keep api::CGenericTags's functions in the skeleton link the way the target calls them. TagSize (target fn 5468)
// needs none: its two target callers, the two-argument EncodeTLV (3647) and AppendTLV (5466), are in cgenerictags.cpp.
// CGenericTags::insert (target fn 1071) is called directly by 3831 and 5892, neither reconstructed yet: two stand-ins
// give it two call sites, one passing a varied length-field size, so dead-argument elimination folds no argument in.
// The two-argument EncodeTLV (3647) is called directly by 3831 (twice) and 5892, and the three-argument AppendTLV (5466)
// by 3831 and 5892 (ledger/callgraph.tsv), none reconstructed: four more stand-ins give the first three call sites and
// the second two, every argument passed through. Each stand-in's body differs from the others' and is no target
// function's; they are address-taken from a static constructor. Declared through asm labels with the wasm-level
// signatures (EncodeTLV's result is the hidden first parameter); compiled as uenux2 code.
extern "C" {
void w1071_root_0(int, int, unsigned long) __asm__("_ZN3api12CGenericTags6insertERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEm");
void w3647_root_0(int, int, int, int) __asm__("_ZNK3api12CGenericTags9EncodeTLVERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_");
void w5466_root_0(int, int, int, int) __asm__("_ZNK3api12CGenericTags9AppendTLVERNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEERKS7_SA_");
}

namespace {

__attribute__((noinline)) void MapeiaTag(int tags, int tag, unsigned long tamanho)
{
    w1071_root_0(tags, tag, tamanho + 1);
}

__attribute__((noinline)) void MapeiaDuasTags(int tags, int tagA, int tagB)
{
    w1071_root_0(tags, tagA, 1);
    w1071_root_0(tags, tagB, 2);
}

__attribute__((noinline)) void CodificaTag(int saida, int tags, int tag, int valor)
{
    w3647_root_0(saida, tags, tag, valor);
}

__attribute__((noinline)) void CodificaDuasTags(int saida, int tags, int tagA, int tagB, int valor)
{
    w3647_root_0(saida, tags, tagA, valor);
    w3647_root_0(saida + 12, tags, tagB, valor);
}

__attribute__((noinline)) void AnexaTag(int tags, int tlv, int tag, int valor)
{
    w5466_root_0(tags, tlv, tag, valor);
}

__attribute__((noinline)) void AnexaTagAoSegundo(int tags, int tlvs, int tag, int valor)
{
    w5466_root_0(tags, tlvs + 12, tag, valor);
}

void* volatile w33_sink;

struct SW33Roots {
    SW33Roots()
    {
        w33_sink = reinterpret_cast<void*>(&MapeiaTag);
        w33_sink = reinterpret_cast<void*>(&MapeiaDuasTags);
        w33_sink = reinterpret_cast<void*>(&CodificaTag);
        w33_sink = reinterpret_cast<void*>(&CodificaDuasTags);
        w33_sink = reinterpret_cast<void*>(&AnexaTag);
        w33_sink = reinterpret_cast<void*>(&AnexaTagAoSegundo);
    }
} w33_roots;

} // namespace
