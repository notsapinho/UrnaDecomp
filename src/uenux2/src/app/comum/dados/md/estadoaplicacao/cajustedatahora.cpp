// Reconstruction: comum::md::estadoaplicacao::CAjusteDataHora's constructor, which binaryen merges with every two-word
// constructor into fn 1081, and AdicionaDeltaT (target fn 3702), line 32's record. The constructor's line is chosen.
#include "app/comum/dados/md/estadoaplicacao/cajustedatahora.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md::estadoaplicacao {

CAjusteDataHora::CAjusteDataHora(ETipoDeltaT tipo, ueint32 deltaT) : m_tipo(tipo), m_deltaT(deltaT)
{
}

// (original lines 15-28: content not recovered)
#line 29
void CAjusteDataHora::AdicionaDeltaT(const ueint32 deltaT)
{
    if (m_tipo != eAlterarDataSistema) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8071, std::format("DeltaT pode ser adicionado apenas para eAlterarDataSistema {}", m_tipo));
    }
    m_deltaT += deltaT;
}

} // namespace comum::md::estadoaplicacao
