// Reconstruction: comum::md::CAbrangencia (target fn 3739); the records (lines 31 to 51) place the throws.
#include "app/comum/md/cabrangencia.h"

#include <format>

#include "app/comum/md/euecomummderror.h"

namespace comum::md {

// (original lines 10-25: content not recovered)
#line 26
CAbrangencia::CAbrangencia(ETipoAbrangencia tipo, const std::string& uf, TMunicipioID municipio)
    : m_tipo(tipo), m_uf(uf), m_municipio(municipio)
{
    const bool semUF = uf.empty();
    if (!semUF && uf.size() != 2) {
        throw CUeComumMdError(EUE_COMUM_MD_8900, "UF inválida [" + uf + "]");
    }
    if (semUF && tipo != ABRANGENCIA_FEDERAL) {
        throw CUeComumMdError(EUE_COMUM_MD_8901, "UF não informada para abrangência não federal");
    }


    if (tipo == ABRANGENCIA_MUNICIPAL && municipio == 0) {
        throw CUeComumMdError(EUE_COMUM_MD_8902, "Município zerado para abrangência municipal");
    }
    if (tipo != ABRANGENCIA_MUNICIPAL && municipio != 0) {
        throw CUeComumMdError(EUE_COMUM_MD_8903, "Município informado para abrangência não municipal");
    }


    if (tipo == ABRANGENCIA_FEDERAL && !semUF) {
        throw CUeComumMdError(EUE_COMUM_MD_8904, "UF informada para abrangência federal");
    }

    if (tipo != ABRANGENCIA_MUNICIPAL && tipo != ABRANGENCIA_ESTADUAL && tipo != ABRANGENCIA_FEDERAL) {
        throw CUeComumMdError(EUE_COMUM_MD_8905, std::format("Tipo de abrangência inválido: ", static_cast<int>(tipo)));
    }
}

} // namespace comum::md
