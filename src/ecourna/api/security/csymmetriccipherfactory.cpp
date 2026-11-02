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
    const auto inicio = resumo.begin() + 16;
    const auto fim = resumo.begin() + 48;
    const std::vector<uebyte> bytes(inicio, fim);
    const CAesKey chave(bytes, ESCKS_256);
    return Create(chave);
}

std::shared_ptr<ISymmetricCipher> CSymmetricCipherFactory::Create(const CAesKey& chave)
{
    return std::shared_ptr<ISymmetricCipher>(new CBlockCipher<CAesCipher, CTrng>(chave));
}

} // namespace ecourna::api::security
