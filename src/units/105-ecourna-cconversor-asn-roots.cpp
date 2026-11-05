// Roots: keep the converters of unit 105 in the skeleton link the way the target keeps them. The users of the outermost
// three are not reconstructed yet (7787 for federations, parametrization and the municipalities' configuration); the
// voter-register result's, 5366 (which stores the vptr, and which 11616 calls), and the attendance detail's, 10273, are
// in the link (unit 122, fragment 321), and their vptr stores keep those vtables. In the
// target each vtable is data whose slots put DoConverte and DoDeconverte in the table, and the inner converters are
// locals of the outer ones, so rooting these vtables keeps the same set. Declared through asm labels, so this TU needs no
// ecourna or ASN.1 header and instantiates nothing.
extern "C" {
extern const char cv105_federacoes[] __asm__("_ZTVN7ecourna3app5dados3asn20CConversorFederacoesE");
extern const char cv105_parametrizacao[] __asm__("_ZTVN7ecourna3app5dados3asn28CConversorParametrizacaoUrnaE");
extern const char cv105_configuracoes[] __asm__("_ZTVN7ecourna3app5dados3asn32CConversorConfiguracaoMunicipiosE");
void cv105_federacoes_dealloc(int) __asm__("_ZNSt3__26vectorIN7ecourna3app5dados10CFederacaoENS_9allocatorIS4_EEE13__vdeallocateEv");
int cv105_detalhamento_ctor(int, int, int, int) __asm__("_ZN7ecourna3app5dados27CDetalhamentoComparecimentoC1E9CBaseTypeItLt0ELt9999ELi15EES4_S4_");
int cv105_copia_parametros(int, int) __asm__("_ZN7ecourna3app5dados15CParametrosUrnaC2ERKS2_");
}

namespace {

const void* volatile cv105_sink;

// CDetalhamentoComparecimento's constructor has two target callers, 9221 and 12098: this stands for 12098.
__attribute__((noinline)) int UsaDetalhamento(int obj, int qtd) { return cv105_detalhamento_ctor(obj, qtd, qtd + 1, qtd + 2) + 3; }
// CMunicipioZona's and CIdentificacaoSecaoEleitoral's constructors have two target callers each, 9130 or 9127 and
// 11616, and the CBaseType constructors of TLocalID, TSecaoID, TZonaID (9127 or 9130, and 11616) and TAno (9064 here,
// 11469 and 11470, unit 66's, 10590, unit 283's, and 11616): all are in the link (11616 is unit 122's), so they need
// no stand-in.

// vector<CFederacao>::__vdeallocate has two target callers, 9207 and 7787: this stands for 7787.
__attribute__((noinline)) int UsaFederacoes(int vetor)
{
    cv105_federacoes_dealloc(vetor + 12);
    return vetor * 9;
}

// CParametrosUrna's implicit copy constructor (3777) has two target callers, 9029 (in the link) and 7787, which calls it
// twice (at code of comum::CConfiguracaoEleicao that binaryen inlined there, a reading): this stands for 7787. The copy
// itself is src/app/roots_iconversorasn.cpp's, uenux2's, ahead of ecourna's objects.
__attribute__((noinline)) int UsaCopiaParametros(int destino, int origem)
{
    cv105_copia_parametros(destino + 88, origem);
    cv105_copia_parametros(destino + 288, origem + 16);
    return destino + origem;
}

struct SCv105Roots {
    SCv105Roots()
    {
        cv105_sink = reinterpret_cast<const void*>(&UsaFederacoes);
        cv105_sink = reinterpret_cast<const void*>(&UsaDetalhamento);
        cv105_sink = reinterpret_cast<const void*>(&UsaCopiaParametros);
        cv105_sink = cv105_federacoes;
        cv105_sink = cv105_parametrizacao;
        cv105_sink = cv105_configuracoes;
    }
} cv105_roots;

} // namespace
