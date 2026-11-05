// Roots: reach CBaseType's constructors and CStringUtils::Trim's copying overload the way the target's callers do, until
// they land. The constructors' bodies come from src/app/roots_cbasetype.cpp, ahead of both trees; this file
// only calls them, since a constructor with one call site is inlined, and a thunk into binaryen's merge with it.
//
// w112_usa stands for each constructor's target callers, which a real caller ends when it lands (search the indices in
// splat/matched.txt):
//   TQtdEleitor (1960): 9221 12098                TAno (2277): 10590 11469 11470 11616
//   TScoreHabilitacao (2850): 9066 11616          TSecaoID (5848): 9127 11616
//   TZonaID (5850): 9130 11616                    TMunicipioID (2851): 7787 9130 9142 11616
//   TLocalID (5849): 9127 11616                   TCargoID (5682): 9228 11352
// It calls each one twice, so each has two call sites here; 9066, 9127, 9130, 9142, 9221, 9228, 11469 and 11470 are
// written, the rest are not. Its body is no target function's: two constructions and a difference.
//
// The copying Trim (1374) needs no stand-in: its target callers 2256, 3712, 5343, 5604, 5667, 5896 and 11377 are in the
// link (5604 is unit 155's written Gera).
//
// std::string::__erase_external_with_move (1136) needs no stand-in: its last target caller, 5892 (unit 95's
// IInterfaceSavd::VerificarArquivo, which holds DecodeTLV's erase), is in the link, with Trim (9406),
// CStringUtils::RemoveZerosAEsquerda's two forms (3510, 5159) and Split (1880), unit 00's, CTradutorFrase::Traduz
// (654), unit 98's, CTextFieldMultiLine::GetTextLines (5497), unit 14's, and (anonymous namespace)::Caminho (2626,
// `differs`) in cwasmresource.cpp. w112_apaga, which stood for 5892, went.
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

__attribute__((noinline)) int w112_todos(int v)
{
    using W = unsigned short;
    using D = unsigned int;
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
