// vota::CPerguntaEleitorVotando (app/vota/operador/aguardaeleitor/cperguntaeleitorvotando.cpp). This comment is the
// reconstruction's: no record names this file or its functions, so every line is a choice, in the order of the use
// bands where they give one (src/units/152-uenux2-app-vota-operador-estados.mk).
#include "app/vota/operador/aguardaeleitor/cperguntaeleitorvotando.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/ipc/cmessagequeue.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/aguardaeleitor/cperguntacodigosuspensao.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"

namespace vota {

CPerguntaEleitorVotando::~CPerguntaEleitorVotando() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_1);
    builder.AddBuzz(51, 10);
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("O eleitor ainda está votando?", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: não", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: sim", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CPerguntaEleitorVotando::CPerguntaEleitorVotando()
    : comum::CAppState(EVENTO_TECLA | EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CPerguntaEleitorVotando& CPerguntaEleitorVotando::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPerguntaEleitorVotando());
    }
    return *s_inst;
}

std::unique_ptr<CPerguntaEleitorVotando> CPerguntaEleitorVotando::s_inst;
std::mutex CPerguntaEleitorVotando::s_mutex;

void CPerguntaEleitorVotando::StartState()
{
    CLogVota::GetInst().LogaIndagaEleitorVotando();
    m_form->Slot2();
    m_pNextState = this;
}

void CPerguntaEleitorVotando::ProcessKey(uebyte tecla)
{
    if (tecla == 5) {
        m_pNextState = &CMostraEleitorVotando::GetInst();
    }
}

void CPerguntaEleitorVotando::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CORRIGE:
        CLogVota::GetInst().LogaEleitorNaoEstaVotando();
        m_pNextState = &CPerguntaCodigoSuspensao::GetInst();
        break;
    case api::INPUT_CONFIRMA:
        CLogVota::GetInst().LogaEleitorEstaVotando();
        CThreadEleitor::GetInst().GetMensagens().Post(4);
        m_pNextState = &CMostraEleitorVotando::GetInst();
        break;
    default:
        break;
    }
}

} // namespace vota
