#pragma once

#include <cstddef>
#include <string>

#include "ecourna/api/uetypes.hpp"

namespace api {

// Target fn 5449: whether a string is a time of day written HHMM or HHMMSS (4 or 6 digits, the hours below 24, the
// minutes and seconds below 60). ctime.cpp's EncodeTime(const std::string &) calls it, and so does the check of a
// date and time that api::CDateTime's constructor from a string (fn 5475, cdatetime.cpp) inlines, on the time part:
// so it is external and declared here. No record, vtable slot or RTTI names it: the name is chosen from that role,
// and it is a free function because it reads no member (a static member of CTime would give the same bytes).
bool IsValidTime(const std::string& hora);

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
