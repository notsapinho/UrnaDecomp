// Roots: keep fragment 159's comum converters in the skeleton link the way the target keeps them. Their users are not
// reconstructed yet; in the target each converter's vtable is data whose DoConverte/DoDesconverte slots put the bodies
// in the table (no slot has a direct caller), so rooting the vtable keeps the same set:
// - comum::asn::CConversorHistoricoVotoImpresso, vtable @1597388 (slots 2 and 3: fns 10276, 10275);
// - comum::asn::CConversorCargo, @1569964 (fns 11372, 11373);
// - comum::asn::CConversorDetalheCandidato, @1569872 (fns 11374, 11375);
// - comum::asn::CConversorDetalheConsulta, @1569764 (fns 11376, 11377);
// - comum::asn::CConversorEleicaoPE, @1570088 (fns 11370, 11371);
// - comum::asn::CConversorDedo, @1566480 (fns 11415, 11416);
// - comum::asn::CConversorBiometriaEleitor, @1565992 (fns 11421, 11422);
// - comum::asn::CConversorBiometriaEleitorCifrada, @1566292 (fns 11418, 11419);
// - comum::asn::CConversorCandidaturas, @1562360 (fns 11444, 11445);
// - comum::asn::CConversorFotoCandidato, @1562580 (fns 11439, 11440).
// Declared through asm labels, so this TU needs no uenux2 or ASN.1 header and instantiates nothing.
extern "C" {
extern const char historicovotoimpresso_vt[] __asm__("_ZTVN5comum3asn31CConversorHistoricoVotoImpressoE");
extern const char cargo_vt[] __asm__("_ZTVN5comum3asn15CConversorCargoE");
extern const char detalhecandidato_vt[] __asm__("_ZTVN5comum3asn26CConversorDetalheCandidatoE");
extern const char detalheconsulta_vt[] __asm__("_ZTVN5comum3asn25CConversorDetalheConsultaE");
extern const char eleicaope_vt[] __asm__("_ZTVN5comum3asn19CConversorEleicaoPEE");
extern const char dedo_vt[] __asm__("_ZTVN5comum3asn14CConversorDedoE");
extern const char biometriaeleitor_vt[] __asm__("_ZTVN5comum3asn26CConversorBiometriaEleitorE");
extern const char biometriaeleitorcifrada_vt[] __asm__("_ZTVN5comum3asn33CConversorBiometriaEleitorCifradaE");
extern const char candidaturas_vt[] __asm__("_ZTVN5comum3asn22CConversorCandidaturasE");
extern const char fotocandidato_vt[] __asm__("_ZTVN5comum3asn23CConversorFotoCandidatoE");
}

namespace {

const void* volatile defaults159_sink[10];

struct SDefaults159Roots {
    SDefaults159Roots()
    {
        defaults159_sink[0] = historicovotoimpresso_vt;
        defaults159_sink[1] = cargo_vt;
        defaults159_sink[2] = detalhecandidato_vt;
        defaults159_sink[3] = detalheconsulta_vt;
        defaults159_sink[4] = eleicaope_vt;
        defaults159_sink[5] = dedo_vt;
        defaults159_sink[6] = biometriaeleitor_vt;
        defaults159_sink[7] = biometriaeleitorcifrada_vt;
        defaults159_sink[8] = candidaturas_vt;
        defaults159_sink[9] = fotocandidato_vt;
    }
} defaults159_roots;

} // namespace
