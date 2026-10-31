#pragma once
#include "ecourna/api/security/irng.hpp"

namespace ecourna::api::security {

// The RNG the block cipher hands to its algorithm. The name, the base and final are RTTI's and the control block's:
// CBlockCipher<CAesCipher, CTrng>::Encrypt (fn 9487) and fn 6154 build it with std::make_shared, whose block is 16
// bytes, so the class holds its vptr alone, and whose __on_zero_shared is the shared empty body 218, which only a final
// class gives (docs/reference/facts/reading.md R4); 9475 also calls slot 5 directly. The path is chosen, beside
// irng.hpp: no record names it. Its slots 2 to 5 are fns 9477, 9476, 9475 and 5173, in ctrng.cpp.
class CTrng final : public IRng {
public:
    uebyte GetByte() override;
    int GetInt() override;
    int Generate(std::vector<uebyte>& dados) override;
    int Generate(std::vector<uebyte>& dados, size_t tamanho) override;
};

} // namespace ecourna::api::security
