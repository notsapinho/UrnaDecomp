// Reconstruction: comum::md::CCarga::ValidaCriacao (target fn 5670); its records (lines 36, 41, 46 and 51, column 15)
// place the throws. The constructor that calls it is not reconstructed.
#include "app/comum/dados/md/correspondencia/ccarga.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 9-32: content not recovered)
#line 33
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
