// api::SRect (/home/rubio/tse/uenux2/src/api/gui/primitives.cpp, the file the records of its setters name, lines 20, 26,
// 32 and 38). This comment is the reconstruction's. Target functions of this file:
//   5488 Left, 5487 Right (here); Top and Bottom have no target function of their own: binaryen inlined each into its
//   one caller, api::CFramedText::DrawChar (fn 5537, in cframedtext.cpp)
//   1915 Move(const SPoint&)   no record: the file is a choice, see src/units/108-uenux2-api-gui-primitives.mk
//   MoveX(TPosition)       no target function of its own: binaryen inlined it into its one caller, fn 10956
//   1916 Union(const SRect&) const   no record, as Move
//   2768 Adjust(TPosition, TPosition, TPosition, TPosition) const   no record, as Move
#include "api/gui/primitives.h"
#include "api/util/eueasserterror.h"

namespace api {

// (original lines 14-17: content not recovered)
#line 18
void SRect::Left(TPosition l)
{
    ASSERT(right >= l, EUA_RECT_LEFT);
    left = l;
}

void SRect::Top(TPosition t)
{
    ASSERT(bottom >= t, EUA_RECT_TOP);
    top = t;
}

void SRect::Right(TPosition r)
{
    ASSERT(r >= left, EUA_RECT_RIGHT);
    right = r;
}

void SRect::Bottom(TPosition b)
{
    ASSERT(b >= top, EUA_RECT_BOTTOM);
    bottom = b;
}

SRect SRect::Union(const SRect& outro) const
{
    const TPosition direitaOutro = outro.right;
    const TPosition direita = right;
    return Normalized(std::min(left, outro.left), std::min(top, outro.top), std::max(direita, direitaOutro), std::max(bottom, outro.bottom));
}

void SRect::Move(const SPoint& posicao)
{
    const TPosition x = posicao.x;
    right += x - left;
    const TPosition y = posicao.y;
    bottom += y - top;
    left = x;
    top = y;
}

void SRect::MoveX(TPosition x)
{
    right += x - left;
    left = x;
}

SRect SRect::Adjust(TPosition dLeft, TPosition dTop, TPosition dRight, TPosition dBottom) const
{
    return Normalized(left + dLeft, top + dTop, right + dRight, bottom + dBottom);
}

} // namespace api
