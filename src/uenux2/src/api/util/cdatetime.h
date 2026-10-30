#pragma once

#include <string>

#include "api/util/cdate.h"
#include "api/util/ctime.h"

namespace api {

// Recovered: the layout only, 12 bytes, the date at +0 and the time of day at +8. CDateTime::ConvertFromLocalTime
// (target fn 5476, record cdatetime.cpp:61) builds a CDate(dia, mes, ano) (fn 2765) and stores its 8 bytes at +0, then
// stores the 4 bytes of a CTime(hora, minuto, segundo) (fn 3642) at +8. The member names are not in the target.
class CDateTime {
public:
    CDateTime(const std::string& dataHora);

private:
    CDate m_data;
    CTime m_hora;
};

} // namespace api
