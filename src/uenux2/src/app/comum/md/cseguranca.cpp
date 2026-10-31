// Reconstruction: comum::md::CSeguranca (target fn 3823); the records (lines 24, 27, 30) place the throws.
#include "app/comum/md/cseguranca.h"

#include "app/comum/md/euecomummderror.h"

namespace comum::md {

// (original lines 8-19: content not recovered)
#line 20
CSeguranca::CSeguranca(uebyte idTipoArquivo, uebyte idCriptografia, const std::vector<uebyte>& chave)
    : m_idTipoArquivo(idTipoArquivo), m_idCriptografia(idCriptografia), m_chave(chave)
{
    if (idTipoArquivo > 2) {
        throw CUeComumMdError(EUE_COMUM_MD_8925, "Tipo do arquivo inválido.");
    }
    if (idCriptografia < 1 || idCriptografia > 3) {
        throw CUeComumMdError(EUE_COMUM_MD_8926, "ID da criptografia inválido.");
    }
    if (chave.empty()) {
        throw CUeComumMdError(EUE_COMUM_MD_8927, "Chave vazia.");
    }
}

} // namespace comum::md
