#pragma once

#include <map>
#include <string>

#include "api/io/cinikey.h"
#include "api/io/cinisection.h"

namespace api {

// Target fn 5484: whether a line ends in a run of backslashes of odd length, so that its last backslash is not
// escaped by the one before it. Its one target caller, fn 5480 (which holds api::CIniStrings::ParseKeyLine,
// cinistrings.cpp lines 183 and 187), calls it twice. No record, slot or RTTI names it: its name, its being a free
// function with external linkage, this header and cinistrings.cpp as its file are chosen.
bool TerminaComBarraInvertida(const std::string& linha);

// Reconstruction: the object an INI file is read into, 24 bytes: a std::map from a section's name to its CIniSection at
// +0 and a std::map from a key's name to its CIniKey at +12. Fn 5480, the loader (not written), builds both maps (the
// stores of their end nodes, then the parse into them) and holds the records of the static ParseKeyLine
// (cinistrings.cpp 183, 187) and of CIniSection::operator= (cinisection.cpp 36); comum::CGeracaoVersoesContratos's
// destructor (fn 5866) destroys two such objects, at +0 and +24, each by its two trees (fns 1397 and 2859, the map at
// +12 and the map at +0). FindKey (fn 10877) and EndKey are the find and the end of the map at +12 that
// comum::md::CVersoesContratos::GetValor and CDependenciasContratos::GetValor call out of line (their merged body, fn
// 6044, calls both, the end as fn 5481, a body the target keeps once for boost's sp_counted_impl_pd's
// get_untyped_deleter too). Chosen: that the class is CIniStrings, the class whose static ParseKeyLine the loader holds
// (a reading), the member names, which map holds what beyond the bodies' layout, the two functions' names, their
// iterator type and that they are not const, and cinistrings.cpp as their file.
class CIniStrings {
public:
    using TMapChaves = std::map<std::string, CIniKey>;

    TMapChaves::iterator FindKey(const std::string& nome);
    TMapChaves::iterator EndKey();

private:
    std::map<std::string, CIniSection> m_secoes;
    TMapChaves m_chaves;
};

} // namespace api
