#include "app/comum/comparecimentomesario/estados/climitemesariosregistradosatingido.h"

#include <format>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/iform.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/cencerraregistromesarios.h"
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace comum {

CLimiteMesariosRegistradosAtingido::~CLimiteMesariosRegistradosAtingido() = default;

CLimiteMesariosRegistradosAtingido::CLimiteMesariosRegistradosAtingido()
    : CAppState(EVENTO_ENTRADA)
{
    m_formEleitor = TelaRegistroMesarios();
    m_form = TelaLimiteMesariosRegistrados(GetControlador().QUANTIDADE_MAXIMA_MESARIOS);
}

CLimiteMesariosRegistradosAtingido& CLimiteMesariosRegistradosAtingido::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CLimiteMesariosRegistradosAtingido());
    }
    return *s_inst;
}

std::unique_ptr<CLimiteMesariosRegistradosAtingido> CLimiteMesariosRegistradosAtingido::s_inst;
std::mutex CLimiteMesariosRegistradosAtingido::s_mutex;

void CLimiteMesariosRegistradosAtingido::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    m_formEleitor->Slot2();
    GetControlador().LogaLimiteMesariosAtingido();
}

void CLimiteMesariosRegistradosAtingido::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CEncerraRegistroMesarios::GetInst();
    }
}

const IControladorRegistraMesarios& CLimiteMesariosRegistradosAtingido::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaLimiteMesariosRegistrados(
    std::size_t quantidadeMaxima)
{
    api::CMTFormBuilder builder;
    builder.AddTextField("Limite de mesários registrados atingido", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(std::format("Quantidade máxima permitida: {}", quantidadeMaxima), api::SPoint{1, 2},
                         api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: Finalizar", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace comum
