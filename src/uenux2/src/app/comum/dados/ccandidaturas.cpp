#include "app/comum/dados/ccandidaturas.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum {

// (original lines 9-84: content not recovered)
#line 85
const std::string CCandidaturas::RecuperaVersaoPacote(TCargoID cargo) const
{
    const auto versao = m_versoesPacote.find(cargo);
    if (versao == m_versoesPacote.end()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7801, std::format("Versão de pacote não encontrada para o cargo {}", cargo));
    }
    return versao->second;
}

} // namespace comum

// <stubs>
// f2838 · 599 B · unmatched · name unknown
// ? f2838(i32) { ... }
// </stubs>
