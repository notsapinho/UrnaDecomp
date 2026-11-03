// Roots: keep this unit's functions in the skeleton link the way the target reaches them. Each has direct callers
// only: CTradutorFrase::Traduz (654) fns 1543, 3689, 4160, 4161, 5591, 10631, 11181, 11188, 11260, 11261 and 11946
// (11181, 3689, 10631, 11188, 5591 and 11261 are in the link, the others not), Lanca (2263) fns 2543 and 7787,
// ConfereDadosDinamicos (3770) fns 1271, 2825 and 10210 (ledger/callgraph.tsv, the "uses" of `pnpm wasm fn`).
// RecuperaLabel (5658) needs none: its two call sites are in 654, which ctradutorfrase.cpp holds. binaryen inlines
// a function with one call site, so each gets two here, and the stand-ins' bodies differ from each other's and
// from every target function. 3770's callers 1271 (CEleitorDetalhe::GetDinamico), 2825 (which holds
// CEleitorDetalhe::MarcaHabilitado inlined) and 10210 (which holds CEleitorDetalhe::MarcaVotou inlined, unit 104's
// csincronismooperador.cpp) are all in the link: it has no stand-in. The converter's users are not reconstructed
// either: its vtable (@1570668) is what the target keeps it by (slots 2 and 3, table slots 2773 and 2774, no
// direct caller). CConversorImpedido's vtable (@1567096) is kept the same way: its slots 2 and 3 (table slots 2633
// and 2634, fns 11409 and 11410) have no direct caller either. DesconverteTipoImpedimento (5699) needs no
// stand-in: its one target caller, 11410, which calls it twice, is in the link (cconversorimpedido.cpp). Declared
// through asm labels with the object's signatures, so this TU needs no uenux2 or ASN.1 header and instantiates
// nothing.
extern "C" {
extern const char tipoidentificador_vt[] __asm__("_ZTVN5comum3asn34CConversorTipoIdentificadorEleitorE");
extern const char impedido_vt[] __asm__("_ZTVN5comum3asn18CConversorImpedidoE");
void w654_root(void*, int) __asm__("_ZN5comum2md14CTradutorFrase6TraduzERKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE");
void w2263_root(int) __asm__("_ZN5comum23CIntegridadeReferencial5LancaERKNSt3__24pairIbNS1_12basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEEE");
int w2266_root(int) __asm__("_ZNK5comum15CEleitorDetalhe14SemImpedimentoEv");
void w1937_root(void*, int) __asm__("_ZNK5comum15CEleitorDetalhe12GetBiometriaEv");
}

namespace {

__attribute__((noinline)) int TraduzOsDois(int a, int b)
{
    int traducoes[6];
    w654_root(traducoes, a);
    w654_root(traducoes + 3, b + 12);
    return traducoes[1] + traducoes[4];
}

__attribute__((noinline)) void LancaOsDois(int primeiro, int segundo)
{
    w2263_root(primeiro);
    w2263_root(segundo + 16);
}

// Stands for two target callers of CEleitorDetalhe::SemImpedimento (fn 2266): fns 11233 and 11616; the other three,
// fns 2823 and 2824 (CEleitores's slot 0), unit 110's celeitores.cpp, and 10635 (unit 104's celeitorencontrado.cpp),
// are in the link.
__attribute__((noinline)) int SemImpedimentoEmOutro(int detalhe)
{
    return w2266_root(detalhe + 208) * 5;
}

// Stands for three target callers of CEleitorDetalhe::GetBiometria (fn 1937): fns 3614, 3616 and 10316, none in the
// link; the fourth, fn 1393 (CEleitores::GetCurrentBiometriaEleitor, unit 110's celeitores.cpp), is. The two 40-byte
// results are md::CBiometriaEleitor's, left undestroyed: nothing calls this.
__attribute__((noinline)) int BiometriasDosDois(int a, int b)
{
    int biometrias[20];
    w1937_root(biometrias, a);
    w1937_root(biometrias + 10, b + 112);
    return biometrias[9] + biometrias[19];
}

const void* volatile comum_dados_sink;

struct SComumDadosRoots {
    SComumDadosRoots()
    {
        comum_dados_sink = tipoidentificador_vt;
        comum_dados_sink = impedido_vt;
        comum_dados_sink = reinterpret_cast<const void*>(&TraduzOsDois);
        comum_dados_sink = reinterpret_cast<const void*>(&LancaOsDois);
        comum_dados_sink = reinterpret_cast<const void*>(&SemImpedimentoEmOutro);
        comum_dados_sink = reinterpret_cast<const void*>(&BiometriasDosDois);
    }
} comum_dados_roots;

} // namespace
