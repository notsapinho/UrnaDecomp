// vota::CSuspensaoAutomaticaEleitor (/home/rubio/tse/uenux2/src/app/vota/operador/aguardaeleitor/csuspensaoautomaticaeleitor.cpp).
// The reconstruction's note, not TSE's text. The file's one record is DisparaSinalizacaoSonora's lambda's (line 89, column
// 22, the default argument of CPolySingleton's instance); every other line is a choice, in the order of the members' use
// band (src/units/152-uenux2-app-vota-operador-estados.mk).
#include "app/vota/operador/aguardaeleitor/csuspensaoautomaticaeleitor.h"

#include <string>
#include <thread>

#include "api/gui/cinteractiveform.h"
#include "api/gui/iscreenmt.h"
#include "api/ipc/cmessagequeue.h"
#include "api/pattern/cpolysingleton.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CSuspensaoAutomaticaEleitor::~CSuspensaoAutomaticaEleitor() = default;

// (original lines 23-79: content not recovered)
#line 80
void CSuspensaoAutomaticaEleitor::AtualizaMensagem()
{
    *m_mensagem = std::string("Suspensão automática em ") + std::to_string(m_contagem) +
                  (m_contagem == 1 ? " segundo..." : " segundos...");
}


void CSuspensaoAutomaticaEleitor::DisparaSinalizacaoSonora()
{
    std::thread([] { api::CPolySingleton<api::IScreenMT>::instance().Buzz(50, 3); }).detach();
}

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

} // namespace vota
