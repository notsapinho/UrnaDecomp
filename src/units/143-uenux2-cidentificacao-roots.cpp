// Roots: reach unit 143's functions the way the target's callers do, until those land. The constructors have direct
// callers in the target (ledger/callgraph.tsv), so each gets two call sites in our link and stays out of line, and every
// call passes the type the target's callers pass, so that binaryen folds that argument into the body as the target's did:
// - comum::md::CIdentificacaoSecao's constructor (fn 5887): fns 11453 (written) and 12098, each with eUrnaVota (49);
// - comum::md::CIdentificacaoUrnaContingencia's constructor (fn 5888): fns 11452 (written) and 12098, each with
//   eUrnaContingencia (50).
// CIdentificacaoUrna's constructor (fn 5886) has those two for its callers, as in the target, and needs no stand-in.
// The stand-ins vary the identifiers, which the target's callers read from their entities, and have bodies no target
// function has.
//
// comum::asn::CConversorSecaoEleitoral's slots have no direct caller: the target reaches them through the vtable, whose
// address point fns 11423, 11424, 11451 and 11452 store (i32.const 1561712; CConversorDadosDisponiveisCarga's two slots,
// written in fragment 245, and CConversorLocal's two). All four are in the link (11452 since unit 296), so the sink that
// stood for 11452 went.
#include "app/comum/md/cidentificacaosecao.h"
#include "app/comum/md/cidentificacaournacontingencia.h"

namespace {

// stands for fn 12098
__attribute__((noinline)) int w143_secao(comum::TMunicipioID municipio, comum::TZonaID zona, comum::TLocalID local,
    comum::TSecaoID secao)
{
    comum::md::CIdentificacaoSecao* a = new comum::md::CIdentificacaoSecao(comum::eUrnaVota, municipio, zona, local, secao);
    return static_cast<int>(a->GetSecao()) + 3;
}

// stands for fn 12098 (11452 is in the link)
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

struct SW143Roots {
    SW143Roots()
    {
        w143_sink_secao = w143_secao;
        w143_sink_contingencia = w143_contingencia;
    }
} w143_roots;

} // namespace
