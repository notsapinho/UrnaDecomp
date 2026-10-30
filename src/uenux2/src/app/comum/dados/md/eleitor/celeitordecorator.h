#pragma once

#include <vector>

#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "ecourna/app/dados/tiposbasicos.hpp"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// A voter's register data. Recovered: only the identities at +8, a std::vector of 16-byte CEleitorIdentidade (fn 708).
// What lies at +0 and from +20 on is not (fn 5764 reads a type at +104), so sizeof is wrong and nothing may build one.
// The members' names are chosen.
class CEleitorDecorator {
public:
    CEleitorIdentidade GetIdentidadePorTipo(ecourna::app::dados::ETipoIdentificadorEleitor tipo) const;

private:
    uedword m_naoRecuperado[2];
    std::vector<CEleitorIdentidade> m_identidades;
};

} // namespace comum::md
