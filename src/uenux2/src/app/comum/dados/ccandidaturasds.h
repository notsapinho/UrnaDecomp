#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace comum {

// Data sources of a candidature's texts and photo (RTTI, in the arguments of api::CDataText and api::CDataImage; fns
// 4185 and 4129 build those with std::make_shared). Recovered: the names only. A source is callable; the call operators
// are declared and not reconstructed. The path is chosen, beside ccandidaturas.h.
class CCandidaturasDSNumero {
public:
    std::string operator()() const;
};

class CCandidaturasDSNome {
public:
    std::string operator()() const;
};

class CCandidaturasDSFoto {
public:
    std::vector<uint8_t> operator()() const;
};

} // namespace comum
