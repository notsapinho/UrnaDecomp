#pragma once

#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace api {

// uenux2's string helpers. The records of api/util/cstringutils.cpp name GetVersionNumber (line 59, target fn 1539) and
// two SetBit overloads (lines 71 and 83), declared as their records print them: fn 2772, which holds the second inlined,
// loads its record, and no function loads the first's. SetBit is not written. The header's path is chosen: no record
// names it.
class CStringUtils {
public:
    static std::string GetVersionNumber(const std::string& versao);
    static void SetBit(uebyte& byte, const uebyte bit, const bool valor);
    static void SetBit(std::vector<uebyte>& bytes, const size_t bit, const bool valor);
    // Target fns 5465 and 5464, the name tests api::CasamTodos (fn 2758, csystem.cpp) calls twice each. No record names
    // them: their names, their being members of this class and their lines in cstringutils.cpp are chosen
    // (src/units/179-uenux2-cvalidamidia.mk says what places them).
    static bool CasaRegex(const std::string& padrao, const std::string& valor);
    static bool CasaCaractere(char mascara, char caractere);
};

} // namespace api
