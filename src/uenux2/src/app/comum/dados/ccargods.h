#pragma once

#include <string>

namespace comum {

// Data sources of a position's texts (RTTI, in the arguments of api::CDataText). Recovered: the names only. A source is
// callable, as api::CDataText calls it; the call operators are declared and not reconstructed. fn 5613 copies a
// CPadDS<CToUpperDS<CCargoDSNome>> as 16 bytes, whose fields are not recovered. The file is the stub file ccargods.cpp's
// header, a chosen path.
class CCargoDSNome {
public:
    std::string operator()() const;
};

class CCargoDSNomeSexoCandidato {
public:
    std::string operator()() const;
};

template <typename TFonte>
class CToUpperDS {
public:
    std::string operator()() const;

private:
    TFonte m_fonte;
};

template <typename TFonte>
class CPadDS {
public:
    std::string operator()() const;

private:
    TFonte m_fonte;
};

} // namespace comum
