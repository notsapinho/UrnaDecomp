// vota::CEleitorImpedidoJustificarVotoCPF: no record names this file or any of its members; the reconstruction's notes
// are in celeitorimpedidojustificarvotocpf.h and src/units/283-uenux2-app-vota-operador-justificativa.mk.
#include "app/vota/operador/justificativa/celeitorimpedidojustificarvotocpf.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"

namespace vota {

CEleitorImpedidoJustificarVotoCPF::~CEleitorImpedidoJustificarVotoCPF() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Não é permitido justificar com o CPF", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("utilize o número do título", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CEleitorImpedidoJustificarVotoCPF& CEleitorImpedidoJustificarVotoCPF::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEleitorImpedidoJustificarVotoCPF());
    }
    return *s_inst;
}

CEleitorImpedidoJustificarVotoCPF::CEleitorImpedidoJustificarVotoCPF()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

std::unique_ptr<CEleitorImpedidoJustificarVotoCPF> CEleitorImpedidoJustificarVotoCPF::s_inst;
std::mutex CEleitorImpedidoJustificarVotoCPF::s_mutex;

void CEleitorImpedidoJustificarVotoCPF::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

} // namespace vota
