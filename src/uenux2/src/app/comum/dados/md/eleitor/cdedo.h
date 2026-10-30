#pragma once

#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace api {

// Recovered: the name and the size only. The record of CDedo's constructor names api::SXYT, fn 11416 divides the
// vector's byte size by 16, and fns 3720 and 2799 copy it with memory.copy, so it is trivially copyable. The members,
// four of 4 bytes, and this header as its home are chosen.
struct SXYT {
    int x;
    int y;
    int t;
    int q;
};

} // namespace api

namespace comum::md {

// One finger of a voter's biometrics, 20 bytes: fn 2799 divides by 20. The constructor's record (cdedo.cpp:28 and :33,
// inlined into fn 11416) gives the three members' types: the finger at +0, the count of minutiae at +4 and the
// minutiae at +8. The names of the members are chosen. The header's path, beside cdedo.cpp, is chosen too.
class CDedo {
public:
    // The enumerators are not recovered: fn 11416 accepts 1 to 10, and no code here tests a value. Compared signed by
    // fns 2799 and 3720, which is the promotion of a plain enum.
    enum TipoDedo {};

    CDedo(TipoDedo tipo, uedword quantidadeMinucias, const std::vector<api::SXYT>& minucias);

    TipoDedo GetTipo() const { return m_tipo; }

private:
    TipoDedo m_tipo;
    uedword m_quantidadeMinucias;
    std::vector<api::SXYT> m_minucias;
};

} // namespace comum::md
