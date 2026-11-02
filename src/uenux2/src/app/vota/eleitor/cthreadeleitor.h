#pragma once

// Reconstruction's note, not TSE's text: vota::CThreadEleitor and vota::CMessageEleitor, named by RTTI (typeinfos
// @1534664 and @1534716). Their members' names, GetInst's and this header's path are chosen, and
// src/units/116-uenux2-cthreads.mk says from what.

#include <cstddef>
#include <memory>
#include <mutex>

#include "api/ipc/cmessagequeue.h"
#include "app/vota/cthreadvota.h"

namespace vota {

class CMessageEleitor : public api::CPriorityMessageQueue<api::SMessage>, public api::CMessageInterface {
public:
    void Espera(size_t milissegundos) override
    {
        const api::ESemaphoreResult resultado = m_semaforo->Wait(milissegundos);
        if (resultado == api::ESR_OK) {
            m_mensagem = Remove();
        }
        m_resultado = resultado;
    }
};

class CThreadEleitor final : public CThreadVota {
public:
    static CThreadEleitor& GetInst();

    ~CThreadEleitor() override;

    // The queue at +36, which vota::CExecucaoVota's slot 8 returns (fn 4708: the thread's address plus 36). The
    // accessor and its name are chosen: no record or out-of-line copy names one.
    api::CPriorityMessageQueue<api::SMessage>& GetMensagens() { return m_mensagens; }

    // Whether the instance exists: target fn 10539 reads s_inst (@1833212) with s_mutex (@1833188) held and creates
    // nothing. The member, its name and its being defined in the class are chosen.
    static bool Existe()
    {
        std::lock_guard<std::mutex> trava(s_mutex);
        return s_inst != nullptr;
    }

    // Fn 4349, one pass over the thread's messages, input and ticks, false when there is no context or Stop was asked;
    // vota::CExecucaoVotaCooperativa's slot 7 (fn 7823) and this class's Run (fn 7061) call it. It holds
    // ProcessarMensagens and ProcessarEntrada (the record cthreadeleitor.cpp:134) under a stack frame each, functions
    // binaryen inlined into their one caller. Its name is chosen; the second's is its record's, and the first's is its
    // logs' "%s" (a reading: they pass __func__, as ProcessarEntrada's passes its record's name).
    bool ProcessaEventos();

protected:
    void Run() override;
    void ParaOutrasThreads() override;

private:
    CThreadEleitor();

    bool ProcessarMensagens(comum::CAppStateContext& contexto);
    bool ProcessarEntrada(comum::CAppStateContext& contexto);

    CMessageEleitor m_mensagens;

    static std::unique_ptr<CThreadEleitor> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
