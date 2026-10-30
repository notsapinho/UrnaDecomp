#include "api/util/ctime.h"

#include "api/util/eueutilerror.h"

namespace api {


static const size_t SEGUNDOS_POR_DIA = 24 * 60 * 60;

// (original lines 10-41: content not recovered)
#line 42
static size_t EncodeTime(uebyte hora, uebyte minuto, uebyte segundo)
{
    if ((hora < 24) && (minuto < 60) && (segundo < 60)) {
        return (hora * 3600) + (minuto * 60) + segundo;
    }

    throw CUeUtilError(EUE_UTIL_HORA_INVALIDA, "Hora inválida");
}

// (original lines 51-70: content not recovered)
#line 71
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
