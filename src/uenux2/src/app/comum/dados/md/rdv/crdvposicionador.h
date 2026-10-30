#pragma once

#include <cstddef>
#include <vector>

#include "app/comum/dados/md/rdv/cvoto.h"

namespace comum::md {

// crdv.h forward-declares this class in comum::md, the records of CVotosCargos::InsereCedula and
// CVotosEleicoesVota::RecebeCedula take it by const reference, and RTTI gives it no base. The path of this header, the
// name Posicao and its first parameter's type are chosen: no evidence names them. Slot 2 is what f4454 calls.
class CRdvPosicionador {
public:
    virtual ~CRdvPosicionador() = default;

    virtual size_t Posicao(const std::vector<CVoto>& votos, const CVoto& voto) const = 0;
};

} // namespace comum::md
