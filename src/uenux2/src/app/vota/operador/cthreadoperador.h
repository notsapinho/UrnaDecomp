#pragma once

// Reconstruction's note, not TSE's text: vota::CThreadOperador and vota::CMessageOperador, named by RTTI (typeinfos
// @1601248 and @1601300). Their members' names, GetInst's and this header's path are chosen, and
// src/units/116-uenux2-cthreads.mk says from what.

#include <cstddef>
#include <memory>
#include <mutex>
#include <string>

#include "api/ipc/cmessagequeue.h"
#include "app/vota/cthreadvota.h"

namespace vota {

class CMessageOperador : public api::CPriorityMessageQueue<api::SMessage>, public api::CMessageInterface {
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

class CThreadOperador final : public CThreadVota {
public:
    static CThreadOperador& GetInst();

    ~CThreadOperador() override;

protected:
    void Run() override;
    void ParaOutrasThreads() override;

private:
    CThreadOperador();

    CMessageOperador m_mensagens;
    std::string m_texto1;
    std::string m_texto2;
    std::string m_texto3;
    std::string m_texto4;

    static std::unique_ptr<CThreadOperador> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
