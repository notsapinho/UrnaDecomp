#pragma once

// Reconstruction's note, not TSE's text: api::CPriorityMessageQueue<api::SMessage>, named by the target's records at
// this file's lines 113 and 114 (the constructor, inlined into 316 and 270) and 153 (Remove, target fn 2073), and by
// its RTTI and vtable @1534764. The offsets come from Remove, the destructors 3162 and 3157 and the constructor's
// stores in 316. Every name but the class's, SMessage's, api::CMessageInterface's and Remove's is chosen:
// src/units/64-uenux2-cmessagequeue.mk lists the choices and the forms that give the same bytes, 116-uenux2-cthreads.mk
// what the constructor and api::CMessageInterface add, and 174-uenux2-app-vota-mensagens.mk Insert, Post and the guard.

#include <cstddef>
#include <memory>
#include <queue>

#include "api/ipc/eueipcerror.h"
#include "api/ipc/isemaphore.h"
#include "api/ipc/isyncctl.h"
#include "api/pattern/cpolysingleton.h"
#include "api/pattern/igenericfactory.h"

namespace api {

// 8 bytes with alignment 4 (Remove copies it with one i64 of align=2). The callers read a short at +0 (4349, 10204).
// The word at +4 is the address of the queue the message is inserted into: fn 3903 stores its first parameter there,
// the queue it passes on to fn 7708 and so to Insert (fn 501), and every caller of 501 that builds a message stores
// the queue it passes as 501's first argument (7221, 7178, 11994, 6018 and the others). No reader of the word is
// known. The field names, the second one's type and this file are chosen.
struct SMessage {
    short m_tipo;
    const void* m_fila;
};

// Reconstruction's note, not TSE's text: a guard that holds an ISyncCtl locked for its lifetime. The target's
// CPriorityMessageQueue<SMessage>::Insert (fn 501) stores m_sync's pointer in a frame word, calls its Lock (slot 2) and
// leaves through fn 5528 on both paths, a function of one parameter that calls that word's Unlock (slot 3) and
// terminates if it throws: a destructor. No record or RTTI names the class, its members or this place: all chosen.
class CSyncCtlGuard {
public:
    explicit CSyncCtlGuard(ISyncCtl* sync)
        : m_sync(sync)
    {
        m_sync->Lock();
    }

    ~CSyncCtlGuard() { m_sync->Unlock(); }

private:
    ISyncCtl* m_sync;
};

template <typename TMessage>
class CPriorityMessageQueue {
public:
    virtual ~CPriorityMessageQueue() = default;

    // (original lines 55-111: content not recovered)
#line 112
    CPriorityMessageQueue()
        : m_semaforo(CPolySingleton<IGenericFactory<ISemaphore>>::instance().Create())
        , m_sync(CPolySingleton<IGenericFactory<ISyncCtl>>::instance().Create())
        , m_ordem(0)
    {
    }

    // (original lines 119-127: content not recovered)
#line 128
    void Insert(const TMessage& mensagem, int prioridade)
    {
        CSyncCtlGuard trava(m_sync.get());
        const unsigned ordem = m_ordem++;
        m_fila.push(SItem{mensagem, prioridade, ordem});
        m_semaforo->Unlock();
    }

    void Insert(const TMessage& mensagem) { Insert(mensagem, 1); }

    void Post(short tipo)
    {
        TMessage mensagem;
        mensagem.m_tipo = tipo;
        mensagem.m_fila = this;
        Insert(mensagem);
    }


    TMessage Remove()
    {
        ISyncCtl* sync = m_sync.get();
        sync->Lock();

        if (m_fila.empty()) {
            throw CUeIpcError(EUE_IPC_FILA_VAZIA, "A fila estava vazia.");
        }

        TMessage mensagem = m_fila.top().m_mensagem;
        m_fila.pop();
        if (m_fila.empty()) {
            m_ordem = 0;
        }

        sync->Unlock();
        return mensagem;
    }

private:
    // 16 bytes: the message, then what the heap compares (both offsets are Remove's; the names are chosen).
    struct SItem {
        TMessage m_mensagem;
        int m_prioridade;
        unsigned m_ordem;

        bool operator<(const SItem& outro) const
        {
            if (m_prioridade < outro.m_prioridade) {
                return true;
            }
            if (m_prioridade > outro.m_prioridade) {
                return false;
            }
            return m_ordem > outro.m_ordem;
        }
    };

    std::priority_queue<SItem> m_fila;

protected:
    // +20: the derived classes' waits read it (fn 4343).
    std::unique_ptr<ISemaphore> m_semaforo;

private:
    std::unique_ptr<ISyncCtl> m_sync;
    unsigned m_ordem;
};

// api::CMessageInterface (RTTI: a class with no base, typeinfo @1534756), the second base of vota::CMessageEleitor and
// vota::CMessageOperador at +32: its slots are the destructor and the wait, as the thunks in those classes' second
// vtable show (fns 4341, 4338, 4337). Its own vtable is not in the target, so nothing stores it. That the fields at +4
// and +12 are this class's is evidence: with them in the derived class the constructor's stores in 316 come in another
// order. This file and every name but the class's are chosen.
class CMessageInterface {
public:
    virtual ~CMessageInterface() = default;

    virtual void Espera(size_t milissegundos) = 0;

protected:
    SMessage m_mensagem{};
    ESemaphoreResult m_resultado = ESR_OK;
};

} // namespace api
