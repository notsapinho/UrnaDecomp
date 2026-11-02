// Reconstruction's note: of this file the reconstruction holds only TerminaComBarraInvertida (target fn 5484), a
// chosen name, file and linkage: no record, slot or RTTI names it (src/units/215-uenux2-api-app-leftovers.mk says
// why it is here). Lines 183 and 187 are the records of api::CIniStrings::ParseKeyLine, which only fn 5480 holds
// (not written), and stay blank; the line of the function after them is a choice.
#include "api/io/cinistrings.h"

namespace api {






















































































































































































bool TerminaComBarraInvertida(const std::string& linha)
{
    if (linha.empty()) {
        return false;
    }
    std::string::size_type i = linha.size() - 1;
    if (linha[i] != '\\') {
        return false;
    }
    bool impar = true;
    while (i > 0 && linha[--i] == '\\') {
        impar = !impar;
    }
    return impar;
}

} // namespace api
