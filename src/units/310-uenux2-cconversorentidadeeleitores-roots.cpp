// Roots of unit 310: stand-ins for target callers not reconstructed, so that each function keeps the call sites the
// target gives it (src/units/README.md "Companion files"). Declared through asm labels with the objects' signatures, so
// this TU instantiates nothing; the bodies differ from every target function's.
//   w310_visitantes   std::vector<std::pair<std::string, std::shared_ptr<ASN1::IAbstractVisitor>>>::__assign_with_size
//                     over two const pointers (fn 5704), which ASN1::CoderEnv::setVisitors gives api::CPartialFileASN's
//                     DecodeObjectFunction: target fn 7787 (its photos' reader, not written); 11523, the other caller,
//                     is in the link. With 11523 alone, binaryen inlines 5704 into it.
//   w310_busca        the hinted __find_equal of std::map<md::CEleitorIdentidade, md::CIndexer>'s tree, which 11411's
//                     copy of the visitor's map calls through __emplace_hint_unique_key_args, matched as fn 2805: the
//                     target's 2805 is binaryen's merge of at least three maps' instances (the nodes its callers
//                     allocate right after the call are 40, 236 and 84 bytes), so the name is the instance our link
//                     holds, and target fns 3614, 5376 and 10451 (not written) call it for the other instances. With
//                     11411 alone, binaryen inlines this instance into its one caller there, and 11411 differs.
extern "C" void w5704(int, int, int, int) __asm__(
    "_ZNSt3__26vectorINS_4pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEENS_10shared_ptrIN4ASN116IAbstractVisitorEEEEENS5_ISC_EEE18__assign_with_sizeB8ne210108IPKSC_SH_EEvT_T0_l");

__attribute__((noinline)) void w310_visitantes(int visitantes, int lista, int quantidade)
{
    w5704(visitantes + 16, lista, lista + 20 * quantidade, quantidade);
}

extern "C" int w2805(int, int, int, int, int) __asm__(
    "_ZNSt3__26__treeINS_12__value_typeIN5comum2md18CEleitorIdentidadeENS3_8CIndexerEEENS_19__map_value_compareIS4_NS_4pairIKS4_S5_EENS_4lessIS4_EELb1EEENS_9allocatorISA_EEE12__find_equalIS4_EERPNS_16__tree_node_baseIPvEENS_21__tree_const_iteratorIS6_PNS_11__tree_nodeIS6_SJ_EElEERPNS_15__tree_end_nodeISL_EESM_RKT_");

__attribute__((noinline)) int w310_busca(int arvore, int dica, int pai, int ficticio, int chave)
{
    return w2805(arvore, dica, pai, ficticio, chave) + 4;
}

namespace {

const void* volatile w310_sink;

struct SW310Roots {
    SW310Roots()
    {
        w310_sink = reinterpret_cast<const void*>(&w310_visitantes);
        w310_sink = reinterpret_cast<const void*>(&w310_busca);
    }
} w310_roots;

} // namespace
