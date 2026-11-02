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

public:
    // The state of each tick, by id: vota::CSuspensaoAutomaticaEleitor::StartState (target fn 10409) holds this copy as
    // binaryen inlines a function into its one caller (the map at +0 and the result reached through two locals that hold
    // their addresses), a loop that inserts each id with 1 when the tick's word at +24 of the value is 0 and 0 otherwise,
    // into a std::map whose 16-byte nodes hold the id at +13 and that byte at +14; the caller compares the byte with 1,
    // which reads as no bool (clang tests a bool for non-zero; a reading, not measured). Out of line in ctickmanager.cpp;
    // the enumeration, its names and the member's name are chosen.
    enum EEstadoTick : uebyte {
        TICK_PARADO = 0,
        TICK_ATIVO = 1,
    };

    std::map<uebyte, EEstadoTick> GetEstadoTicks() const;
};

} // namespace api
