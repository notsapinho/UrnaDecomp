// vota::CSuspensaoAutomaticaEleitor (/home/rubio/tse/uenux2/src/app/vota/operador/aguardaeleitor/csuspensaoautomaticaeleitor.cpp).
// The reconstruction's note, not TSE's text. The file's one record is DisparaSinalizacaoSonora's lambda's (line 89, column
// 22, the default argument of CPolySingleton's instance); every other line is a choice, in the order of the members' use
// band (src/units/152-uenux2-app-vota-operador-estados.mk).
#include "app/vota/operador/aguardaeleitor/csuspensaoautomaticaeleitor.h"

#include <string>
#include <thread>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/ctextsource.h"
#include "api/gui/iscreenmt.h"
#include "api/ipc/cmessagequeue.h"
#include "api/pattern/cpolysingleton.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/csincronismooperador.h"
#include "app/vota/operador/cthreadoperador.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela(std::shared_ptr<std::string> situacao,
                                                                                std::shared_ptr<std::string> mensagem)
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_1);
    builder.AddTextField(api::CTextSource(mensagem), api::SPoint{1, 1}, "%s", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(api::CTextSource(situacao), api::SPoint{1, 2}, "%s", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: Cancelar", api::SPoint{40, 3}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CSuspensaoAutomaticaEleitor::CSuspensaoAutomaticaEleitor()
    : comum::CAppState(EVENTO_TECLA | EVENTO_ENTRADA | EVENTO_TICK)
    , m_bVotou(false)
    , m_tick(CThreadOperador::GetInst().AddStoppedTick(1000))
    , m_contagem(10)
    , m_bSinalizado(false)
    , m_situacao(std::make_shared<std::string>("votou/não votou"))
    , m_mensagem(std::make_shared<std::string>("contagem regressiva"))
    , m_form(MontaTela(m_situacao, m_mensagem))
{
}

CSuspensaoAutomaticaEleitor& CSuspensaoAutomaticaEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CSuspensaoAutomaticaEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CSuspensaoAutomaticaEleitor> CSuspensaoAutomaticaEleitor::s_inst;
std::mutex CSuspensaoAutomaticaEleitor::s_mutex;

CSuspensaoAutomaticaEleitor::~CSuspensaoAutomaticaEleitor() = default;

void CSuspensaoAutomaticaEleitor::InicializaTick()
{
    CThreadOperador& thread = CThreadOperador::GetInst();
    const std::map<uebyte, api::CTickManager::EEstadoTick> ticks = thread.GetEstadoTicks();
    const auto it = ticks.find(m_tick);
    if (it == ticks.end()) {
        m_tick = thread.AddStoppedTick(1000);
    } else if (it->second == api::CTickManager::TICK_ATIVO) {
        thread.StopTick(m_tick);
    }
}


void CSuspensaoAutomaticaEleitor::AtualizaMensagem()
{
    *m_mensagem = std::string("Suspensão automática em ") + std::to_string(m_contagem) +
                  (m_contagem == 1 ? " segundo..." : " segundos...");
}


void CSuspensaoAutomaticaEleitor::DisparaSinalizacaoSonora()
{
    std::thread([] { api::CPolySingleton<api::IScreenMT>::instance().Buzz(50, 3); }).detach();
}

void CSuspensaoAutomaticaEleitor::StartState()
{
    InicializaTick();
    *m_situacao = m_bVotou ? "Votou parcialmente" : "Não votou";
    m_bSinalizado = false;
    m_contagem = 10;
    AtualizaMensagem();
    DisparaSinalizacaoSonora();
    CThreadOperador::GetInst().StartTick(m_tick);
    m_form->Slot2();
    m_pNextState = this;
}

void CSuspensaoAutomaticaEleitor::FinishState()
{
    CThreadOperador::GetInst().StopTick(m_tick);
    m_bSinalizado = false;
}

void CSuspensaoAutomaticaEleitor::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE && !m_bSinalizado) {
        CThreadOperador::GetInst().StopTick(m_tick);
        CLogVota::GetInst().LogaSuspensaoAbortada();
        CThreadEleitor::GetInst().GetMensagens().Post(4);
        m_pNextState = &CMostraEleitorVotando::GetInst();
    }
}

void CSuspensaoAutomaticaEleitor::ProcessTick(uebyte tick)
{
    if (tick != m_tick || m_bSinalizado) {
        return;
    }

    if (m_contagem > 1) {
        m_contagem--;
        AtualizaMensagem();
        DisparaSinalizacaoSonora();
        m_form->Slot2();
        return;
    }

    m_contagem = 0;
    m_bSinalizado = true;
    CThreadOperador::GetInst().StopTick(m_tick);
    AtualizaMensagem();
    m_form->Slot2();
    CThreadEleitor::GetInst().GetMensagens().Post(3);
}

void CSuspensaoAutomaticaEleitor::ProcessKey(uebyte tecla)
{
    if (tecla == 5) {
        CThreadOperador::GetInst().StopTick(m_tick);
        m_pNextState = &CMostraEleitorVotando::GetInst();
    } else if (m_bSinalizado) {
        switch (tecla) {
        case 13:
            m_bSinalizado = false;
            CSincronismoOperador::GetInst().SetSincronizado(true);
            m_pNextState = &CSincronismoOperador::GetInst();
            break;
        case 2:
            m_bSinalizado = false;
            m_pNextState = &CPedeIdentidade::GetInst();
            break;
        default:
            break;
        }
    }
}

} // namespace vota
