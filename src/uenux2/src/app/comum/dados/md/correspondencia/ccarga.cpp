// Reconstruction: comum::md::CCarga's constructor (target fn 2802) and ValidaCriacao (target fn 5670); ValidaCriacao's
// records (lines 36, 41, 46 and 51, column 15) place its throws. The constructor has no record: its line, above
// ValidaCriacao, is chosen.
#include "app/comum/dados/md/correspondencia/ccarga.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 10-19: content not recovered)
#line 20
CCarga::CCarga(uedword numeroInternoUrna, const std::string& numeroSerieFC, const api::CDateTime& dataHoraCarga,
               const std::string& codigoCarga,
               const ecourna::app::dados::CIdentificadorGeradorMidia& identificadorGeradorMidia)
    : m_numeroInternoUrna(numeroInternoUrna),
      m_numeroSerieFC(numeroSerieFC),
      m_dataHoraCarga(dataHoraCarga),
      m_codigoCarga(codigoCarga),
      m_identificadorGeradorMidia(identificadorGeradorMidia)
{
    ValidaCriacao();
}


void CCarga::ValidaCriacao() const
{
    if (m_numeroSerieFC.size() != 8) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8019, "Serial da MC inválido [" + m_numeroSerieFC + "]");
    }


    if (m_numeroSerieFC.find_first_not_of("0123456789ABCDEFabcdef") != std::string::npos) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8020, "Serial da MC inválido [" + m_numeroSerieFC + "]");
    }


    if (m_codigoCarga.size() != 24) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8021, "Código da carga inválido [" + m_codigoCarga + "]");
    }


    if (m_codigoCarga.find_first_not_of("0123456789") != std::string::npos) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8022, "Código da carga inválido [" + m_codigoCarga + "]");
    }
}

} // namespace comum::md
