#pragma once

#include <string>

namespace comum {

// comum::CImprimirIdentificacaoMesariosFinal: its records name two members, GetNomeMesario (fn 5385, record
// cimprimiridentificacaomesariosfinal.cpp 229:84, a non-static, non-const member: the record text has neither `static`
// nor `const`) and GetPrinter (an inline const member at this header's line 41, which fn 12105 holds inlined, not
// written: the file ends above that line). No vtable, typeinfo or allocation of the class is in the target's data, so
// its base, layout and other members are not recovered; GetNomeMesario's access is chosen.
class CImprimirIdentificacaoMesariosFinal {
public:
    std::string GetNomeMesario(const std::string& titulo);
};

} // namespace comum
