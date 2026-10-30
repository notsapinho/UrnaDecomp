#include "api/ipc/cthread.h"

#include "api/ipc/eueipcerror.h"
#include "api/ipc/ithreadimpl.h"

namespace api {

CThread::~CThread() = default;

// (original lines 10-27: content not recovered)
#line 28
// <stubs>
// f3598 · 1956 B · unmatched · name unknown
// ? f3598(i32) { ... }
// </stubs>

// (original lines 33-55: content not recovered)
#line 56
/**
 * Inicia a execução da thread, se ela ainda não está em execução: a
 * implementação da plataforma cria a thread, que executa Run().
 * @throw CUeIpcError se o tipo de implementação não foi especificado
 */
void CThread::Start()
{
    if (m_estado != ESTADO_EXECUTANDO) {
        m_iniciada = false;
        m_estado = ESTADO_EXECUTANDO;

        if (m_impl == nullptr) {
            throw CUeIpcError(EUE_IPC_IMPLEMENTACAO_NAO_ESPECIFICADA, "Nao foi especificado o tipo de implementação");
        }

        m_impl->Create(&CThread::Rotina, this);
    }
}

/**
 * Rotina da thread criada por Start(): executa o laço da classe derivada e
 * marca a thread como finalizada.
 */
void* CThread::Rotina(void* parametro)
{
    CThread* thread = static_cast<CThread*>(parametro);
    thread->Run();
    thread->m_estado = ESTADO_FINALIZADA;
    return nullptr;
}

} // namespace api
