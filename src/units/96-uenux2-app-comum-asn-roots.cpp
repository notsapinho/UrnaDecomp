// Roots: keep comum::asn::Utils's members out of line in the skeleton link. Each has several direct callers in the
// target (the converters, most not reconstructed yet) and none through the table, so with one caller wasm-opt would
// inline it: each stand-in below calls each of its members twice. ConverteTipoLocalVotacao and
// DesconverteTipoLocalVotacao need none: CConversorDadoLocal and CConversorIdentificacaoAgregada call each, and
// DesconverteDataJE neither: DesconverteDataHoraJE and CConversorPleito::DoDesconverte call it, and DesconverteDataHoraJE
// neither: its four target callers (10290, 11391, 11400, 11588) are written, fragment 172's, and ConverteDataJE neither:
// its callers 11385 (twice) and 11394 are written. utils_converte stands for ConverteDataHoraJE's caller 10273, not
// written (10276, 10291, 11390, 11399 and 11589 are, fragment 172's).
// comum::asn::CConversorDadosCandidato's vtable (@1562224) is what the target keeps that converter by: its slots 2
// and 3 (fns 11449, 11450) have no direct caller, and fn 11448 (CConversorCandidatura::DoDesconverte, not written)
// stores its vptr. So the sink holds the vtable, the reference the target has.
// Declared through asm labels with the object's signatures, so this TU needs no uenux2 or ASN.1 header.
extern "C" {
extern const char dadoscandidato_vt[] __asm__("_ZTVN5comum3asn24CConversorDadosCandidatoE");
void converte_fase(void*, const int*) __asm__("_ZN5comum3asn5Utils12ConverteFaseERKNS_9EUrnaFaseE");
int desconverte_fase(const void*) __asm__("_ZN5comum3asn5Utils15DesconverteFaseERKN21ModuloTiposEleitorais4FaseE");
int desconverte_abrangencia(int) __asm__(
    "_ZN5comum3asn5Utils22DesconverteAbrangenciaEN21ModuloTiposEleitorais15TipoAbrangencia11NamedNumberE");
void converte_datahora(void*, const void*) __asm__("_ZN5comum3asn5Utils18ConverteDataHoraJEERKN3api9CDateTimeE");
}

namespace {

const void* volatile utils_sink;

__attribute__((noinline)) int utils_fase(void* resultado, const int* fase, const char* entidade)
{
    converte_fase(resultado, fase);
    converte_fase(resultado, fase + 1);
    return desconverte_fase(entidade) + desconverte_fase(entidade + 12);
}

__attribute__((noinline)) int utils_abrangencia(int a, int b)
{
    return desconverte_abrangencia(a) * desconverte_abrangencia(b);
}

__attribute__((noinline)) void utils_converte(char* resultado, const char* dado)
{
    converte_datahora(resultado, dado);
    converte_datahora(resultado + 20, dado + 12);
}

struct SUtilsRoots {
    SUtilsRoots()
    {
        utils_sink = reinterpret_cast<const void*>(&utils_fase);
        utils_sink = reinterpret_cast<const void*>(&utils_abrangencia);
        utils_sink = reinterpret_cast<const void*>(&utils_converte);
        utils_sink = dadoscandidato_vt;
    }
} utils_roots;

} // namespace
