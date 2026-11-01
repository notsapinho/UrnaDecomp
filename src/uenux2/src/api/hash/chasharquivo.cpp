// The reconstruction's note, not TSE's text: the constructor (fn 3600, no record: its lines are chosen) and
// ValidaObjeto (fn 5364), whose two throws stand on their records' lines, 26 and 30. The gap stands for lines whose
// content is unknown.
#include "api/hash/chasharquivo.h"

#include "api/hash/euehasherror.h"

namespace api::hash {

CHashArquivo::CHashArquivo(const std::string& nome, const std::string& hash)
    : m_nome(nome)
    , m_hash(hash)
{
    ValidaObjeto();
}

// (original lines 17-22: content not recovered)
#line 23
void CHashArquivo::ValidaObjeto() const
{
    if (m_nome.empty()) {
        throw CUeHashError(EUE_HASH_NOME_INVALIDO, "CHashArquivo: nome inválido.");
    }

    if (m_hash.empty()) {
        throw CUeHashError(EUE_HASH_HASH_INVALIDO, "CHashArquivo: hash inválido.");
    }
}

} // namespace api::hash
