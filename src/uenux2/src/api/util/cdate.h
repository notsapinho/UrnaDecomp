#pragma once

#include <string>

namespace api {

// Recovered: the layout only, 8 bytes. CDate(const std::string &) (target fn 3649, records cdate.cpp:94 and :104)
// stores the day, the month and the year it parses as 16-bit words at +0, +2 and +4, and the weekday at +6 (tm_mday,
// tm_mon + 1, tm_year + 1900, tm_wday); the date comparison api::CDateTime's callers use (fn 1261) compares year, month
// and day as signed 16-bit values. The member names are not in the target.
class CDate {
public:
    CDate(const std::string& data);

private:
    short m_dia;
    short m_mes;
    short m_ano;
    short m_diaSemana;
};

} // namespace api
