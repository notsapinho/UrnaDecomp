// Reconstruction's note, not TSE's text: comum::md::CCedula's constructor and Adiciona, out of line in a file of their
// own (src/units/197-uenux2-celeitorvotando.mk says what that rests on and why that unit lists it; the path and the
// name Adiciona are chosen).
#include <utility>

#include "app/comum/dados/md/rdv/ccedula.h"

namespace comum::md {

CCedula::CCedula() = default;

void CCedula::Adiciona(const TCargoID cargo, CVoto voto)
{
    m_votos.push_back(std::make_pair(cargo, std::move(voto)));
}

} // namespace comum::md
