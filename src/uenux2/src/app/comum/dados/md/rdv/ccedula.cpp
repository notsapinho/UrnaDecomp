// Reconstruction's note, not TSE's text: comum::md::CCedula's constructor, its two Adiciona and Limpa, out of line in a
// file of their own (src/units/197-uenux2-celeitorvotando.mk says what that rests on and why that unit lists it; the
// path and the names Adiciona and Limpa are chosen).
#include <utility>

#include "app/comum/dados/md/rdv/ccedula.h"

namespace comum::md {

CCedula::CCedula() = default;

void CCedula::Adiciona(const TCargoID cargo, CVoto voto)
{
    m_votos.push_back({cargo, std::move(voto)});
}

void CCedula::Adiciona(const SVotoCargo& voto)
{
    m_votos.push_back(voto);
}

void CCedula::Limpa()
{
    m_votos.clear();
}

} // namespace comum::md
