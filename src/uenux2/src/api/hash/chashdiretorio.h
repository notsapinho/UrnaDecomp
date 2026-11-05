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
// fragment says why the target cannot tell). ListaHashesArquivos (fn 5358, cmontadorhash.cpp) reads the three members
// in place, which inline getters and public members give alike: the getters and their names are chosen. The constructor
// and ValidaObjeto are chashdiretorio.cpp's (its record, line 41), which binaryen inlines into
// CMontadorHash::CriaHashesDiretorio (fn 5360), their one caller: it copies the name, the files and the subdirectories
// it is given (fns 1300 and 5363) and then tests the name. The parameters' forms (references) are the copies'; their
// order, the constructor's file (inline in the class was not measured) and ValidaObjeto's being private are chosen.
class CHashDiretorio {
public:
    CHashDiretorio(const std::string& nome, const std::vector<CHashArquivo>& arquivos,
        const std::vector<CHashDiretorio>& diretorios);

    const std::string& GetNome() const { return m_nome; }
    const std::vector<CHashArquivo>& GetArquivos() const { return m_arquivos; }
    const std::vector<CHashDiretorio>& GetDiretorios() const { return m_diretorios; }

private:
    void ValidaObjeto() const;

    std::string m_nome;
    std::vector<CHashArquivo> m_arquivos;
    std::vector<CHashDiretorio> m_diretorios;
};

} // namespace api::hash
