// vota::CEleitorMenor16Anos: no record names this file or any of its members; the reconstruction's notes are in
// celeitormenor16anos.h and src/units/283-uenux2-app-vota-operador-justificativa.mk.
#include "app/vota/operador/justificativa/celeitormenor16anos.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/operador/justificativa/cpedeanonascimento.h"

namespace vota {

CEleitorMenor16Anos::~CEleitorMenor16Anos() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField("Eleitor não pode votar ou justificar", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("por não ter idade mínima", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: tentar novamente", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CEleitorMenor16Anos::CEleitorMenor16Anos()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CEleitorMenor16Anos& CEleitorMenor16Anos::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorMenor16Anos());
    }
    return *s_inst;
}

std::unique_ptr<CEleitorMenor16Anos> CEleitorMenor16Anos::s_inst;
std::mutex CEleitorMenor16Anos::s_mutex;

void CEleitorMenor16Anos::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CEleitorMenor16Anos::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CPedeAnoNascimento::GetInst();
    }
}

} // namespace vota
