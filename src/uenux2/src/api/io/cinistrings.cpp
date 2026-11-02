// Reconstruction's note: of this file the reconstruction holds TerminaComBarraInvertida (target fn 5484) and
// CIniStrings::FindKey and EndKey (fn 10877 and the end fn 6044 calls), chosen names, file and lines: no record, slot
// or RTTI names them (src/units/215-uenux2-api-app-leftovers.mk says why they are here). Lines 183 and 187 are the
// records of api::CIniStrings::ParseKeyLine, which only fn 5480 holds (not written), and stay blank.
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

CIniStrings::TMapChaves::iterator CIniStrings::FindKey(const std::string& nome)
{
    return m_chaves.find(nome);
}

CIniStrings::TMapChaves::iterator CIniStrings::EndKey()
{
    return m_chaves.end();
}

} // namespace api
