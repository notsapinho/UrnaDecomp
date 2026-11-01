#pragma once

#include <map>
#include <string>

#include "api/io/cinikey.h"

namespace api {

// Reconstruction: a section of an INI file. Its record names operator= (api/io/cinisection.cpp:36, which target fn 5480
// loads; 5480 also loads "O nome de uma seção é constante."); only that declaration is a record's. SetKey is target fn 5482,
// whose name is chosen: no record, slot or RTTI names it. The layout is what 5482's body reads: a std::map from a
// string to a CIniKey at +12 (its tree's begin node, end node and size at +12, +16 and +20); the 12 bytes before it as
// the section's name, the member names and this header's path are chosen.
class CIniSection {
public:
    CIniSection& operator=(const CIniSection& secao);

    void SetKey(const CIniKey& chave);

private:
    std::string m_nome;
    std::map<std::string, CIniKey> m_chaves;
};

} // namespace api
