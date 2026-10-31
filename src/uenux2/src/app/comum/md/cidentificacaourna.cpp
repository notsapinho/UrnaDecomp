// Reconstruction: comum::md::CIdentificacaoUrna's constructor (target fn 5886); its records (lines 25, 28 and 31,
// column 15) place the throws.
#include "app/comum/md/cidentificacaourna.h"

#include "app/comum/md/euecomummderror.h"

namespace comum::md {

// (original lines 9-20: content not recovered)
#line 21
CIdentificacaoUrna::CIdentificacaoUrna(const EUrnaTipo tipo, const TMunicipioID municipio, const TZonaID zona)
    : m_tipo(tipo), m_municipio(municipio), m_zona(zona)
{
    if (tipo < eUrnaVota || tipo > eUrnaContingenciaVotaRecupera) {
        throw CUeComumMdError(EUE_COMUM_MD_8918, "Tipo inválido.");
    }
    if (municipio > 99999) {
        throw CUeComumMdError(EUE_COMUM_MD_8919, "Município inválido.");
    }
    if (zona > 9999) {
        throw CUeComumMdError(EUE_COMUM_MD_8920, "Zona inválida.");
    }
}

} // namespace comum::md
