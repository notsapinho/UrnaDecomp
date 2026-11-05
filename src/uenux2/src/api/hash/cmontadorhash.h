#pragma once

#include <set>
#include <string>
#include <vector>

#include "api/hash/chasharquivo.h"
#include "api/hash/chashdiretorio.h"

namespace api::hash {

// The hashes of a directory tree. The records of cmontadorhash.cpp name the class and three static members:
// CriaHashesDiretorio (line 121, target fn 5360), CalculaHash (line 78) and CalculaHashGeral (lines 91 and 98), the two
// last held by fn 5360, behind frames of their own (binaryen inlined them, their one caller). 5360 passes a std::string
// at 1910016 as CalculaHashGeral's first argument and replaces it with the result; the one other function that loads it
// is target fn 10259, its exit destructor: s_hashGeral, whose name and being a static member are chosen, as is the
// members' access.
class CMontadorHash {
public:
    static CHashDiretorio CriaHashesDiretorio(const std::string& diretorio, const std::set<std::string>& excluidos);

private:
    static std::string CalculaHash(const std::string& arquivo);
    static std::string CalculaHashGeral(const std::string& hashGeral, const std::string& hash);

    static std::string s_hashGeral;
};

// Target fn 5359: the hashes of a directory's tree as ListaHashesArquivos lists them, built by
// CMontadorHash::CriaHashesDiretorio. Its one caller is comum::CGravadorHashes::GravaResultado (fn 11620), which calls
// it twice through comum::CalculaHashesArquivos (inlined into it), for the root and for the keys' directory, with the
// same set of directories to leave out. No record, slot or RTTI names it: its name, its being a free function (it reads
// no class state) and this header are chosen; its file is its band's (src/units/227-uenux2-contratos-cmontadorhash.mk).
std::vector<CHashArquivo> ListaHashesDiretorio(const std::string& diretorio, const std::set<std::string>& excluidos);

// Target fn 5358: the hashes of a directory's files and, recursively, of its subdirectories', each file's name prefixed
// with its directory's name. Its target callers are itself and fn 5359. No record, slot or RTTI names it: its name,
// its being a free function with external linkage (it reads no class state; a static member of CMontadorHash, whose
// records name only static members, is the other form docs/how-to-decompile.md step 3 allows, not measured), this
// header and cmontadorhash.cpp as its file are chosen.
std::vector<CHashArquivo> ListaHashesArquivos(const CHashDiretorio& diretorio);

} // namespace api::hash
