#include "api/util/ctime.h"

#include "api/util/eueutilerror.h"
#include "ecourna/api/util/cstringutils.hpp"

using ecourna::api::util::CStringUtils;

namespace api {

static const size_t SEGUNDOS_POR_DIA = 24 * 60 * 60;

// (original lines 12-21: content not recovered)
#line 22
bool IsValidTime(const std::string& hora)
{
    if ((hora.size() != 4) && (hora.size() != 6)) {
        return false;
    }

    if (hora.find_first_not_of("0123456789") != std::string::npos) {
        return false;
    }

    uebyte horas = CStringUtils::ToByte(hora.substr(0, 2));
    uebyte minutos = CStringUtils::ToByte(hora.substr(2, 2));
    uebyte segundos = 0;
    if (hora.size() == 6) {
        segundos = CStringUtils::ToByte(hora.substr(4, 2));
    }

    return (horas < 24) && (minutos < 60) && (segundos < 60);
}

static size_t EncodeTime(uebyte hora, uebyte minuto, uebyte segundo)
{
    if ((hora < 24) && (minuto < 60) && (segundo < 60)) {
        return (hora * 3600) + (minuto * 60) + segundo;
    }

    throw CUeUtilError(EUE_UTIL_HORA_INVALIDA, "Hora inválida");
}

static size_t EncodeTime(const std::string& hora)
{
    if (IsValidTime(hora)) {
        uebyte horas = CStringUtils::ToByte(hora.substr(0, 2));
        uebyte minutos = CStringUtils::ToByte(hora.substr(2, 2));
        uebyte segundos = 0;
        if (hora.size() == 6) {
            segundos = CStringUtils::ToByte(hora.substr(4, 2));
        }
        return (horas * 3600) + (minutos * 60) + segundos;
    }

    throw CUeUtilError(EUE_UTIL_HORA_TEXTO_INVALIDA, "Hora inválida");
}

CTime::CTime(const std::string& hora)
    : m_segundos(EncodeTime(hora))
{
}

CTime::CTime(uebyte hora, uebyte minuto, uebyte segundo)
    : m_segundos(EncodeTime(hora, minuto, segundo))
{
}

// (original lines 76-139: content not recovered)
#line 140
void CTime::operator+=(int segundos)
{
    if (segundos < 0) {
        operator-=(-segundos);
    }
    else {
        if ((segundos >= SEGUNDOS_POR_DIA) ||
            ((m_segundos + segundos) >= SEGUNDOS_POR_DIA)) {
            throw CUeUtilError(EUE_UTIL_HORA_OVERFLOW, "Overflow");
        }
        m_segundos += segundos;
    }
}

void CTime::operator-=(int segundos)
{
    if (segundos < 0) {
        operator+=(-segundos);
    }
    else {
        if (m_segundos < static_cast<size_t>(segundos)) {
            throw CUeUtilError(EUE_UTIL_HORA_UNDERFLOW, "Underflow");
        }
        m_segundos -= segundos;
    }
}

CTime CTime::operator-(int segundos) const
{
    CTime tempo(*this);
    tempo -= segundos;
    return tempo;
}

} // namespace api
