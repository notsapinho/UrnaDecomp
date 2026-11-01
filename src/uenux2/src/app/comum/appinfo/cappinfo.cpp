#include "app/comum/appinfo/cappinfo.h"

#include <format>

#include "app/comum/appinfo/euecomumappinfoerror.h"

namespace comum {

// (original lines 9-37: content not recovered)
#line 38
template <typename ESTADO>
static ESTADO& GetEstado(const std::string& nome, std::optional<ESTADO>& estado)
{
    if (!estado) {
        throw CUeComumAppInfoError(EUE_APPINFO_ESTADO_NAO_CARREGADO, std::format("O estado não foi carregado: {}", nome));
    }
    return *estado;
}

// (original lines 47-52: content not recovered)
#line 53
template <typename ESTADO>
static const ESTADO& GetEstado(const std::string& nome, const std::optional<ESTADO>& estado)
{
    if (!estado) {
        throw CUeComumAppInfoError(EUE_APPINFO_ESTADO_CONST_NAO_CARREGADO, std::format("O estado não foi carregado: {}", nome));
    }
    return *estado;
}

// (original lines 62-69: content not recovered)
#line 70
md::estadoaplicacao::CEstadoGeral& CAppInfo::GetGeral()
{
    return GetEstado("GetGeral", m_geral);
}

const md::estadoaplicacao::CEstadoGeral& CAppInfo::GetGeral() const
{
    return GetEstado("GetGeral", m_geral);
}

md::estadoaplicacao::CEstadoGeralVota& CAppInfo::GetVota(EUrnaTurno turno)
{
    return GetEstado("GetVota", m_vota[IndiceTurno("GetVota", turno)]);
}

const md::estadoaplicacao::CEstadoGeralVota& CAppInfo::GetVota(EUrnaTurno turno) const
{
    return GetEstado("GetVota", m_vota[IndiceTurno("GetVota", turno)]);
}

const md::estadoaplicacao::CEstadoGeralGap& CAppInfo::GetGap(EUrnaTurno turno) const
{
    return GetEstado("GetGap", m_gap[IndiceTurno("GetGap", turno)]);
}

std::vector<std::string> CAppInfo::GetCodigosCarga(EUrnaTurno turno) const
{
    return GetGap(turno).GetCodigosCarga();
}

bool CAppInfo::TemVota(EUrnaTurno turno) const
{
    return m_vota[IndiceTurno("TemVota", turno)].has_value();
}

// (original lines 105-452: content not recovered)
#line 453
bool CAppInfo::EhTreinamentoEleitor()
{
    if (GetInst().GetGeral().GetDadoCarga().GetFase() == FASE_TREINAMENTO) {
        return GetInst().GetVota().GetTreinamentoEleitor();
    }
    return false;
}

// (original lines 461-462: content not recovered)
#line 463
size_t CAppInfo::IndiceTurno(const std::string& nome, EUrnaTurno turno)
{
    const EUrnaTurno efetivo = turno == TURNO_ATUAL ? GetInst().GetGeral().GetDadoCarga().GetTurno() : turno;
    switch (efetivo) {
        case TURNO_1:
            return 0;
        case TURNO_2:
            return 1;
        default:
            throw CUeComumAppInfoError(EUE_APPINFO_TURNO_INVALIDO, std::format("Turno {} invalido: {}", turno, nome));
    }
}




} // namespace comum
