#pragma once

// comum::CPacoteArquivos: only RetornaNomeChave is reconstructed. It takes no object, and the class's other members
// (the records of cpacotearquivos.cpp name ValidarChaveEAplicacaoValida, Validar, TrataErroPacote and
// TrataErroPacoteArquivo) are not. The header's path is chosen.

#include <string>

#include "app/comum/iinterfacesavd.h"

namespace comum {

class CPacoteArquivos {
public:
    static std::string RetornaNomeChave(ESavdChaveValidar chave);
};

} // namespace comum
