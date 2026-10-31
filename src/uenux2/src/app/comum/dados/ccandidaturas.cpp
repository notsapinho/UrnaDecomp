#include "app/comum/dados/ccandidaturas.h"

#include <format>
#include <mutex>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum {

CCandidaturas& CCandidaturas::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst = std::make_unique<CCandidaturas>();
    }
    return *s_inst;
}

std::unique_ptr<CCandidaturas> CCandidaturas::s_inst;
std::mutex CCandidaturas::s_mutex;

CCandidaturas::CCandidaturas() : CCandidaturas("CCandidaturas") {}

CCandidaturas::~CCandidaturas() = default;

// (original lines 26-84: content not recovered)
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
