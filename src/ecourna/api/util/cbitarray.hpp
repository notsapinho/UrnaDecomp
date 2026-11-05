#pragma once
#include <memory>
#include <vector>

#include <boost/dynamic_bitset.hpp>

#include "ecourna/api/uetypes.hpp"

namespace ecourna::api::util {

// A bit stream read MSB-first: GetValor(n) returns the next n bits as a number and advances the cursor.
class CBitArray {
public:
    // Out of line in cbitarray.cpp: fn 5702 holds it inlined by binaryen, with an -fexceptions landing pad
    // (src/units/03-ecourna-api-io-util.mk); `explicit` is chosen.
    explicit CBitArray(const std::vector<uebyte>& bytes);
    virtual ~CBitArray() = default;

    ueword GetValor(const uebyte bits);
    ueword GetValor(const ueqword posicao, const uebyte bits) const;

private:
    std::shared_ptr<boost::dynamic_bitset<uebyte>> m_bits;
    std::vector<uebyte> m_bytes;
    bool m_escrita;
    bool m_leitura;
    ueqword m_posicao;
};

} // namespace ecourna::api::util
