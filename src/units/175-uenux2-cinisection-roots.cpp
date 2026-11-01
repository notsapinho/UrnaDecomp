// Roots: api::CIniSection::SetKey (api/io/cinisection.cpp), whose target caller 5480 (the INI loader, two call sites)
// is not reconstructed yet. binaryen inlines a function called once, so w175_define calls it twice. It goes when 5480
// is in splat/matched.txt.
#include "api/io/cinisection.h"

__attribute__((noinline)) void w175_define(api::CIniSection& secao, const api::CIniKey& chave, const api::CIniKey& outra)
{
    secao.SetKey(chave);
    secao.SetKey(outra);
}

namespace {

void* volatile w175_sink;

struct SW175Roots {
    SW175Roots() { w175_sink = reinterpret_cast<void*>(&w175_define); }
} w175_roots;

} // namespace
