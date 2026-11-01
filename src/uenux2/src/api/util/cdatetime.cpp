#include "api/util/cdatetime.h"

#include <format>

#include "api/util/eueutilerror.h"
#include "api/util/isystemdatetime.h"

namespace api {

CDateTime CDateTime::Now()
{
    return CDateTime(ISystemDateTime::GetInst().GetTime());
}

CDateTime::CDateTime(time_t tempo)
{
    ConvertFromLocalTime(tempo);
}

// (original lines 20-26: content not recovered)
#line 27
CDateTime::CDateTime(const std::string& dataHora)
    : m_data(1, 1, 2000)
{
    if (!IsValidDateTime(dataHora)) {
        throw CUeUtilError(EUE_UTIL_DATAHORA_INVALIDA, "Data inválida [" + dataHora + "]");
    }

    m_data = CDate(dataHora.substr(0, 8));
    m_hora = CTime(dataHora.substr(8));
}

bool IsValidDateTime(const std::string& dataHora)
{
    if ((dataHora.size() != 12) && (dataHora.size() != 14)) {
        return false;
    }

    if (dataHora.find_first_not_of("0123456789") != std::string::npos) {
        return false;
    }

    return IsValidDate(dataHora.substr(0, 8)) && IsValidTime(dataHora.substr(8));
}

// (original lines 51-56: content not recovered)
#line 57
void CDateTime::ConvertFromLocalTime(time_t tempo)
{
    struct tm tm;
    if (gmtime_r(&tempo, &tm) == nullptr) {
        throw CUeUtilError(EUE_UTIL_DATAHORA_NAO_CONVERTIDA, "Data inválida [" + std::to_string(tempo) + "]");
    }

    CTime hora(tm.tm_hour, tm.tm_min, tm.tm_sec);
    CDate data(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    m_data = data;
    m_hora = hora;
}

time_t CDateTime::ConvertToLocalTime() const
{
    struct tm tm;
    tm.tm_sec = m_hora.GetSegundo();
    tm.tm_min = m_hora.GetMinuto();
    tm.tm_hour = m_hora.GetHora();
    tm.tm_mday = m_data.GetDia();
    tm.tm_mon = m_data.GetMes() - 1;
    tm.tm_year = m_data.GetAno() - 1900;
    tm.tm_isdst = 0;
    return timegm(&tm);
}

void CDateTime::operator+=(int segundos)
{
    time_t tempo = ConvertToLocalTime() + segundos;
    struct tm tm;
    if (gmtime_r(&tempo, &tm) != nullptr) {
        m_data = CDate(tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
        m_hora = CTime(tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
}

std::strong_ordering CDateTime::operator<=>(const CDateTime& dataHora) const
{
    if (auto comparacao = m_data <=> dataHora.m_data; comparacao != 0) {
        return comparacao;
    }
    return m_hora <=> dataHora.m_hora;
}

std::string CDateTime::FormatCurrentTime(const std::string& formato)
{
    const CDateTime agora = Now();
    const CTime hora = agora.GetHora();
    return hora.Format(formato);
}

std::string CDateTime::FormatCurrentDate(const std::string& formato)
{
    const CDateTime agora = Now();
    const CDate data = agora.GetData();
    return data.Format(formato);
}

std::string CDateTime::FormatCurrentDateTime(const std::string& formato)
{
    const CDateTime agora = Now();
    return agora.GetData().Format(agora.GetHora().Format(formato));
}

CDateTime CDateTime::operator+(time_t segundos) const
{
    CDateTime resultado(*this);
    resultado += segundos;
    return resultado;
}

// (original lines 128-202: content not recovered)
#line 203
CDateTime CDateTime::ConvertFromTimestamp(const std::string& timestamp)
{
    if (timestamp.size() != 14) {
        throw CUeUtilError(EUE_UTIL_TIMESTAMP_INVALIDO, std::format("Data/hora [{}] não está no formato 'AAAAMMDDhhmmss'", timestamp));
    }

    return CDateTime(timestamp.substr(6, 2) + timestamp.substr(4, 2) + timestamp.substr(0, 4) + timestamp.substr(8));
}

} // namespace api
