#include "app/vota/comum/cpreshowformvota.h"

#include "api/gui/cformbuilder.h"
#include "api/gui/cinteractiveformbuilder.h"

namespace vota {

std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> GetFormularioInterativo(
    api::CInteractiveFormBuilder& builder, const std::string& nome)
{
    return builder.GetInteractiveForm(std::shared_ptr<api::IPreShow<api::IScreen>>(new CPreShowFormVota()), nome, true);
}

std::shared_ptr<api::IForm<api::IScreen>> GetFormulario(api::CFormBuilder& builder, const std::string& nome)
{
    return builder.GetForm(std::shared_ptr<api::IPreShow<api::IScreen>>(new CPreShowFormVota()), nome);
}

} // namespace vota
