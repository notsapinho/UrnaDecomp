#pragma once

#include <string>

#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// A party: its number, abbreviation and name, in the order of ModuloPartidos::Partido's fields.
// comum::asn::CConversorPartido::DoConverte (target fn 11460) reads the number as a 16-bit word at +0 and the two
// strings at +4 and +16; the member names follow the entity's fields. ValidaCriacao's records (cpartido.cpp:30, 33,
// 36) and its body, inlined with the constructor into the converter's DoDesconverte (fn 11459), bound the number
// below 100 and the abbreviation and name below 25 and 56 characters. The constructor is not declared here: no record
// spells its parameters, and 11459 evaluates the name, the abbreviation and then the number, which does not settle
// their order. It comes with 11459's reconstruction.
class CPartido {
public:
    ueword GetNumero() const { return m_numero; }
    const std::string& GetSigla() const { return m_sigla; }
    const std::string& GetNome() const { return m_nome; }

private:
    void ValidaCriacao() const;

    ueword m_numero;
    std::string m_sigla;
    std::string m_nome;
};

} // namespace comum::md
