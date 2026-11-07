// Roots: api::SRect::Union (target fn 1916) has five direct callers in the target (fns 1693, 7787, 10896, 10925,
// 10929). 10896, 10925 and 10929 are reconstructed, and so is 1693 (unit 84's); UneRetangulos stands for
// 7787 with one call (a second stood for 1693 until it was written); its body is no target function's. SRect::Left and
// Right (fns 5488 and 5487) have two direct callers each in the target, fns 5537 (unit 92's DrawChar) and 10977 (unit
// 40's api::CProgressBar::Draw), both in the link, so no stand-in calls them (AjustaBordas's calls of them went with
// 10977). SRect::Adjust (fn 2768) has four, fns 2770, 5545, 7787 and 10977, of which 2770 (unit 84's),
// 5545 (api::CFormBuilder::AddProgressBar, unit 31's, which holds CProgressBar's constructor inlined) and 10977 are in
// the link; AjustaBordas stands for 7787 with one call (its call for 5545 went); its body is no target function's.
// Compiled with APP_CXXFLAGS, like the other stand-ins.
#include "api/gui/primitives.h"

namespace {

__attribute__((noinline)) int UneRetangulos(const api::SRect& a, const api::SRect& b)
{
    return a.Union(b).Width() - b.Width();
}

__attribute__((noinline)) int AjustaBordas(const api::SRect& r, api::TPosition a, api::TPosition b)
{
    return r.Adjust(a, b, b, a).Width() + b;
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
