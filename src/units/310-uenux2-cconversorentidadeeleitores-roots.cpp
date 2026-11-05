// Roots of unit 310: stand-ins for target callers not reconstructed, so that each function keeps the call sites the
// target gives it (src/units/README.md "Companion files"). Declared through asm labels with the objects' signatures, so
// this TU instantiates nothing; the bodies differ from every target function's.
//   w310_visitantes   std::vector<std::pair<std::string, std::shared_ptr<ASN1::IAbstractVisitor>>>::__assign_with_size
//                     over two const pointers (fn 5704), which ASN1::CoderEnv::setVisitors gives api::CPartialFileASN's
//                     DecodeObjectFunction: target fn 7787 (its photos' reader, not written); 11523, the other caller,
//                     is in the link. With 11523 alone, binaryen inlines 5704 into it.
// The stand-in for fn 2805 went: its target callers 3614, 5376 and 10451, which call it for the other maps' instances
// binaryen merges into it, are in the link (unit 221's), with 11411.
extern "C" void w5704(int, int, int, int) __asm__(
    "_ZNSt3__26vectorINS_4pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEENS_10shared_ptrIN4ASN116IAbstractVisitorEEEEENS5_ISC_EEE18__assign_with_sizeB8ne210108IPKSC_SH_EEvT_T0_l");

__attribute__((noinline)) void w310_visitantes(int visitantes, int lista, int quantidade)
{
    w5704(visitantes + 16, lista, lista + 20 * quantidade, quantidade);
}

namespace {

const void* volatile w310_sink;

struct SW310Roots {
    SW310Roots()
    {
        w310_sink = reinterpret_cast<const void*>(&w310_visitantes);
    }
} w310_roots;

} // namespace
