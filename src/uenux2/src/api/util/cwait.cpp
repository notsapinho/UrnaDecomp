#include "api/util/cwait.h"

#include <format>
#include <unistd.h>

#include "api/util/csystem.h"
#include "api/util/eueutilerror.h"

namespace api {

namespace {
constexpr size_t MAXIMO_MILISSEGUNDOS = 4000000;
constexpr size_t MICROSSEGUNDOS_POR_MILISSEGUNDO = 1000;
constexpr int MICROSSEGUNDOS_POR_SEGUNDO = 1000000;
constexpr useconds_t INTERVALO_MICROSSEGUNDOS = 200;
} // namespace
/**
 * Inicia a contagem do tempo de espera.
 *
 * @param milissegundos tempo de espera em milissegundos
 */
CWait::CWait(const size_t milissegundos)
    : m_microssegundos(milissegundos * MICROSSEGUNDOS_POR_MILISSEGUNDO)
    , m_inicio{0, 0}
{
    if (milissegundos > MAXIMO_MILISSEGUNDOS) {
        // Evita estouro no cálculo dos microssegundos
        throw CUeUtilError(EUE_UTIL_TEMPO_EXCESSIVO, std::format("Quantidade excessiva de milissegundos {}", milissegundos));
    }

    gettimeofday(&m_inicio, nullptr);
    m_inicio.tv_usec += m_microssegundos;
    if (m_inicio.tv_usec > MICROSSEGUNDOS_POR_SEGUNDO) {
        m_inicio.tv_sec += m_inicio.tv_usec / MICROSSEGUNDOS_POR_SEGUNDO;
        m_inicio.tv_usec %= MICROSSEGUNDOS_POR_SEGUNDO;
    }
}

void CWait::Wait()
{
    while (CSystem::s_dorme) {
        timeval agora;
        gettimeofday(&agora, nullptr);
        if (agora.tv_sec > m_inicio.tv_sec || (agora.tv_sec >= m_inicio.tv_sec && agora.tv_usec >= m_inicio.tv_usec)) {
            break;
        }
        usleep(INTERVALO_MICROSSEGUNDOS);
    }
}

} // namespace api
