#pragma once

#include <string>

#include "app/comum/iinterfacesavd.h"

namespace comum {

// Recovered: the layout and the destructor. The vtable holds the destructor only (slots 0 and 1, fns 1007 and 4694),
// and vota::CAssinadorVota derives from the class, so it is not final (its destructor stores the vptr). The
// constructor is inlined into vota::CAssinadorVota's (fn 1501): it stores 1 as m_aplic and its ESavdPacote argument
// as m_pacote, and leaves the strings empty; CAssinadorVota's constructor then assigns m_diretorio (fn 5462 of the
// package's entry in CArquivosSavd, fn 275, with a '/' appended) and m_caminho (fn 2763 of the same entry). Assina
// passes m_aplic to the inlined comum::AssinarUE (records cassinador.cpp:114, iinterfacesavd.cpp:1004). The member
// names are not in the target. The constructor, Assina and AssinaArquivosResultado are not reconstructed, so not
// declared.
class CAssinador {
public:
    virtual ~CAssinador();

protected:
    ESavdAplic m_aplic;
    ESavdPacote m_pacote;
    std::string m_caminho;
    std::string m_diretorio;
    std::string m_arquivo;
};

} // namespace comum
