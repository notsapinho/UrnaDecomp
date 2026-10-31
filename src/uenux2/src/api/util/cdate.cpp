// api::CDate (/home/rubio/tse/uenux2/src/api/util/cdate.cpp). Reconstruction's note, not TSE's text: the throws of
// CDate(const std::string &) (fn 3649) and Format (fn 706) are records of the target, at lines 94 and 104, column 15,
// and line 130, column 27. Every other line, and the order of the functions no record places, is a choice
// (src/units/125-uenux2-cdatetime.mk).

#include "api/util/cdate.h"

#include <ctime>
#include <format>

#include "api/util/eueutilerror.h"
#include "api/util/isystemdatetime.h"
#include "ecourna/api/util/cstringutils.hpp"

using ecourna::api::util::CStringUtils;

namespace api {

short g_seculo = 2000;

static const char* const DIAS_SEMANA[] = {"DOM", "SEG", "TER", "QUA", "QUI", "SEX", "SAB"};

static bool Bissexto(short ano)
{
    return ((ano % 4) == 0) && (((ano % 100) != 0) || ((ano % 400) == 0));
}

static uebyte DiasNoMes(uebyte mes, short ano)
{
    switch (mes) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 2:
            return Bissexto(ano) ? 29 : 28;
        default:
            return 30;
    }
}

static short DiasNoAno(short ano)
{
    return Bissexto(ano) ? 366 : 365;
}

static ueword DiaDoAno(uebyte dia, uebyte mes, short ano)
{
    ueword total = dia;
    for (uebyte i = 1; i < mes; i++) {
        total += DiasNoMes(i, ano);
    }
    return total;
}

bool IsValidDate(const std::string& data)
{
    if ((data.size() != 6) && (data.size() != 8)) {
        return false;
    }

    if (data.find_first_not_of("0123456789") != std::string::npos) {
        return false;
    }

    uebyte dia = CStringUtils::ToByte(data.substr(0, 2));
    uebyte mes = CStringUtils::ToByte(data.substr(2, 2));
    short ano = CStringUtils::ToInt16(data.substr(4));
    if (data.size() == 6) {
        ano += g_seculo;
    }

    return (dia > 0) && (mes > 0) && (mes <= 12) && (dia <= DiasNoMes(mes, ano));
}

CDate::CDate()
{
    time_t agora = ISystemDateTime::GetInst().GetTime();
    struct tm tm;
    gmtime_r(&agora, &tm);
    m_dia = tm.tm_mday;
    m_mes = tm.tm_mon + 1;
    m_ano = tm.tm_year + 1900;
    m_diaSemana = tm.tm_wday;
}

CDate::CDate(const std::string& data)
{
    if (!IsValidDate(data)) {
        throw CUeUtilError(EUE_UTIL_DATA_INVALIDA, "Data inválida [" + data + "]");
    }

    short ano = CStringUtils::ToInt16(data.substr(4));
    if (data.size() == 6) {
        ano += g_seculo;
    }
    std::string dataCompleta = data.substr(0, 4) + std::to_string(ano);
    struct tm tm = {};
    if (strptime(dataCompleta.c_str(), "%d%m%Y", &tm) == nullptr) {
        throw CUeUtilError(EUE_UTIL_DATA_NAO_CONVERTIDA, "Data inválida [" + dataCompleta + "]");
    }

    m_ano = tm.tm_year + 1900;
    m_mes = tm.tm_mon + 1;
    m_dia = tm.tm_mday;
    m_diaSemana = tm.tm_wday;
}

CDate::CDate(uebyte dia, uebyte mes, short ano)
    : CDate(std::format("{:02}{:02}{:04}", dia, mes, ano))
{
}

// (original lines 118-122: content not recovered)
#line 123
std::string CDate::Format(const std::string& formato) const
{
    std::string data;
    for (size_t i = 0; i < formato.size(); i++) {
        switch (formato[i]) {
            case 'A':
                if ((m_diaSemana < 0) || (m_diaSemana > 6)) {
                    throw CUeUtilError(EUE_UTIL_DIA_SEMANA_INVALIDO, std::format("Dia da semana inválido {}", m_diaSemana));
                }
                data += DIAS_SEMANA[m_diaSemana];
                break;
            case 'D':
                if ((i + 1 < formato.size()) && (formato[i + 1] == 'D')) {
                    std::string dia = std::to_string(m_dia);
                    if (dia.size() < 2) {
                        data += "0" + dia;
                    }
                    else {
                        data += dia;
                    }
                    i++;
                }
                else {
                    data += std::to_string(m_dia);
                }
                break;
            case 'M':
                if ((i + 1 < formato.size()) && (formato[i + 1] == 'M')) {
                    std::string mes = std::to_string(m_mes);
                    if (mes.size() < 2) {
                        data += "0" + mes;
                    }
                    else {
                        data += mes;
                    }
                    i++;
                }
                else {
                    data += std::to_string(m_mes);
                }
                break;
            case 'Y':
                if ((i + 3 < formato.size()) && (formato.substr(i, 4) == "YYYY")) {
                    std::string ano = std::to_string(m_ano);
                    if (ano.size() < 4) {
                        ano.insert(0, 4 - ano.size(), '0');
                    }
                    data += ano;
                    i += 3;
                }
                else if ((i + 1 < formato.size()) && (formato.substr(i, 2) == "YY")) {
                    std::string ano = std::to_string(m_ano % 100);
                    if (ano.size() < 2) {
                        ano.insert(0, 2 - ano.size(), '0');
                    }
                    data += ano;
                    i++;
                }
                else {
                    data += std::to_string(m_ano % 100);
                }
                break;
            default:
                data += formato[i];
                break;
        }
    }
    return data;
}

void CDate::operator+=(int dias)
{
    if (dias < 0) {
        operator-=(-dias);
        return;
    }

    int resto = DiaDoAno(m_dia, m_mes, m_ano) + dias;
    short diasNoAno;
    while (resto > (diasNoAno = DiasNoAno(m_ano))) {
        resto -= diasNoAno;
        m_ano++;
    }

    m_mes = 1;
    uebyte diasNoMes;
    while (resto > (diasNoMes = DiasNoMes(m_mes, m_ano))) {
        resto -= diasNoMes;
        m_mes++;
    }
    m_dia = resto;

    m_diaSemana += dias % 7;
    m_diaSemana %= 7;
}

void CDate::operator-=(int dias)
{
    if (dias < 0) {
        operator+=(-dias);
        return;
    }

    int resto = DiaDoAno(m_dia, m_mes, m_ano) - dias;
    while (resto <= 0) {
        m_ano--;
        resto += DiasNoAno(m_ano);
    }

    m_mes = 1;
    uebyte diasNoMes;
    while (resto > (diasNoMes = DiasNoMes(m_mes, m_ano))) {
        resto -= diasNoMes;
        m_mes++;
    }
    m_dia = resto;

    m_diaSemana += 7 - (dias % 7);
    m_diaSemana %= 7;
}

CDate CDate::operator-(int dias) const
{
    CDate data(*this);
    data -= dias;
    return data;
}

std::strong_ordering CDate::operator<=>(const CDate& data) const
{
    if (auto comparacao = m_ano <=> data.m_ano; comparacao != 0) {
        return comparacao;
    }
    if (auto comparacao = m_mes <=> data.m_mes; comparacao != 0) {
        return comparacao;
    }
    return m_dia <=> data.m_dia;
}

} // namespace api
