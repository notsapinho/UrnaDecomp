#include "api/util/ctickmanager.h"

#include <cmath>
#include <format>

#include "api/util/eueutilerror.h"

namespace api {

namespace {
// intervalo mínimo de um tick
constexpr int MINIMO_MILISSEGUNDOS = 30;
constexpr ueint64 MILISSEGUNDOS_POR_SEGUNDO = 1000;
constexpr ueint64 MICROSSEGUNDOS_POR_MILISSEGUNDO = 1000;
constexpr int MICROSSEGUNDOS_POR_SEGUNDO = 1000000;

} // namespace

/**
 * Cria um tick, que dispara a cada intervalo a partir de agora.
 *
 * @param milissegundos intervalo do tick
 *
 * @return id do tick criado
 *
 * @throw CUeUtilError se o intervalo for menor que o mínimo ou se não houver id disponível
 */
uebyte CTickManager::AddTick(size_t milissegundos)
{
    if (milissegundos < MINIMO_MILISSEGUNDOS) {
        throw CUeUtilError(EUE_UTIL_TICK_TEMPO_INVALIDO, std::format("O tempo do tick deve ser >= {}", MINIMO_MILISSEGUNDOS));
    }

    const uebyte id = SearchNextId();

    const STick tick(milissegundos);
    m_ticks.emplace(id, tick);
    return id;
}

uebyte CTickManager::AddStoppedTick(size_t milissegundos)
{
    const uebyte id = AddTick(milissegundos);
    StopTick(id);
    return id;
}

// (original lines 48-50: content not recovered)
#line 51
/**
 * Para um tick: ele deixa de disparar até ser iniciado de novo.
 *
 * @param id id do tick
 */
void CTickManager::StopTick(uebyte id)
{
    auto it = m_ticks.find(id);
    if (it == m_ticks.end()) {
        throw CUeUtilError(EUE_UTIL_TICK_NAO_EXISTE_PARAR, std::format("Não existe um tick com o id {}", id));
    }
    it->second.m_parado = 1;
}

void CTickManager::StartTick(uebyte id)
{
    auto it = m_ticks.find(id);
    if (it == m_ticks.end()) {
        throw CUeUtilError(EUE_UTIL_TICK_NAO_EXISTE_INICIAR, std::format("Não existe um tick com o id {}", id));
    }
    STick& tick = it->second;
    tick.m_parado = 0;

    timeval agora;
    gettimeofday(&agora, nullptr);
    tick.m_proximo.tv_sec = agora.tv_sec + tick.m_milissegundos / MILISSEGUNDOS_POR_SEGUNDO;
    tick.m_proximo.tv_usec = agora.tv_usec + (tick.m_milissegundos % MILISSEGUNDOS_POR_SEGUNDO) * MICROSSEGUNDOS_POR_MILISSEGUNDO;
    tick.m_proximo.tv_sec += tick.m_proximo.tv_usec / MICROSSEGUNDOS_POR_SEGUNDO;
    tick.m_proximo.tv_usec %= MICROSSEGUNDOS_POR_SEGUNDO;
}

CTickManager::STick::STick(size_t milissegundos)
{
    m_parado = 0;
    m_milissegundos = milissegundos;

    timeval agora;
    gettimeofday(&agora, nullptr);
    m_proximo.tv_sec = agora.tv_sec + m_milissegundos / MILISSEGUNDOS_POR_SEGUNDO;
    m_proximo.tv_usec = agora.tv_usec + (m_milissegundos % MILISSEGUNDOS_POR_SEGUNDO) * MICROSSEGUNDOS_POR_MILISSEGUNDO;
    m_proximo.tv_sec += m_proximo.tv_usec / MICROSSEGUNDOS_POR_SEGUNDO;
    m_proximo.tv_usec %= MICROSSEGUNDOS_POR_SEGUNDO;
}

// (original lines 95-120: content not recovered)
#line 121
inline uebyte CTickManager::SearchNextId()
{
    for (unsigned id = 0; id <= 0xff; ++id) {
        if (m_ticks.find(id) == m_ticks.end()) {
            return id;
        }
    }
    throw CUeUtilError(EUE_UTIL_TICK_SEM_ID_DISPONIVEL, "Não há mais id disponível para tick");
}

namespace {

// Reconstruction's note: no target function holds this loop out of line, clang inlines it into GetExpiredTicks; its
// name is chosen, and unit 02's fragment says why it is a function of its own.
void NormalizaMicrossegundos(timeval& tempo)
{
    while (tempo.tv_usec >= MICROSSEGUNDOS_POR_SEGUNDO) {
        tempo.tv_usec -= MICROSSEGUNDOS_POR_SEGUNDO;
        ++tempo.tv_sec;
    }
}

} // namespace

std::vector<uebyte> CTickManager::GetExpiredTicks()
{
    std::vector<uebyte> vencidos;

    timeval agora;
    gettimeofday(&agora, nullptr);

    for (auto& [id, tick] : m_ticks) {
        if (tick.m_parado == 1) {
            continue;
        }
        if (agora.tv_sec < tick.m_proximo.tv_sec || (agora.tv_sec <= tick.m_proximo.tv_sec && agora.tv_usec < tick.m_proximo.tv_usec)) {
            continue;
        }
        vencidos.push_back(id);

        timeval decorrido;
        timersub(&agora, &tick.m_proximo, &decorrido);

        const double intervalo = static_cast<double>(tick.m_milissegundos) / MILISSEGUNDOS_POR_SEGUNDO;
        const double periodos = decorrido.tv_sec / intervalo;
        const int periodosInteiros = static_cast<int>(periodos);
        const double segundos = intervalo * periodosInteiros;

        timeval incremento;
        incremento.tv_sec = static_cast<int>(segundos);
        const int restante = static_cast<int>(round(intervalo * (periodos - periodosInteiros) * MICROSSEGUNDOS_POR_SEGUNDO)) + decorrido.tv_usec;
        const int intervaloMicro = tick.m_milissegundos * MICROSSEGUNDOS_POR_MILISSEGUNDO;
        incremento.tv_usec = (restante / intervaloMicro + 1) * intervaloMicro + static_cast<int>(round((segundos - incremento.tv_sec) * MICROSSEGUNDOS_POR_SEGUNDO));
        NormalizaMicrossegundos(incremento);

        tick.m_proximo.tv_sec += incremento.tv_sec;
        tick.m_proximo.tv_usec += incremento.tv_usec;
        tick.m_proximo.tv_sec += tick.m_proximo.tv_usec / MICROSSEGUNDOS_POR_SEGUNDO;
        tick.m_proximo.tv_usec %= MICROSSEGUNDOS_POR_SEGUNDO;
    }
    return vencidos;
}

} // namespace api
