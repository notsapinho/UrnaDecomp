#pragma once

#include <vector>

#include "app/comum/dados/md/eleitor/cdedo.h"

namespace comum::asn {

// A finger's minutiae as fn 5702 decodes them from ModuloEleitores::Dedo's minucias, a bit stream of 16-bit pairs: each
// group's angle and point count, then its points. Recovered from 5702, which builds one on its stack and holds the
// constructor and Descompacta inlined by binaryen (both out of line in cminuciascompactadas.cpp): the layout, 36 bytes
// (the x and y minima at +0 and +4, each starting at 999, the bit widths ceil(log2(max - min)) at +2 and +6, the group
// count at +8, the minutiae at +12, a copy of the pairs at +24, the 16-bit members read zero-extended), and what the
// two compute. SPar is trivially copyable: the target copies the list with memcpy, which std::pair's copy does not give
// (fragment 335). No record, vtable or RTTI names the class, its members or its file; those names, the default member
// initializers and SPar's being a nested struct are chosen.
class CMinuciasCompactadas {
public:
    // A pair of 16-bit values of the stream: a group's angle and count of points, or a point's x and y.
    struct SPar {
        ueword primeiro;
        ueword segundo;
    };

    explicit CMinuciasCompactadas(const std::vector<SPar>& pares);

    const std::vector<api::SXYT>& GetMinucias() const { return m_minucias; }

private:
    std::vector<api::SXYT> Descompacta(const std::vector<SPar>& pares);

    ueword m_xMinimo = 999;
    ueword m_bitsX = 0;
    ueword m_yMinimo = 999;
    ueword m_bitsY = 0;
    ueword m_quantidadeAngulos = 0;
    std::vector<api::SXYT> m_minucias;
    std::vector<SPar> m_pares;
};

} // namespace comum::asn
