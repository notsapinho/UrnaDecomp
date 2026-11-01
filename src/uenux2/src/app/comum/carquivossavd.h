#pragma once

// comum::CArquivosSavd: the SAVD file names of a package and of a signed file, looked up by identifier. Recovered: the
// two maps, which operator[] reads (fns 275 and 680: a std::map at +0, by ESavdPacote, and at +12, by ESavdArquivoUE,
// each with a std::string at +20 of its node). Their names, the header's path and the access of each member are chosen;
// the class's construction is not reconstructed.

#include <map>
#include <string>

#include "app/comum/iinterfacesavd.h"

namespace comum {

class CArquivosSavd {
public:
    std::string operator[](ESavdPacote pacote) const;
    std::string operator[](ESavdArquivoUE arquivo) const;

private:
    std::map<ESavdPacote, std::string> m_assinaturas;
    std::map<ESavdArquivoUE, std::string> m_assinados;
};

std::string DescricaoArquivo(ESavdArquivoUE arquivo);

} // namespace comum
