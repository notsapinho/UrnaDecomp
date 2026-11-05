#pragma once

// comum::CPacoteArquivos: a SAVD package and the files it holds, validated through IInterfaceSavd (fn 4625 builds one
// over each vota file's .vsu and the file). RetornaNomeChave (fn 5900), which takes no object, and TrataErroPacote (fn
// 5901) are reconstructed, and so are the members fn 4625 holds: the constructor (no target index, no record),
// ValidarChaveEAplicacaoValida, Validar and TrataErroPacoteArquivo (records cpacotearquivos.cpp 85, 91, 116 and 190,
// each behind a frame of its own in 4625). The layout is the object 4625 builds in its frame: +0 the package's name (a
// std::string, which 5901 formats), +12 the files (a std::vector whose begin and end Validar compares and walks, each
// element a std::string it passes on), +24 the ESavdChaveValidar (5901 passes it to RetornaNomeChave), +28 the SAVD
// command (a 32-bit word, compared with 0x2021 and 0x1011 and stored into the request's 16-bit command) and +32 the
// ESavdAplic (compared with 1 to 9 and or-ed with the key). The vector's element type comes from what Validar passes;
// the members' names, the command's type, the constructor's parameters and their order, the access of each member and
// the header's path are chosen.

#include <string>
#include <vector>

#include "app/comum/iinterfacesavd.h"

namespace comum {

class IInterfaceMensagem;

class CPacoteArquivos {
public:
    CPacoteArquivos(const std::string& nome, const std::string& arquivo, ESavdChaveValidar chave, ESavdAplic aplic);

    void Validar(IInterfaceMensagem& mensagem) const;

    static std::string RetornaNomeChave(ESavdChaveValidar chave);

    void TrataErroPacote(const IInterfaceSavd& savd) const;

private:
    void ValidarChaveEAplicacaoValida();
    void TrataErroPacoteArquivo(const IInterfaceSavd& savd, const std::string& arquivo) const;

    std::string m_nome;
    std::vector<std::string> m_arquivos;
    ESavdChaveValidar m_chave;
    ueint32 m_comando;
    ESavdAplic m_aplic;
};

} // namespace comum
