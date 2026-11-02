// Roots: keep this unit's functions in the skeleton link the way the target reaches them. None of their callers is
// reconstructed yet, and each has direct callers only: CTradutorFrase::Traduz (654) fns 1543, 3689, 4160, 4161, 5591,
// 10631, 11181, 11188, 11260, 11261 and 11946, Lanca (2263) fns 2543 and 7787, ConfereDadosDinamicos (3770) fns 1271,
// 2825 and 10210 (ledger/callgraph.tsv, the "uses" of `pnpm wasm fn`). RecuperaLabel (5658) needs none: its two call
// sites are in 654, which ctradutorfrase.cpp holds. binaryen inlines a function with one call site, so
// each gets two here, and the stand-ins' bodies differ from each other's and from every target function. 3770's callers
// 1271 (CEleitorDetalhe::GetDinamico), 2825 (which holds CEleitorDetalhe::MarcaHabilitado inlined) and 10210 (which
// holds CEleitorDetalhe::MarcaVotou inlined, unit 104's csincronismooperador.cpp) are all in the link: it has no
// stand-in. The converter's
// users are not reconstructed either: its vtable (@1570668) is what the target keeps it by (slots 2 and 3, table
// slots 2773 and 2774, no direct caller). CConversorImpedido's vtable (@1567096) is kept the same way: its slots 2
// and 3 (table slots 2633 and 2634, fns 11409 and 11410) have no direct caller either. DesconverteTipoImpedimento (5699)
// needs no stand-in: its one target caller, 11410, which calls it twice, is in the link (cconversorimpedido.cpp).
// Declared through asm labels with the object's signatures, so this TU needs no uenux2 or ASN.1 header and instantiates
// nothing.
extern "C" {
extern const char tipoidentificador_vt[] __asm__("_ZTVN5comum3asn34CConversorTipoIdentificadorEleitorE");
extern const char impedido_vt[] __asm__("_ZTVN5comum3asn18CConversorImpedidoE");
void w654_root(void*, int) __asm__("_ZN5comum2md14CTradutorFrase6TraduzERKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE");
void w2263_root(int) __asm__("_ZN5comum23CIntegridadeReferencial5LancaERKNSt3__24pairIbNS1_12basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEEE");
int w3769_root(int) __asm__("_ZNK5comum15CEleitorDetalhe14GetImpedimentoEv");
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

// Stands for fn 3769's one caller, 10635 (vota::CEleitorEncontrado's slot 2), which calls it three times.
__attribute__((noinline)) int ImpedimentosDoTurno(int a, int b)
{
    return w3769_root(a) - 3 * w3769_root(b);
}

const void* volatile comum_dados_sink;

struct SComumDadosRoots {
    SComumDadosRoots()
    {
        comum_dados_sink = tipoidentificador_vt;
        comum_dados_sink = impedido_vt;
        comum_dados_sink = reinterpret_cast<const void*>(&TraduzOsDois);
        comum_dados_sink = reinterpret_cast<const void*>(&LancaOsDois);
        comum_dados_sink = reinterpret_cast<const void*>(&ImpedimentosDoTurno);
    }
} comum_dados_roots;

} // namespace
