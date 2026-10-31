#pragma once

// ecourna::api::security::IAsymmetricCipher<...>. RTTI names the template, its four arguments (for
// cepesc::CCepescCipher: CPlainText, CCipheredOut, CCipheredIn, std::vector<unsigned char>) and its private base
// pattern::NonCopyable. The target has no vtable of this class to show its slots pure; slots 2 and 3 of the derived
// vtable take the first and the third argument and return the second and the fourth (fns 2681 and 5171). The path, the
// parameter names, the members' names and their const are chosen.
#include "ecourna/api/pattern/noncopyable.hpp"

namespace ecourna::api::security {

template <typename TEXTO, typename CIFRADO, typename ENTRADA, typename DECIFRADO>
class IAsymmetricCipher : private pattern::NonCopyable {
public:
    virtual ~IAsymmetricCipher() = default;

    virtual CIFRADO Encrypt(const TEXTO& texto) const = 0;
    virtual DECIFRADO Decrypt(const ENTRADA& entrada) const = 0;
};

} // namespace ecourna::api::security
