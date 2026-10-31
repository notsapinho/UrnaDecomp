#pragma once

#include <string>

namespace comum::md {

// A voter's temporary transfer. The records name the class, its nested enum and its constructor from the enum
// (ctransferenciatemporaria.cpp:25 and :35, ValidaConstrucao). Recovered: the layout only, 20 bytes, as CEleitor's
// constructors copy it (target fns 5666 and 5668, to +48 of CEleitor): a word at +0, a string at +4 and a word at +16.
// That this is the class CEleitor holds there is a reading: CConversorEntidadeEleitores's slot 2 (fn 11411), whose
// records include DesconverteTransferenciaTemporaria's, which returns one, is the caller of both constructors. The enum's
// enumerators, the type of the word at +16 and every member name are chosen; neither constructor is reconstructed.
class CTransferenciaTemporaria {
public:
    enum ETransferenciaTemporaria : int;

    explicit CTransferenciaTemporaria(ETransferenciaTemporaria tipo);

private:
    ETransferenciaTemporaria m_tipo;
    std::string m_municipio;
    int m_zona;
};

} // namespace comum::md
