// Reconstruction: comum::md::estadoaplicacao::CDadoCarga's constructor (target fn 5633, which holds ValidaModelo: line
// 84's record, inlined by binaryen) and GetFaseChar (fn 2253, line 108's record). The constructor's line is chosen.
#include "app/comum/dados/md/estadoaplicacao/cdadocarga.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md::estadoaplicacao {

CDadoCarga::CDadoCarga(EUrnaTurno turno, EUrnaTipo tipoUrnaT1, EUrnaTipo tipoUrnaT2, EUrnaModelo modelo, EUrnaFase fase)
    : m_turno(turno), m_tipoUrnaT1(tipoUrnaT1), m_tipoUrnaT2(tipoUrnaT2), m_modelo(modelo), m_fase(fase)
{
    ValidaModelo(m_modelo);
}

// (original lines 17-80: content not recovered)
#line 81
void CDadoCarga::ValidaModelo(const EUrnaModelo modelo)
{
    if (modelo < eModeloUE2013 || modelo > eModeloUE2022) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8075, std::format("Modelo inválido: {}", modelo));
    }
}

// (original lines 88-97: content not recovered)
#line 98
char CDadoCarga::GetFaseChar() const
{
    switch (m_fase) {
        case FASE_OFICIAL:
            return 'o';
        case FASE_SIMULADO:
            return 's';
        case FASE_TREINAMENTO:
            return 't';
        default:
            throw CUeComumDadosError(EUE_COMUM_DADOS_8077, std::format("Fase inválida: {}", m_fase));
    }
}

} // namespace comum::md::estadoaplicacao
