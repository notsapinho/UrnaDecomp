#pragma once

// Reconstruction's note, not TSE's text: api::CPriorityMessageQueue<api::SMessage>, named by the target's records at
// this file's lines 113 and 114 (the constructor, inlined into 316 and 270 and not written, so both lines stay blank)
// and 153 (Remove, target fn 2073), and by its RTTI and vtable @1534764. The offsets come from Remove, the destructors
// 3162 and 3157 and the constructor's stores in 316. Every name but the class's, SMessage's and Remove's is chosen:
// src/units/64-uenux2-cmessagequeue.mk lists the choices and the forms that give the same bytes.

#include <memory>
#include <queue>

#include "api/ipc/eueipcerror.h"
#include "api/ipc/isemaphore.h"
#include "api/ipc/isyncctl.h"

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

    // (original lines 30-146: content not recovered)
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
    std::unique_ptr<ISemaphore> m_semaforo;
    std::unique_ptr<ISyncCtl> m_sync;
    unsigned m_ordem;
};

} // namespace api

// <stubs>
// f316 · 303 B · unmatched · placement: link order · name unknown
// ? f316() { ... }

// f270 · 353 B · unmatched · placement: link order · name unknown
// ? f270() { ... }
// </stubs>
