// Roots of fragment 225, compiled at the tree's flags (UENUX2_CXXFLAGS): the instance below is TSE-template code whose
// target copy is a uenux2 object's.
#include <vector>

#include "app/comum/dados/md/eleitor/celeitor.h"

// comum::asn::CVisitanteEleitor's vtable (@1567204: slots 5698, 11408, 11407). Its only vptr store is the constructor fn
// 11523 holds inlined (a std::function's call operator in CEleitores::GetEleitoresEstaticos, not written); the slots have
// no direct caller but the D0's call of the D2. The address stands for that store and goes when 11523 is in the link.
extern "C" {
extern const char visitanteeleitor_vt[] __asm__("_ZTVN5comum3asn17CVisitanteEleitorE");
}

// std::vector<md::CEleitor>'s __swap_out_circular_buffer (target fn 5700), which its only target caller,
// comum::asn::CConversorEntidadeEleitores's slot 2 (fn 11411, not written), calls twice, and which no object of ours
// instantiates: the relocation of the 104-byte voters, each destroyed through fn 379.
template void std::vector<comum::md::CEleitor>::__swap_out_circular_buffer(
    std::__split_buffer<comum::md::CEleitor, std::allocator<comum::md::CEleitor>&>&);

// The instance is private to vector, hence the label; at its calls clang would inline the instance this TU defines into
// the stand-in, and [[clang::noinline]] keeps the two calls (src/units/README.md "Companion files", roots_vector.cpp).
extern "C" void w225_reloca(int, int) __asm__(
    "_ZNSt3__26vectorIN5comum2md8CEleitorENS_9allocatorIS3_EEE26__swap_out_circular_bufferERNS_14__split_bufferIS3_RS5_EE");

// Stands in for 11411's two calls: two call sites, since binaryen inlines a function called once
// (docs/reference/facts/tool-traps.md X1). It goes when 11411 is in the link.
int w225_cresce(int eleitores, int buffer)
{
    [[clang::noinline]] w225_reloca(eleitores, buffer);
    [[clang::noinline]] w225_reloca(eleitores + 12, buffer + 20);
    return eleitores;
}

namespace {

const void* volatile comumasn225_sink[2];

struct SComumAsn225Roots {
    SComumAsn225Roots()
    {
        comumasn225_sink[0] = visitanteeleitor_vt;
        comumasn225_sink[1] = reinterpret_cast<const void*>(&w225_cresce);
    }
} comumasn225_roots;

} // namespace
