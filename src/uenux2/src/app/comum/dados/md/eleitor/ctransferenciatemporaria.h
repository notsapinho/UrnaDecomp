#pragma once

#include <string>

#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// A voter's temporary transfer. The records name the class, its nested enum and its constructor from the enum
// (ctransferenciatemporaria.cpp:25 and :35, ValidaConstrucao). Recovered: the layout only, 20 bytes, as CEleitor's
// constructors copy it (target fns 5666 and 5668, to +48 of CEleitor): a word at +0, a string at +4 and a word at +16.
// That this is the class CEleitor holds there is a reading: CConversorEntidadeEleitores's slot 2 (fn 11411), whose
// records include DesconverteTransferenciaTemporaria's, which returns one, is the caller of both constructors. The
// string and the word are the destination's state and municipality, a reading from what
// md::CEleitorDecorator::GetAbrangencia (fn 3721) compares them with (the urn's state and municipality, celeitores.h).
// The enum's enumerators, the type of the word at +16, every member name and the three accessors, which the decorator
// reads, are chosen; neither constructor is reconstructed.
class CTransferenciaTemporaria {
public:
    enum ETransferenciaTemporaria : int;

    explicit CTransferenciaTemporaria(ETransferenciaTemporaria tipo);

    ETransferenciaTemporaria GetTipo() const { return m_tipo; }
    const std::string& GetUF() const { return m_uf; }
    uedword GetMunicipio() const { return m_municipio; }

private:
    ETransferenciaTemporaria m_tipo;
    std::string m_uf;
    uedword m_municipio;
};

} // namespace comum::md
