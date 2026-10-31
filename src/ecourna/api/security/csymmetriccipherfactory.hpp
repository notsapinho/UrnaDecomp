#pragma once
#include "ecourna/api/security/isymmetriccipherfactory.hpp"

namespace ecourna::api::security {

// RTTI names the class and its base; slots 2 and 3 are fns 1884 and 9489. Not final: 1884 calls slot 3 through the
// vtable. The path is chosen (src/units/137-ecourna-api-security-ciphers.mk).
class CSymmetricCipherFactory : public ISymmetricCipherFactory {
public:
    std::shared_ptr<ISymmetricCipher> Create(const std::string& senha) override;
    std::shared_ptr<ISymmetricCipher> Create(const CAesKey& chave) override;
};

} // namespace ecourna::api::security
