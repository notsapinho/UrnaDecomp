// Roots: api::SRect::Union (target fn 1916) has five direct callers in the target (fns 1693, 7787, 10896, 10925, 10929).
// Only 10929 is reconstructed, so binaryen would inline Union into it. This stand-in is the second call site, for the
// other four. Its body is no target function's. Compiled with APP_CXXFLAGS, like the other stand-ins.
#include "api/gui/primitives.h"

namespace {

__attribute__((noinline)) int UneRetangulos(const api::SRect& a, const api::SRect& b)
{
    return a.Union(b).Width() + b.Union(a).Width();
}

void* volatile u108_sink;

struct SU108Roots {
    SU108Roots() { u108_sink = reinterpret_cast<void*>(&UneRetangulos); }
} u108_roots;

} // namespace
