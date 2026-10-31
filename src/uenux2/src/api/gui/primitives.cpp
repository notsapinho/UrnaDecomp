// api::SRect (/home/rubio/tse/uenux2/src/api/gui/primitives.cpp, the file the records of its setters name, lines 20, 26,
// 32 and 38). This comment is the reconstruction's. Target functions of this file:
//   5488 Left, 5487 Right, and 5537, which holds Top and Bottom   not reconstructed; their lines stay free
//   1915 Move(const SPoint&)   no record: the file is a choice, see src/units/108-uenux2-api-gui-primitives.mk
//   MoveX(TPosition)       no target function of its own: binaryen inlined it into its one caller, fn 10956
//   1916 Union(const SRect&) const   no record, as Move
#include "api/gui/primitives.h"

namespace api {

// (original lines 11-16: content not recovered)
#line 17
// <stubs>
// f5488 · 77 B · unmatched · name unknown
// void f5488(i32, i32) { ... }
// </stubs>


// <stubs>
// f5537 · 547 B · unmatched · name unknown
// void f5537(i32, i32, i32, i32) { ... }
// </stubs>


// <stubs>
// f5487 · 77 B · unmatched · name unknown
// void f5487(i32, i32) { ... }
// </stubs>

// (original lines 34-36: content not recovered)
#line 37
void SRect::Move(const SPoint& posicao)
{
    const TPosition x = posicao.x;
    right += x - left;
    const TPosition y = posicao.y;
    bottom += y - top;
    left = x;
    top = y;
}

SRect SRect::Union(const SRect& outro) const
{
    const TPosition direitaOutro = outro.right;
    const TPosition direita = right;
    return Normalized(std::min(left, outro.left), std::min(top, outro.top), std::max(direita, direitaOutro), std::max(bottom, outro.bottom));
}

void SRect::MoveX(TPosition x)
{
    right += x - left;
    left = x;
}

} // namespace api
