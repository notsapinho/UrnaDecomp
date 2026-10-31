#pragma once
#include <vector>

#include "ecourna/api/security/cepesc/ccipheredin.hpp"
#include "ecourna/api/security/cepesc/ccipheredout.hpp"
#include "ecourna/api/security/cepesc/cplaintext.hpp"
#include "ecourna/api/security/iasymmetriccipher.hpp"
#include "ecourna/api/uetypes.hpp"

namespace ecourna::api::cepesc {

// RTTI names the class and its base; slots 2 and 3 are fns 2681 and 5171. The path is chosen: the vtable lies between
// asn1/ckeyloader.cpp's record and cepesc/ccipheredin.cpp's, and the namespace's other classes are cepesc/'s
// (src/units/137-ecourna-api-security-ciphers.mk).
class CCepescCipher : public security::IAsymmetricCipher<CPlainText, CCipheredOut, CCipheredIn, std::vector<uebyte>> {
public:
    CCipheredOut Encrypt(const CPlainText& texto) const override;
    std::vector<uebyte> Decrypt(const CCipheredIn& entrada) const override;
};

} // namespace ecourna::api::cepesc
