// Roots: reach unit 143's functions the way the target's callers do, until those land. The constructors have direct
// callers in the target (ledger/callgraph.tsv), so each gets two call sites in our link and stays out of line, and every
// call passes the type the target's callers pass, so that binaryen folds that argument into the body as the target's did:
// - comum::md::CIdentificacaoSecao's constructor (fn 5887): fns 11453 (written) and 12098, each with eUrnaVota (49);
// - comum::md::CIdentificacaoUrnaContingencia's constructor (fn 5888): fns 11452 and 12098, each with eUrnaContingencia
//   (50).
// CIdentificacaoUrna's constructor (fn 5886) has those two for its callers, as in the target, and needs no stand-in.
// The stand-ins vary the identifiers, which the target's callers read from their entities, and have bodies no target
// function has.
//
// comum::asn::CConversorSecaoEleitoral's slots have no direct caller: the target reaches them through the vtable, whose
// address point fn 11452 (CConversorLocal::DoDesconverte, not written) stores (i32.const 1561712), so the vtable's
// address is the reference the target has.
#include "app/comum/md/cidentificacaosecao.h"
#include "app/comum/md/cidentificacaournacontingencia.h"

extern "C" {
extern const char w143_secaoeleitoral_vt[] __asm__("_ZTVN5comum3asn24CConversorSecaoEleitoralE");
}

namespace {

// stands for fn 12098
__attribute__((noinline)) int w143_secao(comum::TMunicipioID municipio, comum::TZonaID zona, comum::TLocalID local,
    comum::TSecaoID secao)
{
    comum::md::CIdentificacaoSecao* a = new comum::md::CIdentificacaoSecao(comum::eUrnaVota, municipio, zona, local, secao);
    return static_cast<int>(a->GetSecao()) + 3;
}

// stands for fns 11452 and 12098
__attribute__((noinline)) int w143_contingencia(comum::TMunicipioID municipio, comum::TZonaID zona)
{
    comum::md::CIdentificacaoUrnaContingencia* a =
        new comum::md::CIdentificacaoUrnaContingencia(comum::eUrnaContingencia, municipio, zona);
    comum::md::CIdentificacaoUrnaContingencia* b =
        new comum::md::CIdentificacaoUrnaContingencia(comum::eUrnaContingencia, municipio + 2, zona);
    return (a == b) ? 5 : 7;
}

int (*volatile w143_sink_secao)(comum::TMunicipioID, comum::TZonaID, comum::TLocalID, comum::TSecaoID);
int (*volatile w143_sink_contingencia)(comum::TMunicipioID, comum::TZonaID);
const void* volatile w143_sink_vt;

struct SW143Roots {
    SW143Roots()
    {
        w143_sink_secao = w143_secao;
        w143_sink_contingencia = w143_contingencia;
        w143_sink_vt = w143_secaoeleitoral_vt;
    }
} w143_roots;

} // namespace
