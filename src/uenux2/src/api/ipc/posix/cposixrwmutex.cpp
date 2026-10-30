// Reconstruction, not TSE's text: each throw sits on its record's line, and the file's six records stay in the target's
// data with no code that loads them. Which throw holds which literal is chosen (src/units/97-uenux2-cvotacaostateaudio.mk).
#include "api/ipc/posix/cposixrwmutex.h"

#include <cstring>
#include <format>

#include "api/ipc/eueipcerror.h"

namespace api {

CPosixRWMutex::CPosixRWMutex()
{
    pthread_rwlockattr_t atributos;

    // (original lines 16-26: content not recovered)
#line 27
    int resultado = pthread_rwlockattr_init(&atributos);
    if (resultado != 0) {
        throw CUeIpcError(EUE_IPC_FALHA_INICIALIZAR_ATRIBUTOS_RWMUTEX, std::format("Falha ao inicializar atributos de mutex: {}", strerror(resultado)));
    }


    resultado = pthread_rwlock_init(&m_rwlock, &atributos);
    if (resultado != 0) {
        throw CUeIpcError(EUE_IPC_FALHA_CRIAR_RWMUTEX, std::format("Falha ao criar mutex: {}", strerror(resultado)));
    }

    // (original lines 38-39: content not recovered)
#line 40
    resultado = pthread_rwlockattr_destroy(&atributos);
    if (resultado != 0) {
        throw CUeIpcError(EUE_IPC_FALHA_DESTRUIR_ATRIBUTOS_RWMUTEX, std::format("Falha ao destruir atributos de mutex: {}", strerror(resultado)));
    }
}

CPosixRWMutex::~CPosixRWMutex()
{
    pthread_rwlock_destroy(&m_rwlock);
}

void CPosixRWMutex::ReadLock()
{

    // (original lines 54-55: content not recovered)
#line 56
    const int resultado = pthread_rwlock_rdlock(&m_rwlock);
    if (resultado != 0) {
        throw CUeIpcError(EUE_IPC_FALHA_BLOQUEAR_LEITURA, std::format("Falha ao bloquear mutex para leitura: {}", strerror(resultado)));
    }
}

void CPosixRWMutex::WriteLock()
{

    // (original lines 65-66: content not recovered)
#line 67
    const int resultado = pthread_rwlock_wrlock(&m_rwlock);
    if (resultado != 0) {
        throw CUeIpcError(EUE_IPC_FALHA_BLOQUEAR_ESCRITA, std::format("Falha ao bloquear mutex para escrita: {}", strerror(resultado)));
    }
}

void CPosixRWMutex::Unlock()
{

    // (original lines 76-77: content not recovered)
#line 78
    const int resultado = pthread_rwlock_unlock(&m_rwlock);
    if (resultado != 0) {
        throw CUeIpcError(EUE_IPC_FALHA_DESBLOQUEAR_RWMUTEX, std::format("Falha ao desbloquear mutex: {}", strerror(resultado)));
    }
}

} // namespace api
