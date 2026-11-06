#pragma once

#include <string>

namespace api {

// Target fn 5484: whether a line ends in a run of backslashes of odd length, so that its last backslash is not
// escaped by the one before it. Its one target caller, fn 5480 (the INI loader, api::CIniFile::Carrega here), calls it
// twice. No record, slot or RTTI names it: its name, its being a free function with external linkage, this header and
// cinistrings.cpp as its file are chosen.
bool TerminaComBarraInvertida(const std::string& linha);

// The INI reader's other string helpers, each a target function of its own that fn 5480 calls out of line. No record,
// slot or RTTI names any of them: their names, their being free functions with external linkage, this header and
// cinistrings.cpp as their file are chosen (src/units/379-uenux2-cinifile.mk).
// - fn 2234: where `procurado` first occurs in `texto` not escaped by an odd run of backslashes, npos when nowhere;
std::string::size_type ProcuraNaoEscapado(const std::string& texto, const std::string& procurado);
// - fn 2236: the line up to its first '#', ';' or NUL that no odd run of backslashes escapes;
std::string RemoveComentario(const std::string& linha);
// - fn 2235: the text without the spaces at its ends (isspace or isblank), a space at the end escaped by an odd run of
//   backslashes kept;
std::string RemoveEspacos(const std::string& texto);
// - fn 5485: whether a line holds anything once its comment and its spaces are gone;
bool LinhaUtil(const std::string& linha);
// - no target index of its own (binaryen inlines it into fn 5480, its one caller): whether a line is a section's,
//   "[" a name "]";
bool EhSecao(const std::string& linha);
// - fn 3651: a name or a value with its comment and spaces gone and its escapes ("\n", "\t", "\;", "\:", "\=", "\#",
//   "\ ", "\[", "\]", "\\") replaced by the characters they stand for.
std::string TrataEscapes(const std::string& texto);

// The records name the class and its static ParseKeyLine (cinistrings.cpp 183 and 187), which only fn 5480 holds,
// inlined by binaryen behind a stack frame of its own. No other member is recovered.
class CIniStrings {
public:
    static void ParseKeyLine(std::string& nome, std::string& valor, const std::string& linha);
};

} // namespace api
