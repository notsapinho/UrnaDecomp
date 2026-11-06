// Roots: keep comum::asn::CConversorDadosCandidato in the skeleton link the way the target keeps it.
// comum::asn::Utils's members need no stand-in now. Each has several direct callers in the target and none through the
// table, so with one caller wasm-opt would inline it, and the stand-ins that called them twice went once their target
// callers were in the link: ConverteFase's (fn 1712: 10266, 10271, 10273, 11401, 11424, 11438 and 11483),
// DesconverteFase's (fn 2843: 10270, 11402, 11423 and 11437) and DesconverteAbrangencia's (fn 5827: 11371 and 11461).
// ConverteTipoLocalVotacao and DesconverteTipoLocalVotacao need none: CConversorDadoLocal and
// CConversorIdentificacaoAgregada call each, and DesconverteDataJE neither: DesconverteDataHoraJE and
// CConversorPleito::DoDesconverte call it, and DesconverteDataHoraJE neither: its four target callers (10290, 11391,
// 11400, 11588) are written, fragment 172's, and ConverteDataJE neither: its callers 11385 (twice) and 11394 are
// written, and ConverteDataHoraJE neither: its callers 10273 (fragment 321's), 10276, 10291, 11390, 11399 and 11589
// (fragment 172's) are written.
// comum::asn::CConversorDadosCandidato's vtable (@1562224) is what the target keeps that converter by: its slots 2
// and 3 (fns 11449, 11450) have no direct caller, and fn 11448 (CConversorCandidatura::DoDesconverte, not written)
// stores its vptr. So the sink holds the vtable, the reference the target has.
// Declared through an asm label, so this TU needs no uenux2 or ASN.1 header.
extern "C" {
extern const char dadoscandidato_vt[] __asm__("_ZTVN5comum3asn24CConversorDadosCandidatoE");
}

namespace {

const void* volatile utils_sink;

struct SUtilsRoots {
    SUtilsRoots()
    {
        utils_sink = dadoscandidato_vt;
    }
} utils_roots;

} // namespace
