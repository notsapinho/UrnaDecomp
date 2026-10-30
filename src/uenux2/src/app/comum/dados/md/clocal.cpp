#include "app/comum/dados/md/clocal.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 7-55: content not recovered)
#line 56
const CSecaoEleitoral& CLocal::GetSecao() const
{
    if (!m_secao.has_value()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8012, "Não há informação.");
    }
    return *m_secao;
}

const CIdentificacaoUrnaContingencia& CLocal::GetContingencia() const
{
    if (!m_contingencia.has_value()) {
        throw CUeComumDadosError(static_cast<EUeComumDadosError>(8013), "Não há informação.");
    }
    return *m_contingencia;
}

void CLocal::ValidaCriacao() const
{
    if (m_nomePais.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8014, "País inválido.");
    }
    if (m_siglaUF.size() != 2) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8015, "Sigla da UF inválida.");
    }
    if (m_nomeUF.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8016, "Nome da UF inválido.");
    }
    if (m_secao.has_value() && m_secao->GetIdentificacao().GetMunicipio() != m_municipio.GetCodigo()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8017, "Códigos de município incompatíveis para seção.");
    }

    if (m_contingencia.has_value() &&
        m_contingencia->GetMunicipio() != m_municipio.GetCodigo()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8018, "Códigos de município incompatíveis para urna de contingência.");
    }
}

} // namespace comum::md
