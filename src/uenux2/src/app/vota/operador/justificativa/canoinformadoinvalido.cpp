// vota::CAnoInformadoInvalido: no record names this file or any of its members; the reconstruction's notes are in
// canoinformadoinvalido.h and src/units/283-uenux2-app-vota-operador-justificativa.mk.
#include "app/vota/operador/justificativa/canoinformadoinvalido.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/operador/justificativa/cpedeanonascimento.h"

namespace vota {

CAnoInformadoInvalido::~CAnoInformadoInvalido() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField("Ano de nascimento inválido.", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: tentar novamente", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CAnoInformadoInvalido::CAnoInformadoInvalido()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CAnoInformadoInvalido& CAnoInformadoInvalido::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CAnoInformadoInvalido());
    }
    return *s_inst;
}

std::unique_ptr<CAnoInformadoInvalido> CAnoInformadoInvalido::s_inst;
std::mutex CAnoInformadoInvalido::s_mutex;

void CAnoInformadoInvalido::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CAnoInformadoInvalido::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CPedeAnoNascimento::GetInst();
    }
}

} // namespace vota
