#pragma once

#include <string>

#include "app/comum/iinterfacesavd.h"

namespace comum {

// Recovered: the layout, the destructor, the constructor and Assina. The vtable holds the destructor only (slots 0 and
// 1, fns 1007 and 4694), and vota::CAssinadorVota derives from the class, so it is not final (its destructor stores the
// vptr). The constructor has no target index: binaryen inlined it into vota::CAssinadorVota's (fn 1501), where it
// stores the ESavdAplic (1) as m_aplic and the ESavdPacote as m_pacote, then assigns m_diretorio (api::GetDirName, fn
// 5462, of the package's entry in CArquivosSavd, fn 275, with a '/' appended) and m_caminho (api::GetFileName, fn 2763,
// of the same entry); m_arquivo stays empty. Assina (fn 1277, record cassinador.cpp:114) passes m_aplic to the inlined
// comum::AssinarUE (record iinterfacesavd.cpp:1004). The member names are not in the target. AssinaArquivosResultado
// (records 141 to 149, fn 12098 holds it inlined) is not reconstructed, so not declared.
class CAssinador {
public:
    CAssinador(ESavdAplic aplic, ESavdPacote pacote);
    virtual ~CAssinador();

    void Assina(const ESavdArquivoUE arquivo) const;

protected:
    ESavdAplic m_aplic;
    ESavdPacote m_pacote;
    std::string m_caminho;
    std::string m_diretorio;
    std::string m_arquivo;
};

} // namespace comum
