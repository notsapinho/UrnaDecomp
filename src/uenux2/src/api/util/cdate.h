#pragma once

#include <compare>
#include <string>

#include "ecourna/api/uetypes.hpp"

namespace api {

// Target fn 5479: whether a string is a date written DDMMYY or DDMMYYYY (6 or 8 digits, the day within the month).
// CDate's constructor from a string calls it, and so does the check of a date and time that api::CDateTime's
// constructor from a string (fn 5475) inlines, on the date part. No record, vtable slot or RTTI names it: the name is
// chosen from that role, as api::IsValidTime's is (ctime.h), and it is a free function as it reads no member.
bool IsValidDate(const std::string& data);

// The day, the month and the year as 16-bit words at +0, +2 and +4, and the weekday at +6 (tm_mday, tm_mon + 1,
// tm_year + 1900, tm_wday of the struct tm the constructors read). The constructors store the 8 bytes as zero before
// anything else (fns 1382 and 3649), which default member initializers give. The member names are not in the target.
// - operator== compares the four words, as fn 5626 holds it inlined; defaulted is a choice. operator<=> (fn 1261) compares
//   the year, the month and the day, in that order, so it is not the defaulted one; each step is written
//   `if (auto c = a <=> b; c != 0)`, since a test of `a != b` before `a <=> b` lets clang fold the result to -1 or 1
//   where the target computes it in full.
// - The getters are inline: fns 1381 and 2233 read the day and the month as bytes and the year as a 16-bit word. Their
//   names, and the parameter types of the constructor from a day, a month and a year (fn 2765: two bytes and a short,
//   as its callers pass them and as its format string's argument types say, two unsigned and an int), are chosen.
class CDate {
public:
    CDate();
    CDate(uebyte dia, uebyte mes, short ano);
    CDate(const std::string& data);

    std::string Format(const std::string& formato) const;

    void operator+=(int dias);
    void operator-=(int dias);
    CDate operator+(int dias) const;
    CDate operator-(int dias) const;

    bool operator==(const CDate& data) const = default;
    std::strong_ordering operator<=>(const CDate& data) const;

    uebyte GetDia() const { return m_dia; }
    uebyte GetMes() const { return m_mes; }
    short GetAno() const { return m_ano; }

private:
    short m_dia = 0;
    short m_mes = 0;
    short m_ano = 0;
    short m_diaSemana = 0;
};

} // namespace api
