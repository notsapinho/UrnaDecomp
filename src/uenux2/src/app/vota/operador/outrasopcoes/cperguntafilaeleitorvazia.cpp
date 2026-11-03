#include "app/vota/operador/outrasopcoes/cperguntafilaeleitorvazia.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/outrasopcoes/caguardaeleitoresvotarem.h"
#include "app/vota/operador/outrasopcoes/cpedetituloencerramento.h"

namespace vota {

CPerguntaFilaEleitorVazia::~CPerguntaFilaEleitorVazia() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Todas as pessoas presentes já votaram?", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: não", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: sim", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CPerguntaFilaEleitorVazia::CPerguntaFilaEleitorVazia()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CPerguntaFilaEleitorVazia& CPerguntaFilaEleitorVazia::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPerguntaFilaEleitorVazia());
    }
    return *s_inst;
}

std::unique_ptr<CPerguntaFilaEleitorVazia> CPerguntaFilaEleitorVazia::s_inst;
std::mutex CPerguntaFilaEleitorVazia::s_mutex;

void CPerguntaFilaEleitorVazia::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
    CLogVota::GetInst().loga("Operador indagado se todas as pessoas presentes votaram");
}

void CPerguntaFilaEleitorVazia::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        m_pNextState = &CPedeTituloEncerramento::GetInst();
        CLogVota::GetInst().LogaTodosEleitoresVotaram(true);
        break;
    case api::INPUT_CORRIGE:
        m_pNextState = &CAguardaEleitoresVotarem::GetInst();
        CLogVota::GetInst().LogaTodosEleitoresVotaram(false);
        break;
    default:
        break;
    }
}

} // namespace vota
