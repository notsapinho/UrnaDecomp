#include "app/vota/comum/cpreshowformvota.h"

#include "api/gui/cinteractiveformbuilder.h"

namespace vota {

std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> GetFormularioInterativo(
    api::CInteractiveFormBuilder& builder, const std::string& nome)
{
    return builder.GetInteractiveForm(std::shared_ptr<api::IPreShow<api::IScreen>>(new CPreShowFormVota()), nome, true);
}

} // namespace vota
