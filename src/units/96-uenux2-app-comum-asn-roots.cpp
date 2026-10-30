// Roots: keep comum::asn::Utils's members out of line in the skeleton link. Each has several direct callers in the
// target (the converters, not reconstructed yet) and none through the table, so with one caller wasm-opt would inline
// it: each stand-in below calls each of its members twice.
// Declared through asm labels with the object's signatures, so this TU needs no uenux2 or ASN.1 header.
extern "C" {
void converte_fase(void*, const int*) __asm__("_ZN5comum3asn5Utils12ConverteFaseERKNS_9EUrnaFaseE");
int desconverte_fase(const void*) __asm__("_ZN5comum3asn5Utils15DesconverteFaseERKN21ModuloTiposEleitorais4FaseE");
int desconverte_abrangencia(int) __asm__(
    "_ZN5comum3asn5Utils22DesconverteAbrangenciaEN21ModuloTiposEleitorais15TipoAbrangencia11NamedNumberE");
void converte_tipo_local(void*, int) __asm__("_ZN5comum3asn5Utils24ConverteTipoLocalVotacaoENS_17ETipoLocalVotacaoE");
int desconverte_tipo_local(const void*) __asm__(
    "_ZN5comum3asn5Utils27DesconverteTipoLocalVotacaoEN19ModuloTiposCadastro16TipoLocalVotacaoE");
}

namespace {

const void* volatile utils_sink;

__attribute__((noinline)) int utils_fase(void* resultado, const int* fase, const char* entidade)
{
    converte_fase(resultado, fase);
    converte_fase(resultado, fase + 1);
    return desconverte_fase(entidade) + desconverte_fase(entidade + 12);
}

__attribute__((noinline)) int utils_tipo_local(char* resultado, int tipo, const char* entidade)
{
    converte_tipo_local(resultado, tipo);
    converte_tipo_local(resultado + 12, tipo + 1);
    return desconverte_tipo_local(entidade) - desconverte_tipo_local(entidade + 24);
}

__attribute__((noinline)) int utils_abrangencia(int a, int b)
{
    return desconverte_abrangencia(a) * desconverte_abrangencia(b);
}

struct SUtilsRoots {
    SUtilsRoots()
    {
        utils_sink = reinterpret_cast<const void*>(&utils_fase);
        utils_sink = reinterpret_cast<const void*>(&utils_tipo_local);
        utils_sink = reinterpret_cast<const void*>(&utils_abrangencia);
    }
} utils_roots;

} // namespace
