// Roots: keep this unit's comum converters in the skeleton link the way the target keeps them. Their users are not
// reconstructed yet. In the target each converter's vtable is data whose slots put the bodies in the table, and no body
// of these slots has a direct caller (ledger/callgraph.tsv), so rooting the vtable keeps the same set:
//   CConversorEleicoesVota (@1571216; fns 11348, 11347, 11350, 11349), whose vptr fn 7787 stores (not written).
// CConversorProcessoEleitoral's vtable (@1570408; fns 11362 and 11363) is not here: fn 3771 (unit 280's
// CarregaProcessoEleitoral), the one target function that stores its vptr, is written and in the link, and a link
// without its sink moves no row.
// w140_votos calls md::CVotos' constructor (fn 2794), standing for its target caller 7787 (not written); 11351 and
// comum::CRdvVota's slots 0 and 1 (fns 5733, 11490, unit 13) are the other call sites.
// Declared through asm labels where no header is needed.
extern "C" {
extern const char w140_eleicoes_vt[] __asm__("_ZTVN5comum3asn22CConversorEleicoesVotaE");
int w140_cvotos(void*, void*) __asm__("_ZN5comum2md6CVotosC1ENSt3__26vectorINS0_5CVotoENS2_9allocatorIS4_EEEE");
}

namespace {

__attribute__((noinline)) int w140_votos(char* destino, char* votos)
{
    return w140_cvotos(destino, votos + 4) * 3;
}

const void* volatile w140_sink;

struct SRoots140 {
    SRoots140()
    {
        w140_sink = w140_eleicoes_vt;
        w140_sink = reinterpret_cast<const void*>(&w140_votos);
    }
} w140_roots;

} // namespace
