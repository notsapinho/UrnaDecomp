// Roots: keep api::CLineField's members (target fns 11068 Draw, 11067 Rect, 11066 GetTypeName and Move 5527, slots 2, 8, 7
// and 9 of the CLineField vtable @1579356) in the skeleton link the way the target keeps them. In the target the vtable is
// referenced only by the constructor, which is inlined into the std::make_shared<CLineField> of fn 2244 (not
// reconstructed yet); the vtable's slots put every member in the table, and no target function calls one directly
// (ledger/callgraph.tsv has no caller of 11066, 11067 or 11068). This stand-in builds the field the same way, which keeps
// the same set and instantiates __shared_ptr_emplace<api::CLineField>, the control block of target fns 11122 and 11121
// (src/units/README.md, "Companion files"). Compiled with APP_CXXFLAGS, like the other stand-ins.
#include <memory>

#include "api/gui/clinefield.h"

namespace {

__attribute__((noinline)) std::shared_ptr<api::IFormField<api::IScreen>> CampoLinha(const api::SPoint& inicio, const api::SPoint& fim,
                                                                                     api::TColor cor)
{
    return std::make_shared<api::CLineField>(inicio, fim, cor);
}

void* volatile clinefield_sink;

struct SCLineFieldRoots {
    SCLineFieldRoots() { clinefield_sink = reinterpret_cast<void*>(&CampoLinha); }
} clinefield_roots;

} // namespace
