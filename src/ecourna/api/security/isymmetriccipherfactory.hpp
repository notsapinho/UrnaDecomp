#pragma once

// ecourna::api::security::ISymmetricCipherFactory: the head alone. RTTI of its control block names it; the path is chosen, beside irng.hpp: no record names a file of this class. The bytes give a virtual destructor in the first slot: the control block's
// __on_zero_shared calls the deleting destructor at vtable + 4 (fn 172). No member is reconstructed, so nothing may construct it.

namespace ecourna::api::security {

class ISymmetricCipherFactory {
public:
    virtual ~ISymmetricCipherFactory() = default;
};

} // namespace ecourna::api::security
