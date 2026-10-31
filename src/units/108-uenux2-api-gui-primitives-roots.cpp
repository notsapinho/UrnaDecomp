// Roots: api::SRect::Union (target fn 1916) has five direct callers in the target (fns 1693, 7787, 10896, 10925, 10929).
// 10896 and 10929 are reconstructed, and UneRetangulos stands for the other three; its body is no target function's.
// SRect::Left and Right (fns 5488 and 5487) have two direct callers each in the target, fns 5537 and 10977, and
// SRect::Adjust (fn 2768) four, fns 2770, 5545, 7787 and 10977, none reconstructed. Each needs two call sites in our
// link, or binaryen inlines it into its one caller. AjustaBordas stands for 5537 and 10977, calling each setter twice,
// and for Adjust's four, calling it twice; its body is no target function's. Compiled with APP_CXXFLAGS, like the other
// stand-ins.
#include "api/gui/primitives.h"

namespace {

__attribute__((noinline)) int UneRetangulos(const api::SRect& a, const api::SRect& b)
{
    return a.Union(b).Width() + b.Union(a).Width();
}

__attribute__((noinline)) int AjustaBordas(api::SRect& r, api::TPosition a, api::TPosition b)
{
    r.Left(a);
    r.Right(b);
    r.Left(b);
    r.Right(a);
    return r.Adjust(a, b, b, a).Width() + r.Adjust(b, a, a, b).Width();
}

void* volatile u108_sink;

struct SU108Roots {
    SU108Roots()
    {
        u108_sink = reinterpret_cast<void*>(&UneRetangulos);
        u108_sink = reinterpret_cast<void*>(&AjustaBordas);
    }
} u108_roots;

} // namespace
