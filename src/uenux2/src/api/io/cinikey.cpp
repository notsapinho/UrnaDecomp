#include "api/io/cinikey.h"

#include <utility>

#include "api/io/eueioerror.h"

namespace api {

/**
 * Atribui o valor de outra chave.
 *
 * A chave é identificada pelo nome: só o valor pode ser modificado.
 *
 * @param chave chave de origem
 * @return esta chave
 */
CIniKey& CIniKey::operator=(const CIniKey& chave)
{
    if (m_nome != chave.m_nome) {
        //
        //
        //
        //
        throw CUeIoError(EUE_IO_NOME_CHAVE_MODIFICADO, "O nome de uma chave não pode ser modificado.");
    }

    m_valor = chave.m_valor;

    return *this;
}

CIniKey::CIniKey(std::string nome, std::string valor)
    : m_nome(std::move(nome))
    , m_valor(std::move(valor))
{
}

} // namespace api
