#include "app/comum/dados/md/csecaoeleitoral.h"

#include <set>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

CIdentificacaoAgregada::CIdentificacaoAgregada(ueword numero, ETipoLocalVotacao tipoLocalOrigem)
    : m_tipoLocalOrigem(tipoLocalOrigem), m_numero(numero)
{
}

// (original lines 14-23: content not recovered)
#line 24
CSecaoEleitoral::CSecaoEleitoral(ETipoLocalVotacao tipo, const CIdentificacaoSecao& identificacao,
    const TVectorIdentificacaoAgregada& agregadas)
    : m_tipo(tipo), m_identificacao(identificacao), m_agregadas(agregadas)
{
    std::set<TSecaoID> numeros;
    for (size_t i = 0; i < agregadas.size(); ++i) {
        const TSecaoID numero = agregadas[i].GetNumero();
        numeros.insert(numero);

        if (numero < 1 || numero > 9999) {
            throw CUeComumDadosError(EUE_COMUM_DADOS_8053, "Agregada inválida.");
        }
        if (numero == identificacao.GetSecao()) {
            throw CUeComumDadosError(EUE_COMUM_DADOS_8054, "Agregada igual à principal.");
        }
    }
    if (numeros.size() != agregadas.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8055, "Agregada repetida.");
    }
}

} // namespace comum::md
