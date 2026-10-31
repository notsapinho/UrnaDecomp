// Roots: reach CBaseType's constructors, CStringUtils::Trim's copying overload and std::string's erase the way the target's
// callers do, until they land. The constructors' bodies come from src/app/roots_uenux2.cpp, ahead of both trees; this file
// only calls them, since a constructor with one call site is inlined, and a thunk into binaryen's merge with it.
//
// w112_usa stands for each constructor's target callers, which a real caller ends when it lands (search the indices in
// splat/matched.txt):
//   TQtdEleitor (1960): 9221 12098                TAno (2277): 10590 11469 11470 11616
//   TScoreHabilitacao (2850): 9066 11616          TSecaoID (5848): 9127 11616
//   TZonaID (5850): 9130 11616                    TMunicipioID (2851): 7787 9130 9142 11616
//   TLocalID (5849): 9127 11616                   TCargoID (5682): 9228 11352
// It calls each one twice, so each has two call sites here; 9066 and 9228 are written, the rest are not. Its body is no
// target function's: two constructions and a difference.
//
// w112_apara stands for the callers of the copying Trim (1374): 2256 3712 5343 5604 5667 5896 11377. Two calls, for the same
// reason. Without a second copying function 1879 stays a whole body: with this one binaryen forms the target's merge 3942.
//
// w112_apaga stands for the other callers of std::string::__erase_external_with_move (1136): 654 1880 2626 3510 5159 5497
// 5892. Trim alone is one call site, and binaryen then inlines the erase into Trim, 85 rows more than the target's 9406.
#include <string>

#include "ecourna/api/util/cstringutils.hpp"
#include "ecourna/app/dados/tiposbasicos.hpp"

using namespace ecourna::app::dados;

namespace {

template <typename T, typename V>
__attribute__((noinline)) int w112_usa(V v)
{
    const T a(v);
    const T b(static_cast<V>(v + 1));
    return static_cast<int>(a.Get()) - static_cast<int>(b.Get());
}

__attribute__((noinline)) int w112_apaga(std::string& s, size_t n)
{
    s.erase(1, n);
    return static_cast<int>(s.size());
}

__attribute__((noinline)) int w112_apara(const std::string& s)
{
    const std::string a = ecourna::api::util::CStringUtils::Trim(s);
    const std::string b = ecourna::api::util::CStringUtils::Trim(a + s);
    return static_cast<int>(a.size() * 3 + b.size());
}

__attribute__((noinline)) int w112_todos(int v)
{
    using W = unsigned short;
    using D = unsigned int;
    std::string texto(static_cast<size_t>(v), 'k');
    v += w112_apaga(texto, static_cast<size_t>(v)) + w112_apara(texto);
    return w112_usa<TQtdEleitor, W>(static_cast<W>(v)) + w112_usa<TAno, W>(static_cast<W>(v + 1)) +
           w112_usa<TScoreHabilitacao, W>(static_cast<W>(v + 2)) + w112_usa<TSecaoID, W>(static_cast<W>(v + 3)) +
           w112_usa<TZonaID, W>(static_cast<W>(v + 4)) + w112_usa<TMunicipioID, D>(static_cast<D>(v + 5)) +
           w112_usa<TLocalID, D>(static_cast<D>(v + 6)) + w112_usa<TCargoID, W>(static_cast<W>(v + 7));
}

int (*volatile w112_sink)(int);

struct SW112Roots {
    SW112Roots() { w112_sink = w112_todos; }
} w112_roots;

} // namespace
