// vota::CPedeAnoNascimento: no record names this file or any of its members; the reconstruction's notes are in
// cpedeanonascimento.h and src/units/283-uenux2-app-vota-operador-justificativa.mk.
#include "app/vota/operador/justificativa/cpedeanonascimento.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

CPedeAnoNascimento::~CPedeAnoNascimento() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Digite o ANO de nascimento: ", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    AdicionaCampoNumerico(builder, 4, true, api::SPoint{29, 2});
    builder.AddTextField("CORRIGE: cancelar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: justificar", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    return builder.GetInteractiveForm("", true);
}

} // namespace

CPedeAnoNascimento::CPedeAnoNascimento()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CPedeAnoNascimento& CPedeAnoNascimento::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeAnoNascimento());
    }
    return *s_inst;
}

std::unique_ptr<CPedeAnoNascimento> CPedeAnoNascimento::s_inst;
std::mutex CPedeAnoNascimento::s_mutex;

void CPedeAnoNascimento::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota
