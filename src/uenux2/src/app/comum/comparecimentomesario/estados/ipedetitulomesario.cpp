#include "app/comum/comparecimentomesario/estados/ipedetitulomesario.h"

#include <utility>

#include "api/gui/cinteractiveform.h"


























namespace comum {

IPedeTituloMesario::IPedeTituloMesario(std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> form,
                                       std::shared_ptr<api::IForm<api::IScreen>> formEleitor)
    : CAppState(EVENTO_ENTRADA), m_form(std::move(form)), m_formEleitor(std::move(formEleitor))
{
}

void IPedeTituloMesario::StartState()
{
    m_pNextState = this;
    m_formEleitor->Slot2();
    m_form->Slot2();
}

} // namespace comum
