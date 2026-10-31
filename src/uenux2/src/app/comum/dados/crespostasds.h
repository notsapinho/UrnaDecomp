#pragma once

#include <string>

namespace comum {

// A data source of an answer's number (RTTI, in the argument of api::CDataText; fn 6652 builds that text with
// std::make_shared). Recovered: the name only. The call operator is declared and not reconstructed. The path is chosen.
class CRespostasDSNumero {
public:
    std::string operator()() const;
};

} // namespace comum
