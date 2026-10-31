#pragma once

// Reconstruction's note, not TSE's text: api::CPriorityMessageQueue<api::SMessage>, named by the target's records at
// this file's lines 113 and 114 (the constructor, inlined into 316 and 270) and 153 (Remove, target fn 2073), and by
// its RTTI and vtable @1534764. The offsets come from Remove, the destructors 3162 and 3157 and the constructor's
// stores in 316. Every name but the class's, SMessage's, api::CMessageInterface's and Remove's is chosen:
// src/units/64-uenux2-cmessagequeue.mk lists the choices and the forms that give the same bytes, and
// src/units/116-uenux2-cthreads.mk what the constructor and api::CMessageInterface add.

#include <cstddef>
#include <memory>
#include <queue>

#include "api/ipc/eueipcerror.h"
#include "api/ipc/isemaphore.h"
#include "api/ipc/isyncctl.h"
#include "api/pattern/cpolysingleton.h"
#include "api/pattern/igenericfactory.h"

namespace api {

// 8 bytes with alignment 4 (Remove copies it with one i64 of align=2). The callers read a short at +0 (4349, 10204);
// nothing read so far uses +4, so the field names and the second one's type are chosen, and so is this file.
struct SMessage {
    short m_tipo;
    int m_valor;
};

template <typename TMessage>
class CPriorityMessageQueue {
public:
    virtual ~CPriorityMessageQueue() = default;

    // (original lines 34-111: content not recovered)
#line 112
    CPriorityMessageQueue()
        : m_semaforo(CPolySingleton<IGenericFactory<ISemaphore>>::instance().Create())
        , m_sync(CPolySingleton<IGenericFactory<ISyncCtl>>::instance().Create())
        , m_ordem(0)
    {
    }

    // (original lines 119-146: content not recovered)
#line 147
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
