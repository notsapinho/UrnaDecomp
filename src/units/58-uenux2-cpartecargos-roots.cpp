// Roots: the comum::CParteCargos constructor (target fn 5587) has two direct callers in the target (fns 5971 and 11946,
// ledger/callgraph.tsv), neither reconstructed and neither through the table. Both build the part with
// std::make_shared<comum::CParteCargos> (the __shared_ptr_emplace<comum::CParteCargos> vptr 1544352, then the
// constructor at +12), moving two std::shared_ptr<api::IReportPart> into it, and keep the constructor's result (a
// constructor returns this in the wasm ABI). These two stand-ins build it the same way, with different bodies (wasm-opt
// would merge identical ones and inline the constructor into the survivor), and are address-taken from a static
// constructor. As unit 29's roots do, this TU includes the class header for make_shared: the control block it
// instantiates, __shared_ptr_emplace<comum::CParteCargos> (D2 11948 and D0 11947 in the target), is this object's own,
// since no source of the unit instantiates it, and it moves to the real callers' objects when they land. The class's
// destructors (fns 11208 and 11207) have no direct caller in the target: they are reached through the vtable the
// constructor stores. Compiled with APP_CXXFLAGS, like the other stand-ins.
#include <memory>
#include <utility>

#include "app/comum/relatorios/cpartecargos.h"

namespace {

__attribute__((noinline)) std::shared_ptr<api::IReportPart> ParteCargosA(std::shared_ptr<api::IReportPart> cabecalho,
                                                                          std::shared_ptr<api::IReportPart> parte)
{
    return std::make_shared<comum::CParteCargos>(std::move(cabecalho), std::move(parte));
}

// no header part, so the two callers differ
__attribute__((noinline)) std::shared_ptr<api::IReportPart> ParteCargosB(std::shared_ptr<api::IReportPart> parte)
{
    return std::make_shared<comum::CParteCargos>(nullptr, std::move(parte));
}

void* volatile w5587_sink;

struct SW5587Roots {
    SW5587Roots()
    {
        w5587_sink = reinterpret_cast<void*>(&ParteCargosA);
        w5587_sink = reinterpret_cast<void*>(&ParteCargosB);
    }
} w5587_roots;

} // namespace
