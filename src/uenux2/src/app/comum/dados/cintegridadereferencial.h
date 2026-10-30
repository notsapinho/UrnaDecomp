#pragma once

#include <string>
#include <utility>

namespace comum {

// Only Lanca (target fn 2263) is reconstructed. TResultado's spelling is the record's and its layout the body's and its
// caller 2543's: a byte tested at +0, a std::string at +4, 16 bytes. That it is a std::pair is chosen; a struct of those
// two members and a std::tuple give the same bytes (the fragment has the measurement).
class CIntegridadeReferencial {
public:
    using TResultado = std::pair<bool, std::string>;

    static void Lanca(const TResultado& resultado);
};

} // namespace comum
