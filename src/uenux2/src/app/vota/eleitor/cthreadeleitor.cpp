// Reconstruction's note, not TSE's text: vota::AbreDiretorio's place in this file is chosen (unit 329's fragment).
#include "app/vota/eleitor/cthreadeleitor.h"

#include <typeinfo>
#include <vector>

#include "api/hwil/iinput.h"
#include "api/util/cdirreader.h"
#include "api/util/csystem.h"
#include "api/util/uedebug.h"
#include "app/vota/eleitor/cajusteinicial.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/iajusteinicial.h"
#include "app/vota/iexecucaovota.h"

namespace vota {

CThreadEleitor& CThreadEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CThreadEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CThreadEleitor> CThreadEleitor::s_inst;
std::mutex CThreadEleitor::s_mutex;

CThreadEleitor::CThreadEleitor() = default;

CThreadEleitor::~CThreadEleitor() = default;

bool CThreadEleitor::ProcessarMensagens(comum::CAppStateContext& contexto)
{
    bool processou = false;
    while (!m_mensagens.Vazia()) {
        const api::SMessage mensagem = m_mensagens.Remove();
        const comum::CAppState* estado = m_contexto ? m_contexto->GetState() : nullptr;
        bool interna = true;
        switch (mensagem.m_tipo) {
        case 0:
        case 6:
            Stop();
            break;
        case 8:
            CEstadoAudio::GetInst().SelecionaModo0();
            break;
        case 9:
            CEstadoAudio::GetInst().SelecionaModo1();
            break;
        case 10:
            CEstadoAudio::GetInst().Desativa();
            break;
        default:
            interna = false;
            break;
        }
        if (interna) {
            Depura("%s: 1 msg[%d] context[%s]", __func__, mensagem.m_tipo, estado ? typeid(*estado).name() : "");
            if (PararSolicitado()) {
                break;
            }
        } else {
            Depura("%s: 2 msg[%d] context[%s]", __func__, mensagem.m_tipo, estado ? typeid(*estado).name() : "");
            if (contexto.AcceptsKey()) {
                contexto.ProcessKey(static_cast<uebyte>(mensagem.m_tipo));
                contexto.TrocaEstado();
            }
        }
        processou = true;
    }
    return processou;
}

// (original lines 76-131: content not recovered)
#line 132
bool CThreadEleitor::ProcessarEntrada(comum::CAppStateContext& contexto)
{
    auto& teclas = api::CPolySingleton<api::IInputKbd>::instance();
    if (contexto.AcceptsInput() && teclas.HasKey()) {
        const comum::CAppState* estado = contexto.GetState();
        Depura("%s: hasKey[%d] context[%s]", __func__, teclas.HasKey(), estado ? typeid(*estado).name() : "");
        contexto.ProcessInput();
        contexto.TrocaEstado();
        return true;
    }
    return false;
}

bool CThreadEleitor::ProcessaEventos()
{
    if (!m_contexto || PararSolicitado()) {
        return false;
    }
    const bool mensagens = ProcessarMensagens(*m_contexto);
    if (PararSolicitado()) {
        return mensagens;
    }
    bool eventos = ProcessarEntrada(*m_contexto);
    if (!PararSolicitado()) {
        {
            comum::CAppStateContext& contexto = *m_contexto;
            const std::vector<uebyte> ticks = m_ticks.GetExpiredTicks();
            if (!ticks.empty() && contexto.AcceptsTick()) {
                for (const uebyte tick : ticks) {
                    contexto.ProcessTick(tick);
                }
                eventos = true;
            }
        }
        m_contexto->TrocaEstado();
    }
    return mensagens || eventos;
}

void CThreadEleitor::Run()
{
    comum::CAppState* inicial = &IAjusteInicial::GetInst();
    m_contexto.reset(new comum::CAppStateContext(inicial));
    if (comum::CAppState* estado = m_contexto->GetState()) {
        estado->StartState();
    }
    while (!PararSolicitado()) {
        const bool processou = ProcessaEventos();
        if (PararSolicitado()) {
            break;
        }
        Yield();
        if (!processou) {
            api::CSystem::Dorme(50);
        }
    }
}

api::CDirReader* AbreDiretorio(const std::string& caminho)
{
    return new api::CDirReader(caminho);
}

void CThreadEleitor::ParaOutrasThreads()
{
    IExecucaoVota::GetInst().ParaThreadsOperadorMonitor();
}

} // namespace vota
