// api::CTextBox (/home/rubio/tse/uenux2/src/api/gui/ctextbox.cpp, the file the class's records name).
// Target functions of this file:
//   10958 Draw(IScreen&) const   record at line 69, column 19   (pending)
//   10957 Move(const SPoint&)    record at line 90, column 15   (here)
//   10956 Rect() const           record at line 110, column 9   (pending)
// The constructor (record at line 41, column 15, code 4961) has no target function of its own (inlined with
// std::make_shared into fn 11805) and is not reconstructed. Move's throw is a record of the target; the lines around it
// are a choice. The destructors and GetTypeName are emitted with the vtable, in the pending object. The pending members
// are defined in src/units/65-uenux2-ctextbox-pending.cpp.

#include "api/gui/ctextbox.h"

#include "api/gui/eueguierror.h"
#include "api/gui/iform.h"

namespace api {

// (original lines 18-80: content not recovered)
#line 81
void CTextBox::Move(const SPoint& posicao)
{
    if (posicao.x == m_posicao.x && posicao.y == m_posicao.y) {
        return;
    }

    m_posicao = posicao;

    if (m_posicao.x < 3 || m_posicao.y < 1) {
        throw CUeGuiError(EUE_GUI_TEXTBOX_POSICAO_INVALIDA, "A posição da caixa não pode ter x < 3 ou y < 1.");
    }

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

} // namespace api
