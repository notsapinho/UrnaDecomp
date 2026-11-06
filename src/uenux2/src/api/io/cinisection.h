#pragma once

#include <map>
#include <string>
#include <utility>

#include "api/io/cinikey.h"

namespace api {

// Reconstruction: a section of an INI file. Its record names operator= (api/io/cinisection.cpp:36, which target fn 5480
// holds; 5480 also loads "O nome de uma seção é constante."); only that declaration is a record's. SetKey is target fn
// 5482, whose name is chosen: no record, slot or RTTI names it. The layout is what 5482's body reads: a std::map from a
// string to a CIniKey at +12 (its tree's begin node, end node and size at +12, +16 and +20); the 12 bytes before it as
// the section's name, the member names and this header's path are chosen. Fn 5480 holds the constructor from a name
// inlined by binaryen (out of line in cinisection.cpp: 5480 keeps the destroy test of the string it moved from) and the
// two accessors (the name passed to the sections' map's find, the keys run over); their names, the by-value parameter
// and the accessors' being inline here are chosen (src/units/379-uenux2-cinifile.mk).
class CIniSection {
public:
    using TMapChaves = std::map<std::string, CIniKey>;

    explicit CIniSection(std::string nome);

    // Declared so that a section moves: target fn 5480 moves a new section's name and map into the sections' map's
    // node, and the user-declared operator= would leave the class no move constructor. `= default` is chosen.
    CIniSection(const CIniSection& secao) = default;
    CIniSection(CIniSection&& secao) = default;

    CIniSection& operator=(const CIniSection& secao);

    void SetKey(const CIniKey& chave);

    const std::string& GetNome() const { return m_nome; }
    const TMapChaves& GetChaves() const { return m_chaves; }

private:
    std::string m_nome;
    TMapChaves m_chaves;
};

} // namespace api
