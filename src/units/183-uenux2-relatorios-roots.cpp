// Roots of unit 183: keep its functions in the skeleton link the way the target keeps them; none of their callers is
// reconstructed. This file compiles with the tree's flags, UENUX2_CXXFLAGS (the fragment's rule), since it emits the
// data sources' instances, a header's code of the uenux2 tree (as unit 139's roots do).
// - comum::CDataSourcesRelatorio<comum::CRdvVota, comum::CEleitores>'s LinhaPartido (fn 11261; the instance by its call
//   of CRdvVota::GetInst, fn 555, and by band 1, where it follows 11260, that instance's recorded
//   TrailerProporcionalPartido): its one user, fn 12110
//   (vota::CGeraBU's slot 2, not written), passes its address, table slot 2921; nothing calls it directly. Taken here
//   the same way; it goes when 12110 lands.
#include <string>

#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/crdvvota.h"
#include "app/comum/relatorios/cdatasourcesrelatorio.h"

namespace {

using DataSources = comum::CDataSourcesRelatorio<comum::CRdvVota, comum::CEleitores>;

std::string (*volatile w183_sink_fonte)();

struct SW183Roots {
    SW183Roots()
    {
        w183_sink_fonte = &DataSources::LinhaPartido;
    }
} w183_roots;

} // namespace
