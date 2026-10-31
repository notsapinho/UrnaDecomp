// Roots: keep the converters of unit 105 in the skeleton link the way the target keeps them. The users of the outermost
// four are not reconstructed yet (7787 for federations, parametrization and the municipalities' configuration, 10273 for
// the attendance detail, 11616 for the voter-register result). In the target each vtable is data whose slots put
// DoConverte and DoDeconverte in the table, and the inner converters are locals of the outer ones, so rooting these
// vtables keeps the same set. Declared through asm labels, so this TU needs no ecourna or ASN.1 header and instantiates
// nothing.
extern "C" {
extern const char cv105_federacoes[] __asm__("_ZTVN7ecourna3app5dados3asn20CConversorFederacoesE");
extern const char cv105_parametrizacao[] __asm__("_ZTVN7ecourna3app5dados3asn28CConversorParametrizacaoUrnaE");
extern const char cv105_configuracoes[] __asm__("_ZTVN7ecourna3app5dados3asn32CConversorConfiguracaoMunicipiosE");
extern const char cv105_detalhamento[] __asm__("_ZTVN7ecourna3app5dados3asn36CConversorDetalhamentoComparecimentoE");
extern const char cv105_resultado[] __asm__("_ZTVN7ecourna3app5dados3asn31CConversorResultadoUrnaCadastroE");
void cv105_federacoes_dealloc(int) __asm__("_ZNSt3__26vectorIN7ecourna3app5dados10CFederacaoENS_9allocatorIS4_EEE13__vdeallocateEv");
int cv105_local_ctor(int, int) __asm__("_ZN9CBaseTypeIjLj0ELj9999ELi8EEC2Ej");
int cv105_secao_id_ctor(int, int) __asm__("_ZN9CBaseTypeItLt0ELt9999ELi9EEC2Et");
int cv105_municipio_ctor(int, int) __asm__("_ZN9CBaseTypeIjLj0ELj99999ELi6EEC2Ej");
int cv105_zona_ctor(int, int) __asm__("_ZN9CBaseTypeItLt0ELt9999ELi7EEC2Et");
int cv105_ano_ctor(int, int) __asm__("_ZN9CBaseTypeItLt0ELt9999ELi36EEC2Et");
int cv105_detalhamento_ctor(int, int, int, int) __asm__("_ZN7ecourna3app5dados27CDetalhamentoComparecimentoC1E9CBaseTypeItLt0ELt9999ELi15EES4_S4_");
int cv105_municipiozona_ctor(int, int, int) __asm__("_ZN7ecourna3app5dados14CMunicipioZonaC1ERK9CBaseTypeIjLj0ELj99999ELi6EERKS3_ItLt0ELt9999ELi7EE");
int cv105_secao_ctor(int, int, int, int) __asm__("_ZN7ecourna3app5dados28CIdentificacaoSecaoEleitoralC1ERKNS1_14CMunicipioZonaE9CBaseTypeIjLj0ELj9999ELi8EES6_ItLt0ELt9999ELi9EE");
}

namespace {

const void* volatile cv105_sink;

// CDetalhamentoComparecimento's constructor has two target callers, 9221 and 12098: this stands for 12098.
__attribute__((noinline)) int UsaDetalhamento(int obj, int qtd) { return cv105_detalhamento_ctor(obj, qtd, qtd + 1, qtd + 2) + 3; }
// CMunicipioZona's and CIdentificacaoSecaoEleitoral's have two, 9130 or 9127 and 11616: these stand for 11616.
__attribute__((noinline)) int UsaMunicipioZona(int obj, int municipio, int zona) { return cv105_municipiozona_ctor(obj + 8, municipio, zona) * 3; }
__attribute__((noinline)) int UsaSecao(int obj, int zona, int local) { return cv105_secao_ctor(obj, zona, local + 5, local) * 7; }

// The CBaseType constructors of TLocalID, TSecaoID, TZonaID (their target callers are 9127 or 9130, and 11616),
// TMunicipioID (9130, 9142, 11616, 7787) and TAno (9064 here; 10590, 11469, 11470, 11616): stands for the callers
// not written, so that binaryen keeps each one out of line as the target does.
__attribute__((noinline)) int UsaTipos(int obj, int valor)
{
    return cv105_local_ctor(obj, valor) + cv105_secao_id_ctor(obj + 4, valor + 1) + cv105_zona_ctor(obj + 6, valor + 2) +
           cv105_municipio_ctor(obj + 8, valor + 3) + cv105_ano_ctor(obj + 12, valor + 4);
}

// vector<CFederacao>::__vdeallocate has two target callers, 9207 and 7787: this stands for 7787.
__attribute__((noinline)) int UsaFederacoes(int vetor)
{
    cv105_federacoes_dealloc(vetor + 12);
    return vetor * 9;
}

struct SCv105Roots {
    SCv105Roots()
    {
        cv105_sink = reinterpret_cast<const void*>(&UsaFederacoes);
        cv105_sink = reinterpret_cast<const void*>(&UsaTipos);
        cv105_sink = reinterpret_cast<const void*>(&UsaDetalhamento);
        cv105_sink = reinterpret_cast<const void*>(&UsaMunicipioZona);
        cv105_sink = reinterpret_cast<const void*>(&UsaSecao);
        cv105_sink = cv105_federacoes;
        cv105_sink = cv105_parametrizacao;
        cv105_sink = cv105_configuracoes;
        cv105_sink = cv105_detalhamento;
        cv105_sink = cv105_resultado;
    }
} cv105_roots;

} // namespace
