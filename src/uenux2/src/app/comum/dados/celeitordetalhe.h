#pragma once

#include <string>

namespace comum {

// Only ConfereDadosDinamicos (target fn 3770) is reconstructed. It reads one byte at +192, tested for zero; bool and the
// member's name are chosen, and nothing of the 192 bytes before it is recovered (the constructor, record at line 49,
// takes a CEleitorDecorator, a CEleitorDinamico and an ETipoImpedimento among others). So sizeof is wrong and nothing
// may construct this class yet; the first unit that needs a member adds the data members.
class CEleitorDetalhe {
public:
    void ConfereDadosDinamicos(const std::string& funcao) const;

private:
    unsigned char m_naoRecuperado[192];
    bool m_dadosDinamicosCarregados;
};

} // namespace comum
