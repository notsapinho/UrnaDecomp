// Reconstruction: api::hash::CHashDiretorio's constructor and ValidaObjeto, which binaryen inlines into
// CMontadorHash::CriaHashesDiretorio (target fn 5360), their one caller. The throw is a record of the target (line 41,
// column 15); the constructor has none, and its lines are a choice (src/units/198-uenux2-chashdiretorio.mk).
#include "api/hash/chashdiretorio.h"

#include "api/hash/euehasherror.h"

namespace api::hash {

CHashDiretorio::CHashDiretorio(const std::string& nome, const std::vector<CHashArquivo>& arquivos,
    const std::vector<CHashDiretorio>& diretorios)
    : m_nome(nome), m_arquivos(arquivos), m_diretorios(diretorios)
{
    ValidaObjeto();
}

// (original lines 17-37: content not recovered)
#line 38
void CHashDiretorio::ValidaObjeto() const
{
    if (m_nome.empty()) {
        throw CUeHashError(EUE_HASH_DIRETORIO_NOME_INVALIDO, "CHashDiretorio: nome inválido.");
    }
}

} // namespace api::hash
