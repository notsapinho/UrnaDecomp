// Roots: a stand-in for fn 7787, the one target caller of libc++'s sort over unsigned char but its own recursion (fn
// 4820, std::__introsort<_ClassicAlgPolicy, ranges::less, unsigned char*, true>, and the seven functions only it
// reaches; src/units/439-libcxx-sort-bytes.mk has the evidence). 7787 is not written. A std::sort over unsigned char
// with the default order calls the extern template __sort<__less<unsigned char>&, unsigned char*> (libc++'s
// __algorithm/sort.h), which libc++.a's algorithm.o defines and binaryen inlines into its one caller: 7787 in the
// target, this stand-in here. 7787 calls 4820 once, so the stand-in sorts once; it goes when 7787 is in the link. The
// file includes only standard headers and declares no TSE function, so no match comes from this object. Address-taken
// from a static constructor.
#include <algorithm>
#include <vector>

namespace {

const void* volatile w439_sink;

// Stands for fn 7787's one call of the family (its call of fn 4820 at +0x11bab): std::sort over the byte vector 7787
// fills with the byte at +0 of each element of CConfiguracaoEleicao::GetTodosCargos()'s result (fn 5790), the cargos'
// TCargoID, a uebyte (std::uint8_t, ecourna's api/uetypes.hpp), by our CCargo header: a reading.
__attribute__((noinline)) std::vector<unsigned char>::size_type OrdenaCargos(std::vector<unsigned char>& cargos)
{
    std::sort(cargos.begin(), cargos.end());
    return cargos.size() + 439;
}

struct S439Roots {
    S439Roots() { w439_sink = reinterpret_cast<const void*>(&OrdenaCargos); }
} w439_roots;

} // namespace
