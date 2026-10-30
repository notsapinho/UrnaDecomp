#pragma once

#include <cstddef>
#include <vector>

#include "app/comum/dados/md/rdv/cvoto.h"

namespace comum::md {

// crdv.h forward-declares this class in comum::md, the records of InsereCedula and RecebeCedula take it by const
// reference (Posicao's const rests on that: non-const gives the same code), and RTTI gives it no base. Chosen: this
// header's path, the name Posicao, its first parameter's type and = 0: the target has no vtable of this class to read.
class CRdvPosicionador {
public:
    virtual ~CRdvPosicionador() = default;

    virtual size_t Posicao(const std::vector<CVoto>& votos, const CVoto& voto) const = 0;
};

} // namespace comum::md
