// Roots: keep this unit's functions in the skeleton link the way the target reaches them. Each has direct callers only:
// CTradutorFrase::Traduz (654) fns 1543, 3689, 4160, 4161, 5591, 10631, 11181, 11188, 11260, 11261 and 11946 (11181,
// 3689, 10631, 11188, 5591, 11261, 1543 and 4161 are in the link, the others not), Lanca (2263) fns 2543 (in the link)
// and 7787, ConfereDadosDinamicos (3770) fns 1271, 2825 and 10210 (ledger/callgraph.tsv, the "uses" of `pnpm wasm fn`).
// RecuperaLabel (5658) needs none: its two call sites are in 654, which ctradutorfrase.cpp holds. binaryen inlines a
// function with one call site, so each gets two here, and the stand-ins' bodies differ from each other's and from every
// target function. 3770's callers 1271 (CEleitorDetalhe::GetDinamico), 2825 (which holds
// CEleitorDetalhe::MarcaHabilitado inlined) and 10210 (which holds CEleitorDetalhe::MarcaVotou inlined, unit 104's
// csincronismooperador.cpp) are all in the link: it has no stand-in. CConversorTipoIdentificadorEleitor's vtable
// (@1570668) is what the target keeps that converter by (slots 2 and 3, table slots 2773 and 2774, no direct caller);
// the one target function that stores its vptr, 11363 (CConversorProcessoEleitoral::DoDesconverte, unit 140), is in
// the link too, and the sink stays until a link without it is measured (src/units/README.md "Companion files").
// CConversorImpedido's vtable (@1567096) has no sink: its slots 2 and 3 (table slots 2633 and 2634, fns 11409 and
// 11410) have no direct caller either, and the one target function that stores its vptr, 11517 (the std::function
// body of CEleitores::GetEleitoresImpedidos's lambda, unit 110's celeitores.cpp), is in the link.
// DesconverteTipoImpedimento (5699) needs no stand-in: its one target caller, 11410, which calls it twice, is in the
// link (cconversorimpedido.cpp). Declared through asm labels with the object's signatures, so this TU needs no uenux2
// or ASN.1 header and instantiates nothing.
extern "C" {
extern const char tipoidentificador_vt[] __asm__("_ZTVN5comum3asn34CConversorTipoIdentificadorEleitorE");
void w654_root(void*, int) __asm__("_ZN5comum2md14CTradutorFrase6TraduzERKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE");
void w2263_root(int) __asm__("_ZN5comum23CIntegridadeReferencial5LancaERKNSt3__24pairIbNS1_12basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEEE");
int w2266_root(int) __asm__("_ZNK5comum15CEleitorDetalhe14SemImpedimentoEv");
void w1937_root(void*, int) __asm__("_ZNK5comum15CEleitorDetalhe12GetBiometriaEv");
void w2543_root() __asm__("_ZN5comum24VerificaIntegridadeVotosEv");
void w2834_root(void*, int) __asm__("_ZNK5comum7CCargos13GetMapaCargosEv");
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

// Stands for fn 11616, a target caller of CEleitorDetalhe::SemImpedimento (fn 2266) not written; the other four, fns
// 2823 and 2824 (CEleitores's slot 0), unit 110's celeitores.cpp, 10635 (unit 104's celeitorencontrado.cpp) and 11233
// (fragment 317's cgeradorrellistaeleitores.cpp), are in the link.
__attribute__((noinline)) int SemImpedimentoEmOutro(int detalhe)
{
    return w2266_root(detalhe + 208) * 5;
}

// Stands for a target caller of CEleitorDetalhe::GetBiometria (fn 1937), fn 3614, not in the link, with one call; the
// call that stood for 10316 went once it was in the link (unit 135's); the others, fn 1393
// (CEleitores::GetCurrentBiometriaEleitor, unit 110's celeitores.cpp) and fn 3616 (unit 319's), are. The 40-byte
// result is md::CBiometriaEleitor's, left undestroyed: nothing calls this.
__attribute__((noinline)) int BiometriasDosDois(int a, int b)
{
    int biometrias[10];
    w1937_root(biometrias, a + b);
    return biometrias[9];
}

// Stands for fn 2543's target callers (comum::VerificaIntegridadeVotos): 6734, 7174 (twice) and 12098, none in the
// link.
__attribute__((noinline)) void VerificaDuasVezes(int vezes)
{
    w2543_root();
    if (vezes > 1) {
        w2543_root();
    }
}

// Stands for fn 2834's target callers but 2543: 5953, 7787 and 12244, none in the link
// (comum::CCargos::GetMapaCargos, ccargos.cpp, unit 88's file). The two 12-byte maps are left undestroyed: nothing
// calls this.
__attribute__((noinline)) int MapasDeCargos(int a, int b)
{
    int mapas[6];
    w2834_root(mapas, a);
    w2834_root(mapas + 3, b + 28);
    return mapas[2] + mapas[5];
}

const void* volatile comum_dados_sink;

struct SComumDadosRoots {
    SComumDadosRoots()
    {
        comum_dados_sink = tipoidentificador_vt;
        comum_dados_sink = reinterpret_cast<const void*>(&TraduzOsDois);
        comum_dados_sink = reinterpret_cast<const void*>(&LancaOsDois);
        comum_dados_sink = reinterpret_cast<const void*>(&SemImpedimentoEmOutro);
        comum_dados_sink = reinterpret_cast<const void*>(&BiometriasDosDois);
        comum_dados_sink = reinterpret_cast<const void*>(&VerificaDuasVezes);
        comum_dados_sink = reinterpret_cast<const void*>(&MapasDeCargos);
    }
} comum_dados_roots;

} // namespace
