#include "app/vota/operador/cthreadoperador.h"

#include <typeinfo>
#include <vector>

#include "api/gui/cmtformbuilder.h"
#include "api/hwil/iinput.h"
#include "api/util/uedebug.h"
#include "app/comum/cappstatecontext.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/monitor/cthreadmonitor.h"
#include "app/vota/operador/caguardainicio.h"

namespace vota {

CThreadOperador& CThreadOperador::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CThreadOperador());
    }
    return *s_inst;
}

std::unique_ptr<CThreadOperador> CThreadOperador::s_inst;
std::mutex CThreadOperador::s_mutex;

CThreadOperador::CThreadOperador()
    : m_texto1("")
    , m_tituloMesario("")
    , m_texto3(" ")
{
}

CThreadOperador::~CThreadOperador() = default;

void MostraTelaUrnaInoperante()
{
    api::CMTFormBuilder builder;
    builder.AddTextField("URNA ELETRÔNICA INOPERANTE", api::SPoint{20, 1}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("Siga as instruções na tela do eleitor", api::SPoint{20, 2}, api::ALINHAMENTO_CENTRO);
    builder.GetForm("")->Slot2();
}

static bool MensagemProcessadaPelaThread(const api::SMessage& mensagem)
{
    Depura("%s: msg[%d]", __func__, mensagem.m_tipo);
    switch (mensagem.m_tipo) {
    case 0:
        MostraTelaUrnaInoperante();
        return true;
    case 16:
        return true;
    default:
        return false;
    }
}

// (original lines 59-79: content not recovered)
#line 80
void CThreadOperador::Run()
{
    comum::CAppState* inicial = &CAguardaInicio::GetInst();
    m_contexto.reset(new comum::CAppStateContext(inicial));
    if (comum::CAppState* estado = m_contexto->GetState()) {
        estado->StartState();
    }
    auto& terminalMT = api::CPolySingleton<api::IInputMT>::instance();
    bool processou;
    while (!PararSolicitado()) {
        processou = false;
        while (!m_mensagens.Vazia()) {
            processou = true;
            const api::SMessage mensagem = m_mensagens.Remove();
            if (MensagemProcessadaPelaThread(mensagem)) {
                Stop();
                return;
            }
            Depura("%s: 1 msg[%d] context[%s]", __func__, mensagem.m_tipo,
                   m_contexto && m_contexto->GetState() ? typeid(*m_contexto->GetState()).name() : "");
            if (m_contexto->AcceptsKey()) {
                m_contexto->ProcessKey(static_cast<uebyte>(mensagem.m_tipo));
                m_contexto->TrocaEstado();
            }
        }
        if (m_contexto->AcceptsInput() && terminalMT.HasKey()) {
            const comum::CAppState* estado = m_contexto ? m_contexto->GetState() : nullptr;
            Depura("%s: 2 hasKey[%d] context[%s]", __func__, terminalMT.HasKey(), estado ? typeid(*estado).name() : "");
            m_contexto->ProcessInput();
            processou = true;
            m_contexto->TrocaEstado();
        }
        const std::vector<uebyte> ticks = m_ticks.GetExpiredTicks();
        if (ticks.size() > 0 && m_contexto->AcceptsTick()) {
            for (const uebyte tick : ticks) {
                m_contexto->ProcessTick(tick);
            }
            processou = true;
        }
        m_contexto->TrocaEstado();
        Yield();
        if (!processou) {
            Dorme(50000);
        }
    }
}

void CThreadOperador::ParaOutrasThreads()
{
    CThreadEleitor::GetInst().Stop();
    CThreadMonitor::GetInst().Stop();
}

} // namespace vota
