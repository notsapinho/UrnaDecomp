#pragma once
#include "ecourna/api/security/irng.hpp"

namespace ecourna::api::security {

// The seeded RNG: RTTI names the class and its base; slots 2 to 5 are fns 9502, 9500, 9499 and 5178, and the
// constructor (9503) is out of line. final is chosen: 9499 calls slot 5 directly, as a qualified call would. The member
// is the constructor's 32-bit store at +4; its name and type are chosen, and so is the path, beside irng.hpp
// (src/units/137-ecourna-api-security-ciphers.mk).
class CPrng final : public IRng {
public:
    explicit CPrng(int semente);

    uebyte GetByte() override;
    int GetInt() override;
    int Generate(std::vector<uebyte>& dados) override;
    int Generate(std::vector<uebyte>& dados, size_t tamanho) override;

private:
    int m_semente;
};

} // namespace ecourna::api::security
