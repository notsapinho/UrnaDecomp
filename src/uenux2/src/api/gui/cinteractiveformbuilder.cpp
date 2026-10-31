// api::CInteractiveFormBuilder (/home/rubio/tse/uenux2/src/api/gui/cinteractiveformbuilder.cpp, named by the records of
// AddLabeledInputControl, fn 653, lines 76 and 86, which is not written: its lines stay blank). Nothing here is TSE's
// text. GetInteractiveForm (fn 554) sits after those lines, a choice: the target's data put this object's first use of
// api::CInteractiveForm<api::IScreen, api::IInputKbd> (its vtable @1579168) right after the two records.

#include "api/gui/cinteractiveformbuilder.h"

#include "api/gui/iscreen.h"

namespace api {
















































































std::shared_ptr<CInteractiveForm<IScreen, IInputKbd>> CInteractiveFormBuilder::GetInteractiveForm(const std::shared_ptr<IPreShow<IScreen>>& preShow,
                                                                                               const std::string& nome, bool limpaTeclado)
{
    std::shared_ptr<CInteractiveForm<IScreen, IInputKbd>> form(new CInteractiveForm<IScreen, IInputKbd>(m_campos, preShow, limpaTeclado));
    if (!nome.empty()) {
        form->SetName(nome);
    }
    m_campos.clear();
    return form;
}

} // namespace api
