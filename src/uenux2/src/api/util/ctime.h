#pragma once

#include <compare>
#include <cstddef>
#include <string>

#include "ecourna/api/uetypes.hpp"

namespace api {

// Target fn 5449: whether a string is a time of day written HHMM or HHMMSS (4 or 6 digits, the hours below 24, the
// minutes and seconds below 60). ctime.cpp's EncodeTime(const std::string &) calls it, and so does the check of a
// date and time that api::CDateTime's constructor from a string (fn 5475, cdatetime.cpp) inlines, on the time part.
// Declared here by choice (src/units/24-uenux2-ctime.mk says why). No record, vtable slot or RTTI names it: the name
// is chosen from that role, and it is a free function as it reads no member (a static member gives the same bytes).
bool IsValidTime(const std::string& hora);

// CTime() (fn 2230) is now, read from ISystemDateTime's clock through gmtime_r. Format (fn 779) has no record; its name is
// chosen after CDate::Format's, whose record names it, as it formats the h, m and s codes the same way. operator<=> is out
// of line: fn 759 calls it, and the target's body for it is the one binaryen keeps for OpenSSL's err_string_data_cmp too
// (fn 5448, the same bytes); its name and its std::strong_ordering result are chosen. The getters are inline: fns 1381
// and 2233 compute the hour, the minute and the second from the word as they do; their names are chosen.

/**
 * Hora do dia, guardada em segundos desde a meia-noite.
 */
class CTime {
public:
    CTime();
    CTime(uebyte hora, uebyte minuto, uebyte segundo);
    explicit CTime(const std::string& hora);

    std::string Format(const std::string& formato) const;

    void operator+=(int segundos);
    void operator-=(int segundos);
    CTime operator-(int segundos) const;

    std::strong_ordering operator<=>(const CTime& hora) const;

    uebyte GetHora() const { return m_segundos / 3600; }
    uebyte GetMinuto() const { return static_cast<ueword>(m_segundos % 3600) / 60; }
    uebyte GetSegundo() const { return m_segundos % 60; }

private:
    size_t m_segundos;
};

} // namespace api
