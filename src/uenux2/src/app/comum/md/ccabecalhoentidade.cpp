// Reconstruction: comum::md::CCabecalhoEntidade's constructor (target fn 1945); its records (lines 24 and 27, column
// 15) place the throws.
#include "app/comum/md/ccabecalhoentidade.h"

#include "app/comum/md/euecomummderror.h"

namespace comum::md {

// (original lines 9-19: content not recovered)
#line 20
CCabecalhoEntidade::CCabecalhoEntidade(const api::CDateTime& dataGeracao, uedword codigo, ETipoCabecalho tipo)
    : m_dataGeracao(dataGeracao), m_codigo(codigo), m_tipo(tipo)
{
    if (codigo > 99999) {
        throw CUeComumMdError(EUE_COMUM_MD_8906, "ID inválido.");
    }
    if (tipo < 0 || tipo > 2) {
        throw CUeComumMdError(EUE_COMUM_MD_8907, "Tipo de ID inválido.");
    }
}

} // namespace comum::md
