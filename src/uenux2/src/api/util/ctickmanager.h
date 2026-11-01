#pragma once

#include <cstddef>
#include <map>
#include <sys/time.h>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace api {

/**
 * Controla os ticks (temporizadores periódicos) de uma thread, identificados por id.
 */
class CTickManager {
public:
    uebyte AddTick(size_t milissegundos);
    // Fn 5452: AddTick, then StopTick of the new id, which it returns. No record names it: the name is chosen from that.
    uebyte AddStoppedTick(size_t milissegundos);
    void StopTick(uebyte id);
    void StartTick(uebyte id);
    // Fn 5450: the ids of the running ticks whose time has come, each tick moved on to its next time. No record names
    // it: the name is chosen from that.
    std::vector<uebyte> GetExpiredTicks();

private:
    struct STick {
        explicit STick(size_t milissegundos);

        ueint64 m_milissegundos;
        timeval m_proximo;
        ueint32 m_parado;
    };

    uebyte SearchNextId();

    std::map<uebyte, STick> m_ticks;
};

} // namespace api
