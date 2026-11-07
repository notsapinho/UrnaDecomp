#include "app/vota/comum/cpreshowformvota.h"

#include "api/gui/capplication.h"
#include "api/gui/cfixedtext.h"
#include "api/gui/cformbuilder.h"
#include "api/gui/cinteractiveformbuilder.h"
#include "api/gui/iscreen.h"

namespace vota {

void CPreShowFormVota::DesenhaDescricaoModo(api::IScreen& tela, api::SPoint posicao)
{
    const std::string modo = api::CApplication::GetDescricaoModo();
    if (!modo.empty()) {
        tela.DrawText(posicao, api::CFixedText(modo, api::ALINHAMENTO_CENTRO), api::SFont{20, 1},
                      static_cast<api::TColor>(3), static_cast<api::TColor>(0));
    }
}

void CPreShowFormVota::PreShow(api::IScreen& tela)
{
    tela.Clear(static_cast<api::TColor>(1));
    DesenhaDescricaoModo(tela, api::SPoint{340, 5});
}

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
