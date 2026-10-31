// Roots: keep this unit's comum converters in the skeleton link the way the target keeps them. Their users are not
// reconstructed yet. In the target each converter's vtable is data whose slots put the bodies in the table, and no body
// of these slots has a direct caller (ledger/callgraph.tsv), so rooting the vtables keeps the same set:
//   CConversorProcessoEleitoral (@1570408; fns 11362 and 11363), whose vptr fn 3771 stores (not written);
//   CConversorEleicoesVota (@1571216; fns 11348, 11347, 11350, 11349), whose vptr fn 7787 stores (not written).
// w140_conversores calls CConversorVotosCargo's constructor (fn 5683), standing for its target caller 11349
// (CConversorEleicoesVota::DoDesconverte, not written); 11350 is the other call site. The constructor stores the
// converter's vptr, so its slots (11352, 11351) are kept the way the target keeps them.
// w140_votos calls md::CVotos' constructor (fn 2794), standing for its target callers 5733, 7787 and 11490 (not
// written); 11351 is the other call site.
// w140_mapa destroys a std::map<md::TCargoID, md::CVotos>, standing for fns 5971 and 11514 (not written), which destroy
// the map comum::CRdvVota's slot 0 (fn 5733, not written) returns: its nodes are 32 bytes, the cargo's byte at +16 and
// the CVotos at +20, and 5733 takes each key from an SCargoInfo's cargo. Its destroy is fn 2877. The key's type is
// chosen. No source of the tree instantiates that map, so this file's copy is the one the link keeps, and the file
// compiles at the tree's flags (the fragment's rule).
// Declared through asm labels where no header is needed.
#include <map>

#include "app/comum/dados/md/rdv/cvotoscargos.h"

extern "C" {
extern const char w140_processo_vt[] __asm__("_ZTVN5comum3asn27CConversorProcessoEleitoralE");
extern const char w140_eleicoes_vt[] __asm__("_ZTVN5comum3asn22CConversorEleicoesVotaE");
int w140_votoscargo(void*, const void*) __asm__("_ZN5comum3asn20CConversorVotosCargoC1ERKNS_2md12CVotosCargos10SCargoInfoE");
int w140_cvotos(void*, void*) __asm__("_ZN5comum2md6CVotosC1ENSt3__26vectorINS0_5CVotoENS2_9allocatorIS4_EEEE");
}

namespace {

__attribute__((noinline)) int w140_conversores(char* destino, const char* info)
{
    return w140_votoscargo(destino + 20, info + 12) * 5;
}

__attribute__((noinline)) int w140_votos(char* destino, char* votos)
{
    return w140_cvotos(destino, votos + 4) * 3;
}

__attribute__((noinline)) void w140_mapa(std::map<comum::md::TCargoID, comum::md::CVotos>* mapa)
{
    mapa->~map();
}

const void* volatile w140_sink;

struct SRoots140 {
    SRoots140()
    {
        w140_sink = w140_processo_vt;
        w140_sink = w140_eleicoes_vt;
        w140_sink = reinterpret_cast<const void*>(&w140_conversores);
        w140_sink = reinterpret_cast<const void*>(&w140_votos);
        w140_sink = reinterpret_cast<const void*>(&w140_mapa);
    }
} w140_roots;

} // namespace
