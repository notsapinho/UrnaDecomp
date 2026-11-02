#pragma once

#include <vector>

#include "api/hash/chasharquivo.h"
#include "api/hash/chashdiretorio.h"

namespace api::hash {

// Target fn 5358: the hashes of a directory's files and, recursively, of its subdirectories', each file's name prefixed
// with its directory's name. Its target callers are itself and fn 5359, which builds the directory with
// CMontadorHash::CriaHashesDiretorio (record cmontadorhash.cpp:121, fn 5360, not written) and passes it here, and which
// comum::CGravadorHashes::GravaResultado (fn 11620) calls. No record, slot or RTTI names it: its name, its being a free
// function with external linkage (it reads no class state; a static member of CMontadorHash, whose records name only
// static members, is the other form docs/how-to-decompile.md step 3 allows, not measured), this header and
// cmontadorhash.cpp as its file are chosen.
std::vector<CHashArquivo> ListaHashesArquivos(const CHashDiretorio& diretorio);

} // namespace api::hash
