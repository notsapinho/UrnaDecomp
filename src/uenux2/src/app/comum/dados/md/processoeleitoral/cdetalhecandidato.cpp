// Reconstruction notes: comum::md::CDetalheCandidato::GetSuplente (target fn 1545), on its record's line 27.
#include "app/comum/dados/md/processoeleitoral/cdetalhecandidato.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 8-23: content not recovered)
#line 24
const CSuplencia& CDetalheCandidato::GetSuplente(uebyte suplente) const
{
    if (suplente == 0 || suplente > m_suplentes.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8145, "Suplente inexistente");
    }
    return m_suplentes[suplente - 1];
}

} // namespace comum::md
