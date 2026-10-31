#pragma once

// ecourna::api::security::ISymmetricCipherFactory. RTTI names the class and its private base pattern::NonCopyable
// (a __vmi_class_type_info, like ISymmetricCipher's). The path is chosen, beside irng.hpp: no record names a file of
// this class. The bytes give a virtual destructor in the first slot: the control block's __on_zero_shared calls the
// deleting destructor at vtable + 4 (fn 172). Slots 2 and 3 are CSymmetricCipherFactory's overrides (fns 1884 and
// 9489); the target has no vtable of this class to show them pure, and their names and their const are chosen: slot 2
// takes a password, slot 3 the key slot 2 derives from it.
#include <memory>
#include <string>

#include "ecourna/api/pattern/noncopyable.hpp"
#include "ecourna/api/security/isymmetriccipher.hpp"

namespace ecourna::api::security {

class ISymmetricCipherFactory : private pattern::NonCopyable {
public:
    virtual ~ISymmetricCipherFactory() = default;

    virtual std::shared_ptr<ISymmetricCipher> Create(const std::string& senha) = 0;
    virtual std::shared_ptr<ISymmetricCipher> Create(const CAesKey& chave) = 0;
};

} // namespace ecourna::api::security
