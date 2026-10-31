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
// - CDateTime(const CDate&, const CTime&) is what comum::asn::Utils::DesconverteDataHoraJE (fn 1713) builds its result
//   with: the date's 8 bytes and the time's word stored into the result. That it is a constructor, inline, is a choice.
// - ConvertToLocalTime (fn 1381) is the time_t of the date and time, by timegm; operator+=(int) (fn 2233) adds seconds
//   through it and gmtime_r. Both names are chosen from what the bodies do; no record names either.
class CDateTime {
public:
    CDateTime() = default;
    explicit CDateTime(time_t tempo);
    CDateTime(const std::string& dataHora);
    CDateTime(const CDate& data, const CTime& hora) : m_data(data), m_hora(hora) {}

    static CDateTime Now();
    static CDateTime ConvertFromTimestamp(const std::string& timestamp);

    time_t ConvertToLocalTime() const;
    void operator+=(int segundos);

    std::strong_ordering operator<=>(const CDateTime& dataHora) const;

private:
    void ConvertFromLocalTime(time_t tempo);

    CDate m_data;
    CTime m_hora;
};

} // namespace api
