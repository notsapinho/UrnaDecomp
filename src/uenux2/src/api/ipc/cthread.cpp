#include "api/ipc/cthread.h"

#include "api/ipc/eueipcerror.h"
#include "api/ipc/isyncctl.h"
#include "api/ipc/ithreadimpl.h"
#include "api/pattern/cpolysingleton.h"
#include "api/pattern/igenericfactory.h"

namespace api {

CThread::~CThread() = default;

// (original lines 13-27: content not recovered)
#line 28
CThread::CThread()
    : m_estado(ESTADO_CRIADA)
    , m_parar(false), m_iniciada(false)
    , m_pImpl(CPolySingleton<IGenericFactory<IThreadImpl>>::instance().Create())
    , m_sync(CPolySingleton<IGenericFactory<ISyncCtl>>::instance().Create())
{
}

// (original lines 36-55: content not recovered)
#line 56
/**
 * Inicia a execução da thread, se ela ainda não está em execução: a
 * implementação da plataforma cria a thread, que executa Run().
 * @throw CUeIpcError se o tipo de implementação não foi especificado
 */
void CThread::Start()
{
    if (m_estado != ESTADO_EXECUTANDO) {
        m_parar = false;
        m_estado = ESTADO_EXECUTANDO;

        if (m_pImpl == nullptr) {
            throw CUeIpcError(EUE_IPC_IMPLEMENTACAO_NAO_ESPECIFICADA, "Nao foi especificado o tipo de implementação");
        }

        m_pImpl->Create(&CThread::Rotina, this);
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
