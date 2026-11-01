#pragma once

#include <string>
#include <vector>

#include "api/hash/chasharquivo.h"

namespace api::hash {

// A directory's hashes: its name, its files' CHashArquivo and its subdirectories. Records name the class:
// chashdiretorio.cpp's ValidaObjeto (line 41) and cmontadorhash.cpp's CriaHashesDiretorio (line 121), which returns
// one; fn 5360 loads both. Its destructor (fn 2220) gives the layout: a string at +0, a vector at +12 whose 24-byte
// elements each free two strings (CHashArquivo's size and shape, a reading) and a vector at +24 of 36-byte elements it
// destroys by calling itself. The members' names are chosen, and so is the destructor's being implicit (unit 198's
// fragment says why the target cannot tell). Nothing else of the class is reconstructed: chashdiretorio.cpp is not
// written.
class CHashDiretorio {
private:
    std::string m_nome;
    std::vector<CHashArquivo> m_arquivos;
    std::vector<CHashDiretorio> m_diretorios;
};

} // namespace api::hash
