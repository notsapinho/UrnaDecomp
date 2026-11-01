// Pending member: the api::CInputMenuField member src/uenux2/src/api/gui/cinputmenufield.cpp does not hold yet. The
// class's vtable is emitted there with the destructor, its key function, and needs it defined; its body is NOT the
// target's, it traps. Target function, reached only through the vtable:
// - Move 10895 (slot 9, 255 B, record cinputmenufield.cpp 278:21, the CPolySingleton<IScreen>::instance() line): it ends
//   with a call of Reposiciona (fn 2770), which is not written (src/units/84-uenux2-cinputmenufield.mk has why), so Move
//   waits for 2770. Written as below on line 272, it scored 4 over 117 rows, all operand-only, and was `unresolved
//   self-voted`: 2770's name came only from Move's own vote. The fragment has what was measured on it.
//       if (posicao.x == m_posicao.x && posicao.y == m_posicao.y) {
//           return;
//       }
//       IScreen& tela = CPolySingleton<IScreen>::instance();
//       tela.Clear(Rect(), static_cast<TColor>(1));
//       const TPosition x = posicao.x;
//       m_posicao.x = x;
//       const TPosition y = posicao.y;
//       m_posicao.y = y;
//       for (CMenuItem& item : m_itens) {
//           item.Desloca(x, y);
//       }
//       m_posicao = posicao;
//       m_rectItens.Move(m_posicao);
//       Reposiciona();
// Move it into cinputmenufield.cpp when it is reconstructed, and delete this file.
#include "api/gui/cinputmenufield.h"

namespace api {

void CInputMenuField::Move(const SPoint&)
{
    __builtin_trap();
}

} // namespace api
