#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace vota {

// Recovered: the class name and its vtable (RTTI N4vota11IQRCodeBUDSE: no base, slots 0 and 1 the destructors, fns
// 12050 and 12049), the constructor's signature (record cmostraqrcodebu.cpp:38) and the 20-byte object GetQRDSInst
// (fn 1956, which inlines the constructor) builds: the vptr, the vector of strings the constructor moves its argument
// into (+4), and the index at +16 it sets to 0, which CMostraQRCodeBU::ProcessInput (fn 12051) steps within the
// vector's size and fn 12053 reads the vector at. The member names are not in the target. The destructor is defined here, in the class: the
// target's D0 (12049) holds the D2's body, which clang gives only for an inline destructor (an out-of-line one is
// called through the D1 alias). It stores the vptr, so the class is not final. This header's path is chosen: the
// class's only record is in cmostraqrcodebu.cpp, which defines its members, and no record names a header.
class IQRCodeBUDS {
public:
    IQRCodeBUDS(std::vector<std::string> partes);
    virtual ~IQRCodeBUDS() = default;

private:
    std::vector<std::string> m_partes;
    std::size_t m_atual = 0;
};

} // namespace vota
