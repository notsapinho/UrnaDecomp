// Roots: keep fragment 159's comum converters in the skeleton link the way the target keeps them. Their users are not
// reconstructed yet; in the target each converter's vtable is data whose DoConverte/DoDesconverte slots put the bodies
// in the table (no slot has a direct caller), so rooting the vtable keeps the same set:
// - comum::asn::CConversorCandidaturas, @1562360 (fns 11444, 11445).
// comum::asn::CConversorHistoricoVotoImpresso's vtable (@1597388, slots 2 and 3: fns 10276, 10275) is not here: fn
// 10273 (unit 321's CConversorEntidadeBU::DoConverte), which stores its vptr, is in the link. Nor is
// comum::asn::CConversorFotoCandidato's (@1562580, fns 11439, 11440): fn 3755 (unit 109's), which stores its vptr, is.
// comum::asn::CConversorCargo's vtable (@1569964) is not here: fn 11371, the one target function that stores its vptr,
// is in the link (fragment 299). Nor is comum::asn::CConversorBiometriaEleitorCifrada's (@1566292, slots 2 and 3: fns
// 11418, 11419): fn 1937 (unit 110's CEleitorDetalhe::GetBiometria), the one target function that stores its vptr,
// matches. Nor is comum::asn::CConversorEleicaoPE's (@1570088, slots 2 and 3: fns 11370, 11371): fn 5778
// (comum::CarregaPleito, unit 280's), the one target function that stores its vptr, is in the link, through the
// converter's constructor out of line in cconversoreleicaope.cpp (unit 299).
// Nor are comum::asn::CConversorDedo's (@1566480) and CConversorBiometriaEleitor's (@1565992): fns 11422 and
// 11419 (fragment 335), the target functions that store their vptrs, are in the link. Nor is
// comum::asn::CConversorEntidadeBU's (@1597528, slots 2 and 3: fns 10273, 10272): fn 11629 (unit 200's
// comum::CGravadorBU::GravaResultado), the one target function that stores its vptr, matches.
// Declared through an asm label, so this TU needs no uenux2 or ASN.1 header and instantiates nothing.
extern "C" {
extern const char candidaturas_vt[] __asm__("_ZTVN5comum3asn22CConversorCandidaturasE");
}

namespace {

const void* volatile defaults159_sink;

struct SDefaults159Roots {
    SDefaults159Roots()
    {
        defaults159_sink = candidaturas_vt;
    }
} defaults159_roots;

} // namespace
