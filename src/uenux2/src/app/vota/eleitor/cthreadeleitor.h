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

protected:
    void Run() override;
    void ParaOutrasThreads() override;

private:
    CThreadEleitor();

    CMessageEleitor m_mensagens;

    static std::unique_ptr<CThreadEleitor> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
