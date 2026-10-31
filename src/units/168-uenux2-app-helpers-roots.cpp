// Roots: reach fragment 168's functions the way the target does. Each is called directly in the target, by callers no
// object of the link holds as code (traps or functions not written), and binaryen inlines a function with one call site,
// so two stand-ins call each. Each stand-in's body is its own: no target function holds these calls.
// - comum::CAppStateContext's constructor (target fn 3844; callers 4713, 7061, 10204) and ProcessKey (3843; callers 4349
//   and 10204): 7061 and 10204 are unit 116's traps, 4349 and 4713 are not written.
// - vota::EhTreinamento (fn 1485; callers 10425, 10566, 10680, 12098): 10566 is unit 50's trap, the others are not
//   written.
// - api::CPolySingletonList::has<vota::IAjusteInicial> (fn 2450; callers 7061, unit 116's trap, and the static
//   initializers in fn 14478, which call it with g_polySingletonsInfo's result and drop what it returns). The instance
//   is the header's template, emitted here first: no object before this one instantiates it.
#include "api/pattern/cpolysingletonlist.h"
#include "app/comum/cappstatecontext.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/iajusteinicial.h"

namespace {

__attribute__((noinline)) int w168_tecla(comum::CAppState* estado, uebyte tecla)
{
    comum::CAppStateContext contexto(estado);
    contexto.ProcessKey(tecla);
    return vota::EhTreinamento() ? 3 : 5;
}

__attribute__((noinline)) int w168_ajuste(comum::CAppState* estado)
{
    comum::CAppStateContext contexto(estado);
    contexto.ProcessKey(7);
    const bool ajuste = api::CPolySingletonList::has<vota::IAjusteInicial>();
    return (ajuste ? 17 : 19) + (vota::EhTreinamento() ? 23 : 29) +
           (api::CPolySingletonList::has<vota::IAjusteInicial>() ? 31 : 37);
}

const void* volatile w168_sink;

struct SW168Roots {
    SW168Roots()
    {
        w168_sink = reinterpret_cast<const void*>(&w168_tecla);
        w168_sink = reinterpret_cast<const void*>(&w168_ajuste);
    }
} w168_roots;

} // namespace
