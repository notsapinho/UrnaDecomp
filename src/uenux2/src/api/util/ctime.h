#pragma once

#include <cstddef>
#include <string>

#include "ecourna/api/uetypes.hpp"

namespace api {

/**
 * Hora do dia, guardada em segundos desde a meia-noite.
 */
class CTime {
public:
    CTime(uebyte hora, uebyte minuto, uebyte segundo);
    explicit CTime(const std::string& hora);

    void operator+=(int segundos);
    void operator-=(int segundos);
    CTime operator-(int segundos) const;

private:
    size_t m_segundos;
};

} // namespace api
