// Reconstruction notes: comum::md::CProcessoEleitoral::GetPleito2 (target fn 1267), on its record's line 61.
#include "app/comum/dados/md/processoeleitoral/cprocessoeleitoral.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 8-57: content not recovered)
#line 58
const CPleito& CProcessoEleitoral::GetPleito2() const
{
    if (!m_pleito2) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8165, "Não há pleito 2.");
    }
    return *m_pleito2;
}

} // namespace comum::md
