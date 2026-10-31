#pragma once

#include <compare>
#include <ctime>
#include <string>

#include "api/util/cdate.h"
#include "api/util/ctime.h"

namespace api {

// Target fn 5475 holds it, inlined by binaryen (a second stack-pointer prologue): whether a string is a date and time
// written DDMMYYYYHHMM[SS], 12 or 14 digits, by IsValidDate on the first 8 and IsValidTime on the rest. No record,
// vtable slot or RTTI names it: the name is chosen from that role, as IsValidDate's and IsValidTime's are.
bool IsValidDateTime(const std::string& dataHora);

// The date at +0 and the time of day at +8, 12 bytes. The member names are not in the target.
// - The default constructor runs CDate's and CTime's (fns 1382 and 2230, today and now): __wasm_call_ctors builds a
//   static one so, calling 1382 on 1833312 and 2230 on 1833320. That it is defaulted is a choice.
// - Now (fn 479) builds one from ISystemDateTime's clock with CDateTime(time_t) (fn 1000) and returns it; the name is
//   chosen. Written as a delegating default constructor instead, clang inlines fn 1000 into it in this TU
//   (-Rpass=inline: cost 70, threshold 337), where the target calls 1000; as a static returning CDateTime(...), the
//   call stays.
// - ConvertToLocalTime (fn 1381) is the time_t of the date and time, by timegm; operator+=(int) (fn 2233) adds seconds
//   through it and gmtime_r. Both names are chosen from what the bodies do; no record names either.
// - FormatCurrentDate and FormatCurrentTime (fns 5472, 5473) are `std::string (*)(const std::string &)` callbacks: fn
//   5343 passes their table slots with "DD/MM/YYYY" and "hh:mm:ss" to api::CMTFormBuilder::AddTextField (fn 651), and
//   fn 7787 to fn 3058, each building an api::CDataTextFmt<std::string (*)(const std::string &)> over the pointer; and
//   comum::CImprimirExtratoCarga::ImprimeDataHoraEmissao (fn 11216) calls both. Each formats the date or the time of
//   Now (inlined, fns 1155 and 1000) through a copy of it. Their names, and that they are static members and not free
//   functions, are chosen; src/units/125-uenux2-cdatetime.mk has the forms measured.
// - GetData and GetHora return the members by reference: comum::CRelatorioTesteImpressora::EstaEmHorarioVerao (fn 11198)
//   hands the date of a local CDateTime to CDate::operator<=> (fn 1261) with no copy. With getters that return by value,
//   a form of 11198 that compares in its own body copies the date into its frame for each compare (its object). Their
//   names are chosen.
class CDateTime {
public:
    CDateTime() = default;
    explicit CDateTime(time_t tempo);
    CDateTime(const std::string& dataHora);

    static CDateTime Now();
    static CDateTime ConvertFromTimestamp(const std::string& timestamp);
    static std::string FormatCurrentDate(const std::string& formato);
    static std::string FormatCurrentTime(const std::string& formato);

    const CDate& GetData() const { return m_data; }
    const CTime& GetHora() const { return m_hora; }

    time_t ConvertToLocalTime() const;
    void operator+=(int segundos);

    std::strong_ordering operator<=>(const CDateTime& dataHora) const;

private:
    void ConvertFromLocalTime(time_t tempo);

    CDate m_data;
    CTime m_hora;
};

} // namespace api
