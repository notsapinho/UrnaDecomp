#pragma once

#include <string>
#include <vector>

#include "app/comum/iinterfacesavd.h"

namespace comum {

// The section identifiers as app/comum/gravadores/iresultado.h declares them in comum; that this header repeats its
// aliases is a choice, as cgravadorutil.h's are.
using TMunicipioID = uedword;
using TSecaoID = ueword;
using TZonaID = ueword;

// Recovered: the layout, the destructor, the two constructors, Assina and AssinaArquivosResultado. The vtable holds the
// destructor only (slots 0 and 1, fns 1007 and 4694), and vota::CAssinadorVota derives from the class, so it is not
// final (its destructor stores the vptr). Neither constructor has a target index. The first: binaryen inlined it into
// vota::CAssinadorVota's (fn 1501), where it stores the ESavdAplic (1) as m_aplic and the ESavdPacote as m_pacote, then
// assigns m_diretorio (api::GetDirName, fn 5462, of the package's entry in CArquivosSavd, fn 275, with a '/' appended)
// and m_caminho (api::GetFileName, fn 2763, of the same entry); m_local stays empty. The second: fn 12098 holds it
// behind a 480-byte stack frame of its own, then stores CAssinadorVota's vptr on the result: it stores the ESavdAplic
// and the package, builds m_local in place with "{}{:05}{:04}{:04}" over CLocal::GetUFMinuscula (fn 3753) and three
// numbers 12098 got from CLocal's GetMunicipio, GetZonaID and GetSecaoID (fns 1004, 1003, 1078), then puts the
// package's entry as a format (std::vformat, the folding test's dead loop) over CDadoCarga::GetFaseChar's char (fn
// 2253), the pleito's identifier, the UF and the same three numbers (the arguments CGravadorUtil's file name formats)
// and takes m_diretorio and m_caminho from that path as the first does. Assina (fn 1277, record cassinador.cpp:114)
// passes m_aplic to the inlined comum::AssinarUE (record iinterfacesavd.cpp:1004); AssinaArquivosResultado (records
// 141, 146 and 149; fn 12098 holds it inlined) sends m_local to the SAVD (IInterfaceSavd::EnviarLocal) and signs each
// file with comum::AssinarEcourna (record iinterfacesavd.cpp:1022). The member names, the second constructor's
// parameters' order and the numbers' types (CGravadorUtil's) are not in the target.
class CAssinador {
public:
    CAssinador(ESavdAplic aplic, ESavdPacote pacote);
    CAssinador(ESavdAplic aplic, ESavdPacote pacote, TMunicipioID municipio, TZonaID zona, TSecaoID secao, char fase);
    virtual ~CAssinador();

    void Assina(const ESavdArquivoUE arquivo) const;
    void AssinaArquivosResultado(const std::vector<ESavdArquivoUE>& arquivos) const;

protected:
    ESavdAplic m_aplic;
    ESavdPacote m_pacote;
    std::string m_caminho;
    std::string m_diretorio;
    std::string m_local;
};

} // namespace comum
