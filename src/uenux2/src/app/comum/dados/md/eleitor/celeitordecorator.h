#pragma once

#include <string>
#include <vector>

#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "ecourna/app/dados/tiposbasicos.hpp"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// A voter's register data. Recovered: the layout, 108 bytes, from its destructor (fn 379): the identities at +8, a
// std::vector of 16-byte CEleitorIdentidade (fn 708), strings at +24, +36, +52 and +68 and a vector of a trivial element
// at +80; fn 5764 reads a type at +104, and CEleitorDetalhe's optional follows at +108. The words between them have no
// reader here, nothing may build one, and the members' names and the vector's element type are chosen.
class CEleitorDecorator {
public:
    CEleitorIdentidade GetIdentidadePorTipo(ecourna::app::dados::ETipoIdentificadorEleitor tipo) const;

private:
    uedword m_naoRecuperado1[2];
    std::vector<CEleitorIdentidade> m_identidades;
    uedword m_naoRecuperado2;
    std::string m_nome;
    std::string m_nomeUrna;
    uedword m_naoRecuperado3;
    std::string m_nomeSocial;
    uedword m_naoRecuperado4;
    std::string m_nomeMae;
    std::vector<uedword> m_impedimentos;
    uedword m_naoRecuperado5[4];
};

} // namespace comum::md
