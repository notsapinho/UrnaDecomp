// api::CLedFieldMT (/home/rubio/tse/uenux2/src/api/gui/cledfieldmt.cpp). Draw's throw is a record of the target, so
// its position in this file is fixed:
//   11050  Draw(IScreenMT &) const   record at line 46, column 19 (slot 2 of the class's vtable)
// Draw is the class's key function, so this object also emits the vtable with what it names that the class
// declares implicitly or inherits inline: slot 0 is IFormFieldBase<IScreenMT>'s destructor (11052), slot 7
// GetTypeName (11051). The deleting destructor (slot 1, fn 2777, one body with three sibling classes') is a thunk
// into 1565, a body binaryen shares among eight functions; our link forms it with api::CLineField's (3681).

#include "api/gui/cledfieldmt.h"

#include <format>

#include "api/gui/eueguierror.h"
#include "api/gui/iscreenmt.h"

namespace api {

CLedFieldMT::CLedFieldMT(ELedOperacao operacao)
    : m_operacao(operacao)
{
}

// (original lines 23-29: content not recovered)
#line 30
void CLedFieldMT::Draw(IScreenMT& screen) const
{
    switch (m_operacao) {
        case LED_OPERACAO_0:
            screen.Led0();
            break;
        case LED_OPERACAO_1:
            screen.Led1();
            break;
        case LED_OPERACAO_2:
            screen.Led2();
            break;
        case LED_OPERACAO_3:
            screen.Led3();
            break;
        default:
            throw CUeGuiError(EUE_GUI_LEDFIELDMT_OPERACAO_DESCONHECIDA, std::format("Operação desconhecida {}", static_cast<int>(m_operacao)));
    }
}

} // namespace api
