#include "app/comum/comparecimentomesario/estados/ipedetitulomesario.h"

#include <utility>

#include "api/gui/cformbuilder.h"
#include "api/gui/cinteractiveform.h"
#include "api/gui/iform.h"
#include "api/gui/itext.h"
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"






















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

std::shared_ptr<api::IForm<api::IScreen>> IPedeTituloMesario::GetTelaEleitor()
{
    api::CFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_MODO |
                            api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("REGISTRO DE MESÁRIOS", api::SPoint(320, 150), FONTE_TITULO_REGISTRO_MESARIOS,
                         api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("Siga as instruções no terminal do mesário.", api::SPoint(320, 250),
                         FONTE_TEXTO_REGISTRO_MESARIOS, api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2),
                         static_cast<api::TColor>(1));
    return builder.GetForm("");
}

} // namespace comum
