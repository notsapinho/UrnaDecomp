#include "ecourna/api/security/csymmetriccipherfactory.hpp"

#include <vector>

#include "ecourna/api/security/caescipher.hpp"
#include "ecourna/api/security/cblockcipher.hpp"
#include "ecourna/api/security/csha.hpp"
#include "ecourna/api/security/ctrng.hpp"

namespace ecourna::api::security {

std::shared_ptr<ISymmetricCipher> CSymmetricCipherFactory::Create(const std::string& senha)
{
    std::vector<uebyte> dados(senha.begin(), senha.end());
    CSha512 sha;
    sha.Update(dados);
    const std::vector<uebyte> resumo = sha.Finish();
    const std::vector<uebyte> bytes(resumo.begin() + 16, resumo.begin() + 48);
    const CAesKey chave(bytes, ESCKS_256);
    return Create(chave);
}

std::shared_ptr<ISymmetricCipher> CSymmetricCipherFactory::Create(const CAesKey& chave)
{
    return std::shared_ptr<ISymmetricCipher>(new CBlockCipher<CAesCipher, CTrng>(chave));
}

} // namespace ecourna::api::security
