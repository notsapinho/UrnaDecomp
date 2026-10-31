// Reconstruction: comum::md::estadoaplicacao::CLocalidadeEleitoral's constructor (target fn 5631) and ValidaCriacao, whose
// records are lines 18, 21 and 24. The constructor's line is chosen; that it holds ValidaCriacao is binaryen's inlining.
#include "app/comum/dados/md/estadoaplicacao/clocalidadeeleitoral.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md::estadoaplicacao {

CLocalidadeEleitoral::CLocalidadeEleitoral(uedword municipio, ueword zona, ueword secao)
    : m_municipio(municipio), m_zona(zona), m_secao(secao)
{
    ValidaCriacao();
}

void CLocalidadeEleitoral::ValidaCriacao() const
{
    if (m_municipio >= 100000) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8095, "Município inválido.");
    }
    if (m_zona >= 10000) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8096, "Zona inválida.");
    }
    if (m_secao >= 10000) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8097, "Seção inválida.");
    }
}

} // namespace comum::md::estadoaplicacao
