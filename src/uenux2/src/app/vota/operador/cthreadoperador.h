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

    // The queue at +36, to which the vota states post with api::CPriorityMessageQueue::Insert (fn 501): each caller
    // passes this thread's address plus 36 (7221, 7178, 11994 and others). The accessor and its name are chosen, after
    // vota::CThreadEleitor's: no record or out-of-line copy names one.
    api::CPriorityMessageQueue<api::SMessage>& GetMensagens() { return m_mensagens; }

    // The titulo of the mesario being registered: vota::CControladorRegistraMesariosVota's slots 17 and 18 return and
    // assign +96 with no call of a member of this class, and its slots 31 to 33 format it into their messages (fn 3887).
    // The names are chosen.
    const std::string& GetTituloMesario() const { return m_tituloMesario; }
    void SetTituloMesario(const std::string& titulo) { m_tituloMesario = titulo; }

    // The string at +108, the line about the voter's state: vota::CEleitorVotando's FinishState (fn 7370) and slot 2
    // (fn 7377) assign it a literal in place (fn 7370's one char inlined, fn 7377's through __assign_external, fn 276),
    // and fn 4464 holds an out-of-line function of this class inlined by binaryen (a second 16-byte frame right after
    // its call of GetInst) that assigns it the first 40 characters of a string: the second, out of line in
    // cthreadoperador.cpp, whose object links after celeitorvotando.cpp's (src/units/197-uenux2-celeitorvotando.mk has
    // the measurement). That the two are overloads of one setter, and their names, are chosen.
    void SetTextoEleitor(const char* texto) { m_texto3 = texto; }
    void SetTextoEleitor(const std::string& texto);

protected:
    void Run() override;
    void ParaOutrasThreads() override;

private:
    CThreadOperador();

    CMessageOperador m_mensagens;
    std::string m_texto1;
    std::string m_tituloMesario;
    std::string m_texto3;
    std::string m_texto4;

    static std::unique_ptr<CThreadOperador> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
