#pragma once

#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// The layout, 16 bytes, from the constructor (target fn 3823, records cseguranca.cpp:24, :27, :30): the two bytes at +0
// and +1 and the vector at +4. The member names are not in the target; they follow ModuloTiposEleitorais::Seguranca's
// fields and the message "Chave vazia."
class CSeguranca {
public:
    CSeguranca(uebyte idTipoArquivo, uebyte idCriptografia, const std::vector<uebyte>& chave);

    uebyte GetIdTipoArquivo() const { return m_idTipoArquivo; }
    uebyte GetIdCriptografia() const { return m_idCriptografia; }
    const std::vector<uebyte>& GetChave() const { return m_chave; }

private:
    uebyte m_idTipoArquivo;
    uebyte m_idCriptografia;
    std::vector<uebyte> m_chave;
};

} // namespace comum::md
