// Roots: keep fragment 159's comum converters in the skeleton link the way the target keeps them. Their users are not
// reconstructed yet; in the target each converter's vtable is data whose DoConverte/DoDesconverte slots put the bodies
// in the table (no slot has a direct caller), so rooting the vtable keeps the same set:
// - comum::asn::CConversorHistoricoVotoImpresso, vtable @1597388 (slots 2 and 3: fns 10276, 10275);
// - comum::asn::CConversorEleicaoPE, @1570088 (fns 11370, 11371);
// - comum::asn::CConversorCandidaturas, @1562360 (fns 11444, 11445);
// - comum::asn::CConversorFotoCandidato, @1562580 (fns 11439, 11440);
// - comum::asn::CConversorEntidadeBU, @1597528 (fns 10273, 10272): the one target function that stores its vptr is
//   comum::CGravadorBU::GravaResultado (fn 11629), not written;
// comum::asn::CConversorCargo's vtable (@1569964) is not here: fn 11371, the one target function that stores its vptr,
// is in the link (fragment 299). Nor is comum::asn::CConversorBiometriaEleitorCifrada's (@1566292, slots 2 and 3: fns
// 11418, 11419): fn 1937 (unit 110's CEleitorDetalhe::GetBiometria), the one target function that stores its vptr,
// matches. Nor are comum::asn::CConversorDedo's (@1566480) and CConversorBiometriaEleitor's (@1565992): fns 11422 and
// 11419 (fragment 335), the target functions that store their vptrs, are in the link.
// Declared through asm labels, so this TU needs no uenux2 or ASN.1 header and instantiates nothing.
extern "C" {
extern const char historicovotoimpresso_vt[] __asm__("_ZTVN5comum3asn31CConversorHistoricoVotoImpressoE");
extern const char eleicaope_vt[] __asm__("_ZTVN5comum3asn19CConversorEleicaoPEE");
extern const char candidaturas_vt[] __asm__("_ZTVN5comum3asn22CConversorCandidaturasE");
extern const char fotocandidato_vt[] __asm__("_ZTVN5comum3asn23CConversorFotoCandidatoE");
extern const char entidadebu_vt[] __asm__("_ZTVN5comum3asn20CConversorEntidadeBUE");
}

namespace {

const void* volatile defaults159_sink[5];

struct SDefaults159Roots {
    SDefaults159Roots()
    {
        defaults159_sink[0] = historicovotoimpresso_vt;
        defaults159_sink[1] = eleicaope_vt;
        defaults159_sink[2] = candidaturas_vt;
        defaults159_sink[3] = fotocandidato_vt;
        defaults159_sink[4] = entidadebu_vt;
    }
} defaults159_roots;

} // namespace
