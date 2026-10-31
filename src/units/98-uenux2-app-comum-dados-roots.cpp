// Roots: keep this unit's functions in the skeleton link the way the target reaches them. None of their callers is
// reconstructed yet, and each has direct callers only: RecuperaLabel (5658) two call sites in fn 654, Lanca (2263) fns
// 2543 and 7787, ConfereDadosDinamicos (3770) fns 1271, 2825 and 10210, DesconverteTipoImpedimento (5699) two call sites
// in fn 11410 (ledger/callgraph.tsv, the "uses" of `pnpm wasm fn`). binaryen inlines a function with one call site, so
// each gets two here, and the stand-ins' bodies differ from each other's and from every target function. 3770's callers
// 1271 (CEleitorDetalhe::GetDinamico) and 2825 (which holds CEleitorDetalhe::MarcaHabilitado inlined) are in the link
// now; its stand-in waits for 10210. The converter's
// users are not reconstructed either: its vtable (@1570668) is what the target keeps it by (slots 2 and 3, table
// slots 2773 and 2774, no direct caller). Declared through asm labels with the object's signatures, so this TU needs no
// uenux2 or ASN.1 header and instantiates nothing; DesconverteTipoImpedimento takes this, unused, and the address of a
// by-value ModuloImpedidos::TipoImpedimento.
extern "C" {
extern const char tipoidentificador_vt[] __asm__("_ZTVN5comum3asn34CConversorTipoIdentificadorEleitorE");
int w5658_root(int) __asm__("_ZN5comum2md14CTradutorFrase13RecuperaLabelERKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE");
void w2263_root(int) __asm__("_ZN5comum23CIntegridadeReferencial5LancaERKNSt3__24pairIbNS1_12basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEEE");
void w3770_root(int, int) __asm__("_ZNK5comum15CEleitorDetalhe21ConfereDadosDinamicosERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int w5699_root(int, int) __asm__("_ZNK5comum3asn18CConversorImpedido26DesconverteTipoImpedimentoEN15ModuloImpedidos15TipoImpedimentoE");
}

namespace {

__attribute__((noinline)) int MesmoRotulo(int a, int b)
{
    return w5658_root(a) == w5658_root(b);
}

__attribute__((noinline)) void LancaOsDois(int primeiro, int segundo)
{
    w2263_root(primeiro);
    w2263_root(segundo + 16);
}

__attribute__((noinline)) void ConfereEleitor(int eleitor, int funcao)
{
    w3770_root(eleitor, funcao);
    w3770_root(eleitor + 200, funcao + 12);
}

__attribute__((noinline)) int SomaImpedimentos(int conversor, int p1, int p2)
{
    return w5699_root(conversor, p1) * 16 + w5699_root(conversor, p2);
}

const void* volatile comum_dados_sink;

struct SComumDadosRoots {
    SComumDadosRoots()
    {
        comum_dados_sink = tipoidentificador_vt;
        comum_dados_sink = reinterpret_cast<const void*>(&MesmoRotulo);
        comum_dados_sink = reinterpret_cast<const void*>(&LancaOsDois);
        comum_dados_sink = reinterpret_cast<const void*>(&ConfereEleitor);
        comum_dados_sink = reinterpret_cast<const void*>(&SomaImpedimentos);
    }
} comum_dados_roots;

} // namespace
