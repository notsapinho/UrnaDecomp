// Roots of fragment 215. Each stand-in's comment names the target callers it stands for; it goes when they are all in
// the link. The functions are declared through asm labels with the objects' signatures, so this TU needs no header and
// instantiates nothing.

// comum::md::estadoaplicacao::CEstadoGeral::SetAjusteDataHora (target fn 3705) has three direct callers in the target,
// fns 7160, 7306 and 10710, all in our link (units 329, 104 and 277): its stand-ins went.

// api::TerminaComBarraInvertida (target fn 5484) has one direct caller in the target, fn 5480, which calls it twice
// and is in our link (fragment 379): its stand-in went.

// comum::md::estadoaplicacao::CEstadoGeral's constructor from its eight parts (target fn 5637) has one direct caller in
// the target, fn 11398 (unit 124, in our link), and a table slot, 427, which fn 10205 (not written) alone passes to
// invoke_iiiiiiiiii (docs/reference/facts/units.md U11's script): its address is the reference the target has. Declared
// with the object's signature: a constructor returns this.
extern "C" int w5637_geral(void*, int, unsigned, void*, void*, void*, const void*, void*, void*) __asm__(
    "_ZN5comum2md15estadoaplicacao12CEstadoGeralC1ENS_11EEstadoUrnaEjNS1_10CDadoLocalENS1_10CDadoCargaE"
    "NS1_15CAjusteDataHoraERKNS1_20CDadoCorrespondenciaENSt3__212basic_stringIcNSA_11char_traitsIcEENSA_9allocatorIcEEEE"
    "NSA_6vectorIhNSE_IhEEEE");

namespace {

const void* volatile leftovers_sink;

struct SLeftoversRoots {
    SLeftoversRoots()
    {
        leftovers_sink = reinterpret_cast<const void*>(&w5637_geral);
    }
} leftovers_roots;

} // namespace
