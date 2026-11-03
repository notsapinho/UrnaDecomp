// Roots of unit 183: keep its functions in the skeleton link the way the target keeps them; none of their callers is
// reconstructed. This file compiles with the tree's flags, UENUX2_CXXFLAGS (the fragment's rule), since it emits the
// data sources' instances, a header's code of the uenux2 tree (as unit 139's roots do).
// - comum::CDataSourcesRelatorio<comum::CRdvVota, comum::CEleitores>'s DetalheCandidatoZE and DetalheCandidato (fns 11973
//   and 11972): their one user, fn 3872 (callers 11946 and 12110), passes their addresses, table slots 1635 and 1636, to
//   api::CPaperFormBuilder::AddTextField (fn 604); nothing calls them directly. Taking each address here instantiates
//   them in this object and puts them in the table.
// - The same instance's LinhaPartido (fn 11261; the instance by its call of CRdvVota::GetInst, fn 555, and by band 1,
//   where it follows 11260, that instance's recorded TrailerProporcionalPartido): its one user, fn 12110
//   (vota::CGeraBU's slot 2, not written), passes its address, table slot 2921; nothing calls it directly. Taken here
//   the same way; it goes when 12110 lands.
// - comum::CGeradorRelPU::AdicionaParametro (fn 677) has one caller in the target, fn 11902 (vota::CImpressaoPU's slot
//   2), which calls it 22 times (awk -F'\t' '$2==677' ledger/callgraph.tsv). w183_parametros stands for it and calls it
//   twice, so binaryen keeps it out of line.
// - comum::CGeradorRelPU's vtable, which only fn 11902 stores (its constructor inlined; the class has no key function):
//   w183_relpu_emite, at namespace scope and unrooted, builds the object so that this object emits the vtable and the
//   inline destructor's D2 and D0, and the static constructor keeps the vtable in w183_sink_vtable. It goes when 11902
//   lands.
#include <string>

#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/crdvvota.h"
#include "app/comum/relatorios/cdatasourcesrelatorio.h"
#include "app/comum/relatorios/cgeradorrelpu.h"

extern "C" {
extern const char w183_relpu_vt[] __asm__("_ZTVN5comum13CGeradorRelPUE");
}

__attribute__((optnone, noinline)) void w183_relpu_emite()
{
    comum::CGeradorRelPU gerador;
}

namespace {

using DataSources = comum::CDataSourcesRelatorio<comum::CRdvVota, comum::CEleitores>;

// Stands for fn 11902.
__attribute__((noinline)) void w183_parametros(comum::CGeradorRelPU& gerador, const std::string& nome,
                                               const std::string& valor)
{
    gerador.AdicionaParametro(nome, valor);
    gerador.AdicionaParametro(valor, nome);
}

std::string (*volatile w183_sink_fonte)();
void (*volatile w183_sink_parametros)(comum::CGeradorRelPU&, const std::string&, const std::string&);
const void* volatile w183_sink_vtable;

struct SW183Roots {
    SW183Roots()
    {
        w183_sink_fonte = &DataSources::DetalheCandidatoZE;
        w183_sink_fonte = &DataSources::DetalheCandidato;
        w183_sink_fonte = &DataSources::LinhaPartido;
        w183_sink_parametros = w183_parametros;
        w183_sink_vtable = w183_relpu_vt;
    }
} w183_roots;

} // namespace
