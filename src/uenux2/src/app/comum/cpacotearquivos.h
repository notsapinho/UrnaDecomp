#pragma once

// comum::CPacoteArquivos: RetornaNomeChave (fn 5900), which takes no object, and TrataErroPacote (fn 5901) are
// reconstructed; the class's other members (the records of cpacotearquivos.cpp name ValidarChaveEAplicacaoValida,
// Validar and TrataErroPacoteArquivo) are not. The layout, as far as 5901 reads it, comes from fn 4625, which builds
// the object in its frame: +0 a std::string (the package's name, which 5901 formats), +12 a std::vector (4625 compares
// its begin and end and walks it), +24 the ESavdChaveValidar (5901 passes it to RetornaNomeChave), and words at +28 and
// +32 that nothing written reads, so they are not declared. The vector's element type, the members' names and the
// header's path are chosen.

#include <string>
#include <vector>

#include "app/comum/iinterfacesavd.h"

namespace comum {

class CPacoteArquivos {
public:
    static std::string RetornaNomeChave(ESavdChaveValidar chave);

    void TrataErroPacote(const IInterfaceSavd& savd) const;

private:
    std::string m_nome;
    std::vector<std::string> m_arquivos;
    ESavdChaveValidar m_chave;
};

} // namespace comum
