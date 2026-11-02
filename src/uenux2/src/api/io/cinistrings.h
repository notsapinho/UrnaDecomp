#pragma once

#include <string>

namespace api {

// Target fn 5484: whether a line ends in a run of backslashes of odd length, so that its last backslash is not
// escaped by the one before it. Its one target caller, fn 5480 (which holds api::CIniStrings::ParseKeyLine,
// cinistrings.cpp lines 183 and 187), calls it twice. No record, slot or RTTI names it: its name, its being a free
// function with external linkage, this header and cinistrings.cpp as its file are chosen.
bool TerminaComBarraInvertida(const std::string& linha);

} // namespace api
